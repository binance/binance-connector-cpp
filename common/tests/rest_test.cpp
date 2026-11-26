//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// End-to-end tests of `RestClient` against a local mock server.
#include <array>
#include <atomic>
#include <cctype>
#include <clocale>
#include <future>
#include <list>
#include <memory>
#include <thread>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/cancel_after.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/json.hpp>
#include <gtest/gtest.h>
#include <openssl/hmac.h>
#include <zlib.h>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>

#include "support/black_hole.hpp"
#include "support/certs.hpp"
#include "support/env.hpp"
#include "support/mock_proxy.hpp"
#include "support/mock_server.hpp"

using namespace binance::common;
using binance::test::BlackHole;
using binance::test::MockProxy;
using binance::test::MockResponse;
using binance::test::MockServer;
using binance::test::RecordedRequest;
using binance::test::TestCertificate;
using namespace std::chrono_literals;

namespace {

RestApiConfig config_for(const MockServer& server) {
    RestApiConfig cfg;
    cfg.base_path = server.url();
    cfg.backoff = 1ms;
    cfg.proxy_from_env = false; // hermetic: ignore a proxy on the developer's machine
    return cfg;
}

RestRequest get(std::string endpoint, Params query = {}) {
    return RestRequest{HttpMethod::Get, std::move(endpoint), std::move(query), {}, {}, false, {}};
}

std::string gzip(std::string_view in) {
    z_stream zs{};
    deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, MAX_WBITS + 16, 8, Z_DEFAULT_STRATEGY);
    std::string out(deflateBound(&zs, static_cast<uLong>(in.size())) + 32, '\0');
    zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(in.data()));
    zs.avail_in = static_cast<uInt>(in.size());
    zs.next_out = reinterpret_cast<Bytef*>(out.data());
    zs.avail_out = static_cast<uInt>(out.size());
    deflate(&zs, Z_FINISH);
    out.resize(zs.total_out);
    deflateEnd(&zs);
    return out;
}

std::string hmac_hex(std::string_view secret, std::string_view payload) {
    std::array<unsigned char, EVP_MAX_MD_SIZE> mac{};
    unsigned int len = 0;
    HMAC(EVP_sha256(), secret.data(), static_cast<int>(secret.size()),
         reinterpret_cast<const unsigned char*>(payload.data()), payload.size(), mac.data(), &len);
    std::string out;
    constexpr const char* kHex = "0123456789abcdef";
    for (unsigned int i = 0; i < len; ++i) {
        out += kHex[mac[i] >> 4];
        out += kHex[mac[i] & 0xF];
    }
    return out;
}

/// A port nothing listens on.
std::string closed_url() {
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::acceptor acc(ioc, {boost::asio::ip::make_address("127.0.0.1"), 0});
    const auto port = acc.local_endpoint().port();
    acc.close();
    return "http://127.0.0.1:" + std::to_string(port);
}

MockResponse respond(unsigned status, std::string body) {
    MockResponse r;
    r.status = status;
    r.body = std::move(body);
    return r;
}

/// Switches the C locale to one where `std::isalnum` accepts bytes above 0x7F, if there is one.
class WideLocale {
public:
    WideLocale() : saved_(std::setlocale(LC_ALL, nullptr)) {
        for (const char* name :
             {"en_US.ISO8859-1", "en_US.ISO-8859-1", "de_DE.ISO8859-1", "en_US.UTF-8", "C.UTF-8"}) {
            if (std::setlocale(LC_ALL, name) != nullptr && std::isalnum(0xE9) != 0) {
                active_ = true;
                return;
            }
        }
        std::setlocale(LC_ALL, saved_.c_str());
    }
    ~WideLocale() { std::setlocale(LC_ALL, saved_.c_str()); }
    WideLocale(const WideLocale&) = delete;
    WideLocale& operator=(const WideLocale&) = delete;

    [[nodiscard]] bool active() const { return active_; }

private:
    std::string saved_;
    bool active_ = false;
};

std::uint16_t port_of(const MockServer& server) {
    const auto url = server.url();
    return static_cast<std::uint16_t>(std::stoul(url.substr(url.rfind(':') + 1)));
}

} // namespace

TEST(RestClient, PlainGetRequest) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"serverTime":1})"); });
    RestClient client(config_for(server));
    const auto raw = client.send_request(get("/api/v3/time"));

    EXPECT_EQ(raw.status, 200);
    EXPECT_EQ(raw.body, R"({"serverTime":1})");
    EXPECT_EQ(raw.headers.at("content-type"), "application/json");
    EXPECT_FALSE(raw.rate_limits.has_value());
    EXPECT_EQ(RestApiResponse<boost::json::object>(raw).data().at("serverTime").as_int64(), 1);
    RestApiResponse<boost::json::object> moved_from(raw);
    const auto moved = std::move(moved_from);
    EXPECT_EQ(moved.data().at("serverTime").as_int64(), 1);
    // NOLINTNEXTLINE(bugprone-use-after-move): a moved-from response still decodes.
    EXPECT_EQ(moved_from.data().at("serverTime").as_int64(), 1);

    const auto reqs = server.requests();
    ASSERT_EQ(reqs.size(), 1U);
    EXPECT_EQ(reqs[0].method, "GET");
    EXPECT_EQ(reqs[0].target, "/api/v3/time");
    EXPECT_EQ(reqs[0].header("user-agent"), binance::common::detail::build_user_agent("common"));
    EXPECT_EQ(reqs[0].header("content-type"), "application/json");
    EXPECT_EQ(reqs[0].header("accept-encoding"), "gzip, deflate");
    EXPECT_EQ(reqs[0].header("host"), server.url().substr(7));
    EXPECT_FALSE(reqs[0].has_header("x-mbx-apikey"));
    EXPECT_FALSE(reqs[0].has_header("x-mbx-time-unit"));
}

TEST(RestClient, GzipResponseIsDecoded) {
    MockServer server([](const RecordedRequest&) {
        auto r = respond(200, gzip(R"({"ok":true})"));
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    RestClient client(config_for(server));
    EXPECT_EQ(client.send_request(get("/x")).body, R"({"ok":true})");
}

TEST(RestClient, CompressionDisabledOmitsAcceptEncoding) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.compression = false;
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    EXPECT_FALSE(server.requests().at(0).has_header("accept-encoding"));
}

TEST(RestClient, RateLimitHeadersAreParsed) {
    MockServer server([](const RecordedRequest&) {
        auto r = respond(200, "{}");
        r.headers = {{"X-MBX-USED-WEIGHT-1M", "12"}, {"x-mbx-order-count-10s", "3"}};
        return r;
    });
    RestClient client(config_for(server));
    const auto raw = client.send_request(get("/x"));
    ASSERT_TRUE(raw.rate_limits.has_value());
    EXPECT_EQ(raw.rate_limits->size(), 2U);
    EXPECT_EQ(raw.headers.at("x-mbx-used-weight-1m"), "12");
}

template <class E>
void expect_status_maps_to(unsigned status, const std::string& body, const std::string& msg,
                           std::optional<std::int64_t> code) {
    MockServer server([&](const RecordedRequest&) { return respond(status, body); });
    auto cfg = config_for(server);
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        ADD_FAILURE() << "status " << status << " did not throw";
    } catch (const E& e) {
        EXPECT_EQ(e.msg(), msg) << status;
        EXPECT_EQ(e.code(), code) << status;
    } catch (const std::exception& e) {
        ADD_FAILURE() << "status " << status << " threw the wrong type: " << e.what();
    }
}

TEST(RestClient, ClientErrorStatusesAreMapped) {
    const std::string body = R"({"code":-1100,"msg":"Illegal characters found"})";
    const std::string msg = "Illegal characters found";
    expect_status_maps_to<BadRequestError>(400, body, msg, -1100);
    expect_status_maps_to<UnauthorizedError>(401, body, msg, -1100);
    expect_status_maps_to<ForbiddenError>(403, body, msg, -1100);
    expect_status_maps_to<NotFoundError>(404, body, msg, -1100);
    expect_status_maps_to<RateLimitBanError>(418, body, msg, -1100);
    expect_status_maps_to<TooManyRequestsError>(429, body, msg, -1100);
    expect_status_maps_to<ConflictError>(409, body, msg, -1100);
    expect_status_maps_to<ConnectorClientError>(422, body, msg, -1100);
}

std::optional<std::chrono::seconds> retry_after_of(unsigned status,
                                                   std::optional<std::string> header) {
    MockServer server([&](const RecordedRequest&) {
        auto r = respond(status, R"({"code":-1003,"msg":"slow down"})");
        if (header) {
            r.headers = {{"Retry-After", *header}};
        }
        return r;
    });
    auto cfg = config_for(server);
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
    } catch (const binance::common::ConnectorError& e) {
        return e.retry_after();
    }
    ADD_FAILURE() << "status " << status << " did not throw";
    return std::nullopt;
}

TEST(RestClient, RetryAfterIsReadFromTooManyRequestsAndBan) {
    for (const unsigned status : {429U, 418U}) {
        EXPECT_EQ(retry_after_of(status, "30"), std::chrono::seconds(30)) << status;
        EXPECT_EQ(retry_after_of(status, " 7 "), std::chrono::seconds(7)) << status;
        EXPECT_EQ(retry_after_of(status, "0"), std::chrono::seconds(0)) << status;
        EXPECT_EQ(retry_after_of(status, std::nullopt), std::nullopt) << status;
        EXPECT_EQ(retry_after_of(status, "soon"), std::nullopt) << status;
        EXPECT_EQ(retry_after_of(status, "-5"), std::nullopt) << status;
        EXPECT_EQ(retry_after_of(status, "Wed, 21 Oct 2026 07:28:00 GMT"), std::nullopt) << status;
    }
}

TEST(RestClient, RetryAfterIsOnlyReadForRateLimitStatuses) {
    EXPECT_EQ(retry_after_of(503, "30"), std::nullopt);
    EXPECT_EQ(retry_after_of(400, "30"), std::nullopt);
}

TEST(RestClient, NonJsonErrorBodyIsUsedAsMessage) {
    expect_status_maps_to<BadRequestError>(400, "plain failure", "plain failure", std::nullopt);
}

TEST(RestClient, ServerErrorIsMapped) {
    MockServer server([](const RecordedRequest&) { return respond(502, "bad gateway"); });
    auto cfg = config_for(server);
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        ADD_FAILURE();
    } catch (const ServerError& e) {
        EXPECT_EQ(e.status_code(), 502);
        EXPECT_STREQ(e.what(), "Internal server error: Server error: 502 (status code: 502)");
    }
}

TEST(RestClient, MalformedJsonFailsOnDecode) {
    MockServer server([](const RecordedRequest&) { return respond(200, "{not json"); });
    RestClient client(config_for(server));
    const RestApiResponse<boost::json::object> res(client.send_request(get("/x")));
    EXPECT_EQ(res.status(), 200);
    EXPECT_THROW((void)res.data(), ConnectorClientError);
}

TEST(RestClient, WrongShapeFailsOnDecode) {
    MockServer server([](const RecordedRequest&) { return respond(200, "[1,2]"); });
    RestClient client(config_for(server));
    const RestApiResponse<boost::json::object> res(client.send_request(get("/x")));
    try {
        (void)res.data();
        ADD_FAILURE();
    } catch (const ConnectorClientError& e) {
        EXPECT_NE(std::string(e.what()).find("Failed to decode response"), std::string::npos);
    }
}

TEST(RestClient, ConnectionRefusedWithZeroRetriesIsNetworkError) {
    RestApiConfig cfg;
    cfg.base_path = closed_url();
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        ADD_FAILURE();
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("HTTP request failed"), std::string::npos) << e.what();
        EXPECT_EQ(e.transport_error(), boost::asio::error::connection_refused);
    }
}

TEST(RestClient, UnresolvableHostCarriesTheResolverError) {
    RestApiConfig cfg;
    cfg.base_path = "http://binance-connector-test.invalid";
    cfg.retries = 0;
    cfg.timeout = 5s;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        ADD_FAILURE() << "expected NetworkError";
    } catch (const NetworkError& e) {
        const auto ec = e.transport_error();
        if (ec != boost::asio::error::host_not_found &&
            ec != boost::asio::error::host_not_found_try_again) {
            GTEST_SKIP() << "no usable resolver: " << ec.message();
        }
    }
}

TEST(RestClient, GetIsRetriedOnServerError) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        return ++calls < 3 ? respond(503, "busy") : respond(200, R"({"ok":1})");
    });
    RestClient client(config_for(server)); // retries = 3
    EXPECT_EQ(client.send_request(get("/x")).body, R"({"ok":1})");
    EXPECT_EQ(server.request_count(), 3U);
}

TEST(RestClient, GetStopsAfterRetriesAreExhausted) {
    MockServer server([](const RecordedRequest&) { return respond(500, "down"); });
    auto cfg = config_for(server);
    cfg.retries = 2;
    RestClient client(std::move(cfg));
    EXPECT_THROW((void)client.send_request(get("/x")), ServerError);
    EXPECT_EQ(server.request_count(), 2U);
}

TEST(RestClient, GetIsRetriedOnNetworkError) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        MockResponse r = respond(200, R"({"ok":1})");
        r.drop = ++calls == 1;
        return r;
    });
    auto cfg = config_for(server);
    cfg.keep_alive = false;
    RestClient client(std::move(cfg));
    EXPECT_EQ(client.send_request(get("/x")).body, R"({"ok":1})");
    EXPECT_EQ(server.request_count(), 2U);
}

TEST(RestClient, PostIsNotRetried) {
    MockServer server([](const RecordedRequest&) { return respond(500, "down"); });
    RestClient client(config_for(server));
    EXPECT_THROW((void)client.send_request({HttpMethod::Post, "/x", {}, {}, {}, false, {}}),
                 ServerError);
    EXPECT_EQ(server.request_count(), 1U);
}

TEST(RestClient, DeleteIsRetriedOnAServerError) {
    MockServer server([](const RecordedRequest&) { return respond(503, "busy"); });
    RestClient client(config_for(server)); // retries = 3
    EXPECT_THROW((void)client.send_request({HttpMethod::Delete, "/order", {}, {}, {}, false, {}}),
                 ServerError);
    EXPECT_EQ(server.request_count(), 3U);
}

TEST(RestClient, DeleteIsRetriedAfterANetworkErrorOnceSent) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.drop = true;
        return r;
    });
    auto cfg = config_for(server);
    cfg.keep_alive = false;
    RestClient client(std::move(cfg)); // retries = 3
    try {
        (void)client.send_request({HttpMethod::Delete, "/order", {}, {}, {}, false, {}});
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_TRUE(e.request_sent());
        const auto ec = e.transport_error();
        EXPECT_TRUE(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset ||
                    ec == boost::beast::http::error::end_of_stream)
            << ec.message();
    }
    EXPECT_EQ(server.request_count(), 3U);
}

TEST(RestClient, DeleteIsRetriedWhenItWasNotSent) {
    RestApiConfig cfg;
    cfg.base_path = closed_url();
    cfg.backoff = 1ms;
    cfg.proxy_from_env = false;
    RestClient client(std::move(cfg)); // retries = 3
    try {
        (void)client.send_request({HttpMethod::Delete, "/order", {}, {}, {}, false, {}});
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_FALSE(e.request_sent());
        EXPECT_NE(std::string(e.what()).find("after 3 attempts"), std::string::npos) << e.what();
    }
}

TEST(RestClient, KeepAliveReusesTheConnection) {
    MockServer server;
    RestClient client(config_for(server));
    for (int i = 0; i < 3; ++i) {
        (void)client.send_request(get("/x"));
    }
    EXPECT_EQ(server.connection_count(), 1U);
}

TEST(RestClient, WrittenPostIsNotReplayedOnAStaleConnection) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        MockResponse r;
        r.drop = ++calls == 2; // read the POST, then close without answering
        return r;
    });
    RestClient client(config_for(server));
    (void)client.send_request(get("/x"));
    try {
        (void)client.send_request({HttpMethod::Post, "/order", {}, {}, {}, false, {}});
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        // It may have been executed: the caller must check before placing it again.
        EXPECT_TRUE(e.request_sent());
    }
    EXPECT_EQ(server.request_count(), 2U);
}

TEST(RestClient, IdleConnectionClosedByTheServerIsNotUsed) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        MockResponse r;
        r.close_after = ++calls == 1;
        return r;
    });
    RestClient client(config_for(server));
    (void)client.send_request(get("/x"));
    std::this_thread::sleep_for(100ms); // let the FIN arrive
    EXPECT_NO_THROW((void)client.send_request({HttpMethod::Post, "/order", {}, {}, {}, false, {}}));
    EXPECT_EQ(server.request_count(), 2U);
    EXPECT_EQ(server.connection_count(), 2U);
}

TEST(RestClient, ServerClosedPooledConnectionIsReplaced) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        MockResponse r;
        r.drop = ++calls == 2; // the second request arrives on the pooled connection
        return r;
    });
    auto cfg = config_for(server);
    cfg.retries = 0; // only the stale-connection retry is allowed
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    EXPECT_NO_THROW((void)client.send_request(get("/x")));
    EXPECT_EQ(server.request_count(), 3U);
}

TEST(RestClient, RequestTimeoutIsRequestTimeoutError) {
    MockServer server([](const RecordedRequest&) {
        std::this_thread::sleep_for(300ms);
        return MockResponse{};
    });
    auto cfg = config_for(server);
    cfg.timeout = 50ms;
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected RequestTimeoutError";
    } catch (const binance::common::RequestTimeoutError& e) {
        EXPECT_TRUE(e.request_sent());
        EXPECT_EQ(e.transport_error(), boost::beast::error::timeout);
    }
}

TEST(RestClient, HugeTimeoutMeansNoDeadline) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(200, R"({"ok":1})");
        r.delay = 100ms;
        return r;
    });
    auto cfg = config_for(server);
    cfg.timeout = std::chrono::milliseconds::max();
    RestClient client(std::move(cfg));
    EXPECT_EQ(client.send_request(get("/x")).body, R"({"ok":1})");
}

TEST(RestClient, UnreachableAddressDoesNotUseTheWholeConnectTimeout) {
    MockServer server;
    const BlackHole hole(boost::asio::ip::make_address("::1"), port_of(server));
    if (!hole.active()) {
        GTEST_SKIP() << "cannot black-hole [::1] here";
    }
    auto cfg = config_for(server);
    cfg.base_path = "http://localhost:" + std::to_string(port_of(server));
    cfg.retries = 0;
    RestClient client(std::move(cfg)); // timeout = 1s
    try {
        EXPECT_EQ(client.send_request(get("/x")).body, "{}");
    } catch (const binance::common::RequestTimeoutError&) {
        throw;
    } catch (const binance::common::NetworkError&) {
        GTEST_SKIP() << "[::1] was not black-holed";
    }
}

TEST(RestClient, LocalhostConnectsWhenOnlyOneFamilyListens) {
    MockServer server; // 127.0.0.1 only; `::1` is refused
    auto cfg = config_for(server);
    cfg.base_path = "http://localhost:" + std::to_string(port_of(server));
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    const auto start = std::chrono::steady_clock::now();
    EXPECT_EQ(client.send_request(get("/x")).body, "{}");
    EXPECT_LT(std::chrono::steady_clock::now() - start, 500ms);
}

// `timeout` bounds the whole attempt, as in the other connectors: a response that keeps arriving
// but takes longer than that times out.
TEST(RestClient, SlowResponseTimesOutAsAWhole) {
    MockServer server([](const RecordedRequest&) {
        return MockResponse{
            .body = std::string(1000, 'x'), .drip_interval = 30ms, .drip_chunks = 10};
    });
    auto cfg = config_for(server);
    cfg.timeout = 100ms;
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    const auto start = std::chrono::steady_clock::now();
    EXPECT_THROW((void)client.send_request(get("/x")), binance::common::RequestTimeoutError);
    EXPECT_LT(std::chrono::steady_clock::now() - start, 250ms);
}

TEST(RestClient, ResponseWithinTheTimeoutSucceeds) {
    MockServer server([](const RecordedRequest&) {
        return MockResponse{
            .body = std::string(1000, 'x'), .drip_interval = 10ms, .drip_chunks = 5};
    });
    auto cfg = config_for(server);
    cfg.timeout = 2s;
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    EXPECT_EQ(client.send_request(get("/x")).body.size(), 1000U);
}

TEST(RestClient, StalledResponseTimesOut) {
    MockServer server([](const RecordedRequest&) {
        return MockResponse{
            .body = std::string(100, 'x'), .drip_interval = 300ms, .drip_chunks = 2};
    });
    auto cfg = config_for(server);
    cfg.timeout = 100ms;
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    EXPECT_THROW((void)client.send_request(get("/x")), binance::common::RequestTimeoutError);
}

TEST(RestClient, GetRequestWithParams) {
    MockServer server;
    RestClient client(config_for(server));
    (void)client.send_request(
        get("/api/v3/depth", {{"symbol", "BTCUSDT"}, {"limit", 5}, {"x", nullptr}}));
    EXPECT_EQ(server.requests().at(0).target, "/api/v3/depth?limit=5&symbol=BTCUSDT");
}

TEST(RestClient, BasePathPrefixIsKept) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.base_path = server.url() + "/sapi-proxy/";
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/api/v3/time"));
    EXPECT_EQ(server.requests().at(0).target, "/sapi-proxy/api/v3/time");
}

TEST(RestClient, SignedGetRequest) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "the-key";
    cfg.api_secret = "the-secret";
    RestClient client(std::move(cfg));
    const auto before = binance::common::detail::timestamp_ms();
    auto req = get("/api/v3/account", {{"omitZeroBalances", true}});
    req.is_signed = true;
    (void)client.send_request(req);

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("x-mbx-apikey"), "the-key");
    const auto query = rec.query();
    const auto sig_pos = query.find("&signature=");
    ASSERT_NE(sig_pos, std::string::npos) << query;
    const auto unsigned_part = query.substr(0, sig_pos);
    EXPECT_TRUE(unsigned_part.starts_with("omitZeroBalances=true&timestamp=")) << query;
    const auto ts = std::stoll(unsigned_part.substr(unsigned_part.find("timestamp=") + 10));
    EXPECT_GE(ts, before);
    EXPECT_LE(ts, binance::common::detail::timestamp_ms());
    EXPECT_EQ(query.substr(sig_pos + 11), hmac_hex("the-secret", unsigned_part));
}

TEST(RestClient, SignedRequestUsesTheTimestampProvider) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "the-key";
    cfg.api_secret = "the-secret";
    cfg.timestamp_provider = [] { return std::int64_t{1700000000123}; };
    RestClient client(std::move(cfg));
    auto req = get("/api/v3/account");
    req.is_signed = true;
    (void)client.send_request(req);

    const auto query = server.requests().at(0).query();
    EXPECT_EQ(query.substr(0, query.find("&signature=")), "timestamp=1700000000123");
    EXPECT_EQ(query.substr(query.find("&signature=") + 11),
              hmac_hex("the-secret", "timestamp=1700000000123"));
}

TEST(RestClient, SignedRetriesAskTheTimestampProviderAgain) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        return ++calls < 3 ? respond(503, "busy") : respond(200, R"({"ok":1})");
    });
    auto cfg = config_for(server);
    cfg.api_secret = "s";
    cfg.backoff = std::chrono::milliseconds{1};
    std::atomic<std::int64_t> now{1700000000000};
    cfg.timestamp_provider = [&now] { return now.fetch_add(7); };
    RestClient client(std::move(cfg));
    auto req = get("/api/v3/account");
    req.is_signed = true;
    (void)client.send_request(req);

    ASSERT_EQ(server.request_count(), 3U);
    for (std::size_t i = 0; i < 3; ++i) {
        const auto query = server.requests().at(i).query();
        const auto unsigned_part = "timestamp=" + std::to_string(1700000000000 + 7 * i);
        EXPECT_EQ(query.substr(0, query.find("&signature=")), unsigned_part);
        EXPECT_EQ(query.substr(query.find("&signature=") + 11), hmac_hex("s", unsigned_part));
    }
}

TEST(RestClient, UnsignedRequestDoesNotAskTheTimestampProvider) {
    MockServer server;
    auto cfg = config_for(server);
    std::atomic<int> asked{0};
    cfg.timestamp_provider = [&asked] {
        ++asked;
        return std::int64_t{1};
    };
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/api/v3/time"));
    EXPECT_EQ(asked.load(), 0);
}

TEST(RestClient, SignedPostRequestWithBody) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "k";
    cfg.api_secret = "s";
    RestClient client(std::move(cfg));
    (void)client.send_request({HttpMethod::Post,
                               "/api/v3/order",
                               {{"symbol", "BTCUSDT"}},
                               {{"note", "hello world"}, {"qty", "0.1"}},
                               {},
                               true,
                               {}});

    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.method, "POST");
    EXPECT_EQ(rec.header("content-type"), "application/x-www-form-urlencoded");
    EXPECT_EQ(rec.body, "note=hello+world&qty=0.1");
    const auto query = rec.query();
    const auto sig_pos = query.find("&signature=");
    ASSERT_NE(sig_pos, std::string::npos);
    EXPECT_EQ(query.substr(sig_pos + 11), hmac_hex("s", query.substr(0, sig_pos) + rec.body));
}

TEST(RestClient, MissingCredentialsOnSignedRequest) {
    MockServer server;
    RestClient client(config_for(server));
    auto req = get("/x");
    req.is_signed = true;
    try {
        (void)client.send_request(req);
        ADD_FAILURE();
    } catch (const ConnectorClientError& e) {
        EXPECT_NE(std::string(e.what()).find("Either 'api_secret' or 'private_key'"),
                  std::string::npos);
    }
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(RestClient, InvalidEndpoint) {
    MockServer server;
    RestClient client(config_for(server));
    EXPECT_THROW((void)client.send_request(get("api/v3/time")), ConnectorClientError);
    EXPECT_THROW((void)client.send_request(get("")), ConnectorClientError);
    for (const char* bad : {"/x\r\nX-Injected: 1", "/x y", "/x?a=1", "/x#frag", "/x\t"}) {
        EXPECT_THROW((void)client.send_request(get(bad)), ConnectorClientError) << bad;
    }
    EXPECT_NO_THROW((void)client.send_request(get("/sapi/v1/sub-account/~list:all@1%20")));
    EXPECT_EQ(server.request_count(), 1U);
}

TEST(RestClient, TimeUnitHeader) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.time_unit = TimeUnit::Microsecond; // only used when the product passes it on
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    auto req = get("/x");
    req.time_unit = TimeUnit::Millisecond;
    (void)client.send_request(req);
    const auto reqs = server.requests();
    EXPECT_FALSE(reqs.at(0).has_header("x-mbx-time-unit"));
    EXPECT_EQ(reqs.at(1).header("x-mbx-time-unit"), "MILLISECOND");
}

TEST(RestClient, CustomHeadersAreSent) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.custom_headers = {{"X-Custom", "abc"}, {" X-Trimmed ", "yes"}};
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("x-custom"), "abc");
    EXPECT_EQ(rec.header("x-trimmed"), "yes");
}

TEST(RestClient, CustomHeadersCannotOverrideSdkHeaders) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "real-key";
    cfg.custom_headers = {{"User-Agent", "evil"},    {"X-MBX-APIKEY", "evil"},
                          {"Content-Type", "evil"},  {"Host", "evil.example"},
                          {"Authorization", "evil"}, {"Cookie", "evil"}};
    RestClient client(std::move(cfg), {.user_agent = "binance-connector-cpp/test"});
    (void)client.send_request(get("/x"));
    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("user-agent"), "binance-connector-cpp/test");
    EXPECT_EQ(rec.header("x-mbx-apikey"), "real-key");
    EXPECT_EQ(rec.header("content-type"), "application/json");
    EXPECT_EQ(rec.header("host"), server.url().substr(7));
    EXPECT_FALSE(rec.has_header("authorization"));
    EXPECT_FALSE(rec.has_header("cookie"));
}

TEST(RestClient, FramingAndCredentialHeadersCannotBeInjected) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.custom_headers = {{"Content-Length", "0"},  {"Transfer-Encoding", "chunked"},
                          {"Connection", "close"},  {"Proxy-Authorization", "evil"},
                          {"Upgrade", "websocket"}, {"x-mbx-apikey", "evil"}};
    RestClient client(std::move(cfg));
    auto req = get("/x");
    req.body = {{"a", "1"}};
    req.method = HttpMethod::Post;
    (void)client.send_request(req);
    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("content-length"), "3");
    EXPECT_FALSE(rec.has_header("transfer-encoding"));
    EXPECT_FALSE(rec.has_header("proxy-authorization"));
    EXPECT_FALSE(rec.has_header("upgrade"));
    EXPECT_FALSE(rec.has_header("x-mbx-apikey"));
    EXPECT_EQ(rec.body, "a=1");
}

TEST(RestClient, ExpectHeaderCannotBeInjected) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.custom_headers = {{"Expect", "100-continue"}};
    RestClient client(std::move(cfg));
    auto req = get("/x");
    req.headers = {{"expect", "100-continue"}};
    (void)client.send_request(req);
    EXPECT_FALSE(server.requests().at(0).has_header("expect"));
}

TEST(RestClient, HeaderAndEndpointCharactersAreAsciiInAnyLocale) {
    MockServer server;
    RestClient client(config_for(server));
    const WideLocale locale;
    if (!locale.active()) {
        GTEST_SKIP() << "no locale with non-ASCII alphanumerics";
    }
    auto req = get("/x");
    req.headers = {{"X-\xE9", "v"}, {"X-Ok", "v"}};
    EXPECT_NO_THROW((void)client.send_request(req));
    ASSERT_EQ(server.request_count(), 1U);
    EXPECT_EQ(server.requests().at(0).headers.count("x-\xE9"), 0U);
    EXPECT_EQ(server.requests().at(0).header("x-ok"), "v");
    EXPECT_THROW((void)client.send_request(get("/\xE9")), ConnectorClientError);
    EXPECT_EQ(server.request_count(), 1U);
}

TEST(RestClient, PerRequestHeadersAreSent) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.custom_headers = {{"X-Config", "c"}};
    RestClient client(std::move(cfg));
    auto req = get("/x");
    req.headers = {{"X-Request", "r"}, {"Host", "evil.example"}};
    (void)client.send_request(req);
    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("x-config"), "c");
    EXPECT_EQ(rec.header("x-request"), "r");
    EXPECT_EQ(rec.header("host"), server.url().substr(7));
}

TEST(RestClient, CrlfInHeaderValuesIsDropped) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.custom_headers = {{"X-Good", "fine"}, {"X-Bad", "a\r\nX-Injected: 1"}, {"Bad Name", "v"}};
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    const auto rec = server.requests().at(0);
    EXPECT_EQ(rec.header("x-good"), "fine");
    EXPECT_FALSE(rec.has_header("x-bad"));
    EXPECT_FALSE(rec.has_header("x-injected"));
}

TEST(RestClient, ApiKeyWithCrlfIsRejected) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "key\r\nX-Injected: 1";
    RestClient client(std::move(cfg));
    EXPECT_THROW((void)client.send_request(get("/x")), ConnectorClientError);
}

TEST(RestClient, RedirectIsAnErrorAndNotFollowed) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(302, "");
        r.headers = {{"Location", "https://elsewhere.example/x"}};
        return r;
    });
    RestClient client(config_for(server));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected ConnectorClientError";
    } catch (const ConnectorClientError& e) {
        EXPECT_NE(std::string(e.what()).find("302"), std::string::npos) << e.what();
        EXPECT_NE(std::string(e.what()).find("elsewhere.example"), std::string::npos) << e.what();
        ASSERT_NE(e.response(), nullptr);
        EXPECT_EQ(e.response()->status, 302);
    }
    EXPECT_EQ(server.request_count(), 1U);
}

TEST(RestClient, ErrorsCarryTheResponse) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(429, R"({"code":-1003,"msg":"Too many requests"})");
        r.headers = {{"Retry-After", "7"}, {"X-MBX-USED-WEIGHT-1M", "6001"}};
        return r;
    });
    RestClient client(config_for(server));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected TooManyRequestsError";
    } catch (const TooManyRequestsError& e) {
        ASSERT_NE(e.response(), nullptr);
        EXPECT_EQ(e.response()->status, 429);
        EXPECT_EQ(e.response()->headers.at("retry-after"), "7");
        ASSERT_TRUE(e.response()->rate_limits);
    }
}

TEST(RestClient, ServerErrorUsesTheBodyMessageAndCode) {
    MockServer server([](const RecordedRequest&) {
        return respond(503, R"({"code":-1008,"msg":"Overloaded"})");
    });
    auto cfg = config_for(server);
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected ServerError";
    } catch (const ServerError& e) {
        EXPECT_EQ(e.status_code(), 503);
        EXPECT_EQ(e.code(), -1008);
        EXPECT_NE(std::string(e.what()).find("Overloaded"), std::string::npos) << e.what();
    }
}

TEST(RestClient, OversizedResponseIsRejected) {
    MockServer server([](const RecordedRequest&) { return respond(200, std::string(4096, 'x')); });
    auto cfg = config_for(server);
    cfg.max_response_size = 1024;
    cfg.retries = 3;
    cfg.backoff = std::chrono::milliseconds(1);
    RestClient client(std::move(cfg));
    EXPECT_THROW((void)client.send_request(get("/x")), ConnectorClientError);
    // An oversized response is not a transient failure, so it is not retried.
    EXPECT_EQ(server.request_count(), 1U);
}

TEST(RestClient, DecompressionBombIsRejected) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(200, gzip(std::string(1024 * 1024, '0')));
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    auto cfg = config_for(server);
    cfg.max_response_size = 64 * 1024; // the compressed body (~1 KiB) fits, the inflated one not
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected ConnectorClientError";
    } catch (const ConnectorClientError& e) {
        EXPECT_NE(std::string(e.what()).find("max_response_size"), std::string::npos) << e.what();
    }
}

TEST(RestClient, EmptyGzipErrorBodyKeepsTheStatus) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(503, "");
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    RestClient client(config_for(server)); // retries = 3
    EXPECT_THROW((void)client.send_request(get("/x")), ServerError);
    EXPECT_EQ(server.request_count(), 3U);
}

TEST(RestClient, EmptyGzipSuccessBodyIsEmpty) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(200, "");
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    RestClient client(config_for(server));
    EXPECT_EQ(client.send_request(get("/x")).body, "");
}

TEST(RestClient, CorruptGzipErrorBodyKeepsTheStatus) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(400, "not gzip");
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    RestClient client(config_for(server));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected BadRequestError";
    } catch (const BadRequestError& e) {
        EXPECT_NE(std::string(e.what()).find("not gzip"), std::string::npos) << e.what();
    }
}

TEST(RestClient, CorruptGzipSuccessBodyIsAnError) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(200, "not gzip");
        r.headers = {{"Content-Encoding", "gzip"}};
        return r;
    });
    RestClient client(config_for(server));
    EXPECT_THROW((void)client.send_request(get("/x")), ConnectorClientError);
}

TEST(RestClient, SignedRetryIsSignedAgain) {
    std::atomic<int> calls{0};
    MockServer server([&](const RecordedRequest&) {
        return ++calls < 2 ? respond(503, "busy") : respond(200, "{}");
    });
    auto cfg = config_for(server);
    cfg.api_key = "k";
    cfg.api_secret = "s";
    cfg.backoff = 20ms;
    RestClient client(std::move(cfg));
    auto req = get("/x");
    req.is_signed = true;
    (void)client.send_request(req);
    const auto reqs = server.requests();
    ASSERT_EQ(reqs.size(), 2U);
    EXPECT_NE(reqs.at(0).query(), reqs.at(1).query()); // fresh timestamp and signature
}

TEST(RestClient, UnreadablePrivateKeyFailsAtConstruction) {
    MockServer server;
    auto cfg = config_for(server);
    cfg.api_key = "k";
    cfg.private_key = PrivateKey::from_file("/nonexistent/binance-test-key.pem");
    EXPECT_THROW(RestClient{cfg}, ConnectorClientError);
}

TEST(RestClient, InvalidConfiguration) {
    RestApiConfig cfg;
    EXPECT_THROW(RestClient{cfg}, ConfigError);
    cfg.base_path = "ftp://example.com";
    EXPECT_THROW(RestClient{cfg}, ConfigError);
    cfg.base_path = "https://example.com";
    cfg.proxy = ProxyConfig{"", 1080, ProxyProtocol::Http, std::nullopt};
    EXPECT_THROW(RestClient{cfg}, ConfigError);
    cfg.proxy.reset();
    cfg.base_path = "https://user:secret-pass@example.com";
    try {
        RestClient client{cfg};
        FAIL() << "expected ConfigError";
    } catch (const ConfigError& e) {
        EXPECT_EQ(std::string(e.what()).find("secret-pass"), std::string::npos) << e.what();
    }
}

namespace {

RestApiConfig trusting_config_for(const MockServer& server) {
    auto cfg = config_for(server);
    cfg.agent = [](boost::asio::ssl::context& ctx) { TestCertificate::get().trust(ctx); };
    return cfg;
}

ProxyConfig proxy_at(const MockProxy& proxy, ProxyProtocol protocol) {
    return ProxyConfig{"127.0.0.1", proxy.port(), protocol, ProxyAuth{"user", "pa:ss"}};
}

constexpr const char* kProxyAuthorization = "Basic dXNlcjpwYTpzcw=="; // user:pa:ss

} // namespace

TEST(RestClient, HttpsTargetIsVerified) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"ok":true})"); },
                      TestCertificate::get().server_context());
    RestClient client(trusting_config_for(server));
    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"ok":true})");
    EXPECT_EQ(server.requests().at(0).header("host"), server.url().substr(8));
}

TEST(RestClient, UntrustedCertificateIsRejected) {
    MockServer server({}, TestCertificate::get().server_context());
    auto cfg = config_for(server);
    cfg.retries = 0;
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("TLS handshake"), std::string::npos) << e.what();
    }
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(RestClient, CertificateForAnotherHostIsRejected) {
    const auto& other = TestCertificate::for_other_host();
    MockServer server({}, other.server_context());
    auto cfg = config_for(server);
    cfg.retries = 0;
    cfg.agent = [&other](boost::asio::ssl::context& ctx) { other.trust(ctx); };
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("TLS handshake"), std::string::npos) << e.what();
    }
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(RestClient, AgentVerifyCallbackCanRejectATrustedCertificate) {
    // Certificate pinning through `agent`: the hook's verify callback runs alongside the host
    // name check.
    MockServer server({}, TestCertificate::get().server_context());
    auto cfg = config_for(server);
    cfg.retries = 0;
    std::atomic<int> calls = 0;
    cfg.agent = [&calls](boost::asio::ssl::context& ctx) {
        TestCertificate::get().trust(ctx);
        ctx.set_verify_callback([&calls](bool, boost::asio::ssl::verify_context&) {
            ++calls;
            return false;
        });
    };
    RestClient client(std::move(cfg));
    EXPECT_THROW((void)client.send_request(get("/x")), NetworkError);
    EXPECT_GT(calls.load(), 0);
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(RestClient, HttpProxyForwardsHttpTargetInAbsoluteForm) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"via":"proxy"})"); });
    MockProxy proxy;
    auto cfg = config_for(server);
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Http);
    RestClient client(std::move(cfg));

    EXPECT_EQ(client.send_request(get("/api/v3/time", {{"a", "1"}})).body, R"({"via":"proxy"})");
    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"via":"proxy"})");

    const auto seen = proxy.requests();
    ASSERT_EQ(seen.size(), 2U);
    EXPECT_EQ(seen[0].method, "GET");
    EXPECT_EQ(seen[0].target, server.url() + "/api/v3/time?a=1");
    EXPECT_EQ(seen[0].proxy_authorization, kProxyAuthorization);
    EXPECT_EQ(server.requests().at(0).target, "/api/v3/time?a=1");
    EXPECT_FALSE(server.requests().at(0).has_header("proxy-authorization"));
    EXPECT_EQ(server.connection_count(), 1U);
}

TEST(RestClient, HttpProxyTunnelsHttpsTarget) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"tunnel":1})"); },
                      TestCertificate::get().server_context());
    MockProxy proxy;
    auto cfg = trusting_config_for(server);
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Http);
    RestClient client(std::move(cfg));

    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"tunnel":1})");
    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"tunnel":1})");

    const auto seen = proxy.requests();
    ASSERT_EQ(seen.size(), 1U); // one tunnel, kept alive
    EXPECT_EQ(seen[0].method, "CONNECT");
    EXPECT_EQ(seen[0].target, server.url().substr(8));
    EXPECT_EQ(seen[0].proxy_authorization, kProxyAuthorization);
    EXPECT_EQ(server.request_count(), 2U);
    EXPECT_FALSE(server.requests().at(0).has_header("proxy-authorization"));
}

TEST(RestClient, HttpsProxyForwardsHttpTarget) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"p":"tls"})"); });
    MockProxy proxy(TestCertificate::get().server_context());
    auto cfg = trusting_config_for(server);
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Https);
    RestClient client(std::move(cfg));

    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"p":"tls"})");
    const auto seen = proxy.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_EQ(seen[0].target, server.url() + "/api/v3/time");
    EXPECT_EQ(seen[0].proxy_authorization, kProxyAuthorization);
}

TEST(RestClient, HttpsProxyTunnelsHttpsTargetWithNestedTls) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"nested":true})"); },
                      TestCertificate::get().server_context());
    MockProxy proxy(TestCertificate::get().server_context());
    auto cfg = trusting_config_for(server);
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Https);
    RestClient client(std::move(cfg));

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(client.send_request(get("/api/v3/time")).body, R"({"nested":true})");
    }
    const auto seen = proxy.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_EQ(seen[0].method, "CONNECT");
    EXPECT_EQ(server.request_count(), 3U);
    EXPECT_EQ(server.connection_count(), 1U);
}

TEST(RestClient, HttpsProxyWithUntrustedCertificateIsRejected) {
    MockServer server;
    MockProxy proxy(TestCertificate::get().server_context());
    auto cfg = config_for(server);
    cfg.retries = 0;
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Https);
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("proxy TLS handshake"), std::string::npos) << e.what();
    }
    EXPECT_TRUE(proxy.requests().empty());
}

TEST(RestClient, ProxyRefusingConnectIsNetworkError) {
    MockServer server({}, TestCertificate::get().server_context());
    MockProxy proxy(nullptr, 407);
    auto cfg = trusting_config_for(server);
    cfg.retries = 0;
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Http);
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("407"), std::string::npos) << e.what();
    }
}

TEST(RestClient, AsyncCallbackAndFuture) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"n":7})"); });
    RestClient client(config_for(server));

    std::promise<std::string> done;
    client.async_send_request(get("/x"), [&](std::exception_ptr ep, RawResponse res) {
        if (ep) {
            done.set_exception(ep);
        } else {
            done.set_value(res.body);
        }
    });
    EXPECT_EQ(done.get_future().get(), R"({"n":7})");

    auto fut = client.async_send_request(get("/x"), boost::asio::use_future);
    EXPECT_EQ(fut.get().body, R"({"n":7})");
}

TEST(RestClient, AsyncErrorsArriveAsExceptionPtr) {
    MockServer server(
        [](const RecordedRequest&) { return respond(404, R"({"code":-1,"msg":"no"})"); });
    RestClient client(config_for(server));
    auto fut = client.async_send_request(get("/x"), boost::asio::use_future);
    EXPECT_THROW((void)fut.get(), NotFoundError);
}

TEST(RestClient, HandlerRunsOnItsAssociatedExecutor) {
    MockServer server;
    RestClient client(config_for(server));
    boost::asio::io_context user_ioc;
    std::thread::id handler_thread;
    client.async_send_request(
        get("/x"), boost::asio::bind_executor(user_ioc, [&](std::exception_ptr, RawResponse) {
            handler_thread = std::this_thread::get_id();
        }));
    user_ioc.run(); // the tracked work keeps run() alive until the handler is done
    EXPECT_EQ(handler_thread, std::this_thread::get_id());
}

TEST(RestClient, AwaitableFromAnotherIoContext) {
    MockServer server([](const RecordedRequest&) { return respond(200, "{}"); });
    RestClient client(config_for(server));
    boost::asio::io_context user_ioc;
    std::uint16_t status = 0;
    boost::asio::co_spawn(
        user_ioc,
        [&]() -> boost::asio::awaitable<void> {
            const auto res =
                co_await client.async_send_request(get("/x"), boost::asio::use_awaitable);
            status = res.status;
        },
        boost::asio::detached);
    user_ioc.run();
    EXPECT_EQ(status, 200);
}

TEST(RestClient, ConcurrentRequests) {
    MockServer server;
    RestClient client(config_for(server));
    std::vector<std::future<RawResponse>> futures;
    for (int i = 0; i < 20; ++i) {
        futures.push_back(client.async_send_request(get("/x"), boost::asio::use_future));
    }
    for (auto& f : futures) {
        EXPECT_EQ(f.get().status, 200);
    }
    EXPECT_EQ(server.request_count(), 20U);
}

TEST(RestClient, ProxyFromTheEnvironmentIsUsed) {
    MockServer server([](const RecordedRequest&) { return respond(200, R"({"via":"env"})"); });
    MockProxy proxy;
    const binance::test::ScopedEnv http_proxy("http_proxy", "http://user:pa%3Ass@127.0.0.1:" +
                                                                std::to_string(proxy.port()));
    const binance::test::ScopedEnv no_proxy("no_proxy", std::nullopt);
    const binance::test::ScopedEnv upper_no_proxy("NO_PROXY", std::nullopt);
    const binance::test::ScopedEnv request_method("REQUEST_METHOD", std::nullopt);
    auto cfg = config_for(server);
    cfg.proxy_from_env = true;
    RestClient client(std::move(cfg));
    EXPECT_EQ(client.send_request(get("/x")).body, R"({"via":"env"})");
    ASSERT_EQ(proxy.requests().size(), 1U);
    EXPECT_EQ(proxy.requests().at(0).proxy_authorization, kProxyAuthorization);
}

TEST(RestClient, PerOperationCancellation) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.delay = 2s;
        return r;
    });
    RestClient client(config_for(server));
    boost::asio::cancellation_signal signal;
    auto fut = client.async_send_request(
        get("/x"), boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    std::this_thread::sleep_for(200ms);
    const auto started = std::chrono::steady_clock::now();
    signal.emit(boost::asio::cancellation_type::terminal);
    try {
        (void)fut.get();
        FAIL() << "expected RequestCancelledError";
    } catch (const RequestCancelledError& e) {
        EXPECT_TRUE(e.request_sent());
        EXPECT_EQ(e.transport_error(), boost::asio::error::operation_aborted);
    }
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
}

TEST(RestClient, PartialCancellationAfterSending) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.delay = 2s;
        return r;
    });
    RestClient client(config_for(server));
    boost::asio::cancellation_signal signal;
    auto fut = client.async_send_request(
        get("/x"), boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    std::this_thread::sleep_for(200ms);
    const auto started = std::chrono::steady_clock::now();
    signal.emit(boost::asio::cancellation_type::partial);
    try {
        (void)fut.get();
        FAIL() << "expected RequestCancelledError";
    } catch (const RequestCancelledError& e) {
        EXPECT_TRUE(e.request_sent());
    }
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
}

TEST(RestClient, TotalCancellationBeforeSending) {
    // Accepts the TCP connection but never answers the TLS handshake.
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::acceptor acceptor(ioc, {boost::asio::ip::make_address("127.0.0.1"), 0});
    RestApiConfig cfg;
    cfg.base_path = "https://127.0.0.1:" + std::to_string(acceptor.local_endpoint().port());
    cfg.timeout = 5s;
    cfg.retries = 0;
    cfg.proxy_from_env = false;
    RestClient client(std::move(cfg));
    boost::asio::cancellation_signal signal;
    auto fut = client.async_send_request(
        get("/x"), boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    std::this_thread::sleep_for(200ms);
    const auto started = std::chrono::steady_clock::now();
    signal.emit(boost::asio::cancellation_type::total);
    try {
        (void)fut.get();
        FAIL() << "expected RequestCancelledError";
    } catch (const RequestCancelledError& e) {
        EXPECT_FALSE(e.request_sent());
    }
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
}

TEST(RestClient, TotalCancellationAfterSendingIsIgnored) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r = respond(200, R"({"ok":1})");
        r.delay = 300ms;
        return r;
    });
    RestClient client(config_for(server));
    boost::asio::cancellation_signal signal;
    auto fut = client.async_send_request(
        get("/x"), boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    std::this_thread::sleep_for(100ms);
    ASSERT_EQ(server.request_count(), 1U);
    signal.emit(boost::asio::cancellation_type::total);
    EXPECT_EQ(fut.get().body, R"({"ok":1})");
}

TEST(RestClient, CancelAfterWithAwaitable) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.delay = 2s;
        return r;
    });
    RestClient client(config_for(server));
    boost::asio::io_context user_ioc;
    boost::asio::steady_timer timer(user_ioc);
    bool cancelled = false;
    boost::asio::co_spawn(
        user_ioc,
        [&]() -> boost::asio::awaitable<void> {
            try {
                (void)co_await client.async_send_request(
                    get("/x"), boost::asio::cancel_after(timer, 100ms, boost::asio::use_awaitable));
            } catch (const RequestCancelledError&) {
                cancelled = true;
            }
        },
        boost::asio::detached);
    const auto started = std::chrono::steady_clock::now();
    user_ioc.run();
    EXPECT_TRUE(cancelled);
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
}

TEST(RestClient, DestructionCompletesInFlightRequests) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.delay = 2s;
        return r;
    });
    std::future<RawResponse> fut;
    const auto started = std::chrono::steady_clock::now();
    {
        RestClient client(config_for(server));
        fut = client.async_send_request(get("/x"), boost::asio::use_future);
        std::this_thread::sleep_for(100ms);
    }
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
    ASSERT_EQ(fut.wait_for(0s), std::future_status::ready);
    EXPECT_THROW((void)fut.get(), RequestCancelledError);
}

TEST(RestClient, ClientsShareAnExternalExecutor) {
    MockServer server([](const RecordedRequest& r) { return respond(200, r.target); });
    boost::asio::io_context ioc;
    auto cfg = config_for(server);
    cfg.executor = ioc.get_executor();
    RestClient a(cfg);
    RestClient b(cfg);
    std::vector<std::string> bodies;
    boost::asio::co_spawn(
        ioc,
        [&]() -> boost::asio::awaitable<void> {
            bodies.push_back(
                (co_await a.async_send_request(get("/a"), boost::asio::use_awaitable)).body);
            bodies.push_back(
                (co_await b.async_send_request(get("/b"), boost::asio::use_awaitable)).body);
        },
        boost::asio::detached);
    ioc.run(); // returns once nothing is pending: the clients add no work of their own
    EXPECT_EQ(bodies, (std::vector<std::string>{"/a", "/b"}));
}

TEST(RestClient, SharedExecutorRunByManyThreads) {
    MockServer server;
    boost::asio::io_context ioc;
    auto guard = boost::asio::make_work_guard(ioc);
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([&ioc] { ioc.run(); });
    }
    {
        auto cfg = config_for(server);
        cfg.executor = ioc.get_executor();
        RestClient a(cfg);
        RestClient b(cfg);
        std::vector<std::future<RawResponse>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.push_back(a.async_send_request(get("/x"), boost::asio::use_future));
            futures.push_back(b.async_send_request(get("/x"), boost::asio::use_future));
        }
        for (auto& f : futures) {
            EXPECT_EQ(f.get().status, 200);
        }
        EXPECT_EQ(a.send_request(get("/x")).status, 200);
    }
    guard.reset();
    for (auto& t : threads) {
        t.join();
    }
    EXPECT_EQ(server.request_count(), 21U);
}

TEST(RestClient, SharedExecutorDestructionCancelsInFlightRequests) {
    MockServer server([](const RecordedRequest&) {
        MockResponse r;
        r.delay = 2s;
        return r;
    });
    boost::asio::io_context ioc;
    std::exception_ptr error;
    auto cfg = config_for(server);
    cfg.executor = ioc.get_executor();
    auto client = std::make_unique<RestClient>(cfg);
    client->async_send_request(get("/x"), [&](std::exception_ptr ep, RawResponse) { error = ep; });
    boost::asio::steady_timer timer(ioc, 100ms);
    timer.async_wait([&](const boost::system::error_code&) { client.reset(); });
    const auto started = std::chrono::steady_clock::now();
    ioc.run();
    EXPECT_LT(std::chrono::steady_clock::now() - started, 1s);
    EXPECT_FALSE(client);
    EXPECT_THROW(std::rethrow_exception(error), RequestCancelledError);
}

TEST(RestClient, BlockingCallOnTheSharedExecutorThrows) {
    MockServer server;
    boost::asio::io_context ioc;
    auto cfg = config_for(server);
    cfg.executor = ioc.get_executor();
    RestClient client(cfg);
    bool threw = false;
    client.async_send_request(get("/x"), [&](std::exception_ptr, RawResponse) {
        try {
            (void)client.send_request(get("/x"));
        } catch (const ConnectorClientError&) {
            threw = true;
        }
    });
    ioc.run();
    EXPECT_TRUE(threw);
}

TEST(RestClient, ClientCanBeDestroyedFromItsOwnHandler) {
    MockServer server;
    auto client = std::make_unique<RestClient>(config_for(server));
    std::promise<void> done;
    client->async_send_request(get("/x"), [&](std::exception_ptr, RawResponse) {
        client.reset();
        done.set_value();
    });
    EXPECT_EQ(done.get_future().wait_for(5s), std::future_status::ready);
}

TEST(RestClient, ThrowingHandlerDoesNotStopTheClient) {
    MockServer server;
    RestClient client(config_for(server));
    std::promise<void> thrown;
    client.async_send_request(get("/x"), [&](std::exception_ptr, RawResponse) {
        thrown.set_value();
        throw std::runtime_error("user bug");
    });
    thrown.get_future().wait();
    EXPECT_EQ(client.send_request(get("/x")).status, 200);
}
