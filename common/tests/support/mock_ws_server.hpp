//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <utility>
#include <variant>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>

namespace binance::test {

struct MockWsServerOptions {
    std::shared_ptr<boost::asio::ssl::context> tls;
    /// Answer the upgrade with this HTTP status and body instead of accepting it.
    unsigned reject_status = 0;
    std::string reject_body;
    /// `Retry-After` header of the rejection, when not empty.
    std::string retry_after;
    /// Delay before accepting the upgrade.
    std::chrono::milliseconds accept_delay{0};
    bool deflate = true;
};

/// A WebSocket server on 127.0.0.1 for client tests (wss:// with a TLS context). Everything runs
/// on the server's own thread; the public members are thread-safe.
class MockWsServer {
public:
    struct Session;
    /// Called on the server thread for each text message a client sends.
    using Handler = std::function<void(Session&, const std::string&)>;

    /// What a connection did, as seen from the test thread.
    struct SessionInfo {
        std::size_t index = 0;
        /// Request target, e.g. `/stream?streams=a/b`.
        std::string target;
        std::string user_agent;
        /// Upgrade request headers, by lower-case name.
        std::map<std::string, std::string> headers;
        bool deflate = false;
        std::vector<std::string> received;
        std::size_t pings = 0;
        bool open = true;
    };

    struct Session {
        MockWsServer* server = nullptr;
        std::size_t index = 0;

        /// Sends a text message.
        void send(std::string text) const { server->send(index, std::move(text), false); }
        /// Sends a binary message.
        void send_binary(std::string data) const { server->send(index, std::move(data), true); }
        /// Sends a close frame.
        void close(std::uint16_t code, std::string reason = {}) const {
            server->close(index, code, std::move(reason));
        }
        /// Closes the TCP connection without a close frame.
        void drop() const { server->drop(index); }
    };

    using Options = MockWsServerOptions;

    explicit MockWsServer(Handler handler = {}, Options options = {})
        : handler_(std::move(handler)), options_(std::move(options)),
          acceptor_(ioc_, {boost::asio::ip::make_address("127.0.0.1"), 0}) {
        boost::asio::co_spawn(ioc_, accept_loop(), boost::asio::detached);
        thread_ = std::thread([this] { ioc_.run(); });
    }

    ~MockWsServer() {
        boost::asio::post(ioc_, [this] {
            boost::system::error_code ec;
            acceptor_.close(ec);
            for (auto& [index, conn] : conns_) {
                conn->abort();
            }
            ioc_.stop();
        });
        thread_.join();
    }

    MockWsServer(const MockWsServer&) = delete;
    MockWsServer& operator=(const MockWsServer&) = delete;

    [[nodiscard]] std::string url() const {
        return std::string(options_.tls ? "wss" : "ws") +
               "://127.0.0.1:" + std::to_string(acceptor_.local_endpoint().port());
    }

    /// Upgrade requests read so far, including ones still waiting for `accept_delay`.
    [[nodiscard]] std::size_t upgrade_requests() const { return upgrade_requests_.load(); }

    void set_handler(Handler handler) {
        boost::asio::post(ioc_,
                          [this, h = std::move(handler)]() mutable { handler_ = std::move(h); });
    }

    [[nodiscard]] std::vector<SessionInfo> sessions() const {
        const std::lock_guard lock(mutex_);
        return infos_;
    }

    [[nodiscard]] std::size_t session_count() const {
        const std::lock_guard lock(mutex_);
        return infos_.size();
    }

    [[nodiscard]] std::size_t open_count() const {
        const std::lock_guard lock(mutex_);
        return static_cast<std::size_t>(
            std::count_if(infos_.begin(), infos_.end(), [](const auto& s) { return s.open; }));
    }

    /// Waits until `pred(sessions())` holds. Returns false on timeout.
    template <class Pred>
    bool wait(Pred pred, std::chrono::milliseconds timeout = std::chrono::seconds(5)) const {
        std::unique_lock lock(mutex_);
        return cv_.wait_for(lock, timeout, [&] { return pred(infos_); });
    }

    void send(std::size_t index, std::string text, bool binary = false) {
        boost::asio::post(ioc_, [this, index, text = std::move(text), binary]() mutable {
            if (const auto it = conns_.find(index); it != conns_.end()) {
                it->second->enqueue(Out{binary ? Out::Binary : Out::Text, std::move(text), 0});
            }
        });
    }

    /// Sends `text` on every open connection.
    void broadcast(const std::string& text) {
        boost::asio::post(ioc_, [this, text] {
            for (auto& [index, conn] : conns_) {
                conn->enqueue(Out{Out::Text, text, 0});
            }
        });
    }

    void close(std::size_t index, std::uint16_t code, std::string reason = {}) {
        boost::asio::post(ioc_, [this, index, code, reason = std::move(reason)]() mutable {
            if (const auto it = conns_.find(index); it != conns_.end()) {
                it->second->enqueue(Out{Out::Close, std::move(reason), code});
            }
        });
    }

    void close_all(std::uint16_t code, const std::string& reason = {}) {
        boost::asio::post(ioc_, [this, code, reason] {
            for (auto& [index, conn] : conns_) {
                conn->enqueue(Out{Out::Close, reason, code});
            }
        });
    }

    void ping(std::size_t index) {
        boost::asio::post(ioc_, [this, index] {
            if (const auto it = conns_.find(index); it != conns_.end()) {
                it->second->enqueue(Out{Out::Ping, {}, 0});
            }
        });
    }

    void drop(std::size_t index) {
        boost::asio::post(ioc_, [this, index] {
            if (const auto it = conns_.find(index); it != conns_.end()) {
                it->second->abort();
            }
        });
    }

    void drop_all() {
        boost::asio::post(ioc_, [this] {
            for (auto& [index, conn] : conns_) {
                conn->abort();
            }
        });
    }

    /// Closes only the sending side of the TCP connection: the client sees EOF without a close
    /// frame while the server can still read.
    void half_close(std::size_t index) {
        boost::asio::post(ioc_, [this, index] {
            if (const auto it = conns_.find(index); it != conns_.end()) {
                it->second->half_close();
            }
        });
    }

    /// Stops reading (or resumes) the next message of every connection, so that a client's
    /// writes pile up in the socket buffers.
    void pause_reading(bool paused) { read_paused_ = paused; }

    /// Answers later upgrades with `status` (0: accept them again).
    void set_reject_status(unsigned status) {
        boost::asio::post(ioc_, [this, status] { options_.reject_status = status; });
    }

    /// Stops accepting connections (new ones are refused).
    void stop_accepting() {
        boost::asio::post(ioc_, [this] {
            boost::system::error_code ec;
            acceptor_.close(ec);
        });
    }

private:
    using tcp = boost::asio::ip::tcp;

    struct Out {
        enum Kind { Text, Binary, Close, Ping } kind;
        std::string data;
        std::uint16_t code;
    };

    struct Conn {
        virtual ~Conn() = default;
        virtual void enqueue(Out out) = 0;
        virtual void abort() = 0;
        virtual void half_close() = 0;
    };

    template <class Next> struct WsConn final : Conn, std::enable_shared_from_this<WsConn<Next>> {
        template <class... Args>
        explicit WsConn(Args&&... args) : ws(std::forward<Args>(args)...) {}

        void enqueue(Out out) override {
            outbox.push_back(std::move(out));
            start_writing();
        }

        /// Frames queued before the upgrade completes are written once it has.
        void start_writing() {
            if (accepted && !writing && !outbox.empty()) {
                writing = true;
                boost::asio::co_spawn(ws.get_executor(), write_loop(this->shared_from_this()),
                                      boost::asio::detached);
            }
        }

        void abort() override {
            boost::system::error_code ec;
            boost::beast::get_lowest_layer(ws).socket().close(ec);
        }

        void half_close() override {
            boost::system::error_code ec;
            boost::beast::get_lowest_layer(ws).socket().shutdown(tcp::socket::shutdown_send, ec);
        }

        static boost::asio::awaitable<void> write_loop(std::shared_ptr<WsConn> self) {
            namespace websocket = boost::beast::websocket;
            while (!self->outbox.empty()) {
                auto out = std::move(self->outbox.front());
                self->outbox.pop_front();
                boost::system::error_code ec;
                const auto token = boost::asio::redirect_error(boost::asio::use_awaitable, ec);
                switch (out.kind) {
                case Out::Text:
                case Out::Binary:
                    self->ws.binary(out.kind == Out::Binary);
                    co_await self->ws.async_write(boost::asio::buffer(out.data), token);
                    break;
                case Out::Close: {
                    websocket::close_reason reason(out.code);
                    reason.reason = out.data;
                    co_await self->ws.async_close(reason, token);
                } break;
                case Out::Ping:
                    co_await self->ws.async_ping({}, token);
                    break;
                }
                if (ec) {
                    self->outbox.clear();
                    break;
                }
            }
            self->writing = false;
        }

        boost::beast::websocket::stream<Next> ws;
        std::deque<Out> outbox;
        bool accepted = false;
        bool writing = false;
    };

    boost::asio::awaitable<void> accept_loop() {
        for (;;) {
            boost::system::error_code ec;
            auto socket = co_await acceptor_.async_accept(
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                co_return;
            }
            if (options_.tls) {
                boost::asio::co_spawn(
                    ioc_,
                    serve(std::make_shared<
                          WsConn<boost::asio::ssl::stream<boost::beast::tcp_stream>>>(
                        boost::beast::tcp_stream(std::move(socket)), *options_.tls)),
                    boost::asio::detached);
            } else {
                boost::asio::co_spawn(
                    ioc_,
                    serve(std::make_shared<WsConn<boost::beast::tcp_stream>>(std::move(socket))),
                    boost::asio::detached);
            }
        }
    }

    template <class Next> boost::asio::awaitable<void> serve(std::shared_ptr<WsConn<Next>> conn) {
        namespace beast = boost::beast;
        namespace http = beast::http;
        namespace websocket = beast::websocket;
        boost::system::error_code ec;
        const auto token = boost::asio::redirect_error(boost::asio::use_awaitable, ec);
        if constexpr (!std::is_same_v<Next, beast::tcp_stream>) {
            co_await conn->ws.next_layer().async_handshake(boost::asio::ssl::stream_base::server,
                                                           token);
            if (ec) {
                co_return;
            }
        }
        auto& stream = conn->ws.next_layer();
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        co_await http::async_read(stream, buffer, req, token);
        if (ec) {
            co_return;
        }
        ++upgrade_requests_;
        if (options_.accept_delay.count() > 0) {
            boost::asio::steady_timer timer(ioc_, options_.accept_delay);
            co_await timer.async_wait(token);
        }
        if (options_.reject_status != 0) {
            http::response<http::string_body> res{static_cast<http::status>(options_.reject_status),
                                                  11};
            res.body() = options_.reject_body;
            if (!options_.retry_after.empty()) {
                res.set(http::field::retry_after, options_.retry_after);
            }
            res.prepare_payload();
            co_await http::async_write(stream, res, token);
            beast::get_lowest_layer(conn->ws).close();
            co_return;
        }

        if (options_.deflate) {
            websocket::permessage_deflate pmd;
            pmd.server_enable = true;
            conn->ws.set_option(pmd);
        }
        const auto index = next_index_++;
        SessionInfo info;
        info.index = index;
        info.target = std::string(req.target());
        info.user_agent = std::string(req[http::field::user_agent]);
        for (const auto& field : req) {
            auto name = std::string(field.name_string());
            std::transform(name.begin(), name.end(), name.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            info.headers[name] = std::string(field.value());
        }
        const auto ext = std::string(req[http::field::sec_websocket_extensions]);
        info.deflate = options_.deflate && ext.find("permessage-deflate") != std::string::npos;
        conn->ws.control_callback([this, index](websocket::frame_type kind, beast::string_view) {
            if (kind == websocket::frame_type::ping) {
                update(index, [](SessionInfo& s) { ++s.pings; });
            }
        });
        // Recorded first: the client may see the upgrade response before `async_accept`
        // resumes this coroutine.
        conns_.emplace(index, conn);
        {
            const std::lock_guard lock(mutex_);
            infos_.push_back(info);
        }
        cv_.notify_all();
        co_await conn->ws.async_accept(req, token);
        if (ec) {
            conns_.erase(index);
            update(index, [](SessionInfo& s) { s.open = false; });
            co_return;
        }
        conn->accepted = true;
        conn->start_writing();

        Session session{this, index};
        for (;;) {
            buffer.clear();
            while (read_paused_) {
                boost::asio::steady_timer timer(ioc_, std::chrono::milliseconds(2));
                co_await timer.async_wait(token);
            }
            co_await conn->ws.async_read(buffer, token);
            if (ec) {
                break;
            }
            auto text = beast::buffers_to_string(buffer.data());
            update(index, [&text](SessionInfo& s) { s.received.push_back(text); });
            if (handler_) {
                handler_(session, text);
            }
        }
        conns_.erase(index);
        update(index, [](SessionInfo& s) { s.open = false; });
    }

    template <class F> void update(std::size_t index, F f) {
        {
            const std::lock_guard lock(mutex_);
            for (auto& s : infos_) {
                if (s.index == index) {
                    f(s);
                }
            }
        }
        cv_.notify_all();
    }

    Handler handler_;
    Options options_;
    boost::asio::io_context ioc_;
    tcp::acceptor acceptor_;
    std::thread thread_;
    std::map<std::size_t, std::shared_ptr<Conn>> conns_;
    std::size_t next_index_ = 0;
    std::atomic<std::size_t> upgrade_requests_{0};
    std::atomic<bool> read_paused_{false};
    mutable std::mutex mutex_;
    mutable std::condition_variable cv_;
    std::vector<SessionInfo> infos_;
};

} // namespace binance::test
