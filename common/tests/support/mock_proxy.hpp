//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <array>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

namespace binance::test {

struct ProxiedRequest {
    std::string method;
    std::string target;
    std::string proxy_authorization;
};

/// A forward proxy on 127.0.0.1, for client tests. It accepts `CONNECT host:port` (and then
/// relays bytes both ways) and absolute-form requests (which it forwards in origin form, without
/// `Proxy-Authorization`). With a TLS context it is an HTTPS proxy.
class MockProxy {
public:
    explicit MockProxy(std::shared_ptr<boost::asio::ssl::context> tls = nullptr,
                       unsigned connect_status = 200)
        : tls_(std::move(tls)), connect_status_(connect_status),
          acceptor_(ioc_, {boost::asio::ip::make_address("127.0.0.1"), 0}) {
        boost::asio::co_spawn(ioc_, accept_loop(), boost::asio::detached);
        thread_ = std::thread([this] { ioc_.run(); });
    }

    ~MockProxy() {
        boost::asio::post(ioc_, [this] {
            boost::system::error_code ec;
            acceptor_.close(ec);
            ioc_.stop();
        });
        thread_.join();
    }

    MockProxy(const MockProxy&) = delete;
    MockProxy& operator=(const MockProxy&) = delete;

    [[nodiscard]] std::uint16_t port() const { return acceptor_.local_endpoint().port(); }

    [[nodiscard]] std::vector<ProxiedRequest> requests() const {
        std::lock_guard lock(mutex_);
        return requests_;
    }

private:
    using tcp = boost::asio::ip::tcp;

    boost::asio::awaitable<void> accept_loop() {
        for (;;) {
            boost::system::error_code ec;
            auto socket = co_await acceptor_.async_accept(
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                co_return;
            }
            boost::asio::co_spawn(ioc_, serve(std::move(socket)), boost::asio::detached);
        }
    }

    boost::asio::awaitable<void> serve(tcp::socket socket) {
        if (!tls_) {
            co_await serve_client(socket);
            co_return;
        }
        boost::asio::ssl::stream<tcp::socket> stream(std::move(socket), *tls_);
        boost::system::error_code ec;
        co_await stream.async_handshake(
            boost::asio::ssl::stream_base::server,
            boost::asio::redirect_error(boost::asio::use_awaitable, ec));
        if (!ec) {
            co_await serve_client(stream);
        }
    }

    static std::pair<std::string, std::string> split_authority(std::string_view authority) {
        const auto colon = authority.rfind(':');
        auto host = authority.substr(0, colon);
        if (host.starts_with('[') && host.ends_with(']')) {
            host = host.substr(1, host.size() - 2);
        }
        return {std::string(host), std::string(authority.substr(colon + 1))};
    }

    boost::asio::awaitable<tcp::socket> dial(std::string_view authority) {
        // Named locals, not a structured binding: GCC reports the binding of a coroutine frame as
        // maybe-uninitialized at -O2.
        const auto authority_parts = split_authority(authority);
        const std::string& host = authority_parts.first;
        const std::string& port = authority_parts.second;
        tcp::resolver resolver(ioc_);
        const auto results =
            co_await resolver.async_resolve(host, port, boost::asio::use_awaitable);
        tcp::socket upstream(ioc_);
        co_await boost::asio::async_connect(upstream, results, boost::asio::use_awaitable);
        co_return upstream;
    }

    template <class From, class To> static boost::asio::awaitable<void> pump(From& from, To& to) {
        std::array<char, 16 * 1024> chunk{};
        for (;;) {
            boost::system::error_code ec;
            const auto n = co_await from.async_read_some(
                boost::asio::buffer(chunk),
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                break;
            }
            co_await boost::asio::async_write(
                to, boost::asio::buffer(chunk.data(), n),
                boost::asio::redirect_error(boost::asio::use_awaitable, ec));
            if (ec) {
                break;
            }
        }
        // Wake the opposite direction, whether or not its operation supports cancellation.
        boost::system::error_code ignored;
        boost::beast::get_lowest_layer(from).close(ignored);
        boost::beast::get_lowest_layer(to).close(ignored);
    }

    template <class Stream> boost::asio::awaitable<void> serve_client(Stream& client) {
        namespace http = boost::beast::http;
        using boost::asio::experimental::awaitable_operators::operator||;
        boost::beast::flat_buffer buffer;
        std::optional<tcp::socket> upstream;
        boost::beast::flat_buffer upstream_buffer;
        try {
            for (;;) {
                http::request<http::string_body> req;
                boost::system::error_code ec;
                co_await http::async_read(
                    client, buffer, req,
                    boost::asio::redirect_error(boost::asio::use_awaitable, ec));
                if (ec) {
                    co_return;
                }
                {
                    std::lock_guard lock(mutex_);
                    requests_.push_back({std::string(req.method_string()),
                                         std::string(req.target()),
                                         std::string(req[http::field::proxy_authorization])});
                }

                if (req.method() == http::verb::connect) {
                    if (connect_status_ != 200) {
                        http::response<http::empty_body> res{
                            static_cast<http::status>(connect_status_), 11};
                        res.keep_alive(false);
                        co_await http::async_write(client, res, boost::asio::use_awaitable);
                        co_return;
                    }
                    auto tunnel = co_await dial(req.target());
                    static constexpr std::string_view kEstablished =
                        "HTTP/1.1 200 Connection Established\r\n\r\n";
                    co_await boost::asio::async_write(client, boost::asio::buffer(kEstablished),
                                                      boost::asio::use_awaitable);
                    if (buffer.size() > 0) {
                        co_await boost::asio::async_write(tunnel, buffer.data(),
                                                          boost::asio::use_awaitable);
                    }
                    co_await (pump(client, tunnel) || pump(tunnel, client));
                    co_return;
                }

                // Absolute form: http://host:port/path?query
                std::string_view target = req.target();
                constexpr std::string_view kScheme = "http://";
                if (!target.starts_with(kScheme)) {
                    co_return;
                }
                target.remove_prefix(kScheme.size());
                const auto slash = target.find('/');
                if (!upstream) {
                    upstream = co_await dial(target.substr(0, slash));
                }
                req.target(slash == std::string_view::npos ? std::string("/")
                                                           : std::string(target.substr(slash)));
                req.erase(http::field::proxy_authorization);
                co_await http::async_write(*upstream, req, boost::asio::use_awaitable);
                http::response<http::string_body> res;
                co_await http::async_read(*upstream, upstream_buffer, res,
                                          boost::asio::use_awaitable);
                co_await http::async_write(client, res, boost::asio::use_awaitable);
            }
        } catch (const boost::system::system_error&) {
            // The client sees the connection drop.
        }
    }

    std::shared_ptr<boost::asio::ssl::context> tls_;
    unsigned connect_status_;
    boost::asio::io_context ioc_;
    tcp::acceptor acceptor_;
    std::thread thread_;
    mutable std::mutex mutex_;
    std::vector<ProxiedRequest> requests_;
};

} // namespace binance::test
