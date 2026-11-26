//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

namespace binance::test {

struct RecordedRequest {
    std::string method;
    std::string target;
    std::map<std::string, std::string> headers; // lower-case names
    std::string body;

    [[nodiscard]] std::string header(const std::string& name) const {
        const auto it = headers.find(name);
        return it == headers.end() ? std::string() : it->second;
    }
    [[nodiscard]] bool has_header(const std::string& name) const { return headers.contains(name); }
    [[nodiscard]] std::string path() const { return target.substr(0, target.find('?')); }
    [[nodiscard]] std::string query() const {
        const auto q = target.find('?');
        return q == std::string::npos ? std::string() : target.substr(q + 1);
    }
};

struct MockResponse {
    unsigned status = 200;
    std::string body = "{}";
    std::vector<std::pair<std::string, std::string>> headers{};
    /// Close the connection without answering (a transport error for the client).
    bool drop = false;
    /// Answer (advertising keep-alive), then close the connection: a pooled connection that the
    /// server closes while it is idle.
    bool close_after = false;
    /// Delay before answering.
    std::chrono::milliseconds delay{0};
    /// Sends the body in `drip_chunks` pieces with this pause between them.
    std::chrono::milliseconds drip_interval{0};
    std::size_t drip_chunks = 1;
};

/// A single-threaded HTTP/1.1 server on 127.0.0.1 with keep-alive, for client tests. With a TLS
/// context it serves HTTPS.
class MockServer {
public:
    using Handler = std::function<MockResponse(const RecordedRequest&)>;

    explicit MockServer(Handler handler = {},
                        std::shared_ptr<boost::asio::ssl::context> tls = nullptr)
        : handler_(handler ? std::move(handler)
                           : [](const RecordedRequest&) { return MockResponse{}; }),
          tls_(std::move(tls)), acceptor_(ioc_, {boost::asio::ip::make_address("127.0.0.1"), 0}) {
        boost::asio::co_spawn(ioc_, accept_loop(), boost::asio::detached);
        thread_ = std::thread([this] { ioc_.run(); });
    }

    ~MockServer() {
        boost::asio::post(ioc_, [this] {
            boost::system::error_code ec;
            acceptor_.close(ec);
            ioc_.stop();
        });
        thread_.join();
    }

    MockServer(const MockServer&) = delete;
    MockServer& operator=(const MockServer&) = delete;

    [[nodiscard]] std::string url() const {
        return std::string(tls_ ? "https" : "http") +
               "://127.0.0.1:" + std::to_string(acceptor_.local_endpoint().port());
    }

    [[nodiscard]] std::vector<RecordedRequest> requests() const {
        std::lock_guard lock(mutex_);
        return requests_;
    }

    [[nodiscard]] std::size_t request_count() const {
        std::lock_guard lock(mutex_);
        return requests_.size();
    }

    [[nodiscard]] std::size_t connection_count() const {
        std::lock_guard lock(mutex_);
        return connections_;
    }

private:
    boost::asio::awaitable<void> accept_loop() {
        for (;;) {
            boost::system::error_code ec;
            auto socket = co_await acceptor_.async_accept(
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                co_return;
            }
            {
                std::lock_guard lock(mutex_);
                ++connections_;
            }
            boost::asio::co_spawn(ioc_, serve(std::move(socket)), boost::asio::detached);
        }
    }

    boost::asio::awaitable<void> serve(boost::asio::ip::tcp::socket socket) {
        if (!tls_) {
            co_await serve_http(socket);
            co_return;
        }
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> stream(std::move(socket), *tls_);
        boost::system::error_code ec;
        co_await stream.async_handshake(
            boost::asio::ssl::stream_base::server,
            boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (!ec) {
            co_await serve_http(stream);
        }
    }

    template <class Stream> boost::asio::awaitable<void> serve_http(Stream& socket) {
        namespace http = boost::beast::http;
        boost::beast::flat_buffer buffer;
        for (;;) {
            boost::system::error_code ec;
            http::request<http::string_body> req;
            co_await http::async_read(socket, buffer, req,
                                      boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                co_return;
            }
            RecordedRequest rec{
                std::string(req.method_string()), std::string(req.target()), {}, req.body()};
            for (const auto& field : req) {
                std::string name(field.name_string());
                for (auto& c : name) {
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
                rec.headers[name] = std::string(field.value());
            }
            {
                std::lock_guard lock(mutex_);
                requests_.push_back(rec);
            }
            const auto out = handler_(rec);
            if (out.delay.count() > 0) {
                boost::asio::steady_timer timer(ioc_, out.delay);
                co_await timer.async_wait(
                    boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            }
            if (out.drop) {
                boost::beast::get_lowest_layer(socket).close(ec);
                co_return;
            }
            http::response<http::string_body> res{static_cast<http::status>(out.status), 11};
            res.set(http::field::content_type, "application/json");
            for (const auto& [name, value] : out.headers) {
                res.insert(name, value);
            }
            res.body() = out.body;
            res.keep_alive(req.keep_alive());
            res.prepare_payload();
            if (out.drip_interval.count() > 0) {
                http::response_serializer<http::string_body> sr{res};
                co_await http::async_write_header(
                    socket, sr, boost::asio::redirect_error(boost::asio::use_awaitable, ec));
                const auto step = std::max<std::size_t>(1, out.body.size() / out.drip_chunks);
                for (std::size_t at = 0; !ec && at < out.body.size(); at += step) {
                    boost::asio::steady_timer timer(ioc_, out.drip_interval);
                    co_await timer.async_wait(
                        boost::asio::redirect_error(boost::asio::use_awaitable, ec));
                    co_await boost::asio::async_write(
                        socket,
                        boost::asio::buffer(out.body.data() + at,
                                            std::min(step, out.body.size() - at)),
                        boost::asio::redirect_error(boost::asio::use_awaitable, ec));
                }
            } else {
                co_await http::async_write(
                    socket, res, boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            }
            if (ec || !res.keep_alive() || out.close_after) {
                boost::beast::get_lowest_layer(socket).shutdown(
                    boost::asio::ip::tcp::socket::shutdown_both, ec);
                co_return;
            }
        }
    }

    Handler handler_;
    std::shared_ptr<boost::asio::ssl::context> tls_;
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::thread thread_;
    mutable std::mutex mutex_;
    std::vector<RecordedRequest> requests_;
    std::size_t connections_ = 0;
};

} // namespace binance::test
