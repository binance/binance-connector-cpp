//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// Tests of the staggered TCP connect shared by the REST client and the WebSocket engine.
#include <chrono>
#include <exception>
#include <list>
#include <memory>
#include <vector>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/beast/core/error.hpp>
#include <gtest/gtest.h>

#include "net.hpp"
#include "support/black_hole.hpp"
#include "support/mock_server.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;
using binance::common::detail::connect_staggered;
using binance::common::detail::connection_attempt_delay;
using binance::common::detail::interleave_families;
using binance::test::BlackHole;
using binance::test::MockServer;
using namespace std::chrono_literals;

namespace {

using Clock = std::chrono::steady_clock;

struct Outcome {
    boost::system::error_code error; // empty on success
    bool threw_other = false;
    std::chrono::milliseconds elapsed{0};
    tcp::endpoint remote;
};

Outcome run(std::vector<tcp::endpoint> endpoints, std::chrono::milliseconds timeout) {
    asio::io_context ioc;
    Outcome out;
    const auto start = Clock::now();
    asio::co_spawn(
        ioc,
        [&]() -> asio::awaitable<void> {
            tcp::socket socket(co_await asio::this_coro::executor);
            co_await connect_staggered(socket, std::move(endpoints), start + timeout);
            out.remote = socket.remote_endpoint();
        },
        [&](std::exception_ptr ep) {
            if (!ep) {
                return;
            }
            try {
                std::rethrow_exception(ep);
            } catch (const boost::system::system_error& e) {
                out.error = e.code();
            } catch (...) {
                out.threw_other = true;
            }
        });
    ioc.run();
    out.elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start);
    return out;
}

tcp::endpoint server_endpoint(const MockServer& server) {
    const auto url = server.url();
    return {asio::ip::make_address("127.0.0.1"),
            static_cast<std::uint16_t>(std::stoul(url.substr(url.rfind(':') + 1)))};
}

tcp::endpoint refused_endpoint() {
    asio::io_context ioc;
    tcp::acceptor acceptor(ioc, {asio::ip::make_address("127.0.0.1"), 0});
    const auto ep = acceptor.local_endpoint();
    acceptor.close();
    return ep;
}

/// `count` black holes on 127.0.0.1; the test is skipped if the system does not black-hole.
std::list<BlackHole> black_holes(std::size_t count) {
    std::list<BlackHole> holes;
    for (std::size_t i = 0; i < count; ++i) {
        holes.emplace_back(asio::ip::make_address("127.0.0.1"));
    }
    return holes;
}

bool all_active(const std::list<BlackHole>& holes) {
    for (const auto& h : holes) {
        if (!h.active()) {
            return false;
        }
    }
    return true;
}

} // namespace

TEST(StaggeredConnect, InterleavesFamiliesStartingWithTheResolversFirst) {
    const auto v4 = [](unsigned short port) {
        return tcp::endpoint(asio::ip::make_address("10.0.0.1"), port);
    };
    const auto v6 = [](unsigned short port) {
        return tcp::endpoint(asio::ip::make_address("::1"), port);
    };
    const std::vector<tcp::endpoint> given{v6(1), v6(2), v6(3), v4(4), v4(5)};
    const auto ordered = interleave_families(
        tcp::resolver::results_type::create(given.begin(), given.end(), "h", "p"));
    EXPECT_EQ(ordered, (std::vector<tcp::endpoint>{v6(1), v4(4), v6(2), v4(5), v6(3)}));
    const std::vector<tcp::endpoint> v4_first{v4(1), v4(2), v6(3)};
    EXPECT_EQ(interleave_families(
                  tcp::resolver::results_type::create(v4_first.begin(), v4_first.end(), "h", "p")),
              (std::vector<tcp::endpoint>{v4(1), v6(3), v4(2)}));
}

TEST(StaggeredConnect, BlackHoleThenGoodConnectsAfterTheAttemptDelay) {
    MockServer server;
    const auto holes = black_holes(1);
    if (!all_active(holes)) {
        GTEST_SKIP() << "cannot black-hole 127.0.0.1 here";
    }
    const auto out = run({holes.front().endpoint(), server_endpoint(server)}, 5s);
    EXPECT_FALSE(out.error);
    EXPECT_EQ(out.remote, server_endpoint(server));
    EXPECT_GT(out.elapsed, connection_attempt_delay - 50ms);
    EXPECT_LT(out.elapsed, 1s);
}

TEST(StaggeredConnect, RefusedThenGoodConnectsWithoutWaiting) {
    MockServer server;
    const auto out = run({refused_endpoint(), server_endpoint(server)}, 5s);
    EXPECT_FALSE(out.error);
    EXPECT_EQ(out.remote, server_endpoint(server));
    EXPECT_LT(out.elapsed, connection_attempt_delay - 50ms);
}

TEST(StaggeredConnect, AllBlackHolesTimeOutAtTheConfiguredTimeout) {
    const auto holes = black_holes(3);
    if (!all_active(holes)) {
        GTEST_SKIP() << "cannot black-hole 127.0.0.1 here";
    }
    std::vector<tcp::endpoint> eps;
    for (const auto& h : holes) {
        eps.push_back(h.endpoint());
    }
    const auto out = run(eps, 700ms);
    EXPECT_EQ(out.error, boost::beast::error::timeout);
    EXPECT_GE(out.elapsed, 690ms);
    EXPECT_LT(out.elapsed, 1000ms);
}

TEST(StaggeredConnect, AllRefusedReportsConnectionRefused) {
    const auto out = run({refused_endpoint(), refused_endpoint()}, 5s);
    EXPECT_EQ(out.error, asio::error::connection_refused);
    EXPECT_LT(out.elapsed, 500ms);
}

TEST(StaggeredConnect, GoodAddressAfterSeveralBlackHolesWinsWithinTheBudget) {
    MockServer server;
    const auto holes = black_holes(5);
    if (!all_active(holes)) {
        GTEST_SKIP() << "cannot black-hole 127.0.0.1 here";
    }
    std::vector<tcp::endpoint> eps;
    for (const auto& h : holes) {
        eps.push_back(h.endpoint());
    }
    eps.push_back(server_endpoint(server));
    const auto out = run(eps, 5s);
    EXPECT_FALSE(out.error);
    EXPECT_EQ(out.remote, server_endpoint(server));
    EXPECT_GT(out.elapsed, 5 * connection_attempt_delay - 100ms);
    EXPECT_LT(out.elapsed, 5 * connection_attempt_delay + 500ms);
}

TEST(StaggeredConnect, BudgetShorterThanTheDelayTimesOutBeforeTheGoodAddress) {
    MockServer server;
    const auto holes = black_holes(1);
    if (!all_active(holes)) {
        GTEST_SKIP() << "cannot black-hole 127.0.0.1 here";
    }
    const auto out = run({holes.front().endpoint(), server_endpoint(server)}, 150ms);
    EXPECT_EQ(out.error, boost::beast::error::timeout);
    EXPECT_LT(out.elapsed, 400ms);
}
