//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// Behaviour tests for `WebsocketApi` and `WebsocketStreams` against a local WebSocket server.

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <regex>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/beast/websocket/error.hpp>
#include <boost/json.hpp>
#include <gtest/gtest.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/signer.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/common/websocket_streams.hpp>

#include "../src/testing.hpp"
#include "support/certs.hpp"
#include "support/keys.hpp"
#include "support/mock_proxy.hpp"
#include "support/mock_ws_server.hpp"
#include "utils.hpp"

using namespace std::chrono_literals;
using binance::common::ConfigError;
using binance::common::ProxyAuth;
using binance::common::ProxyConfig;
using binance::common::ProxyProtocol;
using binance::common::StreamId;
using binance::common::TimeUnit;
using binance::common::WebsocketApi;
using binance::common::WebsocketApiConfig;
using binance::common::WebsocketCancelledError;
using binance::common::WebsocketConnectionFailureReason;
using binance::common::WebsocketError;
using binance::common::WebsocketEvent;
using binance::common::WebsocketEventType;
using binance::common::WebsocketHandshakeError;
using binance::common::WebsocketMessageSendOptions;
using binance::common::WebsocketMode;
using binance::common::WebsocketNetworkError;
using binance::common::WebsocketNoResponseError;
using binance::common::WebsocketNotConnectedError;
using binance::common::WebsocketResponseError;
using binance::common::WebsocketStream;
using binance::common::WebsocketStreamHandle;
using binance::common::WebsocketStreams;
using binance::common::WebsocketStreamsConfig;
using binance::common::WebsocketTimeoutError;
using binance::test::MockProxy;
using binance::test::MockWsServer;
using binance::test::TestCertificate;
namespace json = boost::json;
namespace asio = boost::asio;

namespace {

using Sessions = std::vector<MockWsServer::SessionInfo>;

/// Polls `pred` until it holds or `timeout` passes.
template <class Pred> bool eventually(Pred pred, std::chrono::milliseconds timeout = 5s) {
    const auto deadline = std::chrono::steady_clock::now() + timeout;
    while (std::chrono::steady_clock::now() < deadline) {
        if (pred()) {
            return true;
        }
        std::this_thread::sleep_for(5ms);
    }
    return pred();
}

/// Records events from `on_event`.
class EventLog {
public:
    void operator()(const WebsocketEvent& e) {
        const std::lock_guard lock(mutex_);
        events_.push_back(e);
    }
    [[nodiscard]] std::vector<WebsocketEvent> events() const {
        const std::lock_guard lock(mutex_);
        return events_;
    }
    [[nodiscard]] std::size_t count(WebsocketEventType type) const {
        const std::lock_guard lock(mutex_);
        return static_cast<std::size_t>(std::count_if(
            events_.begin(), events_.end(), [type](const auto& e) { return e.type == type; }));
    }
    [[nodiscard]] bool has_error_containing(const std::string& text) const {
        const std::lock_guard lock(mutex_);
        return std::any_of(events_.begin(), events_.end(), [&](const auto& e) {
            return e.type == WebsocketEventType::Error && e.data.find(text) != std::string::npos;
        });
    }
    [[nodiscard]] std::optional<WebsocketEvent> last(WebsocketEventType type) const {
        const std::lock_guard lock(mutex_);
        for (auto it = events_.rbegin(); it != events_.rend(); ++it) {
            if (it->type == type) {
                return *it;
            }
        }
        return std::nullopt;
    }

private:
    mutable std::mutex mutex_;
    std::vector<WebsocketEvent> events_;
};

json::object parse(const std::string& text) {
    return json::parse(text).as_object();
}

std::string id_of(const std::string& request) {
    return std::string(parse(request).at("id").as_string());
}

/// Answers every request with `{"id", "status": 200, "result": {"echo": method}, "rateLimits"}`.
void echo(MockWsServer::Session& s, const std::string& text) {
    const auto req = parse(text);
    json::object res;
    res["id"] = req.at("id");
    res["status"] = 200;
    res["result"] = json::object{{"echo", req.at("method")}};
    res["rateLimits"] = json::array{json::object{{"rateLimitType", "REQUEST_WEIGHT"},
                                                 {"interval", "MINUTE"},
                                                 {"intervalNum", 1},
                                                 {"limit", 6000},
                                                 {"count", 2}}};
    s.send(json::serialize(res));
}

WebsocketApiConfig api_config(const std::string& url) {
    WebsocketApiConfig cfg;
    cfg.url = url;
    cfg.api_key = "api-key";
    cfg.api_secret = "api-secret";
    cfg.timeout = 2000ms;
    cfg.reconnect_delay = 100ms;
    cfg.connect_timeout = 2000ms;
    cfg.proxy_from_env = false;
    return cfg;
}

WebsocketStreamsConfig streams_config(const std::string& url) {
    WebsocketStreamsConfig cfg;
    cfg.url = url;
    cfg.reconnect_delay = 100ms;
    cfg.connect_timeout = 2000ms;
    cfg.proxy_from_env = false;
    return cfg;
}

/// A port with nothing listening on it.
std::uint16_t closed_port() {
    asio::io_context ioc;
    asio::ip::tcp::acceptor acceptor(ioc, {asio::ip::make_address("127.0.0.1"), 0});
    return acceptor.local_endpoint().port();
}

WebsocketMessageSendOptions signed_opts() {
    WebsocketMessageSendOptions o;
    o.is_signed = true;
    return o;
}

WebsocketMessageSendOptions logon_opts() {
    WebsocketMessageSendOptions o;
    o.is_signed = true;
    o.is_session_logon = true;
    return o;
}

WebsocketMessageSendOptions logout_opts() {
    WebsocketMessageSendOptions o;
    o.is_session_logout = true;
    return o;
}

std::vector<std::string> requests_with_method(const Sessions& sessions, const std::string& method) {
    std::vector<std::string> out;
    for (const auto& s : sessions) {
        for (const auto& r : s.received) {
            if (parse(r).at("method") == json::value(method)) {
                out.push_back(r);
            }
        }
    }
    return out;
}

} // namespace

// ==== Failure reasons ====

TEST(WebsocketFailureReason, ClassifiesStandardCloseCodes) {
    using R = WebsocketConnectionFailureReason;
    const std::vector<std::pair<std::uint16_t, R>> cases = {
        {1000, R::NormalClose},          {1001, R::ServerTemporaryError},
        {1002, R::ProtocolViolation},    {1003, R::ProtocolViolation},
        {1006, R::UnexpectedClose},      {1007, R::ProtocolViolation},
        {1008, R::PermanentServerError}, {1009, R::ProtocolViolation},
        {1010, R::ProtocolViolation},    {1011, R::ServerTemporaryError},
        {1012, R::ServerTemporaryError}, {1013, R::ServerTemporaryError},
        {1014, R::ServerTemporaryError}, {1015, R::ConfigurationError},
        {4000, R::PermanentServerError}, {4999, R::PermanentServerError},
        {3000, R::UnexpectedClose},      {5000, R::UnexpectedClose},
    };
    for (const auto& [code, reason] : cases) {
        EXPECT_EQ(binance::common::detail::failure_reason_from_close_code(code, false), reason)
            << code;
    }
}

TEST(WebsocketFailureReason, UserInitiatedWinsOverCode) {
    for (const std::uint16_t code :
         std::initializer_list<std::uint16_t>{1000, 1001, 1006, 1008, 4001}) {
        EXPECT_EQ(binance::common::detail::failure_reason_from_close_code(code, true),
                  WebsocketConnectionFailureReason::UserInitiatedClose);
    }
}

TEST(WebsocketFailureReason, ClassifiesTransportErrors) {
    using R = WebsocketConnectionFailureReason;
    using binance::common::detail::failure_reason_from_error;
    namespace ws = boost::beast::websocket;
    EXPECT_EQ(failure_reason_from_error(asio::error::connection_reset), R::ConnectionReset);
    EXPECT_EQ(failure_reason_from_error(asio::error::connection_aborted), R::ConnectionReset);
    EXPECT_EQ(failure_reason_from_error(asio::error::broken_pipe), R::ConnectionReset);
    EXPECT_EQ(failure_reason_from_error(ws::error::closed), R::ConnectionReset);
    EXPECT_EQ(failure_reason_from_error(asio::error::eof), R::StreamEnded);
    EXPECT_EQ(failure_reason_from_error(asio::ssl::error::stream_truncated), R::StreamEnded);
    EXPECT_EQ(failure_reason_from_error(asio::error::access_denied), R::AuthenticationFailure);
    EXPECT_EQ(failure_reason_from_error(ws::error::message_too_big), R::ConfigurationError);
    const auto ssl_error = [](int lib, int reason) {
        return boost::system::error_code(static_cast<int>(ERR_PACK(lib, 0, reason)),
                                         asio::error::get_ssl_category());
    };
    EXPECT_EQ(failure_reason_from_error(ssl_error(ERR_LIB_SSL, SSL_R_CERTIFICATE_VERIFY_FAILED)),
              R::ConfigurationError);
    EXPECT_EQ(failure_reason_from_error(ssl_error(ERR_LIB_SSL, SSL_R_UNSUPPORTED_PROTOCOL)),
              R::ConfigurationError);
    // Other TLS errors in the middle of a connection are transient.
    EXPECT_EQ(failure_reason_from_error(
                  ssl_error(ERR_LIB_SSL, SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC)),
              R::NetworkInterruption);
    EXPECT_EQ(
        failure_reason_from_error(boost::system::error_code(1, asio::error::get_ssl_category())),
        R::NetworkInterruption);
    EXPECT_EQ(failure_reason_from_error(asio::ssl::error::unexpected_result),
              R::NetworkInterruption);
    EXPECT_EQ(failure_reason_from_error(ws::error::bad_opcode), R::ProtocolViolation);
    EXPECT_EQ(failure_reason_from_error(asio::error::timed_out), R::NetworkInterruption);
    EXPECT_EQ(failure_reason_from_error(asio::error::host_unreachable), R::NetworkInterruption);
}

TEST(WebsocketFailureReason, ShouldReconnect) {
    using R = WebsocketConnectionFailureReason;
    for (const auto r :
         {R::NetworkInterruption, R::ConnectionReset, R::ServerTemporaryError, R::UnexpectedClose,
          R::StreamEnded, R::ProtocolViolation, R::NormalClose}) {
        EXPECT_TRUE(binance::common::detail::should_reconnect(r)) << binance::common::to_string(r);
    }
    for (const auto r : {R::AuthenticationFailure, R::ConfigurationError, R::UserInitiatedClose,
                         R::PermanentServerError}) {
        EXPECT_FALSE(binance::common::detail::should_reconnect(r)) << binance::common::to_string(r);
    }
}

TEST(WebsocketFailureReason, ToString) {
    EXPECT_EQ(binance::common::to_string(WebsocketConnectionFailureReason::PermanentServerError),
              "PermanentServerError");
    EXPECT_EQ(binance::common::to_string(WebsocketConnectionFailureReason::NormalClose),
              "NormalClose");
}

// ==== WebsocketApi: construction and connecting ====

TEST(WebsocketApi, MissingWsUrlThrows) {
    WebsocketApiConfig cfg;
    EXPECT_THROW(WebsocketApi{cfg}, ConfigError);
    cfg.url = "";
    EXPECT_THROW(WebsocketApi{cfg}, ConfigError);
}

TEST(WebsocketApi, InvalidWsUrlThrows) {
    EXPECT_THROW(WebsocketApi{api_config("http://127.0.0.1:1")}, ConfigError);
    EXPECT_THROW(WebsocketApi{api_config("not a url")}, ConfigError);
}

TEST(WebsocketApi, ConnectSingleOpensOneConnection) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    EXPECT_FALSE(api.is_connected());
    api.connect();
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(server.session_count(), 1U);
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Open) == 1; }));
    const auto s = server.sessions().front();
    EXPECT_EQ(s.target, "/");
    EXPECT_EQ(s.user_agent, binance::common::detail::build_user_agent("common"));
    EXPECT_TRUE(s.deflate);
}

TEST(WebsocketApi, ConnectPoolOpensEveryConnection) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(3);
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(server.session_count(), 3U);
}

TEST(WebsocketApi, ConnectsToLocalhostWhenOnlyOneFamilyListens) {
    MockWsServer server(echo); // 127.0.0.1 only; `::1` is refused
    auto url = server.url();
    url.replace(url.find("127.0.0.1"), 9, "localhost");
    WebsocketApi api(api_config(url));
    api.connect();
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(server.session_count(), 1U);
}

TEST(WebsocketApi, ConnectWhenConnectedIsNoop) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    api.connect();
    EXPECT_EQ(server.session_count(), 1U);
}

TEST(WebsocketApi, ConcurrentConnectsShareTheAttempt) {
    MockWsServer::Options opts;
    opts.accept_delay = 100ms;
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    auto a = api.async_connect(asio::use_future);
    auto b = api.async_connect(asio::use_future);
    EXPECT_NO_THROW(a.get());
    EXPECT_NO_THROW(b.get());
    EXPECT_EQ(server.session_count(), 1U);
}

namespace {

// Windows reports a refused connection only after retrying for about 2 s.
WebsocketApiConfig refused_config() {
    auto cfg = api_config("ws://127.0.0.1:" + std::to_string(closed_port()));
    cfg.connect_timeout = 10s;
    return cfg;
}

} // namespace

TEST(WebsocketApi, ConnectionRefusedFails) {
    WebsocketApi api(refused_config());
    EXPECT_THROW(api.connect(), WebsocketNetworkError);
    EXPECT_FALSE(api.is_connected());
}

TEST(WebsocketApi, ConnectionRefusedCarriesTheTransportError) {
    WebsocketApi api(refused_config());
    try {
        api.connect();
        FAIL() << "expected WebsocketNetworkError";
    } catch (const WebsocketNetworkError& e) {
        EXPECT_EQ(e.transport_error(), boost::asio::error::connection_refused);
    }
}

TEST(WebsocketApi, NetworkErrorsHaveNoSourceLocation) {
    WebsocketApi api(refused_config());
    try {
        api.connect();
        FAIL() << "expected WebsocketNetworkError";
    } catch (const WebsocketNetworkError& e) {
        EXPECT_EQ(std::string(e.what()).find(" ["), std::string::npos) << e.what();
    }
}

TEST(WebsocketApi, RejectedUpgradeFailsWithHandshakeError) {
    MockWsServer::Options opts;
    opts.reject_status = 403;
    opts.reject_body = "forbidden";
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    try {
        api.connect();
        FAIL() << "expected WebsocketHandshakeError";
    } catch (const WebsocketHandshakeError& e) {
        EXPECT_NE(std::string(e.what()).find("HTTP 403"), std::string::npos) << e.what();
        EXPECT_NE(std::string(e.what()).find("forbidden"), std::string::npos) << e.what();
    }
}

TEST(WebsocketApi, SlowUpgradeTimesOut) {
    MockWsServer::Options opts;
    opts.accept_delay = 1s;
    MockWsServer server(echo, opts);
    auto cfg = api_config(server.url());
    cfg.connect_timeout = 200ms;
    WebsocketApi api(cfg);
    EXPECT_THROW(api.connect(), WebsocketTimeoutError);
}

TEST(WebsocketApi, PoolFailureIsPropagated) {
    MockWsServer::Options opts;
    opts.reject_status = 500;
    MockWsServer server(echo, opts);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    EXPECT_THROW(api.connect(), WebsocketHandshakeError);
}

TEST(WebsocketApi, TimeUnitIsAddedToTheUrl) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url() + "/ws-api/v3");
    cfg.time_unit = TimeUnit::Microsecond;
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(server.sessions().front().target, "/ws-api/v3?timeUnit=microsecond");
}

TEST(WebsocketApi, TimeUnitIsAppendedToAnExistingQuery) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url() + "/ws-api/v3?returnRateLimits=false");
    cfg.time_unit = TimeUnit::Millisecond;
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(server.sessions().front().target,
              "/ws-api/v3?returnRateLimits=false&timeUnit=millisecond");
}

TEST(WebsocketApi, CompressionCanBeDisabled) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.compression = false;
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_FALSE(server.sessions().front().deflate);
}

TEST(WebsocketApi, ConnectsOverTls) {
    MockWsServer::Options opts;
    opts.tls = TestCertificate::get().server_context();
    MockWsServer server(echo, opts);
    auto cfg = api_config(server.url());
    cfg.agent = [](asio::ssl::context& ctx) { TestCertificate::get().trust(ctx); };
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(api.send_message("ping", {}).front().result, json::parse(R"({"echo":"ping"})"));
}

TEST(WebsocketApi, AgentVerifyCallbackCanPinCertificates) {
    MockWsServer::Options opts;
    opts.tls = TestCertificate::get().server_context();
    MockWsServer server(echo, opts);
    auto cfg = api_config(server.url());
    std::atomic<int> calls{0};
    cfg.agent = [&calls](asio::ssl::context& ctx) {
        TestCertificate::get().trust(ctx);
        ctx.set_verify_callback([&calls](bool, asio::ssl::verify_context&) {
            ++calls;
            return false;
        });
    };
    WebsocketApi api(cfg);
    EXPECT_THROW(api.connect(), WebsocketNetworkError);
    EXPECT_GT(calls.load(), 0);
    EXPECT_EQ(server.session_count(), 0U);
}

TEST(WebsocketApi, TlsWithUntrustedCertificateFails) {
    MockWsServer::Options opts;
    opts.tls = TestCertificate::get().server_context();
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    EXPECT_THROW(api.connect(), WebsocketNetworkError);
}

namespace {

ProxyConfig proxy_at(const MockProxy& proxy, ProxyProtocol protocol) {
    return ProxyConfig{"127.0.0.1", proxy.port(), protocol, ProxyAuth{"user", "pa:ss"}};
}

void expect_proxied_roundtrip(bool tls_target, bool tls_proxy) {
    MockWsServer::Options opts;
    if (tls_target) {
        opts.tls = TestCertificate::get().server_context();
    }
    MockWsServer server(echo, opts);
    MockProxy proxy(tls_proxy ? TestCertificate::get().server_context() : nullptr);
    auto cfg = api_config(server.url());
    cfg.proxy = proxy_at(proxy, tls_proxy ? ProxyProtocol::Https : ProxyProtocol::Http);
    cfg.agent = [](asio::ssl::context& ctx) { TestCertificate::get().trust(ctx); };
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(api.send_message("ping", {}).front().result, json::parse(R"({"echo":"ping"})"));
    const auto reqs = proxy.requests();
    ASSERT_EQ(reqs.size(), 1U);
    EXPECT_EQ(reqs[0].method, "CONNECT");
    EXPECT_EQ(reqs[0].target, server.url().substr(server.url().find("127.0.0.1")));
    EXPECT_EQ(reqs[0].proxy_authorization, "Basic " + std::string("dXNlcjpwYTpzcw=="));
}

} // namespace

TEST(WebsocketApi, ConnectsThroughHttpProxy) {
    expect_proxied_roundtrip(false, false);
}

TEST(WebsocketApi, ConnectsWithTlsThroughHttpProxy) {
    expect_proxied_roundtrip(true, false);
}

TEST(WebsocketApi, ConnectsThroughHttpsProxy) {
    expect_proxied_roundtrip(false, true);
}

TEST(WebsocketApi, ConnectsWithTlsThroughHttpsProxy) {
    expect_proxied_roundtrip(true, true);
}

TEST(WebsocketApi, ProxyConnectFailureIsReported) {
    MockWsServer server(echo);
    MockProxy proxy(nullptr, 407);
    auto cfg = api_config(server.url());
    cfg.proxy = proxy_at(proxy, ProxyProtocol::Http);
    WebsocketApi api(cfg);
    try {
        api.connect();
        FAIL() << "expected WebsocketNetworkError";
    } catch (const WebsocketNetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("407"), std::string::npos) << e.what();
    }
}

// ==== WebsocketApi: requests ====

TEST(WebsocketApi, SendUnsignedMessage) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    const auto res = api.send_message("time", {{"foo", "bar"}, {"empty", ""}});
    ASSERT_EQ(res.size(), 1U);
    EXPECT_EQ(res[0].result, json::parse(R"({"echo":"time"})"));
    ASSERT_TRUE(res[0].rate_limits.has_value());
    ASSERT_EQ(res[0].rate_limits->size(), 1U);
    EXPECT_EQ(res[0].rate_limits->at(0).rate_limit_type,
              binance::common::RateLimitType::RequestWeight);
    EXPECT_EQ(res[0].rate_limits->at(0).interval, binance::common::Interval::Minute);
    EXPECT_EQ(res[0].rate_limits->at(0).interval_num, 1U);
    EXPECT_EQ(res[0].rate_limits->at(0).limit, 6000U);
    EXPECT_EQ(res[0].rate_limits->at(0).count, 2U);

    const auto req = parse(server.sessions().front().received.front());
    EXPECT_TRUE(binance::common::detail::is_valid_request_id(req.at("id").as_string()));
    EXPECT_EQ(req.at("method"), json::value("time"));
    EXPECT_EQ(req.at("params"), json::parse(R"({"foo":"bar"})"));
}

TEST(WebsocketApi, SendWithApiKeyOnly) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    WebsocketMessageSendOptions o;
    o.with_api_key = true;
    (void)api.send_message("userDataStream.start", {}, o);
    const auto params = parse(server.sessions().front().received.front()).at("params").as_object();
    EXPECT_EQ(params.at("apiKey"), json::value("api-key"));
    EXPECT_FALSE(params.contains("signature"));
    EXPECT_FALSE(params.contains("timestamp"));
}

TEST(WebsocketApi, SignedMessageHasTimestampAndSignature) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("account.status", {{"symbol", "BTCUSDT"}}, signed_opts());
    const auto params = parse(server.sessions().front().received.front()).at("params").as_object();
    EXPECT_EQ(params.at("apiKey"), json::value("api-key"));
    EXPECT_TRUE(params.at("timestamp").is_number());
    EXPECT_TRUE(params.at("signature").is_string());
}

TEST(WebsocketApi, SignedMessageUsesTheTimestampProvider) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    std::atomic<std::int64_t> now{1700000000000};
    cfg.timestamp_provider = [&now] { return now.fetch_add(1000); };
    WebsocketApi api(cfg);
    api.connect();
    (void)api.send_message("account.status", {}, signed_opts());
    (void)api.send_message("account.status", {}, signed_opts());
    const auto reqs = requests_with_method(server.sessions(), "account.status");
    ASSERT_EQ(reqs.size(), 2U);
    EXPECT_EQ(parse(reqs[0]).at("params").as_object().at("timestamp"), json::value(1700000000000));
    EXPECT_EQ(parse(reqs[1]).at("params").as_object().at("timestamp"), json::value(1700000001000));
}

TEST(WebsocketApi, RelogonUsesAFreshTimestamp) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    std::atomic<std::int64_t> now{1700000000000};
    cfg.timestamp_provider = [&now] { return now.fetch_add(1000); };
    WebsocketApi api(cfg);
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    server.drop(0);
    ASSERT_TRUE(
        server.wait([](const Sessions& s) { return s.size() == 2 && !s[1].received.empty(); }));
    const auto first = parse(server.sessions()[0].received.front()).at("params").as_object();
    const auto again = parse(server.sessions()[1].received.front()).at("params").as_object();
    EXPECT_EQ(first.at("timestamp"), json::value(1700000000000));
    EXPECT_EQ(again.at("timestamp"), json::value(1700000001000));
    EXPECT_NE(first.at("signature"), again.at("signature"));
}

TEST(WebsocketApi, PoolReconnectsWhenEveryMemberIsLost) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    api.connect();
    server.drop_all();
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 4 && s[2].open && s[3].open; }, 15s));
    ASSERT_TRUE(eventually([&] { return api.is_connected(); }));
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, TypedSendDecodesTheResult) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    const auto res = binance::common::send<std::map<std::string, std::string>>(api, "time", {});
    EXPECT_EQ(res.data().at("echo"), "time");
    EXPECT_TRUE(res.rate_limits().has_value());
}

TEST(WebsocketApi, AsyncTypedSend) {
    MockWsServer server(echo);
    auto api = std::make_shared<WebsocketApi>(api_config(server.url()));
    api->connect();
    auto f = binance::common::async_send<json::object>(api, "time", {}, {}, asio::use_future);
    EXPECT_EQ(f.get().data().at("echo"), json::value("time"));
}

TEST(WebsocketApi, TypedSendAllReturnsEveryConnectionsResponse) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    auto api = std::make_shared<WebsocketApi>(cfg);
    api->connect();
    const auto res =
        binance::common::send_all<json::object>(*api, "session.logon", {}, logon_opts());
    ASSERT_EQ(res.size(), 2U);
    for (const auto& r : res) {
        EXPECT_EQ(r.data().at("echo"), json::value("session.logon"));
    }
    auto f = binance::common::async_send_all<json::object>(api, "session.logout", {}, logout_opts(),
                                                           asio::use_future);
    EXPECT_EQ(f.get().size(), 2U);
}

TEST(WebsocketApi, UsesResponseWhenNoResult) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(R"({"id":")" + id_of(text) + R"(","status":200,"response":{"x":1}})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    const auto res = api.send_message("m", {});
    EXPECT_EQ(res[0].result, json::parse(R"({"x":1})"));
    EXPECT_FALSE(res[0].rate_limits.has_value());
}

TEST(WebsocketApi, ErrorStatusFailsWithResponseError) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(
            R"({"id":")" + id_of(text) +
            R"(","status":400,"error":{"code":-1100,"msg":"Illegal characters"},)"
            R"("rateLimits":[{"rateLimitType":"ORDERS","interval":"SECOND","intervalNum":10,"limit":50,"count":1}]})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    try {
        (void)api.send_message("order.place", {});
        FAIL() << "expected WebsocketResponseError";
    } catch (const WebsocketResponseError& e) {
        EXPECT_EQ(e.code(), -1100);
        EXPECT_EQ(e.msg(), "Illegal characters");
        EXPECT_EQ(e.status(), 400);
        ASSERT_EQ(e.rate_limits().size(), 1U);
        EXPECT_EQ(e.rate_limits()[0].rate_limit_type, binance::common::RateLimitType::Orders);
        EXPECT_TRUE(e.request_sent());
    }
}

TEST(WebsocketApi, ErrorDataRetryAfterIsAnEpochTimestamp) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(R"({"id":")" + id_of(text) +
               R"(","status":418,"error":{"code":-1003,"msg":"banned","data":)"
               R"({"serverTime":1659142907531,"retryAfter":1659146400000}}})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    try {
        (void)api.send_message("m", {});
        FAIL() << "expected WebsocketResponseError";
    } catch (const WebsocketResponseError& e) {
        ASSERT_TRUE(e.retry_at().has_value());
        EXPECT_EQ(
            std::chrono::duration_cast<std::chrono::milliseconds>(e.retry_at()->time_since_epoch()),
            std::chrono::milliseconds(1659146400000));
    }
}

TEST(WebsocketApi, ErrorDataIsKeptWhole) {
    const std::string data =
        R"({"cancelResult":"FAILURE","newOrderResult":"NOT_ATTEMPTED",)"
        R"("cancelResponse":{"code":-2011,"msg":"Unknown order sent."},"newOrderResponse":null})";
    MockWsServer server([&](MockWsServer::Session& s, const std::string& text) {
        s.send(R"({"id":")" + id_of(text) +
               R"(","status":409,"error":{"code":-2022,"msg":"Order cancel-replace failed.",)"
               R"("data":)" +
               data + "}}");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    try {
        (void)api.send_message("order.cancelReplace", {});
        FAIL() << "expected WebsocketResponseError";
    } catch (const WebsocketResponseError& e) {
        EXPECT_EQ(e.code(), -2022);
        ASSERT_NE(e.data(), nullptr);
        EXPECT_EQ(*e.data(), json::parse(data));
        EXPECT_FALSE(e.retry_at().has_value());
    }
}

TEST(WebsocketApi, AnErrorWithoutDataHasNone) {
    for (const char* error :
         {R"({"code":-1100,"msg":"x"})", R"({"code":-1100,"msg":"x","data":null})"}) {
        MockWsServer server([&](MockWsServer::Session& s, const std::string& text) {
            s.send(R"({"id":")" + id_of(text) + R"(","status":400,"error":)" + error + "}");
        });
        WebsocketApi api(api_config(server.url()));
        api.connect();
        try {
            (void)api.send_message("m", {});
            FAIL() << "expected WebsocketResponseError";
        } catch (const WebsocketResponseError& e) {
            EXPECT_EQ(e.data(), nullptr) << error;
        }
    }
}

TEST(WebsocketApi, ErrorWithoutRetryAfterHasNoRetryAt) {
    for (const char* error :
         {R"({"code":-1100,"msg":"x"})", R"({"code":-1100,"msg":"x","data":{"serverTime":1}})",
          R"({"code":-1100,"msg":"x","data":{"retryAfter":"soon"}})"}) {
        MockWsServer server([&](MockWsServer::Session& s, const std::string& text) {
            s.send(R"({"id":")" + id_of(text) + R"(","status":429,"error":)" + error + "}");
        });
        WebsocketApi api(api_config(server.url()));
        api.connect();
        try {
            (void)api.send_message("m", {});
            FAIL() << "expected WebsocketResponseError";
        } catch (const WebsocketResponseError& e) {
            EXPECT_FALSE(e.retry_at().has_value()) << error;
        }
    }
}

TEST(WebsocketApi, ErrorStatusWithoutBodyUsesTheStatus) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(R"({"id":")" + id_of(text) + R"(","status":429})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    try {
        (void)api.send_message("m", {});
        FAIL() << "expected WebsocketResponseError";
    } catch (const WebsocketResponseError& e) {
        EXPECT_EQ(e.code(), 429);
        EXPECT_EQ(e.msg(), "Unknown error");
    }
}

TEST(WebsocketApi, InvalidRateLimitEntriesAreSkipped) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(
            R"({"id":")" + id_of(text) +
            R"(","status":200,"result":{},"rateLimits":[{"rateLimitType":"BOGUS","interval":"MINUTE","intervalNum":1,"limit":1},)"
            R"({"rateLimitType":"RAW_REQUESTS","interval":"DAY","intervalNum":1,"limit":5,"count":3}]})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    const auto res = api.send_message("m", {});
    ASSERT_EQ(res[0].rate_limits->size(), 1U);
    EXPECT_EQ(res[0].rate_limits->at(0).rate_limit_type,
              binance::common::RateLimitType::RawRequests);
    EXPECT_EQ(res[0].rate_limits->at(0).interval, binance::common::Interval::Day);
}

TEST(WebsocketApi, UnansweredRequestTimesOut) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    auto cfg = api_config(server.url());
    cfg.timeout = 200ms;
    WebsocketApi api(cfg);
    api.connect();
    try {
        (void)api.send_message("m", {});
        FAIL() << "expected WebsocketTimeoutError";
    } catch (const WebsocketTimeoutError& e) {
        EXPECT_TRUE(e.request_sent());
    }
}

TEST(WebsocketApi, LateResponseAfterTimeoutIsIgnored) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        const auto id = id_of(text);
        std::thread([&s, id] {
            std::this_thread::sleep_for(300ms);
            s.send(R"({"id":")" + id + R"(","status":200,"result":{}})");
        }).detach();
    });
    auto cfg = api_config(server.url());
    cfg.timeout = 100ms;
    EventLog log;
    WebsocketApi api(cfg);
    auto sub = api.on_event(std::ref(log));
    api.connect();
    EXPECT_THROW((void)api.send_message("m", {}), WebsocketTimeoutError);
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Message) == 1; }));
    EXPECT_TRUE(api.is_connected());
}

TEST(WebsocketApi, SendWhenNotConnectedFails) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    EXPECT_THROW((void)api.send_message("m", {}), WebsocketNotConnectedError);
}

TEST(WebsocketApi, SignedSendWithoutApiKeyFails) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.api_key.reset();
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_THROW((void)api.send_message("m", {}, signed_opts()),
                 binance::common::ConnectorClientError);
}

TEST(WebsocketApi, PendingRequestFailsWhenTheSocketDrops) {
    MockWsServer server([](MockWsServer::Session& s, const std::string&) { s.drop(); });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    EXPECT_THROW((void)api.send_message("m", {}), WebsocketNoResponseError);
}

TEST(WebsocketApi, RequestsAreSpreadRoundRobin) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(3);
    WebsocketApi api(cfg);
    api.connect();
    for (int i = 0; i < 6; ++i) {
        (void)api.send_message("m", {});
    }
    for (const auto& s : server.sessions()) {
        EXPECT_EQ(s.received.size(), 2U);
    }
}

TEST(WebsocketApi, CustomRequestIdIsUsed) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    const std::string id = "0123456789abcdef0123456789abcdef";
    (void)api.send_message("m", {{"id", json::string(id)}});
    EXPECT_EQ(id_of(server.sessions().front().received.front()), id);
}

TEST(WebsocketApi, ConcurrentRequestsFromManyThreads) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    api.connect();
    std::atomic<int> ok{0};
    std::vector<std::thread> threads;
    for (int t = 0; t < 8; ++t) {
        threads.emplace_back([&] {
            for (int i = 0; i < 25; ++i) {
                if (!api.send_message("m", {}).empty()) {
                    ++ok;
                }
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    EXPECT_EQ(ok.load(), 200);
}

TEST(WebsocketApi, CancellationCompletesWithCancelledError) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    WebsocketApi api(api_config(server.url()));
    api.connect();
    asio::cancellation_signal signal;
    auto f = api.async_send_message("m", {}, {},
                                    asio::bind_cancellation_slot(signal.slot(), asio::use_future));
    ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    signal.emit(asio::cancellation_type::terminal);
    try {
        (void)f.get();
        FAIL() << "expected WebsocketCancelledError";
    } catch (const WebsocketCancelledError& e) {
        EXPECT_TRUE(e.request_sent());
    }
    // The request is forgotten: a graceful disconnect does not wait for its timeout (2 s).
    const auto start = std::chrono::steady_clock::now();
    api.disconnect();
    EXPECT_LT(std::chrono::steady_clock::now() - start, 1500ms);
}

TEST(WebsocketApi, DestroyingTheClientCancelsPendingRequests) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    std::future<std::vector<binance::common::WebsocketApiRawResponse>> f;
    {
        WebsocketApi api(api_config(server.url()));
        api.connect();
        f = api.async_send_message("m", {}, {}, asio::use_future);
        ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    }
    EXPECT_THROW((void)f.get(), WebsocketCancelledError);
}

TEST(WebsocketApi, CompletionRunsOnTheBoundExecutor) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    asio::io_context user;
    auto guard = asio::make_work_guard(user);
    std::thread user_thread([&] { user.run(); });
    std::promise<std::thread::id> where;
    api.async_send_message(
        "m", {}, {},
        asio::bind_executor(
            user, [&](std::exception_ptr, std::vector<binance::common::WebsocketApiRawResponse>) {
                where.set_value(std::this_thread::get_id());
            }));
    EXPECT_EQ(where.get_future().get(), user_thread.get_id());
    guard.reset();
    user_thread.join();
}

TEST(WebsocketApi, BlockingCallFromCallbackThrows) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    std::promise<std::string> error;
    auto sub = api.on_event([&](const WebsocketEvent& e) {
        if (e.type != WebsocketEventType::Open) {
            return;
        }
        try {
            (void)api.send_message("m", {});
            error.set_value("no error");
        } catch (const WebsocketError& ex) {
            error.set_value(ex.what());
        }
    });
    api.connect();
    EXPECT_NE(error.get_future().get().find("client's executor"), std::string::npos);
}

// ==== WebsocketApi: session logon ====

TEST(WebsocketApi, SessionLogonGoesToEveryConnection) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    api.connect();
    const auto res = api.send_message("session.logon", {}, logon_opts());
    EXPECT_EQ(res.size(), 2U);
    const auto logons = requests_with_method(server.sessions(), "session.logon");
    ASSERT_EQ(logons.size(), 2U);
    EXPECT_EQ(id_of(logons[0]), id_of(logons[1]));
}

TEST(WebsocketApi, LoggedOnSessionSkipsAuthentication) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    (void)api.send_message("account.status", {}, signed_opts());
    const auto req = requests_with_method(server.sessions(), "account.status");
    ASSERT_EQ(req.size(), 1U);
    const auto params = parse(req[0]).at("params").as_object();
    EXPECT_FALSE(params.contains("apiKey"));
    EXPECT_FALSE(params.contains("signature"));
    EXPECT_TRUE(params.contains("timestamp"));
}

TEST(WebsocketApi, WithoutAutoRelogonRequestsStaySigned) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.auto_session_relogon = false;
    WebsocketApi api(cfg);
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    (void)api.send_message("account.status", {}, signed_opts());
    const auto params = parse(requests_with_method(server.sessions(), "account.status")[0])
                            .at("params")
                            .as_object();
    EXPECT_TRUE(params.contains("signature"));
}

TEST(WebsocketApi, SessionLogoutRestoresSigning) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    (void)api.send_message("session.logout", {}, logout_opts());
    (void)api.send_message("account.status", {}, signed_opts());
    const auto params = parse(requests_with_method(server.sessions(), "account.status")[0])
                            .at("params")
                            .as_object();
    EXPECT_TRUE(params.contains("signature"));
}

TEST(WebsocketApi, FailedLogonDoesNotLogOn) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        if (parse(text).at("method") == json::value("session.logon")) {
            s.send(R"({"id":")" + id_of(text) +
                   R"(","status":401,"error":{"code":-1022,"msg":"bad signature"}})");
            return;
        }
        echo(s, text);
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    EXPECT_THROW((void)api.send_message("session.logon", {}, logon_opts()), WebsocketResponseError);
    (void)api.send_message("account.status", {}, signed_opts());
    const auto params = parse(requests_with_method(server.sessions(), "account.status")[0])
                            .at("params")
                            .as_object();
    EXPECT_TRUE(params.contains("signature"));
}

TEST(WebsocketApi, SessionIsLoggedOnAgainAfterReconnect) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {{"extra", 1}}, logon_opts());
    server.drop(0);
    ASSERT_TRUE(
        server.wait([](const Sessions& s) { return s.size() == 2 && !s[1].received.empty(); }));
    const auto relogon = parse(server.sessions()[1].received.front());
    EXPECT_EQ(relogon.at("method"), json::value("session.logon"));
    EXPECT_EQ(relogon.at("params").as_object().at("extra"), json::value(1));
    EXPECT_TRUE(relogon.at("params").as_object().contains("signature"));
}

TEST(WebsocketApi, SessionIsLoggedOnAgainAfterRenewal) {
    MockWsServer server;
    server.set_handler([](MockWsServer::Session& s, const std::string& text) {
        echo(s, text);
        if (s.index == 0 && parse(text).at("method") == json::value("session.logon")) {
            s.send(R"({"event":{"e":"serverShutdown"}})");
        }
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 2 && !s[0].open && !s[1].received.empty(); }));
    EXPECT_EQ(parse(server.sessions()[1].received.front()).at("method"),
              json::value("session.logon"));
    // Requests on the new connection are signed until its logon succeeds, then skip auth.
    ASSERT_TRUE(eventually([&] {
        (void)api.send_message("account.status", {}, signed_opts());
        const auto reqs = requests_with_method({server.sessions()[1]}, "account.status");
        return !parse(reqs.back()).at("params").as_object().contains("signature");
    }));
}

TEST(WebsocketApi, RelogonFailureKeepsTheConnection) {
    std::atomic<int> logons{0};
    MockWsServer server([&](MockWsServer::Session& s, const std::string& text) {
        if (parse(text).at("method") == json::value("session.logon") && ++logons > 1) {
            s.send(R"({"id":")" + id_of(text) +
                   R"(","status":400,"error":{"code":-1,"msg":"no"}})");
            return;
        }
        echo(s, text);
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return logons.load() == 2; }));
    ASSERT_TRUE(eventually([&] { return api.is_connected(); }));
    // Not logged on: requests are signed again.
    (void)api.send_message("account.status", {}, signed_opts());
    const auto params = parse(requests_with_method(server.sessions(), "account.status")[0])
                            .at("params")
                            .as_object();
    EXPECT_TRUE(params.contains("signature"));
}

TEST(WebsocketApi, DisconnectForgetsTheSession) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    api.disconnect();
    api.connect();
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2; }));
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(server.sessions()[1].received.empty());
}

// ==== WebsocketApi: messages and user data ====

TEST(WebsocketApi, UnknownIdAndInvalidJsonAreIgnored) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.send(0, R"({"id":"0123456789abcdef0123456789abcdef","status":200,"result":{}})");
    server.send(0, "not json");
    server.send(0, R"({"something":"else"})");
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Message) == 3; }));
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, UserDataEventsReachTheStream) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto stream = api.create_stream();
    EXPECT_TRUE(binance::common::detail::is_valid_request_id(stream.stream()));
    std::mutex m;
    std::vector<json::value> got;
    stream.on_message([&](const json::value& v) {
        const std::lock_guard lock(m);
        got.push_back(v);
    });
    server.send(0, R"({"subscriptionId":0,"event":{"e":"outboundAccountPosition","E":1}})");
    ASSERT_TRUE(eventually([&] {
        const std::lock_guard lock(m);
        return got.size() == 1;
    }));
    EXPECT_EQ(got[0], json::parse(R"({"e":"outboundAccountPosition","E":1})"));

    // Events without a type are not dispatched.
    server.send(0, R"({"event":{"E":2}})");
    server.send(0, R"({"event":{"e":"marker"}})");
    ASSERT_TRUE(eventually([&] {
        const std::lock_guard lock(m);
        return got.size() == 2;
    }));
    EXPECT_EQ(got[1], json::parse(R"({"e":"marker"})"));

    stream.unsubscribe();
    server.send(0, R"({"event":{"e":"balanceUpdate"}})");
    server.send(0, R"({"event":{"e":"marker"}})");
    std::this_thread::sleep_for(100ms);
    const std::lock_guard lock(m);
    EXPECT_EQ(got.size(), 2U);
}

TEST(WebsocketApi, TypedUserDataStream) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    binance::common::WebsocketStream<std::map<std::string, std::string>> stream(
        api.create_stream("x"));
    EXPECT_EQ(stream.stream(), "x");
    std::promise<std::string> got;
    stream.on_message(
        [&](const std::map<std::string, std::string>& v) { got.set_value(v.at("e")); });
    server.send(0, R"({"event":{"e":"executionReport"}})");
    EXPECT_EQ(got.get_future().get(), "executionReport");
}

TEST(WebsocketApi, CallbackExceptionsAreContained) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event([](const WebsocketEvent&) { throw std::runtime_error("boom"); });
    api.connect();
    auto stream = api.create_stream();
    stream.on_message([](const json::value&) { throw std::runtime_error("boom"); });
    server.send(0, R"({"event":{"e":"x"}})");
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, UnsubscribedEventCallbackStops) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    sub.unsubscribe();
    sub.unsubscribe();
    api.connect();
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(log.events().empty());
}

TEST(WebsocketApi, DestroyedEventSubscriptionStops) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    {
        auto sub = api.on_event(std::ref(log));
    }
    api.connect();
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(log.events().empty());
}

TEST(WebsocketApi, ReleasedEventSubscriptionKeepsRunning) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    api.on_event(std::ref(log)).release();
    api.connect();
    ASSERT_TRUE(eventually([&] { return !log.events().empty(); }));
}

TEST(WebsocketApi, SubscriptionOutlivingTheClientIsSafe) {
    MockWsServer server(echo);
    binance::common::Subscription sub;
    binance::common::WebsocketStreamHandle handle("", nullptr);
    {
        WebsocketApi api(api_config(server.url()));
        sub = api.on_event([](const WebsocketEvent&) {});
        handle = api.create_stream();
    }
    sub.unsubscribe();
    handle.on_message([](const json::value&) {});
    handle.unsubscribe();
}

TEST(WebsocketApi, ServerShutdownRenewsWithoutLosingRequests) {
    MockWsServer server;
    server.set_handler([&server](MockWsServer::Session& s, const std::string& text) {
        if (s.index == 0) {
            // Announce the shutdown, then answer on the old connection once it is replaced.
            s.send(R"({"event":{"e":"serverShutdown"}})");
            const auto id = id_of(text);
            std::thread([&server, id] {
                server.wait([](const Sessions& all) { return all.size() == 2; });
                server.send(0, R"({"id":")" + id + R"(","status":200,"result":{"old":true}})");
            }).detach();
            return;
        }
        echo(s, text);
    });
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    EXPECT_EQ(api.send_message("m", {}).front().result, json::parse(R"({"old":true})"));
    // The old connection is closed by the client once drained.
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && !s[0].open; }));
    EXPECT_TRUE(server.sessions()[1].open);
    EXPECT_EQ(api.send_message("m", {}).front().result, json::parse(R"({"echo":"m"})"));
    EXPECT_EQ(log.count(WebsocketEventType::Open), 1U);
    EXPECT_TRUE(api.is_connected());
}

// ==== WebsocketApi: reconnects ====

TEST(WebsocketApi, ReconnectsAfterAnAbnormalDrop) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Open) == 2; }));
    const auto close = log.last(WebsocketEventType::Close);
    ASSERT_TRUE(close.has_value());
    EXPECT_EQ(close->close_code, 1006);
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, UnsubscribingWaitsForARunningEventCallback) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    std::atomic<bool> started{false};
    std::atomic<bool> finished{false};
    auto sub = api.on_event([&](const WebsocketEvent& e) {
        if (e.type == WebsocketEventType::Close && !started.exchange(true)) {
            std::this_thread::sleep_for(200ms);
            finished = true;
        }
    });
    api.connect();
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return started.load(); }));
    sub.unsubscribe();
    EXPECT_TRUE(finished.load());
}

TEST(WebsocketApi, ReconnectsAfterATemporaryServerClose) {
    for (const std::uint16_t code :
         std::initializer_list<std::uint16_t>{1000, 1001, 1002, 1011, 1012, 1014, 3000}) {
        MockWsServer server(echo);
        WebsocketApi api(api_config(server.url()));
        EventLog log;
        auto sub = api.on_event(std::ref(log));
        api.connect();
        server.close(0, code, "going away");
        ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }))
            << code;
        const auto close = log.last(WebsocketEventType::Close);
        ASSERT_TRUE(close.has_value());
        EXPECT_EQ(close->close_code, code);
        EXPECT_EQ(close->data, "going away");
    }
}

TEST(WebsocketApi, DoesNotReconnectAfterAPermanentClose) {
    for (const std::uint16_t code : std::initializer_list<std::uint16_t>{1008, 4000, 4999}) {
        MockWsServer server(echo);
        WebsocketApi api(api_config(server.url()));
        EventLog log;
        auto sub = api.on_event(std::ref(log));
        api.connect();
        server.close(0, code);
        ASSERT_TRUE(eventually([&] { return log.count(WebsocketEventType::Close) == 1; }));
        std::this_thread::sleep_for(300ms);
        EXPECT_EQ(server.session_count(), 1U) << code;
        EXPECT_FALSE(api.is_connected());
        EXPECT_TRUE(log.has_error_containing("[CRITICAL]")) << code;
    }
}

TEST(WebsocketApi, FailedReconnectsAreRetried) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.set_reject_status(503);
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return log.has_error_containing("HTTP 503"); }));
    server.set_reject_status(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 10s));
    EXPECT_TRUE(eventually([&] { return api.is_connected(); }));
}

TEST(WebsocketApi, RepeatedQuickClosesBackOff) {
    std::mutex mutex;
    std::vector<long long> delays;
    struct SinkGuard {
        SinkGuard(const SinkGuard&) = delete;
        SinkGuard& operator=(const SinkGuard&) = delete;
        SinkGuard() = default;
        ~SinkGuard() { binance::common::Logger::set_sink({}); }
    } const guard;
    binance::common::Logger::set_sink([&](binance::common::LogLevel, std::string_view line) {
        static const std::regex re(R"(reconnecting \S+ in (\d+)ms)");
        std::cmatch m;
        if (std::regex_search(line.data(), line.data() + line.size(), m, re)) {
            const std::lock_guard lock(mutex);
            delays.push_back(std::stoll(m[1].str()));
        }
    });
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.reconnect_delay = 300ms;
    WebsocketApi api(cfg);
    api.connect();
    // Every new connection is closed at once: 300 ms, then 300 ms plus a jittered backoff of
    // 500-1000 ms, then of 1000-2000 ms.
    for (std::size_t i = 0; i < 3; ++i) {
        ASSERT_TRUE(server.wait([i](const Sessions& s) { return s.size() > i && s[i].open; }, 10s));
        server.close(i, 1001);
    }
    ASSERT_TRUE(eventually([&] {
        const std::lock_guard lock(mutex);
        return delays.size() >= 3;
    }));
    const std::lock_guard lock(mutex);
    EXPECT_EQ(delays[0], 300);
    EXPECT_GE(delays[1], 800);
    EXPECT_LE(delays[1], 1300);
    EXPECT_GE(delays[2], 1300);
    EXPECT_LE(delays[2], 2300);
}

TEST(WebsocketApi, ConnectAfterAPermanentCloseReconnects) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    server.close(0, 1008);
    ASSERT_TRUE(eventually([&] { return !api.is_connected(); }));
    api.connect();
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(server.session_count(), 2U);
}

// ==== WebsocketApi: disconnect and ping ====

TEST(WebsocketApi, DisconnectClosesGracefully) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    api.disconnect();
    EXPECT_FALSE(api.is_connected());
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].open; }));
    const auto close = log.last(WebsocketEventType::Close);
    ASSERT_TRUE(close.has_value());
    EXPECT_EQ(close->close_code, 1000);
    std::this_thread::sleep_for(300ms);
    EXPECT_EQ(server.session_count(), 1U);
    EXPECT_EQ(log.count(WebsocketEventType::Error), 0U);
}

TEST(WebsocketApi, DisconnectWaitsForPendingResponses) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        const auto id = id_of(text);
        std::thread([&s, id] {
            std::this_thread::sleep_for(200ms);
            s.send(R"({"id":")" + id + R"(","status":200,"result":{}})");
        }).detach();
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto f = api.async_send_message("m", {}, {}, asio::use_future);
    ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    api.disconnect();
    EXPECT_EQ(f.get().size(), 1U);
}

TEST(WebsocketApi, DisconnectWhenNotConnectedSucceeds) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    EXPECT_NO_THROW(api.disconnect());
}

TEST(WebsocketApi, DisconnectDuringConnectCancelsIt) {
    MockWsServer::Options opts;
    opts.accept_delay = 200ms;
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    auto f = api.async_connect(asio::use_future);
    std::this_thread::sleep_for(50ms);
    api.disconnect();
    EXPECT_THROW(f.get(), WebsocketCancelledError);
    EXPECT_FALSE(api.is_connected());
}

TEST(WebsocketApi, ConnectAgainAfterDisconnect) {
    MockWsServer server(echo);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    api.disconnect();
    api.connect();
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, PingServerPingsEveryConnection) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    api.connect();
    api.ping_server();
    EXPECT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 2 && s[0].pings == 1 && s[1].pings == 1; }));
}

TEST(WebsocketApi, ServerPingsEmitPingEvents) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.ping(0);
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Ping) == 1; }));
}

TEST(WebsocketApi, DestructorFromCallbackDoesNotDeadlock) {
    MockWsServer server(echo);
    auto api = std::make_shared<WebsocketApi>(api_config(server.url()));
    std::promise<void> done;
    api->connect();
    api->async_send_message(
        "m", {}, {},
        [&api, &done](std::exception_ptr, std::vector<binance::common::WebsocketApiRawResponse>) {
            api.reset();
            done.set_value();
        });
    EXPECT_EQ(done.get_future().wait_for(5s), std::future_status::ready);
}

// ==== WebsocketStreams ====

namespace {

std::vector<std::string> methods_of(const MockWsServer::SessionInfo& s) {
    std::vector<std::string> out;
    for (const auto& r : s.received) {
        out.emplace_back(parse(r).at("method").as_string());
    }
    return out;
}

/// Shortens the renewal interval of connections opened while it lives.
class RenewalInterval {
public:
    explicit RenewalInterval(std::chrono::milliseconds interval) {
        binance::common::detail::set_renewal_interval_for_testing(interval);
    }
    ~RenewalInterval() { binance::common::detail::set_renewal_interval_for_testing({}); }
    RenewalInterval(const RenewalInterval&) = delete;
    RenewalInterval& operator=(const RenewalInterval&) = delete;
    RenewalInterval(RenewalInterval&&) = delete;
    RenewalInterval& operator=(RenewalInterval&&) = delete;
};

/// Records the payloads a stream handle receives.
struct Collector {
    std::mutex m;
    std::vector<json::value> got;
    auto callback() {
        return [this](const json::value& v) {
            const std::lock_guard lock(m);
            got.push_back(v);
        };
    }
    std::size_t size() {
        const std::lock_guard lock(m);
        return got.size();
    }
};

} // namespace

TEST(WebsocketStreams, MissingWsUrlThrows) {
    EXPECT_THROW(WebsocketStreams{WebsocketStreamsConfig{}}, ConfigError);
}

TEST(WebsocketStreams, ConnectWithStreamsPutsThemInTheUrl) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"btcusdt@trade", "ethusdt@trade"});
    EXPECT_TRUE(ws.is_connected());
    EXPECT_EQ(server.sessions().front().target, "/stream?streams=btcusdt@trade/ethusdt@trade");
    EXPECT_TRUE(ws.is_subscribed("btcusdt@trade"));
    EXPECT_FALSE(ws.is_subscribed("bnbusdt@trade"));
}

TEST(WebsocketStreams, ConnectWithoutStreams) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    EXPECT_EQ(server.sessions().front().target, "/stream?streams=");
}

TEST(WebsocketStreams, TimeUnitIsAppended) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.time_unit = TimeUnit::Microsecond;
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    EXPECT_EQ(server.sessions().front().target, "/stream?streams=a&timeUnit=microsecond");
}

TEST(WebsocketStreams, PoolOpensEveryConnectionAndStreamsGoToTheFirst) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(3);
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    const auto sessions = server.sessions();
    ASSERT_EQ(sessions.size(), 3U);
    EXPECT_EQ(std::count_if(sessions.begin(), sessions.end(),
                            [](const auto& s) { return s.target == "/stream?streams=a"; }),
              1);
}

TEST(WebsocketStreams, UrlPathsGetTheirOwnConnections) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg, {"public", "market"});
    ws.connect({"a"});
    const auto sessions = server.sessions();
    ASSERT_EQ(sessions.size(), 4U);
    std::multiset<std::string> targets;
    for (const auto& s : sessions) {
        targets.insert(s.target);
    }
    EXPECT_EQ(targets.count("/public/stream?streams=a"), 1U);
    EXPECT_EQ(targets.count("/public/stream?streams="), 1U);
    EXPECT_EQ(targets.count("/market/stream?streams=a"), 1U);
    EXPECT_EQ(targets.count("/market/stream?streams="), 1U);
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, ConnectRefusedFails) {
    WebsocketStreams ws(streams_config("ws://127.0.0.1:" + std::to_string(closed_port())));
    EXPECT_THROW(ws.connect(), WebsocketNetworkError);
}

TEST(WebsocketStreams, SubscribeSendsSubscribe) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.subscribe({"btcusdt@trade", "ethusdt@trade"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    const auto msg = parse(server.sessions()[0].received[0]);
    EXPECT_EQ(msg.at("method"), json::value("SUBSCRIBE"));
    EXPECT_EQ(msg.at("params"), json::parse(R"(["btcusdt@trade","ethusdt@trade"])"));
    EXPECT_TRUE(binance::common::detail::is_valid_request_id(msg.at("id").as_string()));
    EXPECT_TRUE(ws.is_subscribed("ethusdt@trade"));
}

TEST(WebsocketStreams, SubscribeEmptyListDoesNothing) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.subscribe({});
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(server.sessions()[0].received.empty());
}

TEST(WebsocketStreams, StreamIsSubscribedOnce) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    ws.subscribe({"a"});
    ws.subscribe({"b"});
    ws.subscribe({"b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() >= 1; }));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(server.sessions()[0].received.size(), 1U);
}

TEST(WebsocketStreams, CustomAndNumericIds) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.subscribe({"a"}, StreamId(std::string("0123456789abcdef0123456789abcdef")));
    ws.subscribe({"b"}, StreamId(std::uint32_t{42}));
    ws.subscribe({"c"}, StreamId(std::string("bad")));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 3; }));
    const auto r = server.sessions()[0].received;
    EXPECT_EQ(parse(r[0]).at("id"), json::value("0123456789abcdef0123456789abcdef"));
    EXPECT_EQ(parse(r[1]).at("id").to_number<std::uint64_t>(), 42U);
    EXPECT_TRUE(binance::common::detail::is_valid_request_id(parse(r[2]).at("id").as_string()));
}

TEST(WebsocketStreams, StrictlyNumericIds) {
    MockWsServer server;
    WebsocketStreams ws(
        streams_config(server.url()), {},
        {.user_agent = {}, .signed_streams = false, .stream_id_is_strictly_number = true});
    ws.connect();
    ws.subscribe({"a"}, StreamId(std::string("0123456789abcdef0123456789abcdef")));
    ws.subscribe({"b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    const auto r = server.sessions()[0].received;
    EXPECT_TRUE(parse(r[0]).at("id").is_number());
    EXPECT_TRUE(parse(r[1]).at("id").is_number());
}

TEST(WebsocketStreams, SubscriptionsBeforeConnectGoInTheUrl) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.subscribe({"a", "b"});
    EXPECT_TRUE(ws.is_subscribed("a"));
    ws.connect();
    EXPECT_EQ(server.sessions()[0].target, "/stream?streams=a/b");
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(server.sessions()[0].received.empty());
}

TEST(WebsocketStreams, SubscriptionsWhileConnectingAreSentOnOpen) {
    MockWsServer::Options opts;
    opts.accept_delay = 100ms;
    MockWsServer server({}, opts);
    WebsocketStreams ws(streams_config(server.url()));
    auto f = ws.async_connect({"a"}, asio::use_future);
    std::this_thread::sleep_for(30ms);
    ws.subscribe({"b"});
    f.get();
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    EXPECT_EQ(server.sessions()[0].target, "/stream?streams=a");
    EXPECT_EQ(parse(server.sessions()[0].received[0]).at("params"), json::parse(R"(["b"])"));
}

TEST(WebsocketStreams, PoolSpreadsSubscriptionsRoundRobin) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect();
    ws.subscribe({"a", "b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        return s.size() == 2 && s[0].received.size() == 1 && s[1].received.size() == 1;
    }));
}

TEST(WebsocketStreams, SubscribeToAnUnknownUrlPathFails) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"public"});
    ws.connect();
    EXPECT_THROW(ws.subscribe({"a"}, std::nullopt, std::string("private")), WebsocketError);
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, SameStreamOnDifferentUrlPaths) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"public", "market"});
    ws.connect();
    ws.subscribe({"a"}, std::nullopt, std::string("public"));
    ws.subscribe({"a"}, std::nullopt, std::string("market"));
    ws.subscribe({"a"}, std::nullopt, std::string("market"));
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        return s.size() == 2 && s[0].received.size() == 1 && s[1].received.size() == 1;
    }));
    EXPECT_EQ(WebsocketStreams::stream_key("a", std::string("public")), "public::a");
    EXPECT_EQ(WebsocketStreams::stream_key("a", std::nullopt), "a");
    EXPECT_EQ(WebsocketStreams::stream_key("a", std::string()), "a");
    EXPECT_TRUE(ws.is_subscribed("a"));
    EXPECT_FALSE(ws.is_subscribed("public"));
}

TEST(WebsocketStreams, EmptyUrlPathMeansNone) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.subscribe({"a"}, std::nullopt, std::string());
    ws.subscribe({"a"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    ws.unsubscribe({"a"}, std::nullopt, std::string());
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, UnsubscribeSendsUnsubscribe) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    ws.unsubscribe({"a"}, StreamId(std::uint32_t{5}));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    const auto msg = parse(server.sessions()[0].received[0]);
    EXPECT_EQ(msg.at("method"), json::value("UNSUBSCRIBE"));
    EXPECT_EQ(msg.at("params"), json::parse(R"(["a"])"));
    EXPECT_EQ(msg.at("id").to_number<std::uint64_t>(), 5U);
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, UnsubscribeUnknownStreamSendsNothing) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.unsubscribe({"a"});
    ws.unsubscribe({});
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(server.sessions()[0].received.empty());
}

TEST(WebsocketStreams, UnsubscribeKeepsStreamsWithCallbacks) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto handle = ws.create_stream("a");
    handle.on_message([](const json::value&) {});
    ws.unsubscribe({"a"});
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(methods_of(server.sessions()[0]), std::vector<std::string>{"SUBSCRIBE"});
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, UnsubscribeWhileDisconnectedDropsTheQueuedSubscription) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.subscribe({"a", "b"});
    ws.unsubscribe({"a"});
    EXPECT_FALSE(ws.is_subscribed("a"));
    ws.connect();
    EXPECT_EQ(server.sessions()[0].target, "/stream?streams=b");
}

TEST(WebsocketStreams, UnsubscribeWithUrlPathOnlyAffectsThatPath) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"public", "market"});
    ws.connect();
    ws.subscribe({"a"}, std::nullopt, std::string("public"));
    ws.subscribe({"a"}, std::nullopt, std::string("market"));
    ws.unsubscribe({"a"}, std::nullopt, std::string("market"));
    const auto on = [](const Sessions& s, const char* prefix) {
        return *std::find_if(s.begin(), s.end(),
                             [prefix](const auto& i) { return i.target.starts_with(prefix); });
    };
    ASSERT_TRUE(server.wait(
        [&](const Sessions& s) { return s.size() == 2 && on(s, "/market").received.size() == 2; }));
    EXPECT_EQ(methods_of(on(server.sessions(), "/public")), std::vector<std::string>{"SUBSCRIBE"});
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, StreamDataReachesTheHandle) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto handle = ws.create_stream("btcusdt@trade");
    EXPECT_EQ(handle.stream(), "btcusdt@trade");
    Collector first;
    Collector second;
    handle.on_message(first.callback());
    handle.on_message(second.callback());
    server.send(0, R"({"stream":"btcusdt@trade","data":{"p":"1.0"}})");
    server.send(0, R"({"stream":"other@trade","data":{}})");
    server.send(0, R"({"stream":"btcusdt@trade","data":null})");
    server.send(0, "garbage");
    server.send(0, R"({"result":null,"id":"x"})");
    ASSERT_TRUE(eventually([&] { return first.size() == 2 && second.size() == 2; }));
    EXPECT_EQ(first.got[0], json::parse(R"({"p":"1.0"})"));
    EXPECT_TRUE(first.got[1].is_null());
}

TEST(WebsocketStreams, TypedStream) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    binance::common::WebsocketStream<std::map<std::string, std::string>> stream(
        ws.create_stream("a"));
    std::promise<std::string> got;
    std::atomic<int> calls{0};
    stream.on_message([&](const std::map<std::string, std::string>& v) {
        if (++calls == 1) {
            got.set_value(v.at("p"));
        }
    });
    server.send(0, R"({"stream":"a","data":{"p":1}})"); // does not decode: skipped
    server.send(0, R"({"stream":"a","data":{"p":"2"}})");
    EXPECT_EQ(got.get_future().get(), "2");
}

TEST(WebsocketStreams, UrlPathRoutesData) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"public", "market"});
    ws.connect();
    auto pub = ws.create_stream("a", std::nullopt, std::string("public"));
    auto mkt = ws.create_stream("a", std::nullopt, std::string("market"));
    Collector pub_got;
    Collector mkt_got;
    pub.on_message(pub_got.callback());
    mkt.on_message(mkt_got.callback());
    const auto sessions = server.sessions();
    const auto market = sessions[0].target.starts_with("/market") ? 0U : 1U;
    server.send(market, R"({"stream":"a","data":1})");
    ASSERT_TRUE(eventually([&] { return mkt_got.size() == 1; }));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(pub_got.size(), 0U);
}

TEST(WebsocketStreams, HandleUnsubscribeRemovesCallbacksAndUnsubscribes) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto one = ws.create_stream("a");
    auto two = ws.create_stream("a");
    Collector c1;
    Collector c2;
    one.on_message(c1.callback());
    two.on_message(c2.callback());
    one.unsubscribe();
    EXPECT_TRUE(ws.is_subscribed("a"));
    server.send(0, R"({"stream":"a","data":1})");
    ASSERT_TRUE(eventually([&] { return c2.size() == 1; }));
    EXPECT_EQ(c1.size(), 0U);
    two.unsubscribe();
    EXPECT_FALSE(ws.is_subscribed("a"));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    EXPECT_EQ(methods_of(server.sessions()[0]),
              (std::vector<std::string>{"SUBSCRIBE", "UNSUBSCRIBE"}));
}

TEST(WebsocketStreams, EmptyStreamNameThrows) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    EXPECT_THROW(ws.connect({"a", ""}), WebsocketError);
    EXPECT_THROW(ws.subscribe({"a", ""}), WebsocketError);
    EXPECT_THROW((void)ws.create_stream(""), WebsocketError);
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, DestroyingTheHandleUnsubscribes) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    {
        auto handle = ws.create_stream("a");
        EXPECT_TRUE(ws.is_subscribed("a"));
    }
    ASSERT_TRUE(eventually([&] { return !ws.is_subscribed("a"); }));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    EXPECT_EQ(methods_of(server.sessions()[0]),
              (std::vector<std::string>{"SUBSCRIBE", "UNSUBSCRIBE"}));
}

TEST(WebsocketStreams, AStreamStaysWhileAnyHandleLives) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto first = ws.create_stream("a");
    {
        // Destroyed before `first` gets a callback: the stream must stay subscribed.
        auto second = ws.create_stream("a");
    }
    Collector c;
    first.on_message(c.callback());
    server.send(0, R"({"stream":"a","data":1})");
    ASSERT_TRUE(eventually([&] { return c.size() == 1; }));
    EXPECT_TRUE(ws.is_subscribed("a"));
    first.unsubscribe();
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, ReleasedHandleKeepsTheStream) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    Collector c;
    {
        auto handle = ws.create_stream("a");
        handle.on_message(c.callback());
        handle.release();
    }
    server.send(0, R"({"stream":"a","data":1})");
    ASSERT_TRUE(eventually([&] { return c.size() == 1; }));
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, MoveAssigningOverAHandleUnsubscribesTheOldOne) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto handle = ws.create_stream("a");
    handle = ws.create_stream("b");
    ASSERT_TRUE(eventually([&] { return !ws.is_subscribed("a"); }));
    EXPECT_TRUE(ws.is_subscribed("b"));
    EXPECT_EQ(handle.stream(), "b");
}

TEST(WebsocketStreams, ReconnectResubscribesThroughTheUrl) {
    MockWsServer server;
    EventLog log;
    WebsocketStreams ws(streams_config(server.url()));
    auto sub = ws.on_event(std::ref(log));
    ws.connect({"a"});
    ws.subscribe({"b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=a/b");
    std::this_thread::sleep_for(50ms);
    EXPECT_TRUE(server.sessions()[1].received.empty());
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Open) == 2; }));
}

TEST(WebsocketStreams, SubscriptionsWhileReconnectingAreKept) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    server.set_reject_status(503);
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return !ws.is_connected(); }));
    ws.subscribe({"b"});
    server.set_reject_status(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 10s));
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=a/b");
}

TEST(WebsocketStreams, ChangesDuringARenewalReachTheNewConnection) {
    MockWsServer::Options opts;
    opts.accept_delay = 500ms;
    MockWsServer server({}, opts);
    WebsocketStreams ws(streams_config(server.url()));
    std::optional<RenewalInterval> renewal(std::in_place, 200ms);
    ws.connect({"a"});
    // The renewal's upgrade request is in: its URL is fixed, and it opens after `accept_delay`.
    ASSERT_TRUE(eventually([&] { return server.upgrade_requests() == 2; }));
    renewal.reset();
    ws.subscribe({"b"});
    ws.unsubscribe({"a"});
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 2 && s[1].received.size() == 2; }, 10s));
    const auto renewed = server.sessions()[1];
    EXPECT_EQ(renewed.target, "/stream?streams=a");
    EXPECT_EQ(parse(renewed.received[0]).at("method"), json::value("SUBSCRIBE"));
    EXPECT_EQ(parse(renewed.received[0]).at("params"), json::parse(R"(["b"])"));
    EXPECT_EQ(parse(renewed.received[1]).at("method"), json::value("UNSUBSCRIBE"));
    EXPECT_EQ(parse(renewed.received[1]).at("params"), json::parse(R"(["a"])"));
    // The old connection, still in use until then, got both as well.
    EXPECT_EQ(methods_of(server.sessions()[0]),
              (std::vector<std::string>{"SUBSCRIBE", "UNSUBSCRIBE"}));
    EXPECT_TRUE(ws.is_subscribed("b"));
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, ResubscribeDuringARenewalKeepsTheStream) {
    MockWsServer::Options opts;
    opts.accept_delay = 500ms;
    MockWsServer server({}, opts);
    WebsocketStreams ws(streams_config(server.url()));
    std::optional<RenewalInterval> renewal(std::in_place, 200ms);
    ws.connect({"a"});
    ASSERT_TRUE(eventually([&] { return server.upgrade_requests() == 2; }));
    renewal.reset();
    ws.unsubscribe({"a"});
    ws.subscribe({"a"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 10s));
    std::this_thread::sleep_for(100ms);
    // The URL subscribes it: nothing to send on the new connection.
    EXPECT_TRUE(server.sessions()[1].received.empty());
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, HandleUnsubscribeReusesItsId) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    const std::string id = "0123456789abcdef0123456789abcdef";
    auto handle = ws.create_stream("a", StreamId(id));
    handle.unsubscribe();
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    const auto session = server.sessions()[0];
    for (const auto& r : session.received) {
        EXPECT_EQ(parse(r).at("id"), json::value(id));
    }
}

TEST(WebsocketStreams, DisconnectClearsSubscriptions) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    auto handle = ws.create_stream("b");
    Collector c;
    handle.on_message(c.callback());
    ws.disconnect();
    EXPECT_FALSE(ws.is_connected());
    EXPECT_FALSE(ws.is_subscribed("a"));
    EXPECT_FALSE(ws.is_subscribed("b"));
    ws.connect();
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=");
    server.send(1, R"({"stream":"b","data":1})");
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(c.size(), 0U);
}

TEST(WebsocketStreams, MessageEventsAreEmitted) {
    MockWsServer server;
    EventLog log;
    WebsocketStreams ws(streams_config(server.url()));
    auto sub = ws.on_event(std::ref(log));
    ws.connect();
    server.send(0, R"({"stream":"a","data":1})");
    EXPECT_TRUE(eventually([&] { return log.count(WebsocketEventType::Message) == 1; }));
    EXPECT_EQ(log.last(WebsocketEventType::Message)->data, R"({"stream":"a","data":1})");
}

TEST(WebsocketStreams, MessageEventsAreSkippedUnlessWanted) {
    MockWsServer server;
    EventLog lifecycle;
    EventLog all;
    WebsocketStreams ws(streams_config(server.url()));
    auto sub = ws.on_event(std::ref(lifecycle), false);
    ws.connect();
    server.send(0, R"({"stream":"a","data":1})");
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(lifecycle.count(WebsocketEventType::Message), 0U);
    EXPECT_EQ(lifecycle.count(WebsocketEventType::Open), 1U);

    auto wanting = ws.on_event(std::ref(all));
    server.send(0, R"({"stream":"a","data":2})");
    EXPECT_TRUE(eventually([&] { return all.count(WebsocketEventType::Message) == 1; }));
    EXPECT_EQ(lifecycle.count(WebsocketEventType::Message), 0U);
}

TEST(WebsocketStreams, PingServer) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.ping_server();
    EXPECT_TRUE(server.wait([](const Sessions& s) { return s[0].pings == 1; }));
}

TEST(WebsocketStreams, ConnectsOverTls) {
    MockWsServer::Options opts;
    opts.tls = TestCertificate::get().server_context();
    MockWsServer server({}, opts);
    auto cfg = streams_config(server.url());
    cfg.agent = [](asio::ssl::context& ctx) { TestCertificate::get().trust(ctx); };
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    auto h = ws.create_stream("b");
    Collector c;
    h.on_message(c.callback());
    server.send(0, R"({"stream":"b","data":1})");
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

// ==== Shared executor ====

/// An `io_context` run by `threads` threads until destroyed.
class SharedLoop {
public:
    explicit SharedLoop(int threads) {
        for (int i = 0; i < threads; ++i) {
            threads_.emplace_back([this] { ioc_.run(); });
        }
    }
    ~SharedLoop() {
        guard_.reset();
        for (auto& t : threads_) {
            t.join();
        }
    }
    SharedLoop(const SharedLoop&) = delete;
    SharedLoop& operator=(const SharedLoop&) = delete;
    SharedLoop(SharedLoop&&) = delete;
    SharedLoop& operator=(SharedLoop&&) = delete;

    [[nodiscard]] asio::any_io_executor executor() { return ioc_.get_executor(); }

private:
    asio::io_context ioc_;
    asio::executor_work_guard<asio::io_context::executor_type> guard_ = asio::make_work_guard(ioc_);
    std::vector<std::thread> threads_;
};

TEST(SharedExecutor, ClientsShareOneLoop) {
    MockWsServer api_server(echo);
    MockWsServer streams_server;
    SharedLoop loop(2);
    auto api_cfg = api_config(api_server.url());
    api_cfg.executor = loop.executor();
    api_cfg.mode = WebsocketMode::pool(2);
    auto streams_cfg = streams_config(streams_server.url());
    streams_cfg.executor = loop.executor();

    WebsocketApi api(api_cfg);
    WebsocketStreams ws(streams_cfg);
    api.connect();
    ws.connect();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(api.send_message("m", {}).at(0).result, json::parse(R"({"echo":"m"})"));
    }
    auto h = ws.create_stream("a");
    Collector c;
    h.on_message(c.callback());
    streams_server.send(0, R"({"stream":"a","data":1})");
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

TEST(SharedExecutor, DestroyingConnectedClientsLeavesNoWork) {
    MockWsServer server(echo);
    asio::io_context ioc;
    std::optional<WebsocketApi> api;
    std::optional<WebsocketStreams> ws;
    bool done = false;
    asio::co_spawn(
        ioc,
        [&]() -> asio::awaitable<void> {
            auto api_cfg = api_config(server.url());
            api_cfg.executor = ioc.get_executor();
            auto streams_cfg = streams_config(server.url());
            streams_cfg.executor = ioc.get_executor();
            api.emplace(api_cfg);
            ws.emplace(streams_cfg);
            co_await api->async_connect(asio::use_awaitable);
            co_await ws->async_connect({"a"}, asio::use_awaitable);
            const auto res = co_await api->async_send_message("m", {}, {}, asio::use_awaitable);
            done = res.at(0).result == json::parse(R"({"echo":"m"})");
            // Pending: completes with WebsocketCancelledError when the client goes away.
            api->async_send_message("m", {}, {}, asio::detached);
            api.reset();
            ws.reset();
        },
        asio::detached);
    // run() returns only once the clients' sockets, timers and coroutines are all gone.
    ioc.run();
    EXPECT_TRUE(done);
}

TEST(SharedExecutor, BlockingCallOnTheLoopThrows) {
    MockWsServer server(echo);
    asio::io_context ioc;
    auto cfg = api_config(server.url());
    cfg.executor = ioc.get_executor();
    WebsocketApi api(cfg);
    std::string error;
    api.async_connect([&](std::exception_ptr) {
        try {
            (void)api.send_message("m", {});
        } catch (const WebsocketError& e) {
            error = e.what();
        }
        api.async_disconnect(asio::detached);
    });
    ioc.run();
    EXPECT_NE(error.find("client's executor"), std::string::npos) << error;
}

TEST(SharedExecutor, BlockingCallFromAnotherTaskOnTheLoopThrows) {
    MockWsServer server(echo);
    asio::io_context ioc;
    auto cfg = api_config(server.url());
    cfg.executor = ioc.get_executor();
    WebsocketApi api(cfg);
    std::string error;
    // Not on the client's strand, but on the thread running its executor: waiting would deadlock.
    asio::post(ioc, [&] {
        try {
            api.connect();
        } catch (const WebsocketError& e) {
            error = e.what();
        }
    });
    ioc.run();
    EXPECT_NE(error.find("client's executor"), std::string::npos) << error;
}

// ==== Delivery and threading ====

namespace {

/// Answers `userDataStream.subscribe` with `{"subscriptionId": <session index>}`, then sends one
/// event of that subscription; echoes anything else.
void user_data_server(MockWsServer::Session& s, const std::string& text) {
    const auto req = parse(text);
    if (req.at("method") != json::value("userDataStream.subscribe")) {
        echo(s, text);
        return;
    }
    const auto sub = std::to_string(s.index);
    s.send(R"({"id":")" + id_of(text) + R"(","status":200,"result":{"subscriptionId":)" + sub +
           "}}");
    s.send(R"({"subscriptionId":)" + sub + R"(,"event":{"e":"hello","s":)" + sub + "}}");
}

} // namespace

TEST(WebsocketApi, SubscribeDeliversEventsArrivingBeforeTheCallback) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    EXPECT_EQ(sub.response.result, json::parse(R"({"subscriptionId":0})"));
    std::this_thread::sleep_for(50ms);
    Collector c;
    sub.stream.on_message(c.callback());
    ASSERT_TRUE(eventually([&] { return c.size() == 1; }));
    EXPECT_EQ(c.got[0], json::parse(R"({"e":"hello","s":0})"));
}

TEST(WebsocketApi, SubscribeRoutesBySubscriptionId) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    Collector c;
    sub.stream.on_message(c.callback());
    ASSERT_TRUE(eventually([&] { return c.size() == 1; }));
    server.send(0, R"({"subscriptionId":7,"event":{"e":"other"}})");
    server.send(0, R"({"subscriptionId":0,"event":{"e":"mine"}})");
    ASSERT_TRUE(eventually([&] { return c.size() == 2; }));
    EXPECT_EQ(c.got[1], json::parse(R"({"e":"mine"})"));
}

TEST(WebsocketApi, AsyncSubscribe) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.async_subscribe("userDataStream.subscribe", {}, {}, asio::use_future).get();
    Collector c;
    sub.stream.on_message(c.callback());
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

TEST(WebsocketApi, TypedSubscribe) {
    MockWsServer server(user_data_server);
    auto api = std::make_shared<WebsocketApi>(api_config(server.url()));
    api->connect();
    using Event = std::map<std::string, json::value>;
    auto [res, stream] = binance::common::async_subscribe<std::map<std::string, int>, Event>(
                             api, "userDataStream.subscribe", {}, {}, asio::use_future)
                             .get();
    EXPECT_EQ(res.data().at("subscriptionId"), 0);
    std::promise<json::value> got;
    stream.on_message([&](const Event& e) { got.set_value(e.at("e")); });
    EXPECT_EQ(got.get_future().get(), json::value("hello"));
}

TEST(WebsocketApi, SubscriptionsAreReplayedAfterAReconnect) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    Collector c;
    sub.stream.on_message(c.callback());
    ASSERT_TRUE(eventually([&] { return c.size() == 1; }));
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return c.size() == 2; }));
    EXPECT_EQ(c.got[1], json::parse(R"({"e":"hello","s":1})"));

    sub.stream.unsubscribe();
    server.drop(1);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 3 && s[2].open; }));
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(requests_with_method({server.sessions()[2]}, "userDataStream.subscribe").empty());
}

namespace {

/// The `subscriptionId` of every `userDataStream.unsubscribe` that `session` received.
std::vector<json::value> unsubscribed_ids(const MockWsServer::SessionInfo& session) {
    std::vector<json::value> out;
    for (const auto& r : requests_with_method({session}, "userDataStream.unsubscribe")) {
        out.push_back(parse(r).at("params").at("subscriptionId"));
    }
    return out;
}

} // namespace

TEST(WebsocketApi, UnsubscribingTheStreamEndsTheSubscriptionOnTheServer) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    sub.stream.unsubscribe();
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !unsubscribed_ids(s[0]).empty(); }));
    EXPECT_EQ(unsubscribed_ids(server.sessions()[0]), std::vector<json::value>{0});
}

TEST(WebsocketApi, DestroyingTheStreamEndsTheSubscriptionOnTheServer) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    {
        auto sub = api.subscribe("userDataStream.subscribe", {});
    }
    EXPECT_TRUE(server.wait([](const Sessions& s) { return !unsubscribed_ids(s[0]).empty(); }));
}

TEST(WebsocketApi, UnsubscribingAfterAReconnectUsesTheCurrentSubscriptionId) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    Collector c;
    sub.stream.on_message(c.callback());
    server.drop(0);
    // Sent again on the new socket, which assigns `subscriptionId` 1.
    ASSERT_TRUE(eventually([&] { return c.size() == 2; }));
    sub.stream.unsubscribe();
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 2 && !unsubscribed_ids(s[1]).empty(); }));
    EXPECT_EQ(unsubscribed_ids(server.sessions()[1]), std::vector<json::value>{1});
}

TEST(WebsocketApi, UnsubscribingGoesToTheConnectionHoldingTheSubscription) {
    MockWsServer server(user_data_server);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketApi api(cfg);
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    const auto sessions = server.sessions();
    const std::size_t owner =
        requests_with_method({sessions[0]}, "userDataStream.subscribe").empty() ? 1 : 0;
    // Moves the round-robin on, so that the next request would go to the other connection.
    (void)api.send_message("ping", {});
    sub.stream.unsubscribe();
    ASSERT_TRUE(
        server.wait([owner](const Sessions& s) { return !unsubscribed_ids(s[owner]).empty(); }));
    EXPECT_EQ(unsubscribed_ids(server.sessions()[owner]),
              std::vector<json::value>{static_cast<std::int64_t>(owner)});
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(unsubscribed_ids(server.sessions()[1 - owner]).empty());
}

TEST(WebsocketApi, UnsubscribeSentDirectlyStopsTheResubscription) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    (void)api.send_message("userDataStream.unsubscribe", {{"subscriptionId", 0}});
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(requests_with_method({server.sessions()[1]}, "userDataStream.subscribe").empty());
    // Already ended: the stream sends nothing more.
    sub.stream.unsubscribe();
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(unsubscribed_ids(server.sessions()[1]).empty());
}

TEST(WebsocketApi, SubscriptionsAreReplayedAfterTheRelogon) {
    MockWsServer server;
    server.set_handler([](MockWsServer::Session& s, const std::string& text) {
        user_data_server(s, text);
        if (s.index == 0 && parse(text).at("method") == json::value("userDataStream.subscribe")) {
            s.send(R"({"event":{"e":"serverShutdown"}})");
        }
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    auto sub = api.subscribe("userDataStream.subscribe", {});
    Collector c;
    sub.stream.on_message(c.callback());
    ASSERT_TRUE(eventually([&] { return c.size() == 2; }));
    const auto received = server.sessions()[1].received;
    ASSERT_EQ(received.size(), 2U);
    EXPECT_EQ(parse(received[0]).at("method"), json::value("session.logon"));
    EXPECT_EQ(parse(received[1]).at("method"), json::value("userDataStream.subscribe"));
}

TEST(WebsocketApi, FailedRelogonEmitsAnError) {
    std::atomic<int> logons{0};
    MockWsServer server([&](MockWsServer::Session& s, const std::string& text) {
        if (parse(text).at("method") == json::value("session.logon") && ++logons > 1) {
            s.send(R"({"id":")" + id_of(text) +
                   R"(","status":400,"error":{"code":-1,"msg":"no"}})");
            return;
        }
        echo(s, text);
    });
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto events = api.on_event(std::ref(log));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    server.drop(0);
    EXPECT_TRUE(eventually([&] { return log.has_error_containing("re-logon failed"); }));
}

TEST(WebsocketApi, ResponseErrorsShareTheCommonBase) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        s.send(R"({"id":")" + id_of(text) +
               R"(","status":400,"error":{"code":-1100,"msg":"bad"}})");
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    try {
        (void)api.send_message("m", {});
        FAIL() << "expected an error";
    } catch (const binance::common::Error& e) {
        EXPECT_EQ(e.code(), -1100);
        EXPECT_EQ(e.msg(), "bad");
    }
}

TEST(WebsocketApi, RejectedUpgradeCarriesStatusAndRetryAfter) {
    MockWsServer::Options opts;
    opts.reject_status = 429;
    opts.retry_after = "7";
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    try {
        api.connect();
        FAIL() << "expected WebsocketHandshakeError";
    } catch (const WebsocketHandshakeError& e) {
        EXPECT_EQ(e.status(), 429);
        EXPECT_EQ(e.retry_after(), std::chrono::seconds(7));
    }
}

TEST(WebsocketApi, TransportHookOpensTheConnection) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    std::atomic<int> calls{0};
    cfg.transport = [&](asio::ip::tcp::socket& socket, std::string host,
                        std::uint16_t port) -> asio::awaitable<void> {
        ++calls;
        co_await socket.async_connect({asio::ip::make_address(host), port}, asio::use_awaitable);
    };
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(calls.load(), 1);
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, FailingTransportHookFailsTheConnect) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.transport = [](asio::ip::tcp::socket&, std::string,
                       std::uint16_t) -> asio::awaitable<void> {
        throw std::runtime_error("no route");
        co_return;
    };
    WebsocketApi api(cfg);
    EXPECT_THROW(api.connect(), WebsocketNetworkError);
}

TEST(WebsocketStreams, NoCallbackAfterTheClientIsDestroyed) {
    MockWsServer server;
    std::atomic<bool> destroyed{false};
    std::atomic<int> late{0};
    std::atomic<int> received{0};
    {
        WebsocketStreams ws(streams_config(server.url()));
        ws.connect();
        auto h = ws.create_stream("a");
        h.on_message([&](const json::value&) {
            ++received;
            std::this_thread::sleep_for(1ms);
            if (destroyed) {
                ++late;
            }
        });
        for (int i = 0; i < 200; ++i) {
            server.send(0, R"({"stream":"a","data":1})");
        }
        ASSERT_TRUE(eventually([&] { return received.load() > 0; }));
    }
    destroyed = true;
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(late.load(), 0);
}

TEST(WebsocketStreams, NoCallbackAfterTheHandleIsUnsubscribed) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto h = ws.create_stream("a");
    std::atomic<bool> unsubscribed{false};
    std::atomic<int> late{0};
    std::atomic<int> received{0};
    h.on_message([&](const json::value&) {
        ++received;
        std::this_thread::sleep_for(1ms);
        if (unsubscribed) {
            ++late;
        }
    });
    for (int i = 0; i < 200; ++i) {
        server.send(0, R"({"stream":"a","data":1})");
    }
    ASSERT_TRUE(eventually([&] { return received.load() > 0; }));
    h.unsubscribe();
    unsubscribed = true;
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(late.load(), 0);
}

TEST(WebsocketStreams, SubscribeWithoutAUrlPathUsesAnyConnection) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"public"});
    ws.connect();
    auto h = ws.create_stream("a");
    Collector c;
    h.on_message(c.callback());
    ASSERT_TRUE(
        server.wait([](const Sessions& s) { return s.size() == 1 && !s[0].received.empty(); }));
    server.send(0, R"({"stream":"a","data":1})");
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

TEST(WebsocketStreams, StreamsMoveOffAConnectionThatClosedForGood) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect();
    ws.subscribe({"a"});
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        return s.size() == 2 && s[0].received.size() + s[1].received.size() == 1;
    }));
    const std::size_t first = server.sessions()[0].received.empty() ? 1 : 0;
    server.close(first, 1008);
    ASSERT_TRUE(server.wait([&](const Sessions& s) { return s[1 - first].received.size() == 1; }));
    EXPECT_NE(server.sessions()[1 - first].received[0].find("\"a\""), std::string::npos);
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(SharedExecutor, CallsFromTheLoopThreadDoNotBlock) {
    MockWsServer server;
    asio::io_context ioc;
    auto cfg = streams_config(server.url());
    cfg.executor = ioc.get_executor();
    WebsocketStreams ws(cfg);
    binance::common::WebsocketStreamHandle handle;
    Collector c;
    bool subscribed = false;
    bool connected = false;
    ws.async_connect(std::vector<std::string>{}, [&](std::exception_ptr ep) {
        ASSERT_FALSE(ep);
        connected = ws.is_connected();
        ws.subscribe({"b"});
        subscribed = ws.is_subscribed("b");
        handle = ws.create_stream("a");
        handle.on_message(c.callback());
        auto sub = ws.on_event([](const WebsocketEvent&) {});
        sub.unsubscribe();
        ws.unsubscribe({"b"});
    });
    std::thread feeder([&] {
        // SUBSCRIBE b and a (batched), then UNSUBSCRIBE b.
        if (server.wait(
                [](const Sessions& s) { return s.size() == 1 && s[0].received.size() >= 2; })) {
            server.send(0, R"({"stream":"a","data":1})");
        }
        (void)eventually([&] { return c.size() == 1; });
        asio::post(ioc, [&] { ws.async_disconnect(asio::detached); });
    });
    ioc.run_for(10s);
    feeder.join();
    EXPECT_TRUE(connected);
    EXPECT_TRUE(subscribed);
    EXPECT_EQ(c.size(), 1U);
    EXPECT_FALSE(ws.is_subscribed("b"));
}

// ==== Robustness ====

using binance::common::WebsocketApiRawResponse;

TEST(WebsocketApi, ThrowingCompletionHandlersDoNotStrandOtherRequests) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    WebsocketApi api(api_config(server.url()));
    api.connect();
    std::atomic<int> called{0};
    auto handler = [&](std::exception_ptr, std::vector<WebsocketApiRawResponse>) {
        ++called;
        throw std::runtime_error("handler bug");
    };
    api.async_send_message("a", {}, {}, handler);
    api.async_send_message("b", {}, {}, handler);
    ASSERT_TRUE(eventually([&] { return server.sessions().front().received.size() == 2; }));
    server.drop(0);
    EXPECT_TRUE(eventually([&] { return called.load() == 2; }));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_TRUE(eventually([&] { return api.is_connected(); }));
}

TEST(WebsocketApi, ThrowingConnectHandlerDoesNotStrandOtherConnects) {
    MockWsServer::Options opts;
    opts.accept_delay = 100ms;
    MockWsServer server(echo, opts);
    WebsocketApi api(api_config(server.url()));
    api.async_connect([](std::exception_ptr) { throw std::runtime_error("handler bug"); });
    auto other = api.async_connect(asio::use_future);
    ASSERT_EQ(other.wait_for(5s), std::future_status::ready);
    EXPECT_NO_THROW(other.get());
    EXPECT_EQ(api.send_message("m", {}).size(), 1U);
}

TEST(WebsocketApi, ThrowingCompletionHandlerDoesNotHangTheDestructor) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    auto api = std::make_unique<WebsocketApi>(api_config(server.url()));
    api->connect();
    for (int i = 0; i < 2; ++i) {
        api->async_send_message("a", {}, {},
                                [](std::exception_ptr, std::vector<WebsocketApiRawResponse>) {
                                    throw std::runtime_error("handler bug");
                                });
    }
    ASSERT_TRUE(eventually([&] { return server.sessions().front().received.size() == 2; }));
    // Detached, so that a hung destructor fails the test instead of blocking it.
    const auto destroyed = std::make_shared<std::atomic<bool>>(false);
    std::thread([api = std::shared_ptr<WebsocketApi>(std::move(api)), destroyed]() mutable {
        api.reset();
        *destroyed = true;
    }).detach();
    EXPECT_TRUE(eventually([&] { return destroyed->load(); })) << "destructor hung";
}

TEST(SharedExecutor, RegistrationsDoNotWaitForAnIdleExecutor) {
    MockWsServer server(echo);
    asio::io_context ioc;
    auto cfg = api_config(server.url());
    cfg.executor = ioc.get_executor();
    auto api = std::make_unique<WebsocketApi>(cfg);
    // The io_context is not running: none of these may wait for it.
    auto calls = std::async(std::launch::async, [&] {
        auto sub = api->on_event([](const WebsocketEvent&) {});
        auto handle = api->create_stream();
        handle.on_message([](const json::value&) {});
        handle.unsubscribe();
        sub.unsubscribe();
    });
    EXPECT_EQ(calls.wait_for(2s), std::future_status::ready);
    while (calls.wait_for(0s) != std::future_status::ready) {
        ioc.restart();
        ioc.run_for(50ms);
    }
    api.reset();
    ioc.restart();
    ioc.run_for(200ms);
}

TEST(WebsocketApi, SubscribeAnsweredDuringARenewalIsSentAgain) {
    MockWsServer server;
    server.set_handler([&server](MockWsServer::Session& s, const std::string& text) {
        const auto req = parse(text);
        if (s.index == 0 && req.at("method") == json::value("userDataStream.subscribe")) {
            // Renew before answering, and answer on the old socket once the new one is open.
            s.send(R"({"event":{"e":"serverShutdown"}})");
            std::thread([&server, id = id_of(text)] {
                if (server.wait([](const Sessions& all) { return all.size() == 2; })) {
                    std::this_thread::sleep_for(100ms);
                    server.send(0, R"({"id":")" + id +
                                       R"(","status":200,"result":{"subscriptionId":0}})");
                }
            }).detach();
            return;
        }
        echo(s, text);
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    std::atomic<int> got{0};
    sub.stream.on_message([&](const json::value&) { ++got; });
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        return s.size() == 2 && !s[0].open &&
               !requests_with_method({s[1]}, "userDataStream.subscribe").empty();
    }));
    std::this_thread::sleep_for(100ms);
    server.send(1, R"({"subscriptionId":0,"event":{"e":"executionReport"}})");
    EXPECT_TRUE(eventually([&] { return got.load() == 1; }));
}

TEST(WebsocketApi, LogonAnsweredDuringARenewalLogsTheNewSocketOn) {
    MockWsServer server;
    server.set_handler([&server](MockWsServer::Session& s, const std::string& text) {
        const auto req = parse(text);
        if (s.index == 0 && req.at("method") == json::value("session.logon")) {
            s.send(R"({"event":{"e":"serverShutdown"}})");
            std::thread([&server, id = id_of(text)] {
                if (server.wait([](const Sessions& all) { return all.size() == 2; })) {
                    std::this_thread::sleep_for(100ms);
                    server.send(0, R"({"id":")" + id + R"(","status":200,"result":{}})");
                }
            }).detach();
            return;
        }
        echo(s, text);
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    (void)api.send_message("session.logon", {}, logon_opts());
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        return s.size() == 2 && !requests_with_method({s[1]}, "session.logon").empty();
    }));
    std::this_thread::sleep_for(100ms);
    (void)api.send_message("order.place", {}, signed_opts());
    // The new socket was logged on before requests skipped authentication.
    const auto received = server.sessions()[1].received;
    const auto method_at = [&](std::size_t i) { return parse(received[i]).at("method"); };
    std::size_t logon = received.size();
    for (std::size_t i = 0; i < received.size(); ++i) {
        if (method_at(i) == json::value("session.logon") && logon == received.size()) {
            logon = i;
        }
        if (method_at(i) == json::value("order.place")) {
            EXPECT_TRUE(i > logon ||
                        parse(received[i]).at("params").as_object().contains("signature"));
        }
    }
    EXPECT_LT(logon, received.size());
}

TEST(WebsocketApi, RenewalKeepsTheOldSocketUntilSubscriptionsAreRestored) {
    MockWsServer server;
    std::atomic<bool> answered{false};
    std::atomic<bool> old_open_when_answered{false};
    server.set_handler([&](MockWsServer::Session& s, const std::string& text) {
        if (s.index == 1 && parse(text).at("method") == json::value("userDataStream.subscribe")) {
            std::thread([&server, &answered, &old_open_when_answered, id = id_of(text)] {
                std::this_thread::sleep_for(300ms);
                old_open_when_answered = server.sessions()[0].open;
                server.send(1,
                            R"({"id":")" + id + R"(","status":200,"result":{"subscriptionId":1}})");
                answered = true;
            }).detach();
            return;
        }
        echo(s, text);
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    server.send(0, R"({"event":{"e":"serverShutdown"}})");
    ASSERT_TRUE(eventually([&] { return answered.load(); }));
    EXPECT_TRUE(old_open_when_answered.load());
    // Closed once the subscription moved.
    EXPECT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && !s[0].open; }));
}

TEST(WebsocketApi, ConnectDuringADisconnectConnectsAfterIt) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {});
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto unanswered = api.async_send_message("m", {}, {}, asio::use_future);
    ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    auto disconnected = api.async_disconnect(asio::use_future);
    std::this_thread::sleep_for(100ms);
    api.connect();
    EXPECT_THROW((void)unanswered.get(), WebsocketTimeoutError);
    EXPECT_NO_THROW(disconnected.get());
    EXPECT_TRUE(api.is_connected());
    EXPECT_EQ(server.session_count(), 2U);
    EXPECT_FALSE(server.sessions()[0].open);
}

TEST(WebsocketApi, SubscribeWhileDisconnectingFails) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        if (parse(text).at("method") != json::value("m")) {
            echo(s, text);
        }
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto unanswered = api.async_send_message("m", {}, {}, asio::use_future);
    ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    auto disconnected = api.async_disconnect(asio::use_future);
    std::this_thread::sleep_for(100ms);
    EXPECT_THROW((void)api.subscribe("userDataStream.subscribe", {}), WebsocketNotConnectedError);
    EXPECT_TRUE(requests_with_method(server.sessions(), "userDataStream.subscribe").empty());
    EXPECT_THROW((void)unanswered.get(), WebsocketTimeoutError);
    disconnected.get();
}

TEST(WebsocketApi, ServerShutdownOnAReplacedSocketIsIgnored) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        if (parse(text).at("method") != json::value("slow")) {
            echo(s, text);
        }
    });
    WebsocketApi api(api_config(server.url()));
    api.connect();
    // Keeps the old socket open after the renewal.
    auto slow = api.async_send_message("slow", {}, {}, asio::use_future);
    ASSERT_TRUE(eventually([&] { return !server.sessions().front().received.empty(); }));
    server.send(0, R"({"event":{"e":"serverShutdown"}})");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    server.send(0, R"({"event":{"e":"serverShutdown"}})");
    std::this_thread::sleep_for(1200ms);
    EXPECT_EQ(server.session_count(), 2U);
    EXPECT_THROW((void)slow.get(), WebsocketTimeoutError);
}

TEST(WebsocketApi, SessionLogonReachesReconnectingConnections) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    cfg.reconnect_delay = 300ms;
    WebsocketApi api(cfg);
    api.connect();
    server.drop(1);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[1].open; }));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(api.send_message("session.logon", {}, logon_opts()).size(), 1U);
    ASSERT_TRUE(
        server.wait([](const Sessions& s) { return s.size() == 3 && !s[2].received.empty(); }));
    EXPECT_EQ(parse(server.sessions()[2].received.front()).at("method"),
              json::value("session.logon"));
}

TEST(WebsocketApi, SessionLogoutForgetsTheLogonOfReconnectingConnections) {
    MockWsServer server(echo);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    cfg.reconnect_delay = 300ms;
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_EQ(api.send_message("session.logon", {}, logon_opts()).size(), 2U);
    server.drop(1);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[1].open; }));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(api.send_message("session.logout", {}, logout_opts()).size(), 1U);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 3 && s[2].open; }));
    std::this_thread::sleep_for(100ms);
    EXPECT_TRUE(requests_with_method({server.sessions()[2]}, "session.logon").empty());
}

TEST(WebsocketStreams, ReconnectsAfterANormalServerClose) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    server.close(0, 1000);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=a");
    EXPECT_TRUE(eventually([&] { return ws.is_connected(); }));
}

// ==== WebSocket streams: subscriptions ====

namespace {

/// Whether a session from `from` on has `needle` in its URL or in a message it received.
bool any_has(const Sessions& sessions, std::size_t from, const std::string& needle) {
    for (std::size_t i = from; i < sessions.size(); ++i) {
        if (sessions[i].target.find(needle) != std::string::npos ||
            std::any_of(sessions[i].received.begin(), sessions[i].received.end(),
                        [&](const auto& r) { return r.find(needle) != std::string::npos; })) {
            return true;
        }
    }
    return false;
}

/// The streams in the URL of a session.
std::vector<std::string> url_streams(const std::string& target) {
    std::vector<std::string> out;
    const auto start = target.find("streams=");
    if (start == std::string::npos) {
        return out;
    }
    std::string rest = target.substr(start + 8);
    rest = rest.substr(0, rest.find('&'));
    for (std::size_t pos = 0; !rest.empty() && pos != std::string::npos;) {
        const auto next = rest.find('/', pos);
        out.push_back(rest.substr(pos, next == std::string::npos ? next : next - pos));
        pos = next == std::string::npos ? next : next + 1;
    }
    return out;
}

/// Answers SUBSCRIBE / UNSUBSCRIBE like Binance, rejecting the streams named `bad*`.
void stream_server(MockWsServer::Session& s, const std::string& text) {
    const auto req = parse(text);
    const auto& params = req.at("params").as_array();
    const bool bad = std::any_of(params.begin(), params.end(),
                                 [](const auto& p) { return p.as_string().starts_with("bad"); });
    json::object res;
    res["id"] = req.at("id");
    if (bad) {
        res["error"] = json::object{{"code", 2}, {"msg", "Invalid request"}};
    } else {
        res["result"] = nullptr;
    }
    s.send(json::serialize(res));
}

} // namespace

TEST(WebsocketStreams, CreateStreamWhileThePoolReconnectsIsKept) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect();
    server.set_reject_status(503);
    server.drop_all();
    ASSERT_TRUE(eventually([&] { return !ws.is_connected(); }));
    auto h = ws.create_stream("xyz@trade");
    Collector c;
    h.on_message(c.callback());
    EXPECT_TRUE(ws.is_subscribed("xyz@trade"));
    server.set_reject_status(0);
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 4 && s[2].open && s[3].open; }, 15s));
    EXPECT_TRUE(any_has(server.sessions(), 2, "xyz@trade"));
    server.broadcast(R"({"stream":"xyz@trade","data":1})");
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

TEST(WebsocketStreams, PoolReconnectsWhenEveryMemberIsLost) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect();
    auto h = ws.create_stream("xyz@trade");
    Collector c;
    h.on_message(c.callback());
    server.drop_all();
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 4 && s[2].open && s[3].open; }, 15s));
    ASSERT_TRUE(eventually([&] { return ws.is_connected(); }));
    EXPECT_TRUE(any_has(server.sessions(), 2, "xyz@trade"));
    server.broadcast(R"({"stream":"xyz@trade","data":1})");
    EXPECT_TRUE(eventually([&] { return c.size() == 1; }));
}

TEST(WebsocketStreams, SubscriptionWhileAUrlPathReconnectsIsKept) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()), {"market"});
    ws.connect();
    server.set_reject_status(503);
    server.drop_all();
    ASSERT_TRUE(eventually([&] { return !ws.is_connected(); }));
    auto h = ws.create_stream("xyz@trade", std::nullopt, std::string("market"));
    server.set_reject_status(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 15s));
    EXPECT_EQ(server.sessions()[1].target, "/market/stream?streams=xyz@trade");
}

TEST(WebsocketStreams, SubscriptionsAfterDisconnectAreSentOnConnect) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    ws.disconnect();
    ws.subscribe({"b"});
    auto h = ws.create_stream("c");
    EXPECT_TRUE(ws.is_subscribed("b"));
    EXPECT_FALSE(ws.is_subscribed("a"));
    ws.connect();
    const auto sessions = server.sessions();
    ASSERT_EQ(sessions.size(), 4U);
    std::set<std::string> streams;
    for (std::size_t i = 2; i < 4; ++i) {
        for (const auto& stream : url_streams(sessions[i].target)) {
            streams.insert(stream);
        }
    }
    EXPECT_EQ(streams, (std::set<std::string>{"b", "c"}));
}

TEST(WebsocketStreams, ConnectDuringADisconnectPutsTheStreamsInTheUrl) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    ws.async_disconnect(asio::detached);
    ws.connect({"a"});
    ASSERT_EQ(server.session_count(), 2U);
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=a");
    EXPECT_TRUE(server.sessions()[0].received.empty());
    EXPECT_TRUE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, SubscriptionsSkipAConnectionThatFailedForGood) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect();
    server.close(0, 1008);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].open; }));
    ASSERT_TRUE(eventually([&] { return server.open_count() == 1; }));
    std::this_thread::sleep_for(100ms);
    for (int i = 0; i < 4; ++i) {
        ws.subscribe({"s" + std::to_string(i)});
    }
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        std::size_t n = 0;
        for (const auto& r : s[1].received) {
            n += parse(r).at("params").as_array().size();
        }
        return n == 4;
    }));
    for (int i = 0; i < 4; ++i) {
        EXPECT_TRUE(ws.is_subscribed("s" + std::to_string(i)));
    }
    // connect() opens the failed connection again.
    ws.connect();
    EXPECT_EQ(server.session_count(), 3U);
}

TEST(WebsocketStreams, NoDuplicateWhenAStreamMovesOffAReconnectingConnection) {
    MockWsServer::Options opts;
    opts.accept_delay = 600ms;
    MockWsServer server({}, opts);
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    auto h = ws.create_stream("a");
    Collector c;
    h.on_message(c.callback());
    const auto sessions = server.sessions();
    const std::size_t first = sessions[0].target == "/stream?streams=a" ? 0 : 1;
    server.drop(first);
    // The reconnect's URL, with `a`, is fixed: `a` moves to the other connection meanwhile.
    ASSERT_TRUE(eventually([&] { return server.upgrade_requests() == 3; }));
    ws.subscribe({"a"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 3 && s[2].open; }, 5s));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[2].received.empty(); }));
    EXPECT_EQ(parse(server.sessions()[2].received[0]).at("method"), json::value("UNSUBSCRIBE"));
    server.broadcast(R"({"stream":"a","data":1})");
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(c.size(), 1U);
}

TEST(WebsocketStreams, StaleHandleAfterDisconnectDoesNothing) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    std::optional<binance::common::WebsocketStreamHandle> stale(ws.create_stream("a"));
    ws.disconnect();
    ws.connect();
    auto h = ws.create_stream("a");
    ASSERT_TRUE(
        server.wait([](const Sessions& s) { return s.size() == 2 && s[1].received.size() == 1; }));
    Collector late;
    stale->on_message(late.callback());
    stale.reset();
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(server.sessions()[1].received.size(), 1U);
    EXPECT_TRUE(ws.is_subscribed("a"));
    server.send(1, R"({"stream":"a","data":1})");
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(late.size(), 0U);
}

TEST(WebsocketStreams, SubscriptionsAreBatched) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    std::vector<binance::common::WebsocketStreamHandle> handles;
    // Calls made from the client's executor are batched deterministically; calls from other
    // threads are batched when they reach the executor together.
    const auto on_executor = [&](auto f) {
        std::promise<void> done;
        boost::asio::post(ws.get_executor(), [&] {
            f();
            done.set_value();
        });
        done.get_future().wait();
    };
    on_executor([&] {
        for (int i = 0; i < 20; ++i) {
            handles.push_back(ws.create_stream("s" + std::to_string(i)));
        }
    });
    const auto params = [](const Sessions& s, const std::string& method) {
        std::size_t n = 0;
        std::size_t frames = 0;
        for (const auto& r : s[0].received) {
            if (parse(r).at("method") == json::value(method)) {
                n += parse(r).at("params").as_array().size();
                ++frames;
            }
        }
        return std::pair{n, frames};
    };
    ASSERT_TRUE(server.wait([&](const Sessions& s) { return params(s, "SUBSCRIBE").first == 20; }));
    EXPECT_EQ(params(server.sessions(), "SUBSCRIBE").second, 1U);
    on_executor([&] { handles.clear(); });
    ASSERT_TRUE(
        server.wait([&](const Sessions& s) { return params(s, "UNSUBSCRIBE").first == 20; }));
    EXPECT_EQ(params(server.sessions(), "UNSUBSCRIBE").second, 1U);
    EXPECT_FALSE(ws.is_subscribed("s0"));
}

TEST(WebsocketStreams, RejectedSubscribeDropsTheStreams) {
    MockWsServer server(stream_server);
    EventLog log;
    WebsocketStreams ws(streams_config(server.url()));
    auto sub = ws.on_event(std::ref(log));
    ws.connect();
    ws.subscribe({"bad1"});
    ws.subscribe({"good"}, StreamId(std::uint32_t{7}));
    ASSERT_TRUE(eventually([&] { return !ws.is_subscribed("bad1"); }));
    EXPECT_TRUE(log.has_error_containing("SUBSCRIBE failed for bad1: Invalid request"));
    EXPECT_TRUE(ws.is_subscribed("good"));
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_EQ(server.sessions()[1].target, "/stream?streams=good");
}

TEST(WebsocketStreams, WaitSubscribedCompletesOnceTheServerAcknowledges) {
    MockWsServer server(stream_server);
    WebsocketStreams ws(streams_config(server.url()));
    // Before connect(): through the URL, once the connection opens.
    auto early = ws.create_stream("early");
    auto waiting = ws.async_wait_subscribed("early", std::nullopt, boost::asio::use_future);
    EXPECT_EQ(waiting.wait_for(200ms), std::future_status::timeout);
    ws.connect();
    ASSERT_EQ(waiting.wait_for(5s), std::future_status::ready);
    EXPECT_NO_THROW(waiting.get());
    // Once connected: by its SUBSCRIBE and the response.
    auto late = ws.create_stream("late");
    EXPECT_NO_THROW(ws.wait_subscribed("late"));
    // Acknowledged already: at once, also after a reconnect.
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }));
    EXPECT_NO_THROW(ws.wait_subscribed("early"));
}

TEST(WebsocketStreams, WaitSubscribedFailsForARejectedSubscription) {
    MockWsServer server(stream_server);
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto bad = ws.create_stream("bad1");
    try {
        ws.wait_subscribed("bad1");
        ADD_FAILURE() << "a rejected SUBSCRIBE must fail the wait";
    } catch (const WebsocketResponseError& e) {
        EXPECT_EQ(e.code(), 2);
        EXPECT_NE(std::string(e.what()).find("Invalid request"), std::string::npos);
    }
    // A wait that starts after the rejection gets it too.
    EXPECT_THROW(ws.wait_subscribed("bad1"), WebsocketResponseError);
    // Never subscribed.
    EXPECT_THROW(ws.wait_subscribed("other"), WebsocketCancelledError);
}

TEST(WebsocketStreams, WaitSubscribedIsCancelledWhenTheSubscriptionEnds) {
    MockWsServer server; // never answers a SUBSCRIBE
    auto ws = std::make_unique<WebsocketStreams>(streams_config(server.url()));
    ws->connect();
    auto first = ws->create_stream("first");
    auto second = ws->create_stream("second");
    auto third = ws->create_stream("third");
    auto unsubscribed = ws->async_wait_subscribed("first", std::nullopt, boost::asio::use_future);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    EXPECT_EQ(unsubscribed.wait_for(100ms), std::future_status::timeout);

    first.unsubscribe();
    ASSERT_EQ(unsubscribed.wait_for(5s), std::future_status::ready);
    EXPECT_THROW(unsubscribed.get(), WebsocketCancelledError);

    auto disconnected = ws->async_wait_subscribed("second", std::nullopt, boost::asio::use_future);
    ws->disconnect();
    ASSERT_EQ(disconnected.wait_for(5s), std::future_status::ready);
    EXPECT_THROW(disconnected.get(), WebsocketCancelledError);

    ws->connect();
    auto again = ws->create_stream("third");
    auto destroyed = ws->async_wait_subscribed("third", std::nullopt, boost::asio::use_future);
    ws.reset();
    ASSERT_EQ(destroyed.wait_for(5s), std::future_status::ready);
    EXPECT_THROW(destroyed.get(), WebsocketCancelledError);
}

TEST(WebsocketStreams, WaitSubscribedEndsOnCancellationOrTimeout) {
    MockWsServer server; // never answers a SUBSCRIBE
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto stream = ws.create_stream("slow");
    boost::asio::cancellation_signal signal;
    auto waiting = ws.async_wait_subscribed(
        "slow", std::nullopt,
        boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    EXPECT_EQ(waiting.wait_for(100ms), std::future_status::timeout);
    signal.emit(boost::asio::cancellation_type::terminal);
    ASSERT_EQ(waiting.wait_for(5s), std::future_status::ready);
    EXPECT_THROW(waiting.get(), WebsocketCancelledError);
    // The subscription stays.
    EXPECT_TRUE(ws.is_subscribed("slow"));

    const auto start = std::chrono::steady_clock::now();
    EXPECT_THROW(ws.wait_subscribed("slow", std::nullopt, 200ms), WebsocketTimeoutError);
    EXPECT_GE(std::chrono::steady_clock::now() - start, 200ms);
    EXPECT_TRUE(ws.is_subscribed("slow"));
}

TEST(WebsocketStreams, HandleWaitSubscribed) {
    MockWsServer server(stream_server);
    auto ws = std::make_unique<WebsocketStreams>(streams_config(server.url()));
    ws->connect();
    auto good = ws->create_stream("good");
    EXPECT_NO_THROW(good.wait_subscribed());
    auto typed = WebsocketStream<json::value>(ws->create_stream("typed"));
    auto waiting = typed.async_wait_subscribed(boost::asio::use_future);
    ASSERT_EQ(waiting.wait_for(5s), std::future_status::ready);
    EXPECT_NO_THROW(waiting.get());
    auto bad = ws->create_stream("bad1");
    EXPECT_THROW(bad.wait_subscribed(), WebsocketResponseError);
    // Unsubscribed, released, empty, or the client is gone.
    good.unsubscribe();
    EXPECT_THROW(good.wait_subscribed(), WebsocketCancelledError);
    WebsocketStreamHandle empty;
    EXPECT_THROW(empty.wait_subscribed(), WebsocketCancelledError);
    ws.reset();
    EXPECT_THROW(typed.wait_subscribed(), WebsocketCancelledError);
}

TEST(WebsocketStreams, HandleWaitSubscribedTimesOut) {
    MockWsServer server; // never answers a SUBSCRIBE
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    auto stream = ws.create_stream("slow");
    EXPECT_THROW(stream.wait_subscribed(200ms), WebsocketTimeoutError);
    EXPECT_TRUE(ws.is_subscribed("slow"));
}

TEST(WebsocketApi, UserDataHandleWaitSubscribedCompletesAtOnce) {
    MockWsServer server(user_data_server);
    WebsocketApi api(api_config(server.url()));
    api.connect();
    auto sub = api.subscribe("userDataStream.subscribe", {});
    EXPECT_NO_THROW(sub.stream.wait_subscribed(1s));
}

TEST(WebsocketStreams, AnUnsubscribedStreamForgetsItsRejection) {
    MockWsServer server(stream_server);
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    {
        auto bad = ws.create_stream("bad1");
        EXPECT_THROW(ws.wait_subscribed("bad1"), WebsocketResponseError);
    } // the handle unsubscribes
    EXPECT_THROW(ws.wait_subscribed("bad1"), WebsocketCancelledError);
}

TEST(WebsocketStreams, StreamsBeyondTheUrlLimitAreSubscribedOnOpen) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    std::vector<std::string> streams;
    for (int i = 0; i < 500; ++i) {
        streams.push_back("stream_number_" + std::to_string(i) + "@trade");
    }
    ws.connect(streams);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    const auto session = server.sessions()[0];
    EXPECT_LE(server.url().size() + session.target.size(), 4096U);
    const auto in_url = url_streams(session.target).size();
    EXPECT_GT(in_url, 0U);
    const auto req = parse(session.received[0]);
    EXPECT_EQ(req.at("method"), json::value("SUBSCRIBE"));
    EXPECT_EQ(in_url + req.at("params").as_array().size(), streams.size());
}

TEST(WebsocketStreams, StreamsBeyondTheConnectionLimitGoToThePool) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg);
    std::vector<std::string> streams;
    for (int i = 0; i < 1100; ++i) {
        streams.push_back("s" + std::to_string(i));
    }
    ws.connect(streams);
    // In the URL, or subscribed once open when the URL would be too long.
    const auto count = [](const MockWsServer::SessionInfo& s) {
        auto n = url_streams(s.target).size();
        for (const auto& r : s.received) {
            n += parse(r).at("params").as_array().size();
        }
        return n;
    };
    ASSERT_TRUE(server.wait(
        [&](const Sessions& s) { return s.size() == 2 && count(s[0]) + count(s[1]) == 1100; }));
    for (const auto& s : server.sessions()) {
        EXPECT_LE(count(s), 1024U);
    }
}

TEST(WebsocketStreams, RenewalKeepsDeliveringFromThePreviousSocketUntilTheNewOneDoes) {
    MockWsServer::Options opts;
    opts.accept_delay = 300ms;
    MockWsServer server({}, opts);
    WebsocketStreams ws(streams_config(server.url()));
    std::optional<RenewalInterval> renewal(std::in_place, 200ms);
    ws.connect({"a"});
    auto ha = ws.create_stream("a");
    Collector a;
    ha.on_message(a.callback());
    ASSERT_TRUE(eventually([&] { return server.upgrade_requests() == 2; }));
    renewal.reset();
    // Subscribed by the new socket once it opens, never answered: the previous one stays.
    ws.subscribe({"b"});
    auto hb = ws.create_stream("b");
    Collector b;
    hb.on_message(b.callback());
    ASSERT_TRUE(server.wait(
        [](const Sessions& s) { return s.size() == 2 && s[1].open && !s[1].received.empty(); }));
    std::this_thread::sleep_for(50ms);
    server.send(0, R"({"stream":"a","data":1})");
    server.send(0, R"({"stream":"b","data":1})");
    ASSERT_TRUE(eventually([&] { return a.size() == 1 && b.size() == 1; }));
    // Once the new socket delivers `a`, the previous one no longer does.
    server.send(1, R"({"stream":"a","data":2})");
    ASSERT_TRUE(eventually([&] { return a.size() == 2; }));
    server.send(0, R"({"stream":"a","data":3})");
    server.send(0, R"({"stream":"b","data":2})");
    ASSERT_TRUE(eventually([&] { return b.size() == 2; }));
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(a.size(), 2U);
}

TEST(WebsocketStreams, IsSubscribedReflectsEachCallAtOnce) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    for (int i = 0; i < 200; ++i) {
        ws.subscribe({"a"});
        ASSERT_TRUE(ws.is_subscribed("a"));
        ws.unsubscribe({"a"});
        ASSERT_FALSE(ws.is_subscribed("a"));
    }
    std::this_thread::sleep_for(50ms);
    EXPECT_FALSE(ws.is_subscribed("a"));
}

TEST(WebsocketStreams, BoundCallbacksStopAfterUnsubscribeAndAreContained) {
    MockWsServer server;
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect();
    asio::io_context ioc;
    auto h = ws.create_stream("a");
    std::atomic<int> calls{0};
    h.on_message(asio::bind_executor(ioc, [&](const json::value&) {
        ++calls;
        throw std::runtime_error("boom");
    }));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    server.send(0, R"({"stream":"a","data":1})");
    ASSERT_TRUE(eventually([&] {
        ioc.restart();
        return ioc.poll() > 0;
    }));
    EXPECT_EQ(calls.load(), 1);
    // Queued on the idle io_context, then unsubscribed: it does not run.
    server.send(0, R"({"stream":"a","data":2})");
    std::this_thread::sleep_for(100ms);
    h.unsubscribe();
    ioc.restart();
    ioc.poll();
    EXPECT_EQ(calls.load(), 1);
}

TEST(SharedExecutor, StreamCallsDoNotWaitForAnIdleExecutor) {
    MockWsServer server;
    asio::io_context ioc;
    auto cfg = streams_config(server.url());
    cfg.executor = ioc.get_executor();
    auto ws = std::make_unique<WebsocketStreams>(
        cfg, std::vector<std::string>{},
        binance::common::detail::ClientOptions{
            .user_agent = {}, .signed_streams = false, .stream_id_is_strictly_number = true});
    // The io_context is not running: none of these may wait for it.
    auto calls = std::async(std::launch::async, [&] {
        auto handle = ws->create_stream("a", StreamId(std::uint32_t{5}));
        handle.on_message([](const json::value&) {});
        ws->subscribe({"b"});
        const bool subscribed = ws->is_subscribed("a") && ws->is_subscribed("b");
        ws->unsubscribe({"b"});
        handle.unsubscribe();
        return subscribed && !ws->is_subscribed("a") && !ws->is_subscribed("b");
    });
    ASSERT_EQ(calls.wait_for(2s), std::future_status::ready);
    EXPECT_TRUE(calls.get());
    ws.reset();
    ioc.run_for(200ms);
}

// ==== Signed WebsocketStreams ====

namespace {

using binance::common::PrivateKey;
using binance::common::SignatureGenerator;

/// Shortens the PING interval of signed connections opened while it lives.
class SignedPingInterval {
public:
    explicit SignedPingInterval(std::chrono::milliseconds interval) {
        binance::common::detail::set_signed_ping_interval_for_testing(interval);
    }
    ~SignedPingInterval() { binance::common::detail::set_signed_ping_interval_for_testing({}); }
    SignedPingInterval(const SignedPingInterval&) = delete;
    SignedPingInterval& operator=(const SignedPingInterval&) = delete;
    SignedPingInterval(SignedPingInterval&&) = delete;
    SignedPingInterval& operator=(SignedPingInterval&&) = delete;
};

/// What a product with signed streams passes to its client.
const binance::common::detail::ClientOptions kSigned{.user_agent = {}, .signed_streams = true};

WebsocketStreamsConfig signed_config(const std::string& url) {
    auto cfg = streams_config(url);
    cfg.api_key = "the-api-key";
    cfg.api_secret = "the-api-secret";
    return cfg;
}

std::string percent_decode(const std::string& in) {
    std::string out;
    for (std::size_t i = 0; i < in.size(); ++i) {
        if (in[i] == '%' && i + 2 < in.size()) {
            out += static_cast<char>(std::stoi(in.substr(i + 1, 2), nullptr, 16));
            i += 2;
        } else {
            out += in[i];
        }
    }
    return out;
}

/// The parameters of a request target, in order, percent-decoded.
std::vector<std::pair<std::string, std::string>> query_of(const std::string& target) {
    std::vector<std::pair<std::string, std::string>> out;
    auto rest = target.substr(target.find('?') + 1);
    for (std::size_t pos = 0; pos <= rest.size();) {
        auto end = rest.find('&', pos);
        end = end == std::string::npos ? rest.size() : end;
        const auto item = rest.substr(pos, end - pos);
        const auto eq = item.find('=');
        out.emplace_back(item.substr(0, eq), percent_decode(item.substr(eq + 1)));
        pos = end + 1;
    }
    return out;
}

/// The part of the query that is signed.
std::string signed_part(const std::vector<std::pair<std::string, std::string>>& q) {
    return q[0].first + "=" + q[0].second + "&" + q[1].first + "=" + q[1].second + "&" +
           q[2].first + "=" + q[2].second;
}

void expect_signed_query(const std::string& target, const SignatureGenerator& signer) {
    const auto q = query_of(target);
    ASSERT_EQ(q.size(), 4U) << target;
    EXPECT_EQ(q[0].first, "random");
    EXPECT_EQ(q[0].second.size(), 32U);
    EXPECT_EQ(q[1], (std::pair<std::string, std::string>{"recvWindow", "30000"}));
    EXPECT_EQ(q[2].first, "timestamp");
    EXPECT_EQ(q[3].first, "signature");
    EXPECT_EQ(q[3].second, signer.sign_payload(signed_part(q)));
}

const SignatureGenerator kHmac{"the-api-secret", std::nullopt, std::nullopt};

std::vector<json::object> commands_of(const MockWsServer::SessionInfo& s) {
    std::vector<json::object> out;
    for (const auto& r : s.received) {
        out.push_back(parse(r));
    }
    return out;
}

std::string topic_message(const std::string& topic, const std::string& data) {
    return json::serialize(json::object{{"topic", topic}, {"data", data}});
}

} // namespace

TEST(SignedStreams, HandshakeCarriesTheApiKeyAndASignedUrl) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect({"a", "b"});
    const auto session = server.sessions().front();
    EXPECT_EQ(session.headers.at("x-mbx-apikey"), "the-api-key");
    expect_signed_query(session.target, kHmac);
    EXPECT_EQ(session.target.find("streams"), std::string::npos);
    EXPECT_EQ(session.target.find("timeUnit"), std::string::npos);
}

TEST(SignedStreams, TimeUnitDoesNotApply) {
    MockWsServer server;
    auto cfg = signed_config(server.url());
    cfg.time_unit = TimeUnit::Microsecond;
    WebsocketStreams ws(cfg, {}, kSigned);
    ws.connect();
    EXPECT_EQ(server.sessions().front().target.find("timeUnit"), std::string::npos);
}

TEST(SignedStreams, QueryIsAppendedToAnExistingOne) {
    MockWsServer server;
    auto cfg = signed_config(server.url() + "/sapi/wss?x=1");
    WebsocketStreams ws(cfg, {}, kSigned);
    ws.connect();
    const auto target = server.sessions().front().target;
    EXPECT_TRUE(target.starts_with("/sapi/wss?x=1&random=")) << target;
}

TEST(SignedStreams, PrivateKeysSign) {
    for (const auto& key : {binance::test::generate_ed25519(), binance::test::generate_rsa()}) {
        MockWsServer server;
        auto cfg = signed_config(server.url());
        cfg.api_secret.reset();
        cfg.private_key = PrivateKey::from_pem(binance::test::private_pem(key));
        WebsocketStreams ws(cfg, {}, kSigned);
        ws.connect();
        const auto q = query_of(server.sessions().front().target);
        ASSERT_EQ(q.size(), 4U);
        EXPECT_TRUE(binance::test::verify(key, signed_part(q), q[3].second));
    }
}

TEST(SignedStreams, MissingCredentialsThrow) {
    auto cfg = signed_config("ws://127.0.0.1:1");
    cfg.api_key.reset();
    EXPECT_THROW(WebsocketStreams(cfg, {}, kSigned), ConfigError);
    cfg.api_key = "";
    EXPECT_THROW(WebsocketStreams(cfg, {}, kSigned), ConfigError);
    cfg = signed_config("ws://127.0.0.1:1");
    cfg.api_secret.reset();
    EXPECT_THROW(WebsocketStreams(cfg, {}, kSigned), ConfigError);
    cfg.private_key =
        PrivateKey::from_pem(binance::test::private_pem(binance::test::generate_ed25519()));
    EXPECT_NO_THROW(WebsocketStreams(cfg, {}, kSigned));
}

TEST(SignedStreams, UnsignedClientIgnoresCredentials) {
    MockWsServer server;
    auto cfg = streams_config(server.url());
    cfg.api_key = "the-api-key";
    WebsocketStreams ws(cfg);
    ws.connect({"a"});
    const auto session = server.sessions().front();
    EXPECT_EQ(session.target, "/stream?streams=a");
    EXPECT_FALSE(session.headers.contains("x-mbx-apikey"));
}

TEST(SignedStreams, ConfigOutputRedactsTheCredentials) {
    auto cfg = signed_config("wss://example");
    cfg.private_key = PrivateKey::from_pem("-----BEGIN PRIVATE KEY-----secret");
    cfg.private_key_passphrase = "the-passphrase";
    std::ostringstream os;
    os << cfg;
    for (const char* secret :
         {"the-api-key", "the-api-secret", "BEGIN PRIVATE KEY", "the-passphrase"}) {
        EXPECT_EQ(os.str().find(secret), std::string::npos) << secret;
    }
}

TEST(SignedStreams, SubscribeIsOneCommandPerConnection) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    std::vector<std::string> streams;
    std::string joined;
    for (int i = 0; i < 20; ++i) {
        streams.push_back("topic" + std::to_string(i));
        joined += (i == 0 ? "" : "|") + streams.back();
    }
    ws.subscribe(streams);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    const auto commands = commands_of(server.sessions()[0]);
    ASSERT_EQ(commands.size(), 1U);
    EXPECT_EQ(commands[0], (json::object{{"command", "SUBSCRIBE"}, {"value", joined}}));
}

TEST(SignedStreams, UnsubscribeCommand) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    ws.subscribe({"a", "b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    ws.unsubscribe({"a", "b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    EXPECT_EQ(commands_of(server.sessions()[0])[1],
              (json::object{{"command", "UNSUBSCRIBE"}, {"value", "a|b"}}));
}

TEST(SignedStreams, StreamsOfConnectGoOutAsOneCommandAfterOpening) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect({"a", "b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    std::this_thread::sleep_for(50ms);
    const auto commands = commands_of(server.sessions()[0]);
    ASSERT_EQ(commands.size(), 1U);
    EXPECT_EQ(commands[0], (json::object{{"command", "SUBSCRIBE"}, {"value", "a|b"}}));
}

TEST(SignedStreams, ReconnectSignsAgainAndSubscribesEverything) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect({"a"});
    ws.subscribe({"b", "c"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() >= 2; }));
    // The timestamp has a resolution of 1 ms: make sure that it moves.
    std::this_thread::sleep_for(5ms);
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 10s));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[1].received.empty(); }));
    const auto sessions = server.sessions();
    expect_signed_query(sessions[1].target, kHmac);
    EXPECT_NE(sessions[1].target, sessions[0].target);
    EXPECT_EQ(sessions[1].headers.at("x-mbx-apikey"), "the-api-key");
    const auto commands = commands_of(sessions[1]);
    ASSERT_EQ(commands.size(), 1U);
    EXPECT_EQ(commands[0], (json::object{{"command", "SUBSCRIBE"}, {"value", "a|b|c"}}));
}

TEST(SignedStreams, RenewalSignsAgainAndSubscribesEverything) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    const RenewalInterval renewal(300ms);
    ws.connect({"a", "b"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() >= 2 && s[1].open; }, 10s));
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[1].received.empty(); }));
    const auto sessions = server.sessions();
    expect_signed_query(sessions[1].target, kHmac);
    EXPECT_NE(sessions[1].target, sessions[0].target);
    EXPECT_EQ(commands_of(sessions[1])[0],
              (json::object{{"command", "SUBSCRIBE"}, {"value", "a|b"}}));
}

TEST(SignedStreams, UrlsUseTheTimestampProviderOnEveryConnect) {
    MockWsServer server;
    auto cfg = signed_config(server.url());
    std::atomic<std::int64_t> now{1700000000000};
    cfg.timestamp_provider = [&now] { return now.fetch_add(1000); };
    WebsocketStreams ws(cfg, {}, kSigned);
    ws.connect({"a"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s.empty(); }));
    server.drop(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2 && s[1].open; }, 10s));
    const auto sessions = server.sessions();
    for (std::size_t i = 0; i < 2; ++i) {
        expect_signed_query(sessions[i].target, kHmac);
        EXPECT_EQ(query_of(sessions[i].target)[2].second, std::to_string(1700000000000 + 1000 * i));
    }
}

TEST(SignedStreams, PoolConnectionsSignTheirOwnUrls) {
    MockWsServer server;
    auto cfg = signed_config(server.url());
    cfg.mode = WebsocketMode::pool(2);
    WebsocketStreams ws(cfg, {}, kSigned);
    ws.connect({"a"});
    ws.subscribe({"b", "c"});
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() == 2; }));
    const auto sessions = server.sessions();
    for (const auto& s : sessions) {
        expect_signed_query(s.target, kHmac);
        EXPECT_EQ(s.headers.at("x-mbx-apikey"), "the-api-key");
    }
    EXPECT_NE(query_of(sessions[0].target)[0].second, query_of(sessions[1].target)[0].second);
    ASSERT_TRUE(server.wait([](const Sessions& s) {
        std::size_t total = 0;
        for (const auto& x : s) {
            total += x.received.size();
        }
        return total >= 2;
    }));
}

TEST(SignedStreams, PingsAreSentPeriodically) {
    MockWsServer server;
    const SignedPingInterval interval(50ms);
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    EXPECT_TRUE(server.wait([](const Sessions& s) { return s[0].pings >= 3; }));
}

TEST(SignedStreams, UnsignedClientDoesNotPing) {
    MockWsServer server;
    const SignedPingInterval interval(30ms);
    WebsocketStreams ws(streams_config(server.url()));
    ws.connect({"a"});
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(server.sessions()[0].pings, 0U);
}

TEST(SignedStreams, DeliversTheParsedData) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    auto handle = ws.create_stream("news");
    Collector got;
    handle.on_message(got.callback());
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    server.send(0, topic_message("news", R"({"title":"hello","n":1})"));
    server.send(0, topic_message("news", "not json"));
    server.send(0, topic_message("other", R"({"x":1})"));
    ASSERT_TRUE(eventually([&] { return got.size() == 2; }));
    EXPECT_EQ(got.got[0], json::parse(R"({"title":"hello","n":1})"));
    EXPECT_EQ(got.got[1], json::value("not json"));
}

TEST(SignedStreams, TypedStreamDecodesTheData) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    binance::common::WebsocketStream<std::map<std::string, std::string>> stream(
        ws.create_stream("news"));
    std::promise<std::string> got;
    std::atomic<int> calls{0};
    stream.on_message([&](const std::map<std::string, std::string>& v) {
        if (++calls == 1) {
            got.set_value(v.at("title"));
        }
    });
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    server.send(0, topic_message("news", R"({"title":"hello"})"));
    EXPECT_EQ(got.get_future().get(), "hello");
}

TEST(SignedStreams, CommandFailureEmitsAnError) {
    MockWsServer server;
    EventLog log;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    auto sub = ws.on_event(std::ref(log));
    ws.connect();
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"SUCCESS"})");
    ASSERT_TRUE(eventually([&] { return log.count(WebsocketEventType::Message) == 1; }));
    EXPECT_EQ(log.count(WebsocketEventType::Error), 0U);
    server.send(0, R"({"type":"COMMAND","subType":"UNSUBSCRIBE","data":"INVALID TOPIC"})");
    ASSERT_TRUE(eventually([&] { return log.count(WebsocketEventType::Error) == 1; }));
    EXPECT_TRUE(log.has_error_containing("UNSUBSCRIBE"));
    EXPECT_TRUE(log.has_error_containing("INVALID TOPIC"));
}

TEST(SignedStreams, WaitSubscribedFollowsTheCommandAcknowledgement) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    auto good = ws.create_stream("good");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    auto waiting = ws.async_wait_subscribed("good", std::nullopt, boost::asio::use_future);
    EXPECT_EQ(waiting.wait_for(100ms), std::future_status::timeout);
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"SUCCESS"})");
    ASSERT_EQ(waiting.wait_for(5s), std::future_status::ready);
    EXPECT_NO_THROW(waiting.get());

    // A rejected command drops the streams it was for, as a rejected SUBSCRIBE response does.
    auto bad = ws.create_stream("bad");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    auto rejected = ws.async_wait_subscribed("bad", std::nullopt, boost::asio::use_future);
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"INVALID TOPIC"})");
    ASSERT_EQ(rejected.wait_for(5s), std::future_status::ready);
    EXPECT_THROW(rejected.get(), WebsocketResponseError);
    EXPECT_FALSE(ws.is_subscribed("bad"));
    EXPECT_THROW(ws.wait_subscribed("bad"), WebsocketResponseError);
    // The acknowledged stream is not affected.
    EXPECT_TRUE(ws.is_subscribed("good"));
    EXPECT_NO_THROW(ws.wait_subscribed("good"));
}

TEST(SignedStreams, EachAcknowledgementSettlesItsOwnCommand) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    auto first = ws.create_stream("first");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 1; }));
    auto second = ws.create_stream("second");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s[0].received.size() == 2; }));
    auto second_wait = ws.async_wait_subscribed("second", std::nullopt, boost::asio::use_future);

    // The first command is rejected: only its stream is dropped.
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"INVALID TOPIC"})");
    ASSERT_TRUE(eventually([&] { return !ws.is_subscribed("first"); }));
    EXPECT_TRUE(ws.is_subscribed("second"));
    EXPECT_EQ(second_wait.wait_for(100ms), std::future_status::timeout);

    // The second one succeeds, and its stream delivers.
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"SUCCESS"})");
    ASSERT_EQ(second_wait.wait_for(5s), std::future_status::ready);
    EXPECT_NO_THROW(second_wait.get());
    std::promise<std::string> got;
    second.on_message([&](const json::value& v) { got.set_value(json::serialize(v)); });
    server.send(0, topic_message("second", "7"));
    auto delivered = got.get_future();
    ASSERT_EQ(delivered.wait_for(5s), std::future_status::ready);
    EXPECT_EQ(delivered.get(), "7");
}

TEST(SignedStreams, ARejectedStreamIsGoneWhenTheErrorEventArrives) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    std::atomic<int> errors{0};
    std::atomic<bool> gone_at_error{false};
    auto events = ws.on_event([&](const WebsocketEvent& e) {
        if (e.type == WebsocketEventType::Error) {
            gone_at_error = !ws.is_subscribed("bad");
            ++errors;
        }
    });
    ws.connect();
    auto bad = ws.create_stream("bad");
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"INVALID TOPIC"})");
    ASSERT_TRUE(eventually([&] { return errors.load() == 1; }));
    EXPECT_TRUE(gone_at_error.load());
}

TEST(SignedStreams, CallbackExceptionsDoNotBreakDelivery) {
    MockWsServer server;
    WebsocketStreams ws(signed_config(server.url()), {}, kSigned);
    ws.connect();
    auto handle = ws.create_stream("news");
    std::atomic<int> calls{0};
    handle.on_message([&](const json::value&) {
        if (++calls == 1) {
            throw std::runtime_error("callback failure");
        }
    });
    ASSERT_TRUE(server.wait([](const Sessions& s) { return !s[0].received.empty(); }));
    server.send(0, topic_message("news", "1"));
    server.send(0, topic_message("news", "2"));
    EXPECT_TRUE(eventually([&] { return calls.load() == 2; }));
}

// ==== Lost sockets, failed renewals and reconnect edge cases ====

namespace {

MockWsServer::Options plain_options() {
    MockWsServer::Options options;
    options.deflate = false;
    return options;
}

struct StalledWriter {
    bool both_failed = false;
    bool peer_saw_end = false;
    bool stale_delivered = false;
};

StalledWriter run_stalled_writer(MockWsServer& server) {
    auto cfg = api_config(server.url());
    cfg.timeout = 30s;
    cfg.reconnect_delay = 10s;
    WebsocketApi api(cfg);
    api.connect();
    EXPECT_TRUE(server.wait([](const Sessions& s) { return s.size() == 1; }));
    const std::string big(24ULL * 1024 * 1024, 'x');
    auto a = api.async_send_message("big", {{"pad", json::string(big)}}, {}, asio::use_future);
    auto b = api.async_send_message("stale.marker", {}, {}, asio::use_future);
    server.half_close(0);
    StalledWriter out;
    out.both_failed = a.wait_for(10s) == std::future_status::ready &&
                      b.wait_for(10s) == std::future_status::ready;
    if (out.both_failed) {
        EXPECT_THROW((void)a.get(), WebsocketNoResponseError);
        EXPECT_THROW((void)b.get(), WebsocketNoResponseError);
    }
    server.pause_reading(false);
    out.peer_saw_end = server.wait([](const Sessions& s) { return !s[0].open; }, 5s);
    const auto first = server.sessions()[0];
    for (const auto& m : first.received) {
        out.stale_delivered = out.stale_delivered || m.find("stale.marker") != std::string::npos;
    }
    return out;
}

} // namespace

TEST(WebsocketApi, QueuedFrameIsNotSentAfterTheRequestFailed) {
    MockWsServer server(echo, plain_options());
    server.pause_reading(true);
    const auto r = run_stalled_writer(server);
    ASSERT_TRUE(r.both_failed);
    EXPECT_FALSE(r.stale_delivered);
}

TEST(WebsocketApi, LostSocketIsClosedEvenWhenAWriteIsStalled) {
    MockWsServer server(echo, plain_options());
    server.pause_reading(true);
    const auto r = run_stalled_writer(server);
    ASSERT_TRUE(r.both_failed);
    EXPECT_TRUE(r.peer_saw_end);
}

TEST(WebsocketApi, FailedRenewalIsRetriedUntilTheServerAccepts) {
    const RenewalInterval renewal(300ms);
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.set_reject_status(503);
    ASSERT_TRUE(eventually([&] { return log.has_error_containing("HTTP 503"); }));
    EXPECT_TRUE(api.is_connected()); // the old socket keeps serving
    EXPECT_EQ(api.send_message("m", {}).front().result, json::parse(R"({"echo":"m"})"));
    server.set_reject_status(0);
    ASSERT_TRUE(server.wait([](const Sessions& s) { return s.size() >= 2 && !s[0].open; }, 10s));
    EXPECT_TRUE(eventually([&] { return api.is_connected(); }));
    EXPECT_EQ(api.send_message("m", {}).front().result, json::parse(R"({"echo":"m"})"));
}

TEST(WebsocketApi, PoolMembersStartTheirHandshakesTogether) {
    MockWsServer::Options options;
    options.accept_delay = 1500ms;
    MockWsServer server(echo, options);
    auto cfg = api_config(server.url());
    cfg.mode = WebsocketMode::pool(3);
    WebsocketApi api(cfg);
    auto connected = api.async_connect(asio::use_future);
    // Each handshake is held for 1.5 s, so all three upgrades arrive well before the first ends
    // only if no member waits for another.
    EXPECT_TRUE(eventually([&] { return server.upgrade_requests() == 3; }, 1s));
    EXPECT_EQ(connected.wait_for(10s), std::future_status::ready);
}

TEST(WebsocketApi, NoReconnectAfterDisconnectDuringTheBackoff) {
    MockWsServer server(echo);
    EventLog log;
    WebsocketApi api(api_config(server.url()));
    auto sub = api.on_event(std::ref(log));
    api.connect();
    server.set_reject_status(503);
    server.drop(0);
    ASSERT_TRUE(eventually([&] { return log.has_error_containing("HTTP 503"); }));
    api.disconnect();
    server.set_reject_status(0);
    const auto upgrades = server.upgrade_requests();
    std::this_thread::sleep_for(700ms); // longer than the first reconnect delay (100 ms)
    EXPECT_EQ(server.upgrade_requests(), upgrades);
    EXPECT_EQ(server.session_count(), 1U);
    EXPECT_FALSE(api.is_connected());
}
