//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <chrono>
#include <cstdint>
#include <list>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>

namespace binance::test {

using namespace std::chrono_literals;

/// A listener that completes no TCP handshake: its backlog is full and further SYNs are dropped.
class BlackHole {
public:
    BlackHole(const boost::asio::ip::address& address, std::uint16_t port = 0) : acceptor_(ioc_) {
        boost::system::error_code ec;
        boost::asio::ip::tcp::endpoint ep(address, port);
        acceptor_.open(ep.protocol(), ec);
        if (!ec) {
            acceptor_.bind(ep, ec);
        }
        if (!ec) {
            acceptor_.listen(1, ec);
        }
        if (ec) {
            return;
        }
        ep = acceptor_.local_endpoint();
        for (int i = 0; i < 64 && !active_; ++i) {
            auto& socket = fills_.emplace_back(ioc_);
            boost::asio::steady_timer timer(ioc_, 200ms);
            bool timed_out = false;
            socket.async_connect(ep, [&](const boost::system::error_code&) { timer.cancel(); });
            timer.async_wait([&](const boost::system::error_code& e) {
                if (!e) {
                    timed_out = true;
                    socket.cancel();
                }
            });
            ioc_.restart();
            ioc_.run();
            active_ = timed_out;
        }
    }

    [[nodiscard]] bool active() const { return active_; }
    [[nodiscard]] boost::asio::ip::tcp::endpoint endpoint() const {
        return acceptor_.local_endpoint();
    }

private:
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::list<boost::asio::ip::tcp::socket> fills_;
    bool active_ = false;
};

} // namespace binance::test
