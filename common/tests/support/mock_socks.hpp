//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>

namespace binance::test {

struct SocksRequest {
    /// Authentication methods the client offered.
    std::vector<std::uint8_t> methods;
    std::optional<std::string> username;
    std::optional<std::string> password;
    /// Address type of the CONNECT request: 1 IPv4, 3 domain name, 4 IPv6. 0 if it was not read.
    std::uint8_t address_type = 0;
    /// The requested host: a domain name, or the address in text form.
    std::string host;
    std::uint16_t port = 0;
};

struct MockSocksOptions {
    /// Requires username / password authentication with these credentials.
    std::optional<std::pair<std::string, std::string>> credentials;
    /// Answers the method request with this method instead of choosing one.
    std::optional<std::uint8_t> method_reply;
    /// Answers the CONNECT request with this failure code (nonzero) instead of tunnelling.
    std::uint8_t connect_reply = 0;
    /// Waits this long before answering the method request.
    std::chrono::milliseconds delay{0};
};

inline MockSocksOptions socks_credentials(std::string username, std::string password) {
    MockSocksOptions options;
    options.credentials = std::pair(std::move(username), std::move(password));
    return options;
}

inline MockSocksOptions socks_method_reply(std::uint8_t method) {
    MockSocksOptions options;
    options.method_reply = method;
    return options;
}

inline MockSocksOptions socks_connect_reply(std::uint8_t code) {
    MockSocksOptions options;
    options.connect_reply = code;
    return options;
}

inline MockSocksOptions socks_delay(std::chrono::milliseconds delay) {
    MockSocksOptions options;
    options.delay = delay;
    return options;
}

/// A SOCKS5 server on 127.0.0.1 (RFC 1928, RFC 1929) for client tests: it records what each
/// client asked for and relays bytes to the target. The IPv6 loopback address is relayed to the
/// IPv4 one, where the other mock servers listen.
class MockSocks {
public:
    using Options = MockSocksOptions;

    explicit MockSocks(Options options = {})
        : options_(std::move(options)),
          acceptor_(ioc_, {boost::asio::ip::make_address("127.0.0.1"), 0}) {
        boost::asio::co_spawn(ioc_, accept_loop(), boost::asio::detached);
        thread_ = std::thread([this] { ioc_.run(); });
    }

    ~MockSocks() {
        boost::asio::post(ioc_, [this] {
            boost::system::error_code ec;
            acceptor_.close(ec);
            ioc_.stop();
        });
        thread_.join();
    }

    MockSocks(const MockSocks&) = delete;
    MockSocks& operator=(const MockSocks&) = delete;

    [[nodiscard]] std::uint16_t port() const { return acceptor_.local_endpoint().port(); }

    [[nodiscard]] std::vector<SocksRequest> requests() const {
        const std::lock_guard lock(mutex_);
        return requests_;
    }

private:
    using tcp = boost::asio::ip::tcp;
    using Bytes = std::vector<std::uint8_t>;

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

    static boost::asio::awaitable<Bytes> read_exact(tcp::socket& socket, std::size_t size) {
        Bytes data(size);
        co_await boost::asio::async_read(socket, boost::asio::buffer(data),
                                         boost::asio::use_awaitable);
        co_return data;
    }

    // Callers pass a named Bytes: GCC 12 rejects a braced list inside a co_await expression
    // ("array used as initializer"), because the initializer_list's array lands in the frame.
    static boost::asio::awaitable<void> write_all(tcp::socket& socket, const Bytes& data) {
        co_await boost::asio::async_write(socket, boost::asio::buffer(data),
                                          boost::asio::use_awaitable);
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
        boost::system::error_code ignored;
        from.close(ignored);
        to.close(ignored);
    }

    boost::asio::awaitable<void> serve(tcp::socket client) {
        using boost::asio::experimental::awaitable_operators::operator||;
        SocksRequest seen;
        try {
            const auto greeting = co_await read_exact(client, 2);
            seen.methods = co_await read_exact(client, greeting[1]);
            if (options_.delay.count() > 0) {
                boost::asio::steady_timer timer(ioc_, options_.delay);
                co_await timer.async_wait(boost::asio::use_awaitable);
            }
            const auto offered = [&](std::uint8_t method) {
                return std::find(seen.methods.begin(), seen.methods.end(), method) !=
                       seen.methods.end();
            };
            std::uint8_t method = 0xFF;
            if (options_.method_reply) {
                method = *options_.method_reply;
            } else if (options_.credentials) {
                method = offered(2) ? 2 : 0xFF;
            } else if (offered(0)) {
                method = 0;
            }
            const Bytes method_reply{5, method};
            co_await write_all(client, method_reply);
            if (method == 0xFF) {
                record(seen);
                co_return;
            }
            if (method == 2) {
                const auto head = co_await read_exact(client, 2);
                const auto user = co_await read_exact(client, head[1]);
                const auto plen = co_await read_exact(client, 1);
                const auto pass = co_await read_exact(client, plen[0]);
                seen.username = std::string(user.begin(), user.end());
                seen.password = std::string(pass.begin(), pass.end());
                const bool ok = options_.credentials &&
                                *options_.credentials == std::pair(*seen.username, *seen.password);
                const Bytes auth_reply{1, static_cast<std::uint8_t>(ok ? 0 : 1)};
                co_await write_all(client, auth_reply);
                if (!ok) {
                    record(seen);
                    co_return;
                }
            } else if (method != 0) {
                record(seen);
                co_return;
            }

            const auto head = co_await read_exact(client, 4);
            seen.address_type = head[3];
            std::string host;
            if (head[3] == 1) {
                const auto bytes = co_await read_exact(client, 4);
                host = boost::asio::ip::address_v4({bytes[0], bytes[1], bytes[2], bytes[3]})
                           .to_string();
            } else if (head[3] == 4) {
                const auto bytes = co_await read_exact(client, 16);
                boost::asio::ip::address_v6::bytes_type raw;
                std::copy(bytes.begin(), bytes.end(), raw.begin());
                host = boost::asio::ip::address_v6(raw).to_string();
            } else {
                const auto length = co_await read_exact(client, 1);
                const auto name = co_await read_exact(client, length[0]);
                host.assign(name.begin(), name.end());
            }
            const auto port_bytes = co_await read_exact(client, 2);
            seen.host = host;
            seen.port = static_cast<std::uint16_t>((port_bytes[0] << 8) | port_bytes[1]);
            record(seen);

            if (options_.connect_reply != 0) {
                const Bytes failure_reply{5, options_.connect_reply, 0, 1, 0, 0, 0, 0, 0, 0};
                co_await write_all(client, failure_reply);
                co_return;
            }
            if (host == "::1") {
                host = "127.0.0.1";
            }
            tcp::resolver resolver(ioc_);
            const auto results = co_await resolver.async_resolve(host, std::to_string(seen.port),
                                                                 boost::asio::use_awaitable);
            tcp::socket upstream(ioc_);
            co_await boost::asio::async_connect(upstream, results, boost::asio::use_awaitable);
            const Bytes success_reply{5, 0, 0, 1, 127, 0, 0, 1, 0, 0};
            co_await write_all(client, success_reply);
            co_await (pump(client, upstream) || pump(upstream, client));
        } catch (const boost::system::system_error&) {
            // The client sees the connection drop.
        }
    }

    void record(const SocksRequest& request) {
        const std::lock_guard lock(mutex_);
        requests_.push_back(request);
    }

    Options options_;
    boost::asio::io_context ioc_;
    tcp::acceptor acceptor_;
    std::thread thread_;
    mutable std::mutex mutex_;
    std::vector<SocksRequest> requests_;
};

} // namespace binance::test
