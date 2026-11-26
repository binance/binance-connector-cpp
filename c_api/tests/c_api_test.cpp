//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include <boost/json.hpp>
#include <gtest/gtest.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include <binance/binance_c.h>

#include "support/certs.hpp"
#include "support/env.hpp"
#include "support/mock_server.hpp"
#include "support/mock_socks.hpp"
#include "support/mock_ws_server.hpp"

using namespace std::chrono_literals;
using binance::test::MockResponse;
using binance::test::MockServer;
using binance::test::MockSocks;
using binance::test::MockWsServer;
using binance::test::ScopedEnv;
using binance::test::socks_credentials;
using binance::test::TestCertificate;
namespace json = boost::json;

namespace {

struct RestResult {
    bool ok = false;
    bnc_error error{};
    int status = 0;
    std::string body;
    std::string headers;
    std::string rate_limits;
};

void on_rest(void* user, const bnc_error* error, const bnc_rest_response* response) {
    RestResult result;
    result.ok = error == nullptr;
    if (error != nullptr) {
        result.error = *error;
    }
    // On an HTTP error, `response` is the answer that caused it.
    if (response != nullptr) {
        result.status = response->status;
        result.body.assign(response->body, response->body_len);
        result.headers = response->headers_json;
        result.rate_limits = response->rate_limits_json;
    }
    static_cast<std::promise<RestResult>*>(user)->set_value(std::move(result));
}

struct RestClientPtr {
    explicit RestClientPtr(const std::string& config) {
        bnc_error error{};
        client = bnc_rest_new(config.c_str(), &error);
        EXPECT_NE(client, nullptr) << error.message;
    }
    ~RestClientPtr() { bnc_rest_free(client); }
    RestClientPtr(const RestClientPtr&) = delete;
    RestClientPtr& operator=(const RestClientPtr&) = delete;
    bnc_rest_client* client = nullptr;
};

RestResult send(bnc_rest_client* client, const std::string& request) {
    std::promise<RestResult> done;
    bnc_error error{};
    EXPECT_EQ(bnc_rest_send(client, request.c_str(), on_rest, &done, nullptr, &error), 0)
        << error.message;
    auto future = done.get_future();
    EXPECT_EQ(future.wait_for(5s), std::future_status::ready);
    return future.get();
}

std::string rest_config(const std::string& base, const std::string& extra = "") {
    return R"({"base_path":")" + base + R"(","api_key":"key","api_secret":"secret","retries":0)" +
           extra + "}";
}

} // namespace

TEST(CApi, ReportsItsVersions) {
    EXPECT_EQ(bnc_abi_version(), static_cast<std::uint32_t>(BNC_ABI_VERSION));
    EXPECT_NE(std::string(bnc_version()), "");
}

// The layout the header documents, which bindings copy (the library asserts it too).
TEST(CApi, StructLayoutsAreTheDocumentedOnes) {
    EXPECT_EQ(sizeof(bnc_error), 600U);
    EXPECT_EQ(offsetof(bnc_error, code), 16U);
    EXPECT_EQ(offsetof(bnc_error, message), 80U);
    EXPECT_EQ(offsetof(bnc_error, ws_kind), 592U);
    EXPECT_EQ(sizeof(bnc_rest_response), 5 * sizeof(void*));
    EXPECT_EQ(sizeof(bnc_client_options), 5 * sizeof(void*));
    EXPECT_EQ(offsetof(bnc_client_options, timestamp), 3 * sizeof(void*));
    EXPECT_EQ(offsetof(bnc_client_options, timestamp_data), 4 * sizeof(void*));
}

TEST(CApi, RestSendsASignedRequest) {
    MockServer server([](const auto&) { return MockResponse{.body = R"({"ok":true})"}; });
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(
        rest.client, R"({"method":"GET","endpoint":"/api/v3/account","query":{"omitZero":true},)"
                     R"("signed":true})");
    ASSERT_TRUE(result.ok);
    EXPECT_EQ(result.status, 200);
    EXPECT_EQ(result.body, R"({"ok":true})");
    const auto requests = server.requests();
    ASSERT_EQ(requests.size(), 1U);
    EXPECT_EQ(requests[0].path(), "/api/v3/account");
    EXPECT_EQ(requests[0].header("x-mbx-apikey"), "key");
    EXPECT_NE(requests[0].query().find("omitZero=true"), std::string::npos);
    EXPECT_NE(requests[0].query().find("timestamp="), std::string::npos);
    EXPECT_NE(requests[0].query().find("signature="), std::string::npos);
}

TEST(CApi, TimeOffsetShiftsTheTimestampOfSignedRequests) {
    MockServer server([](const auto&) { return MockResponse{.body = "{}"}; });
    const auto timestamp_of = [&](const std::string& extra) {
        RestClientPtr rest(rest_config(server.url(), extra));
        const auto before = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::system_clock::now().time_since_epoch())
                                .count();
        EXPECT_TRUE(send(rest.client, R"({"method":"GET","endpoint":"/x","signed":true})").ok);
        const auto query = server.requests().back().query();
        return std::stoll(query.substr(query.find("timestamp=") + 10)) - before;
    };
    // The clock may differ by a few milliseconds between threads, so the bounds are not exact.
    EXPECT_LT(std::llabs(timestamp_of("")), 2000);
    const auto ahead = timestamp_of(R"(,"time_offset_ms":3600000)");
    EXPECT_GE(ahead, 3600000 - 50);
    EXPECT_LT(ahead, 3602000);
    const auto behind = timestamp_of(R"(,"time_offset_ms":-3600000)");
    EXPECT_LE(behind, -3600000 + 50);
    EXPECT_GT(behind, -3602000);
}

namespace {

std::int64_t fixed_timestamp(void* user) {
    ++*static_cast<std::atomic<int>*>(user);
    return 1234567890123;
}

} // namespace

TEST(CApi, ATimestampCallbackStampsSignedRequests) {
    MockServer server([](const auto&) { return MockResponse{.body = "{}"}; });
    std::atomic<int> calls{0};
    bnc_client_options options{};
    options.struct_size = sizeof options;
    options.timestamp = fixed_timestamp;
    options.timestamp_data = &calls;
    bnc_error error{};
    std::unique_ptr<bnc_rest_client, decltype(&bnc_rest_free)> rest(
        bnc_rest_new_ex(rest_config(server.url()).c_str(), &options, &error), &bnc_rest_free);
    ASSERT_NE(rest, nullptr) << error.message;
    EXPECT_TRUE(send(rest.get(), R"({"method":"GET","endpoint":"/x","signed":true})").ok);
    EXPECT_NE(server.requests().back().query().find("timestamp=1234567890123"), std::string::npos);
    EXPECT_EQ(calls.load(), 1);

    // With a time offset as well, it is ambiguous.
    EXPECT_EQ(bnc_rest_new_ex(rest_config(server.url(), R"(,"time_offset_ms":5)").c_str(), &options,
                              &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    // An options struct of the first version has no callback: the host clock.
    options.struct_size = offsetof(bnc_client_options, timestamp);
    std::unique_ptr<bnc_rest_client, decltype(&bnc_rest_free)> v1(
        bnc_rest_new_ex(rest_config(server.url()).c_str(), &options, &error), &bnc_rest_free);
    ASSERT_NE(v1, nullptr) << error.message;
    EXPECT_TRUE(send(v1.get(), R"({"method":"GET","endpoint":"/x","signed":true})").ok);
    EXPECT_EQ(server.requests().back().query().find("timestamp=1234567890123"), std::string::npos);
    EXPECT_EQ(calls.load(), 1);
}

TEST(CApi, TimeOffsetMustBeAnInteger) {
    bnc_error error{};
    EXPECT_EQ(bnc_rest_new(R"({"base_path":"http://x","time_offset_ms":"5"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_wsapi_new(R"({"url":"ws://x","time_offset_ms":1.5})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_streams_new(R"({"url":"ws://x","time_offset_ms":true})", nullptr, &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, RestPostsABody) {
    MockServer server;
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(rest.client, R"({"method":"POST","endpoint":"/x","body":{"a":1.50}})");
    ASSERT_TRUE(result.ok);
    EXPECT_EQ(server.requests().at(0).body, "a=1.5");
}

TEST(CApi, NumbersAreSentExactlyAsWritten) {
    MockServer server;
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(
        rest.client, R"({"endpoint":"/x","query":{"price":0.1,"tiny":1.5e-7,)"
                     R"("long":0.123456789012345678901234,"huge":123456789012345678901234567890,)"
                     R"("count":5,"negative":-2,"scaled":2.50E+2}})");
    ASSERT_TRUE(result.ok) << result.error.message;
    const auto query = server.requests().at(0).query();
    // Through a double, 0.123456789012345678901234 would be 0.12345678901234568.
    for (const auto* part :
         {"price=0.1", "tiny=0.00000015", "long=0.123456789012345678901234",
          "huge=123456789012345678901234567890", "count=5", "negative=-2", "scaled=250"}) {
        EXPECT_NE(query.find(part), std::string::npos) << part << " not in " << query;
    }

    // An exponent Decimal refuses is invalid input, not a huge number.
    bnc_error error{};
    EXPECT_NE(bnc_rest_send(
                  rest.client, R"({"endpoint":"/x","query":{"a":1e100000}})",
                  [](void*, const bnc_error*, const bnc_rest_response*) {}, nullptr, nullptr,
                  &error),
              0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, RateLimitErrorsCarryTheRetryDelay) {
    MockServer server([](const auto&) {
        return MockResponse{.status = 429,
                            .body = R"({"code":-1003,"msg":"Too many requests"})",
                            .headers = {{"Retry-After", "7"}}};
    });
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_TOO_MANY_REQUESTS);
    EXPECT_EQ(result.error.http_status, 429);
    EXPECT_EQ(result.error.retry_after_seconds, 7);
    EXPECT_EQ(result.error.retry_at_ms, -1);
    EXPECT_EQ(result.error.has_code, 1);
    EXPECT_EQ(result.error.code, -1003);
}

TEST(CApi, HttpErrorsComeWithTheirResponse) {
    MockServer server([](const auto&) {
        return MockResponse{.status = 400,
                            .body = R"({"code":-1100,"msg":"Illegal characters"})",
                            .headers = {{"X-MBX-USED-WEIGHT-1M", "12"}}};
    });
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_BAD_REQUEST);
    EXPECT_EQ(result.status, 400);
    EXPECT_EQ(json::parse(result.body),
              json::parse(R"({"code":-1100,"msg":"Illegal characters"})"));
    EXPECT_EQ(json::parse(result.headers).at("x-mbx-used-weight-1m"), "12");
    EXPECT_FALSE(json::parse(result.rate_limits).as_array().empty());
}

TEST(CApi, ANetworkErrorComesWithoutAResponse) {
    RestClientPtr rest(rest_config("http://127.0.0.1:1"));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.status, 0);
    EXPECT_TRUE(result.body.empty());
}

TEST(CApi, ConnectionFailuresCarryTheTransportError) {
    std::uint16_t port = 0;
    {
        MockServer server;
        port =
            static_cast<std::uint16_t>(std::stoi(server.url().substr(server.url().rfind(':') + 1)));
    }
    // Windows reports a refused connection to a closed port only after its connection retries.
    RestClientPtr rest(
        rest_config("http://127.0.0.1:" + std::to_string(port), R"(,"timeout_ms":10000)"));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_NETWORK);
    EXPECT_NE(result.error.transport_code, 0);
    EXPECT_NE(std::string(result.error.transport_category), "");
}

TEST(CApi, TimeoutsAreTold) {
    MockServer server([](const auto&) { return MockResponse{.delay = 2s}; });
    RestClientPtr rest(rest_config(server.url(), R"(,"timeout_ms":100)"));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_TIMEOUT);
}

TEST(CApi, InvalidInputIsAConfigError) {
    bnc_error error{};
    EXPECT_EQ(bnc_rest_new("{", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_rest_new(R"({"api_key":"k"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_rest_new(R"({"base_path":"http://x","timeout_ms":"1"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    // Integers out of range are refused rather than wrapped around.
    for (const auto* config : {R"({"base_path":"http://x","retries":-1})",
                               R"({"base_path":"http://x","retries":4294967296})",
                               R"({"base_path":"http://x","retries":18446744073709551615})",
                               R"({"base_path":"http://x","max_response_size":0})",
                               R"({"base_path":"http://x","max_response_size":-5})",
                               R"({"base_path":"http://x","proxy":{"host":"p","port":70000}})",
                               R"({"base_path":"http://x","proxy":{"host":"p","port":-1}})"}) {
        error = {};
        EXPECT_EQ(bnc_rest_new(config, &error), nullptr) << config;
        EXPECT_EQ(error.kind, BNC_ERROR_CONFIG) << config;
    }
    EXPECT_EQ(bnc_wsapi_new(R"({"url":"ws://x","pool_size":-1})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_streams_new(R"({"url":"ws://x","max_message_size":-1})", nullptr, &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);

    MockServer server;
    RestClientPtr rest(rest_config(server.url()));
    auto callback = [](void*, const bnc_error*, const bnc_rest_response*) {};
    EXPECT_NE(bnc_rest_send(rest.client, R"({"method":"FETCH","endpoint":"/x"})", callback, nullptr,
                            nullptr, &error),
              0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_NE(bnc_rest_send(rest.client, "[]", callback, nullptr, nullptr, &error), 0);
    EXPECT_NE(bnc_rest_send(rest.client, R"({"method":"GET"})", callback, nullptr, nullptr, &error),
              0);
    EXPECT_EQ(server.request_count(), 0U);
}

namespace {

struct Messages {
    std::mutex mutex;
    std::vector<std::string> got;
    [[nodiscard]] std::size_t size() {
        const std::lock_guard lock(mutex);
        return got.size();
    }
};

void on_message(void* user, const char* data, size_t len) {
    auto* messages = static_cast<Messages*>(user);
    const std::lock_guard lock(messages->mutex);
    messages->got.emplace_back(data, len);
}

void on_status(void* user, const bnc_error* error) {
    static_cast<std::promise<int>*>(user)->set_value(error == nullptr ? 0 : error->kind);
}

} // namespace

TEST(CApi, StreamsDeliverEvents) {
    MockWsServer server;
    bnc_error error{};
    const auto config = R"({"url":")" + server.url() + R"("})";
    std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)> streams(
        bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
    ASSERT_NE(streams, nullptr) << error.message;

    std::promise<int> connected;
    ASSERT_EQ(bnc_streams_connect(streams.get(), R"(["btcusdt@trade"])", on_status, &connected,
                                  nullptr, &error),
              0);
    auto connected_future = connected.get_future();
    ASSERT_EQ(connected_future.wait_for(5s), std::future_status::ready);
    EXPECT_EQ(connected_future.get(), 0);
    EXPECT_EQ(bnc_streams_is_connected(streams.get()), 1);
    EXPECT_EQ(server.sessions().front().target, "/stream?streams=btcusdt@trade");

    Messages messages;
    std::unique_ptr<bnc_stream, decltype(&bnc_stream_free)> stream(
        bnc_stream_new(streams.get(), "btcusdt@trade", nullptr, nullptr, on_message, &messages,
                       nullptr, nullptr, &error),
        &bnc_stream_free);
    ASSERT_NE(stream, nullptr) << error.message;
    server.send(0, R"({"stream":"btcusdt@trade","data":{"p":"1.0","q":12345678901234567890}})");
    for (int i = 0; i < 1000 && messages.size() == 0; ++i) {
        std::this_thread::sleep_for(5ms);
    }
    ASSERT_EQ(messages.size(), 1U);
    EXPECT_EQ(json::parse(messages.got[0]), json::parse(R"({"p":"1.0","q":12345678901234567890})"));

    stream.reset();
    std::promise<int> closed;
    ASSERT_EQ(bnc_streams_disconnect(streams.get(), on_status, &closed, nullptr, &error), 0);
    EXPECT_EQ(closed.get_future().get(), 0);
}

TEST(CApi, StreamsReportConnectFailures) {
    std::string url;
    {
        MockWsServer server;
        url = server.url();
    }
    bnc_error error{};
    const auto config = R"({"url":")" + url + R"("})";
    std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)> streams(
        bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
    ASSERT_NE(streams, nullptr);
    std::promise<int> done;
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status, &done, nullptr, &error), 0);
    EXPECT_EQ(done.get_future().get(), BNC_ERROR_NETWORK);

    EXPECT_EQ(bnc_stream_new(streams.get(), "", nullptr, nullptr, on_message, nullptr, nullptr,
                             nullptr, &error),
              nullptr);
    EXPECT_NE(error.kind, BNC_OK);
}

TEST(CApi, SignedStreamsNeedCredentials) {
    MockWsServer server;
    bnc_error error{};
    const auto config = R"({"url":")" + server.url() + R"(","signed_streams":true})";
    EXPECT_EQ(bnc_streams_new(config.c_str(), nullptr, &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

namespace {

void echo(MockWsServer::Session& s, const std::string& text) {
    const auto req = json::parse(text).as_object();
    if (req.at("method") == json::value("userDataStream.subscribe")) {
        s.send(R"({"id":")" + std::string(req.at("id").as_string()) +
               R"(","status":200,"result":{"subscriptionId":1}})");
        s.send(R"({"subscriptionId":1,"event":{"e":"hello"}})");
        return;
    }
    if (req.at("method") == json::value("fail_limited")) {
        s.send(R"({"id":")" + std::string(req.at("id").as_string()) +
               R"(","status":400,"error":{"code":-1102,"msg":"bad","data":{"leg":"FAILURE"}},)"
               R"("rateLimits":[)"
               R"({"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,)"
               R"("limit":6000,"count":12}]})");
        return;
    }
    if (req.at("method") == json::value("fail")) {
        s.send(R"({"id":")" + std::string(req.at("id").as_string()) +
               R"(","status":429,"error":{"code":-1003,"msg":"slow down",)"
               R"("data":{"retryAfter":1659146400000}}})");
        return;
    }
    json::object res{
        {"id", req.at("id")},
        {"status", 200},
        {"result", json::object{{"echo", req.at("method")}, {"params", req.at("params")}}},
        {"rateLimits", json::array{json::object{{"rateLimitType", "REQUEST_WEIGHT"},
                                                {"interval", "MINUTE"},
                                                {"intervalNum", 1},
                                                {"limit", 6000},
                                                {"count", 2}}}}};
    s.send(json::serialize(res));
}

struct WsResult {
    bnc_error error{};
    std::string json;
    bnc_stream* stream = nullptr;
};

void on_ws(void* user, const bnc_error* error, const char* text, size_t len) {
    WsResult r;
    if (error != nullptr) {
        r.error = *error;
    }
    // On an error answered by the server, the rate limits of the answer.
    if (text != nullptr) {
        r.json.assign(text, len);
    }
    static_cast<std::promise<WsResult>*>(user)->set_value(std::move(r));
}

void on_ws_subscribe(void* user, const bnc_error* error, const char* text, size_t len,
                     bnc_stream* stream) {
    WsResult r;
    if (error != nullptr) {
        r.error = *error;
    } else {
        r.json.assign(text, len);
        r.stream = stream;
    }
    static_cast<std::promise<WsResult>*>(user)->set_value(std::move(r));
}

struct WsApiPtr {
    explicit WsApiPtr(const std::string& url) {
        bnc_error error{};
        const auto config =
            R"({"url":")" + url + R"(","api_key":"key","api_secret":"secret","timeout_ms":2000})";
        api = bnc_wsapi_new(config.c_str(), &error);
        EXPECT_NE(api, nullptr) << error.message;
        std::promise<int> connected;
        EXPECT_EQ(bnc_wsapi_connect(api, on_status, &connected, nullptr, &error), 0);
        EXPECT_EQ(connected.get_future().get(), 0);
    }
    ~WsApiPtr() { bnc_wsapi_free(api); }
    WsApiPtr(const WsApiPtr&) = delete;
    WsApiPtr& operator=(const WsApiPtr&) = delete;
    bnc_wsapi* api = nullptr;
};

WsResult ws_send(bnc_wsapi* api, const std::string& request) {
    std::promise<WsResult> done;
    bnc_error error{};
    EXPECT_EQ(bnc_wsapi_send(api, request.c_str(), on_ws, &done, nullptr, &error), 0)
        << error.message;
    return done.get_future().get();
}

} // namespace

TEST(CApi, WebsocketApiSendsRequests) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    EXPECT_EQ(bnc_wsapi_is_connected(ws.api), 1);
    const auto result = ws_send(ws.api, R"({"method":"ping","params":{"symbol":"BTCUSDT"}})");
    ASSERT_EQ(result.error.kind, BNC_OK);
    const auto responses = json::parse(result.json).as_array();
    ASSERT_EQ(responses.size(), 1U);
    EXPECT_EQ(responses[0].at("result").at("echo"), json::value("ping"));
    EXPECT_EQ(responses[0].at("result").at("params").at("symbol"), json::value("BTCUSDT"));
    EXPECT_EQ(responses[0].at("rateLimits").at(0).at("count"), json::value(2));
}

TEST(CApi, WebsocketApiSendsNumbersExactly) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const auto result = ws_send(
        ws.api, R"({"method":"order.test","params":{"price":0.1,"quantity":1.5e-7,"limit":5}})");
    ASSERT_EQ(result.error.kind, BNC_OK);
    // What the server received, echoed: decimals as strings, as the C++ API sends a Decimal.
    const auto params = json::parse(result.json).as_array().at(0).at("result").at("params");
    EXPECT_EQ(params.at("price"), json::value("0.1"));
    EXPECT_EQ(params.at("quantity"), json::value("0.00000015"));
    EXPECT_EQ(params.at("limit"), json::value(5));
}

TEST(CApi, WebsocketApiSignsRequests) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const auto result = ws_send(ws.api, R"({"method":"account.status","auth":"signed"})");
    ASSERT_EQ(result.error.kind, BNC_OK);
    const auto sent = json::parse(server.sessions().front().received.back()).as_object();
    const auto& params = sent.at("params").as_object();
    EXPECT_EQ(params.at("apiKey"), json::value("key"));
    EXPECT_TRUE(params.contains("signature"));
    EXPECT_TRUE(params.contains("timestamp"));
}

TEST(CApi, WebsocketApiErrorsCarryTheRetryTime) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const auto result = ws_send(ws.api, R"({"method":"fail"})");
    EXPECT_EQ(result.error.kind, BNC_ERROR_WEBSOCKET);
    EXPECT_EQ(result.error.http_status, 429);
    EXPECT_EQ(result.error.retry_at_ms, 1659146400000);
    EXPECT_EQ(result.error.has_code, 1);
    EXPECT_EQ(result.error.code, -1003);
}

TEST(CApi, WebsocketApiErrorsCarryTheirRateLimitsAndData) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const auto limited = ws_send(ws.api, R"({"method":"fail_limited"})");
    EXPECT_EQ(limited.error.kind, BNC_ERROR_WEBSOCKET);
    EXPECT_EQ(limited.error.ws_kind, BNC_WS_RESPONSE_ERROR);
    const auto limits = json::parse(limited.json).at("rateLimits").as_array();
    ASSERT_EQ(limits.size(), 1U);
    EXPECT_EQ(limits[0].at("count"), json::value(12));
    EXPECT_EQ(limits[0].at("limit"), json::value(6000));
    EXPECT_EQ(json::parse(limited.json).at("data"), json::parse(R"({"leg":"FAILURE"})"));
    // Without rate limits in the answer, an empty list.
    // Without rate limits in the answer, an empty list; its error.data comes too.
    const auto plain = ws_send(ws.api, R"({"method":"fail"})");
    EXPECT_TRUE(json::parse(plain.json).at("rateLimits").as_array().empty());
    EXPECT_EQ(json::parse(plain.json).at("data").at("retryAfter"), json::value(1659146400000));
}

TEST(CApi, WebsocketApiSubscribesToUserData) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    Messages messages;
    std::promise<WsResult> done;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_subscribe(ws.api, R"({"method":"userDataStream.subscribe"})",
                                  on_ws_subscribe, &done, on_message, &messages, nullptr, &error),
              0);
    auto result = done.get_future().get();
    ASSERT_EQ(result.error.kind, BNC_OK);
    ASSERT_NE(result.stream, nullptr);
    EXPECT_EQ(json::parse(result.json).at("result").at("subscriptionId"), json::value(1));
    for (int i = 0; i < 1000 && messages.size() == 0; ++i) {
        std::this_thread::sleep_for(5ms);
    }
    ASSERT_EQ(messages.size(), 1U);
    EXPECT_EQ(json::parse(messages.got[0]), json::parse(R"({"e":"hello"})"));
    bnc_stream_free(result.stream);
}

TEST(CApi, WebsocketApiRejectsBadRequests) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    bnc_error error{};
    EXPECT_NE(bnc_wsapi_send(ws.api, R"({"params":{}})", on_ws, nullptr, nullptr, &error), 0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_NE(
        bnc_wsapi_send(ws.api, R"({"method":"x","auth":"magic"})", on_ws, nullptr, nullptr, &error),
        0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_wsapi_new(R"({"api_key":"k"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, WebsocketApiDisconnects) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    std::promise<int> closed;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_disconnect(ws.api, on_status, &closed, nullptr, &error), 0);
    EXPECT_EQ(closed.get_future().get(), 0);
    EXPECT_EQ(bnc_wsapi_is_connected(ws.api), 0);
}

TEST(CApi, RestRequestsCanBeCancelled) {
    MockServer server([](const auto&) { return MockResponse{.delay = 3s}; });
    RestClientPtr rest(rest_config(server.url(), R"(,"timeout_ms":10000)"));
    std::promise<RestResult> done;
    bnc_request* request = nullptr;
    bnc_error error{};
    ASSERT_EQ(bnc_rest_send(rest.client, R"({"endpoint":"/x"})", on_rest, &done, &request, &error),
              0);
    ASSERT_NE(request, nullptr);
    std::this_thread::sleep_for(100ms);
    const auto start = std::chrono::steady_clock::now();
    bnc_request_cancel(request);
    auto future = done.get_future();
    ASSERT_EQ(future.wait_for(2s), std::future_status::ready);
    const auto result = future.get();
    EXPECT_EQ(result.error.kind, BNC_ERROR_CANCELLED);
    EXPECT_LT(std::chrono::steady_clock::now() - start, 1s);
    bnc_request_cancel(request);
    bnc_request_release(request);
}

TEST(CApi, CancellingAfterCompletionIsHarmless) {
    MockServer server;
    RestClientPtr rest(rest_config(server.url()));
    std::promise<RestResult> done;
    bnc_request* request = nullptr;
    bnc_error error{};
    ASSERT_EQ(bnc_rest_send(rest.client, R"({"endpoint":"/x"})", on_rest, &done, &request, &error),
              0);
    EXPECT_TRUE(done.get_future().get().ok);
    bnc_request_cancel(request);
    bnc_request_release(request);
    bnc_request_release(nullptr);
    bnc_request_cancel(nullptr);
}

TEST(CApi, WebsocketApiRequestsCanBeCancelled) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {}); // never answers
    WsApiPtr ws(server.url());
    std::promise<WsResult> done;
    bnc_request* request = nullptr;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_send(ws.api, R"({"method":"ping"})", on_ws, &done, &request, &error), 0);
    std::this_thread::sleep_for(100ms);
    bnc_request_cancel(request);
    auto future = done.get_future();
    ASSERT_EQ(future.wait_for(1500ms), std::future_status::ready);
    EXPECT_EQ(future.get().error.kind, BNC_ERROR_CANCELLED);
    bnc_request_release(request);
}

TEST(CApi, StreamsSubscribeAndUnsubscribeByName) {
    MockWsServer server;
    bnc_error error{};
    const auto config = R"({"url":")" + server.url() + R"("})";
    std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)> streams(
        bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
    ASSERT_NE(streams, nullptr);
    std::promise<int> connected;
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status, &connected, nullptr, &error),
              0);
    ASSERT_EQ(connected.get_future().get(), 0);
    ASSERT_EQ(
        bnc_streams_subscribe(streams.get(), R"(["a@trade","b@trade"])", nullptr, "7", &error), 0)
        << error.message;
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "a@trade"), 1);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "b@trade"), 1);
    ASSERT_TRUE(server.wait([](const auto& sessions) {
        return !sessions.empty() && !sessions.front().received.empty();
    }));
    const auto subscribe = json::parse(server.sessions().front().received.back());
    EXPECT_EQ(subscribe.at("method"), "SUBSCRIBE");
    EXPECT_EQ(subscribe.at("id"), json::value(7));

    ASSERT_EQ(bnc_streams_unsubscribe(streams.get(), R"(["a@trade"])", nullptr, nullptr, &error),
              0);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "a@trade"), 0);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "b@trade"), 1);
    ASSERT_TRUE(server.wait([](const auto& sessions) {
        return !sessions.empty() && sessions.front().received.size() >= 2 &&
               json::parse(sessions.front().received.back()).at("method") == "UNSUBSCRIBE";
    }));

    EXPECT_NE(bnc_streams_subscribe(streams.get(), R"({"a":1})", nullptr, nullptr, &error), 0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_NE(bnc_streams_subscribe(nullptr, R"(["a"])", nullptr, nullptr, &error), 0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, StreamsAcceptARequestId) {
    MockWsServer server;
    bnc_error error{};
    const auto config = R"({"url":")" + server.url() + R"("})";
    std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)> streams(
        bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
    ASSERT_NE(streams, nullptr);
    std::promise<int> connected;
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status, &connected, nullptr, &error),
              0);
    ASSERT_EQ(connected.get_future().get(), 0);
    Messages messages;
    std::unique_ptr<bnc_stream, decltype(&bnc_stream_free)> stream(
        bnc_stream_new(streams.get(), "btcusdt@trade", nullptr, "42", on_message, &messages,
                       nullptr, nullptr, &error),
        &bnc_stream_free);
    ASSERT_NE(stream, nullptr) << error.message;
    ASSERT_TRUE(server.wait([](const auto& sessions) {
        return !sessions.empty() && !sessions.front().received.empty();
    }));
    EXPECT_EQ(json::parse(server.sessions().front().received.back()).at("id"), json::value(42));
    EXPECT_EQ(bnc_stream_new(streams.get(), "x@y", nullptr, "-1", on_message, nullptr, nullptr,
                             nullptr, &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

namespace {

struct Logs {
    std::mutex mutex;
    std::vector<std::pair<int, std::string>> lines;
};

void on_log(void* user, bnc_log_level level, const char* text, size_t len) {
    auto* logs = static_cast<Logs*>(user);
    const std::lock_guard lock(logs->mutex);
    logs->lines.emplace_back(static_cast<int>(level), std::string(text, len));
}

} // namespace

TEST(CApi, LogsGoToTheCallback) {
    Logs logs;
    bnc_set_log_level(BNC_LOG_DEBUG);
    bnc_set_log_callback(on_log, &logs);
    {
        MockWsServer server;
        bnc_error error{};
        const auto config = R"({"url":")" + server.url() + R"("})";
        std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)> streams(
            bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
        std::promise<int> connected;
        ASSERT_EQ(
            bnc_streams_connect(streams.get(), nullptr, on_status, &connected, nullptr, &error), 0);
        EXPECT_EQ(connected.get_future().get(), 0);
    }
    bnc_set_log_callback(nullptr, nullptr);
    bnc_set_log_level(BNC_LOG_INFO);
    const std::lock_guard lock(logs.mutex);
    EXPECT_FALSE(logs.lines.empty());
}

namespace {

using StreamsPtr = std::unique_ptr<bnc_streams, decltype(&bnc_streams_free)>;

StreamsPtr new_streams(const MockWsServer& server, const std::string& extra = "") {
    bnc_error error{};
    const auto config = R"({"url":")" + server.url() + R"(")" + extra + "}";
    StreamsPtr streams(bnc_streams_new(config.c_str(), nullptr, &error), &bnc_streams_free);
    EXPECT_NE(streams, nullptr) << error.message;
    return streams;
}

int status_of(std::promise<int>& done) {
    auto future = done.get_future();
    EXPECT_EQ(future.wait_for(5s), std::future_status::ready);
    return future.get();
}

void connect(bnc_streams* streams) {
    std::promise<int> done;
    bnc_error error{};
    ASSERT_EQ(bnc_streams_connect(streams, nullptr, on_status, &done, nullptr, &error), 0);
    ASSERT_EQ(status_of(done), 0);
}

void disconnect(bnc_streams* streams) {
    std::promise<int> done;
    bnc_error error{};
    ASSERT_EQ(bnc_streams_disconnect(streams, on_status, &done, nullptr, &error), 0);
    ASSERT_EQ(status_of(done), 0);
}

/// What `on_terminated` saw.
struct Terminal {
    std::mutex mutex;
    int calls = 0;
    bool had_error = false;
    bnc_error error{};
    bnc_stream* free_it = nullptr; // freed from inside the callback if set

    [[nodiscard]] int count() {
        const std::lock_guard lock(mutex);
        return calls;
    }
};

void on_terminated(void* user, const bnc_error* error) {
    auto* t = static_cast<Terminal*>(user);
    bnc_stream* to_free = nullptr;
    {
        const std::lock_guard lock(t->mutex);
        ++t->calls;
        t->had_error = error != nullptr;
        if (error != nullptr) {
            t->error = *error;
        }
        to_free = t->free_it;
    }
    if (to_free != nullptr) {
        bnc_stream_free(to_free);
    }
}

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

bnc_stream* new_stream(bnc_streams* streams, const char* name, Terminal& terminal,
                       Messages* messages = nullptr) {
    static Messages unused;
    bnc_error error{};
    auto* stream =
        bnc_stream_new(streams, name, nullptr, nullptr, on_message,
                       messages != nullptr ? messages : &unused, on_terminated, &terminal, &error);
    EXPECT_NE(stream, nullptr) << error.message;
    return stream;
}

/// Answers SUBSCRIBE like Binance, rejecting the streams named `bad*`.
void rejecting_server(MockWsServer::Session& s, const std::string& text) {
    const auto req = json::parse(text).as_object();
    json::object res{{"id", req.at("id")}};
    if (req.at("params").as_array().at(0).as_string().starts_with("bad")) {
        res["error"] = json::object{{"code", 2}, {"msg", "Invalid request"}};
    } else {
        res["result"] = nullptr;
    }
    s.send(json::serialize(res));
}

struct Events {
    std::atomic<int> count{0};
    std::atomic<int> errors{0};
    std::atomic<int> messages{0};
};

void on_event(void* user, bnc_event_type type, const char*, size_t, uint16_t, const char*) {
    auto* events = static_cast<Events*>(user);
    ++events->count;
    if (type == BNC_EVENT_ERROR) {
        ++events->errors;
    }
    if (type == BNC_EVENT_MESSAGE) {
        ++events->messages;
    }
}

/// Sends messages on every connection until destroyed.
class Flood {
public:
    explicit Flood(MockWsServer& server)
        : thread_([this, &server] {
              while (!stop_) {
                  server.broadcast(R"({"stream":"a@b","data":1})");
                  std::this_thread::sleep_for(1ms);
              }
          }) {}
    ~Flood() {
        stop_ = true;
        thread_.join();
    }
    Flood(const Flood&) = delete;
    Flood& operator=(const Flood&) = delete;

private:
    std::atomic<bool> stop_{false};
    std::thread thread_;
};

} // namespace

TEST(CApi, PingsReachTheServer) {
    MockWsServer server(echo);
    auto streams = new_streams(server);
    connect(streams.get());
    bnc_error error{};
    EXPECT_EQ(bnc_streams_ping(streams.get(), &error), 0);
    EXPECT_TRUE(server.wait([](const auto& s) { return s.at(0).pings == 1; }));

    MockWsServer api_server(echo);
    WsApiPtr ws(api_server.url());
    EXPECT_EQ(bnc_wsapi_ping(ws.api, &error), 0);
    EXPECT_TRUE(api_server.wait([](const auto& s) { return s.at(0).pings == 1; }));

    EXPECT_NE(bnc_streams_ping(nullptr, &error), 0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_NE(bnc_wsapi_ping(nullptr, &error), 0);
}

TEST(CApi, StreamIdsCanBeStrictlyNumbers) {
    MockWsServer server;
    auto streams = new_streams(server, R"(,"stream_id_is_strictly_number":true)");
    connect(streams.get());
    bnc_error error{};
    std::unique_ptr<bnc_stream, decltype(&bnc_stream_free)> stream(
        bnc_stream_new(streams.get(), "a@b", nullptr, R"("abc")", on_message, nullptr, nullptr,
                       nullptr, &error),
        &bnc_stream_free);
    ASSERT_NE(stream, nullptr) << error.message;
    ASSERT_TRUE(server.wait([](const auto& s) { return !s.at(0).received.empty(); }));
    EXPECT_TRUE(json::parse(server.sessions().front().received.back()).at("id").is_number());

    const auto bad_config = R"({"url":")" + server.url() + R"(","stream_id_is_strictly_number":1})";
    EXPECT_EQ(bnc_streams_new(bad_config.c_str(), nullptr, &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

// The pool size applies only before the shared pool is first used, and the pool is shared by every
// test in this process, so only the absence of side effects can be checked here.
TEST(CApi, SetThreadCountLeavesClientsWorking) {
    bnc_set_thread_count(3);
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Terminal terminal;
    auto* stream = new_stream(streams.get(), "a@b", terminal);
    EXPECT_EQ(bnc_stream_is_active(stream), 1);
    disconnect(streams.get());
    EXPECT_EQ(terminal.count(), 1);
    bnc_stream_free(stream);
}

TEST(CApi, WaitSubscribedTellsTheAnswerOfTheServer) {
    Terminal good_terminal;
    Terminal bad_terminal;
    MockWsServer server(rejecting_server);
    auto streams = new_streams(server);
    connect(streams.get());
    const auto wait = [&](const char* stream) {
        std::promise<int> done;
        bnc_error error{};
        EXPECT_EQ(bnc_streams_wait_subscribed(streams.get(), stream, nullptr, on_status, &done,
                                              nullptr, &error),
                  0)
            << error.message;
        return status_of(done);
    };
    auto* good = new_stream(streams.get(), "good", good_terminal);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "good"), 1);
    EXPECT_EQ(wait("good"), BNC_OK);
    auto* bad = new_stream(streams.get(), "bad1", bad_terminal);
    EXPECT_EQ(wait("bad1"), BNC_ERROR_WEBSOCKET);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "bad1"), 0);
    EXPECT_EQ(wait("never"), BNC_ERROR_CANCELLED);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "never"), 0);
    // An error is told apart from "not subscribed".
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), nullptr), -1);
    EXPECT_EQ(bnc_streams_is_subscribed(nullptr, "good"), -1);
    bnc_stream_free(good);
    EXPECT_EQ(bnc_streams_is_subscribed(streams.get(), "good"), 0);
    bnc_stream_free(bad);
    bnc_error error{};
    EXPECT_NE(bnc_streams_wait_subscribed(streams.get(), nullptr, nullptr, on_status, nullptr,
                                          nullptr, &error),
              0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, ARejectedSubscribeEndsTheStream) {
    Terminal good_terminal;
    Terminal bad_terminal;
    Events events;
    MockWsServer server(rejecting_server);
    auto streams = new_streams(server, R"(,"reconnect_delay_ms":50)");
    bnc_streams_set_event_callback(streams.get(), on_event, &events);
    connect(streams.get());
    auto* good = new_stream(streams.get(), "good", good_terminal);
    // Subscribed one by one: a request with a rejected stream drops all of its streams.
    ASSERT_TRUE(server.wait([](const auto& s) { return !s.at(0).received.empty(); }));
    auto* bad = new_stream(streams.get(), "bad1", bad_terminal);
    ASSERT_TRUE(eventually([&] { return bad_terminal.count() == 1; }));
    {
        const std::lock_guard lock(bad_terminal.mutex);
        EXPECT_TRUE(bad_terminal.had_error);
        EXPECT_EQ(bad_terminal.error.kind, BNC_ERROR_WEBSOCKET);
        EXPECT_EQ(bad_terminal.error.ws_kind, BNC_WS_RESPONSE_ERROR);
        EXPECT_NE(std::string(bad_terminal.error.message).find("Invalid request"),
                  std::string::npos);
    }
    EXPECT_EQ(bnc_stream_is_active(bad), 0);
    EXPECT_EQ(bnc_stream_is_active(good), 1);
    EXPECT_EQ(good_terminal.count(), 0);
    EXPECT_GE(events.errors.load(), 1) << "the user's event callback coexists with ours";

    // A reconnect is not an end, and a finished stream does not end twice.
    server.drop(0);
    ASSERT_TRUE(server.wait([](const auto& s) { return s.size() == 2 && s[1].open; }));
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(bnc_stream_is_active(good), 1);
    EXPECT_EQ(good_terminal.count(), 0);

    disconnect(streams.get());
    EXPECT_EQ(good_terminal.count(), 1);
    EXPECT_FALSE(good_terminal.had_error);
    EXPECT_EQ(bnc_stream_is_active(good), 0);
    EXPECT_EQ(bad_terminal.count(), 1);
    bnc_stream_free(good);
    bnc_stream_free(bad);
}

TEST(CApi, ARejectedSignedSubscribeEndsTheStream) {
    Terminal good_terminal;
    Terminal bad_terminal;
    MockWsServer server;
    auto streams = new_streams(server, R"(,"signed_streams":true,"api_key":"k","api_secret":"s")");
    connect(streams.get());
    auto* good = new_stream(streams.get(), "good", good_terminal);
    ASSERT_TRUE(server.wait([](const auto& s) { return s.at(0).received.size() == 1; }));
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"SUCCESS"})");
    auto* bad = new_stream(streams.get(), "bad", bad_terminal);
    ASSERT_TRUE(server.wait([](const auto& s) { return s.at(0).received.size() == 2; }));
    server.send(0, R"({"type":"COMMAND","subType":"SUBSCRIBE","data":"INVALID TOPIC"})");
    ASSERT_TRUE(eventually([&] { return bad_terminal.count() == 1; }));
    {
        const std::lock_guard lock(bad_terminal.mutex);
        EXPECT_TRUE(bad_terminal.had_error);
        EXPECT_EQ(bad_terminal.error.kind, BNC_ERROR_WEBSOCKET);
        EXPECT_NE(std::string(bad_terminal.error.message).find("INVALID TOPIC"), std::string::npos);
    }
    EXPECT_EQ(bnc_stream_is_active(bad), 0);
    EXPECT_EQ(bnc_stream_is_active(good), 1);
    EXPECT_EQ(good_terminal.count(), 0);
    bnc_stream_free(good);
    bnc_stream_free(bad);
}

TEST(CApi, SwitchingToTheEventCallbackLosesNoLifecycleEvent) {
    MockWsServer server;
    auto streams = new_streams(server, R"(,"reconnect_delay_ms":10)");
    Events events;
    bnc_streams_set_lifecycle_callback(streams.get(), on_event, &events);
    connect(streams.get());
    // Pings from the server are events; switch back and forth while they arrive.
    ASSERT_TRUE(eventually([&] { return events.count.load() == 1; })); // Open
    std::atomic<bool> stop{false};
    std::atomic<int> pings{0};
    std::thread pinger([&] {
        while (!stop) {
            server.ping(0);
            ++pings;
            std::this_thread::sleep_for(1ms);
        }
    });
    for (int i = 0; i < 200; ++i) {
        if (i % 2 == 0) {
            bnc_streams_set_event_callback(streams.get(), on_event, &events);
        } else {
            bnc_streams_set_lifecycle_callback(streams.get(), on_event, &events);
        }
    }
    stop = true;
    pinger.join();
    // Each ping is one Ping event: none lost in a switch, none delivered twice.
    EXPECT_TRUE(eventually([&] { return events.count.load() == 1 + pings.load(); }))
        << events.count.load() << " events for " << pings.load() << " pings";
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(events.count.load(), 1 + pings.load());
    bnc_streams_set_lifecycle_callback(streams.get(), nullptr, nullptr);
}

TEST(CApi, DisconnectEndsTheStreamsThatExist) {
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Terminal first;
    auto* before = new_stream(streams.get(), "a@b", first);
    disconnect(streams.get());
    EXPECT_EQ(first.count(), 1);
    EXPECT_FALSE(first.had_error);
    EXPECT_EQ(bnc_stream_is_active(before), 0);

    Terminal second;
    auto* after = new_stream(streams.get(), "c@d", second);
    EXPECT_EQ(bnc_stream_is_active(after), 1);
    bnc_stream_free(before);
    bnc_stream_free(after);
    EXPECT_EQ(first.count(), 1);
    EXPECT_EQ(second.count(), 0);
}

TEST(CApi, FreeingTheStreamsEndsTheStreamsOnce) {
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Terminal terminal;
    auto* stream = new_stream(streams.get(), "a@b", terminal);
    streams.reset();
    EXPECT_EQ(terminal.count(), 1);
    EXPECT_FALSE(terminal.had_error);
    EXPECT_EQ(bnc_stream_is_active(stream), 0);
    bnc_stream_free(stream); // after its client: nothing dangles
    EXPECT_EQ(terminal.count(), 1);
}

TEST(CApi, AFreedStreamIsNotTold) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {}); // never answers
    auto streams = new_streams(server);
    connect(streams.get());
    Terminal terminal;
    bnc_stream_free(new_stream(streams.get(), "a@b", terminal));
    disconnect(streams.get());
    streams.reset();
    EXPECT_EQ(terminal.count(), 0);
}

TEST(CApi, AStreamMayBeFreedByItsOwnTerminalCallback) {
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Terminal terminal;
    terminal.free_it = new_stream(streams.get(), "a@b", terminal);
    disconnect(streams.get());
    EXPECT_EQ(terminal.count(), 1);
}

TEST(CApi, ATransientDisconnectDoesNotEndTheStream) {
    MockWsServer server;
    auto streams = new_streams(server, R"(,"reconnect_delay_ms":50)");
    connect(streams.get());
    Terminal terminal;
    auto* stream = new_stream(streams.get(), "a@b", terminal);
    server.drop(0);
    ASSERT_TRUE(server.wait([](const auto& s) { return s.size() == 2 && s[1].open; }));
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(terminal.count(), 0);
    EXPECT_EQ(bnc_stream_is_active(stream), 1);
    bnc_stream_free(stream);
}

TEST(CApi, ALifecycleCallbackGetsNoMessages) {
    Events lifecycle;
    Events all;
    MockWsServer server;
    auto streams = new_streams(server);
    bnc_streams_set_lifecycle_callback(streams.get(), on_event, &lifecycle);
    connect(streams.get());
    ASSERT_TRUE(eventually([&] { return lifecycle.count >= 1; }));
    Flood flood(server);
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(lifecycle.messages.load(), 0);

    bnc_streams_set_event_callback(streams.get(), on_event, &all);
    EXPECT_TRUE(eventually([&] { return all.messages > 5; }));
}

TEST(CApi, ANullEventCallbackIsNotCalledAgain) {
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Flood flood(server);
    Events events;
    bnc_streams_set_event_callback(streams.get(), on_event, &events);
    ASSERT_TRUE(eventually([&] { return events.count > 10; }));
    bnc_streams_set_event_callback(streams.get(), nullptr, nullptr);
    const auto seen = events.count.load();
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(events.count.load(), seen);

    MockWsServer api_server(echo);
    WsApiPtr ws(api_server.url());
    Flood api_flood(api_server);
    Events api_events;
    bnc_wsapi_set_event_callback(ws.api, on_event, &api_events);
    ASSERT_TRUE(eventually([&] { return api_events.count > 0; }));
    bnc_wsapi_set_event_callback(ws.api, nullptr, nullptr);
    const auto api_seen = api_events.count.load();
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(api_events.count.load(), api_seen);
}

TEST(CApi, NothingStartsAfterStreamsAreFreed) {
    MockWsServer server;
    auto streams = new_streams(server);
    connect(streams.get());
    Messages messages;
    Events events;
    Terminal terminal;
    auto* stream = new_stream(streams.get(), "a@b", terminal, &messages);
    bnc_streams_set_event_callback(streams.get(), on_event, &events);
    Flood flood(server);
    ASSERT_TRUE(eventually([&] { return messages.size() > 5 && events.count > 5; }));
    streams.reset();
    const auto seen_messages = messages.size();
    const auto seen_events = events.count.load();
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(messages.size(), seen_messages);
    EXPECT_EQ(events.count.load(), seen_events);
    EXPECT_EQ(terminal.count(), 1);
    bnc_stream_free(stream);
}

TEST(CApi, NothingStartsAfterTheWebsocketApiIsFreed) {
    MockWsServer server([](MockWsServer::Session& s, const std::string& text) {
        if (json::parse(text).as_object().at("method") != json::value("never")) {
            echo(s, text);
        }
    });
    auto* ws = new WsApiPtr(server.url());
    Messages messages;
    Events events;
    bnc_wsapi_set_event_callback(ws->api, on_event, &events);
    std::promise<WsResult> subscribed;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_subscribe(ws->api, R"({"method":"userDataStream.subscribe"})",
                                  on_ws_subscribe, &subscribed, on_message, &messages, nullptr,
                                  &error),
              0);
    auto stream = subscribed.get_future().get().stream;
    ASSERT_NE(stream, nullptr);
    std::promise<WsResult> pending;
    ASSERT_EQ(bnc_wsapi_send(ws->api, R"({"method":"never"})", on_ws, &pending, nullptr, &error),
              0);
    Flood flood(server);
    ASSERT_TRUE(eventually([&] { return events.count > 5; }));
    delete ws;
    const auto seen_messages = messages.size();
    const auto seen_events = events.count.load();
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(messages.size(), seen_messages);
    EXPECT_EQ(events.count.load(), seen_events);
    auto future = pending.get_future();
    ASSERT_EQ(future.wait_for(2s), std::future_status::ready);
    EXPECT_EQ(future.get().error.kind, BNC_ERROR_CANCELLED);
    bnc_stream_free(stream);
}

TEST(CApi, SessionLogonIsSigned) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const auto result = ws_send(ws.api, R"({"method":"session.logon","auth":"session_logon"})");
    ASSERT_EQ(result.error.kind, BNC_OK);
    const auto sent = json::parse(server.sessions().front().received.back()).as_object();
    const auto& params = sent.at("params").as_object();
    EXPECT_EQ(params.at("apiKey"), json::value("key"));
    EXPECT_TRUE(params.contains("signature"));
    EXPECT_TRUE(params.contains("timestamp"));
}

// ---- TLS ---------------------------------------------------------------------------------------

namespace {

std::string json_text(const json::object& o) {
    return json::serialize(o);
}

/// The DER form of the first certificate in `pem`.
std::string der_of(const std::string& pem) {
    std::unique_ptr<BIO, decltype(&BIO_free)> bio(
        BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())), BIO_free);
    std::unique_ptr<X509, decltype(&X509_free)> cert(
        PEM_read_bio_X509(bio.get(), nullptr, nullptr, nullptr), X509_free);
    unsigned char* der = nullptr;
    const int length = i2d_X509(cert.get(), &der);
    std::string out(reinterpret_cast<char*>(der), static_cast<std::size_t>(length));
    OPENSSL_free(der);
    return out;
}

/// A file with `text` that is removed when destroyed.
class TempFile {
public:
    explicit TempFile(const std::string& text) {
        static std::atomic<int> counter{0};
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        path_ = (std::filesystem::temp_directory_path() /
                 ("bnc-test-" + std::to_string(stamp) + "-" + std::to_string(counter++) + ".pem"))
                    .string();
        std::ofstream(path_, std::ios::binary) << text;
    }
    ~TempFile() { std::filesystem::remove(path_); }
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    [[nodiscard]] const std::string& path() const { return path_; }

private:
    std::string path_;
};

/// What the verify callback saw, and what it answers: 1, 0, or (-1) the `preverified` value.
struct Verify {
    std::mutex mutex;
    std::vector<std::string> certs;
    std::vector<int> depths;
    std::vector<int> preverified;
    int answer = -1;

    [[nodiscard]] std::size_t calls() {
        const std::lock_guard lock(mutex);
        return certs.size();
    }
};

int32_t on_verify(void* user, const uint8_t* der, size_t len, int32_t depth, int32_t preverified) {
    auto* v = static_cast<Verify*>(user);
    const std::lock_guard lock(v->mutex);
    v->certs.emplace_back(reinterpret_cast<const char*>(der), len);
    v->depths.push_back(depth);
    v->preverified.push_back(preverified);
    return v->answer < 0 ? preverified : v->answer;
}

bnc_client_options verify_options(Verify& verify) {
    bnc_client_options options{};
    options.struct_size = sizeof options;
    options.tls_verify = on_verify;
    options.tls_verify_data = &verify;
    return options;
}

const std::string& cert_pem() {
    return TestCertificate::get().cert_pem;
}

std::string tls_rest_config(const MockServer& server, json::object extra = {}) {
    json::object config{{"base_path", server.url()}, {"retries", 0}};
    for (auto& [name, value] : extra) {
        config[name] = value;
    }
    return json_text(config);
}

RestResult send_new(const std::string& config, const bnc_client_options* options = nullptr) {
    bnc_error error{};
    std::unique_ptr<bnc_rest_client, decltype(&bnc_rest_free)> client(
        bnc_rest_new_ex(config.c_str(), options, &error), &bnc_rest_free);
    EXPECT_NE(client, nullptr) << error.message;
    return client != nullptr ? send(client.get(), R"({"endpoint":"/x"})") : RestResult{};
}

} // namespace

TEST(CApiTls, ACaFromPemIsTrusted) {
    MockServer server({}, TestCertificate::get().server_context());
    const auto untrusted = send_new(tls_rest_config(server));
    ASSERT_FALSE(untrusted.ok);
    EXPECT_EQ(untrusted.error.kind, BNC_ERROR_NETWORK);
    EXPECT_EQ(std::string(untrusted.error.transport_category), "asio.ssl");
    EXPECT_EQ(untrusted.error.request_sent, 0);
    EXPECT_EQ(server.request_count(), 0U);

    const auto trusted = send_new(tls_rest_config(server, {{"ca_pem", cert_pem()}}));
    EXPECT_TRUE(trusted.ok) << trusted.error.message;
}

TEST(CApiTls, ACaFromAFileIsTrusted) {
    MockServer server({}, TestCertificate::get().server_context());
    // A bundle: another certificate first, then the one that matters.
    const TempFile bundle(TestCertificate::unrelated().cert_pem + "\n" + cert_pem());
    const auto result = send_new(tls_rest_config(server, {{"ca_file", bundle.path()}}));
    EXPECT_TRUE(result.ok) << result.error.message;
}

TEST(CApiTls, AClientCertificateIsPresented) {
    // A server that requires a client certificate issued by the "unrelated" test certificate.
    auto ctx = TestCertificate::get().server_context();
    ctx->set_verify_mode(boost::asio::ssl::verify_peer |
                         boost::asio::ssl::verify_fail_if_no_peer_cert);
    ctx->add_certificate_authority(boost::asio::buffer(TestCertificate::unrelated().cert_pem));
    MockServer server({}, ctx);
    const auto& client = TestCertificate::unrelated();

    const auto without = send_new(tls_rest_config(server, {{"ca_pem", cert_pem()}}));
    EXPECT_FALSE(without.ok);
    EXPECT_EQ(server.request_count(), 0U);

    const auto with = send_new(tls_rest_config(server, {{"ca_pem", cert_pem()},
                                                        {"client_cert_pem", client.cert_pem},
                                                        {"client_key_pem", client.key_pem}}));
    EXPECT_TRUE(with.ok) << with.error.message;

    const TempFile cert_file(client.cert_pem);
    const TempFile key_file(client.key_pem);
    const auto from_files =
        send_new(tls_rest_config(server, {{"ca_pem", cert_pem()},
                                          {"client_cert_file", cert_file.path()},
                                          {"client_key_file", key_file.path()}}));
    EXPECT_TRUE(from_files.ok) << from_files.error.message;
}

TEST(CApiTls, UnusableClientCertificatesAreConfigErrors) {
    const auto& client = TestCertificate::unrelated();
    const auto config = [](json::object extra) {
        json::object o{{"base_path", "https://127.0.0.1:1"}};
        for (auto& [name, value] : extra) {
            o[name] = value;
        }
        return json_text(o);
    };
    for (const auto& bad : {
             config({{"client_cert_pem", client.cert_pem}}),
             config({{"client_key_pem", client.key_pem}}),
             config({{"client_cert_pem", "not a certificate"}, {"client_key_pem", client.key_pem}}),
             // The key of another certificate.
             config({{"client_cert_pem", client.cert_pem},
                     {"client_key_pem", TestCertificate::get().key_pem}}),
             config({{"client_cert_pem", client.cert_pem},
                     {"client_cert_file", "/x"},
                     {"client_key_pem", client.key_pem}}),
             config({{"client_cert_file", "/does/not/exist"}, {"client_key_pem", client.key_pem}}),
             config({{"client_key_passphrase", "pw"}}),
         }) {
        bnc_error error{};
        EXPECT_EQ(bnc_rest_new(bad.c_str(), &error), nullptr) << bad;
        EXPECT_EQ(error.kind, BNC_ERROR_CONFIG) << bad;
    }
}

TEST(CApiTls, TheSystemStoreStaysUnlessCaOnly) {
#ifdef _WIN32
    GTEST_SKIP()
        << "The library reads the Windows certificate store, and its C runtime does not see "
           "the SSL_CERT_FILE that this test sets";
#endif
    MockServer server({}, TestCertificate::get().server_context());
    const TempFile system_roots(cert_pem());
    const ScopedEnv env("SSL_CERT_FILE", system_roots.path());
    const auto other = TestCertificate::unrelated().cert_pem;

    EXPECT_TRUE(send_new(tls_rest_config(server)).ok) << "the system store is loaded";
    EXPECT_TRUE(send_new(tls_rest_config(server, {{"ca_pem", other}})).ok)
        << "added CAs do not replace it";
    const auto replaced = send_new(tls_rest_config(server, {{"ca_pem", other}, {"ca_only", true}}));
    EXPECT_FALSE(replaced.ok) << "ca_only drops it";
    EXPECT_EQ(replaced.error.kind, BNC_ERROR_NETWORK);
    EXPECT_TRUE(send_new(tls_rest_config(server, {{"ca_pem", cert_pem()}, {"ca_only", true}})).ok);
}

TEST(CApiTls, UnusableCaSettingsAreConfigErrors) {
    bnc_error error{};
    for (const auto& config : {
             R"({"base_path":"https://x","ca_pem":"not a certificate"})",
             R"({"base_path":"https://x","ca_file":"/nonexistent/ca.pem"})",
             R"({"base_path":"https://x","ca_only":true})",
             R"({"base_path":"https://x","ca_pem":1})",
         }) {
        EXPECT_EQ(bnc_rest_new(config, &error), nullptr) << config;
        EXPECT_EQ(error.kind, BNC_ERROR_CONFIG) << config << ": " << error.message;
    }
    EXPECT_EQ(bnc_wsapi_new(R"({"url":"wss://x","ca_pem":"nope"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_streams_new(R"({"url":"wss://x","ca_only":true})", nullptr, &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApiTls, TheVerifyCallbackSeesTheDerCertificates) {
    MockServer server({}, TestCertificate::get().server_context());
    Verify verify;
    const auto options = verify_options(verify);
    const auto result =
        send_new(tls_rest_config(server, {{"ca_pem", cert_pem()}}), &options); // accepts
    EXPECT_TRUE(result.ok) << result.error.message;
    const std::lock_guard lock(verify.mutex);
    ASSERT_FALSE(verify.certs.empty());
    EXPECT_EQ(verify.depths.front(), 0);
    EXPECT_EQ(verify.preverified.front(), 1);
    EXPECT_EQ(verify.certs.front(), der_of(cert_pem()));
}

TEST(CApiTls, TheVerifyCallbackCanReject) {
    MockServer server({}, TestCertificate::get().server_context());
    Verify verify;
    verify.answer = 0;
    const auto options = verify_options(verify);
    const auto result = send_new(tls_rest_config(server, {{"ca_pem", cert_pem()}}), &options);
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_NETWORK);
    EXPECT_EQ(std::string(result.error.transport_category), "asio.ssl");
    EXPECT_GT(verify.calls(), 0U);
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(CApiTls, TheVerifyCallbackCanTakeOverTheDecision) {
    MockServer server({}, TestCertificate::get().server_context());
    Verify verify;
    verify.answer = 1;
    const auto options = verify_options(verify);
    const auto result = send_new(tls_rest_config(server), &options); // no CA
    EXPECT_TRUE(result.ok) << result.error.message;
    const std::lock_guard lock(verify.mutex);
    ASSERT_FALSE(verify.preverified.empty());
    EXPECT_EQ(verify.preverified.front(), 0);
}

TEST(CApiTls, ClientOptionsAreChecked) {
    bnc_error error{};
    const std::string config = R"({"base_path":"https://x"})";
    bnc_client_options options{};
    EXPECT_EQ(bnc_rest_new_ex(config.c_str(), &options, &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    options.struct_size = sizeof options;
    auto* client = bnc_rest_new_ex(config.c_str(), &options, &error);
    EXPECT_NE(client, nullptr) << error.message;
    bnc_rest_free(client);
}

namespace {

MockWsServer::Options tls_server_options() {
    MockWsServer::Options options;
    options.tls = TestCertificate::get().server_context();
    return options;
}

struct StatusResult {
    int calls = 0;
    bnc_error error{};
};

void on_status_full(void* user, const bnc_error* error) {
    auto* done = static_cast<std::promise<StatusResult>*>(user);
    StatusResult result;
    result.calls = 1;
    if (error != nullptr) {
        result.error = *error;
    }
    done->set_value(result);
}

} // namespace

TEST(CApiTls, WebsocketApiUsesCasAndTheVerifyCallback) {
    MockWsServer server(echo, tls_server_options());
    const auto config =
        json_text({{"url", server.url()}, {"ca_pem", cert_pem()}, {"timeout_ms", 2000}});
    bnc_error error{};

    Verify reject;
    reject.answer = 0;
    auto rejecting = verify_options(reject);
    std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> denied(
        bnc_wsapi_new_ex(config.c_str(), &rejecting, &error), &bnc_wsapi_free);
    ASSERT_NE(denied, nullptr) << error.message;
    std::promise<StatusResult> failed;
    ASSERT_EQ(bnc_wsapi_connect(denied.get(), on_status_full, &failed, nullptr, &error), 0);
    const auto failure = failed.get_future().get();
    EXPECT_EQ(failure.error.kind, BNC_ERROR_NETWORK);
    EXPECT_EQ(failure.error.ws_kind, BNC_WS_NETWORK);
    EXPECT_EQ(std::string(failure.error.transport_category), "asio.ssl");
    EXPECT_GT(reject.calls(), 0U);

    Verify accept;
    auto accepting = verify_options(accept);
    std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(
        bnc_wsapi_new_ex(config.c_str(), &accepting, &error), &bnc_wsapi_free);
    ASSERT_NE(api, nullptr) << error.message;
    std::promise<StatusResult> connected;
    ASSERT_EQ(bnc_wsapi_connect(api.get(), on_status_full, &connected, nullptr, &error), 0);
    EXPECT_EQ(connected.get_future().get().error.kind, BNC_OK);
    EXPECT_EQ(ws_send(api.get(), R"({"method":"ping"})").error.kind, BNC_OK);
    {
        const std::lock_guard lock(accept.mutex);
        ASSERT_FALSE(accept.certs.empty());
        EXPECT_EQ(accept.certs.front(), der_of(cert_pem()));
        EXPECT_EQ(accept.depths.front(), 0);
    }

    // Without the CA the handshake fails.
    const auto bare = json_text({{"url", server.url()}});
    std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> bare_api(
        bnc_wsapi_new(bare.c_str(), &error), &bnc_wsapi_free);
    std::promise<StatusResult> untrusted;
    ASSERT_EQ(bnc_wsapi_connect(bare_api.get(), on_status_full, &untrusted, nullptr, &error), 0);
    EXPECT_EQ(untrusted.get_future().get().error.kind, BNC_ERROR_NETWORK);
}

TEST(CApiTls, StreamsUseCasAndTheVerifyCallback) {
    MockWsServer server({}, tls_server_options());
    const auto config = json_text({{"url", server.url()}, {"ca_pem", cert_pem()}});
    bnc_error error{};

    Verify reject;
    reject.answer = 0;
    auto rejecting = verify_options(reject);
    StreamsPtr denied(bnc_streams_new_ex(config.c_str(), nullptr, &rejecting, &error),
                      &bnc_streams_free);
    ASSERT_NE(denied, nullptr) << error.message;
    std::promise<StatusResult> failed;
    ASSERT_EQ(bnc_streams_connect(denied.get(), nullptr, on_status_full, &failed, nullptr, &error),
              0);
    const auto failure = failed.get_future().get();
    EXPECT_EQ(failure.error.kind, BNC_ERROR_NETWORK);
    EXPECT_EQ(std::string(failure.error.transport_category), "asio.ssl");
    EXPECT_GT(reject.calls(), 0U);

    Verify accept;
    auto accepting = verify_options(accept);
    StreamsPtr streams(bnc_streams_new_ex(config.c_str(), nullptr, &accepting, &error),
                       &bnc_streams_free);
    ASSERT_NE(streams, nullptr) << error.message;
    connect(streams.get());
    EXPECT_EQ(bnc_streams_is_connected(streams.get()), 1);
    EXPECT_GT(accept.calls(), 0U);
}

// ---- SOCKS5 --------------------------------------------------------------------------------

TEST(CApiProxy, RestGoesThroughSocks5) {
    MockServer server;
    MockSocks socks(socks_credentials("user", "pw"));
    auto url = server.url();
    url.replace(url.find("127.0.0.1"), 9, "localhost");
    // "localhost" may resolve to ::1 first, which Windows refuses only after a second or two.
    const auto config = json_text({{"base_path", url},
                                   {"retries", 0},
                                   {"timeout_ms", 10000},
                                   {"proxy", json::object{{"host", "127.0.0.1"},
                                                          {"port", socks.port()},
                                                          {"protocol", "socks5h"},
                                                          {"username", "user"},
                                                          {"password", "pw"}}}});
    const auto result = send_new(config);
    ASSERT_TRUE(result.ok) << result.error.message;
    const auto seen = socks.requests().at(0);
    EXPECT_EQ(seen.address_type, 3);
    EXPECT_EQ(seen.host, "localhost");
    EXPECT_EQ(seen.username, "user");

    const auto wrong = json_text({{"base_path", server.url()},
                                  {"retries", 0},
                                  {"proxy", json::object{{"host", "127.0.0.1"},
                                                         {"port", socks.port()},
                                                         {"protocol", "socks5"},
                                                         {"username", "user"},
                                                         {"password", "bad"}}}});
    const auto failed = send_new(wrong);
    ASSERT_FALSE(failed.ok);
    EXPECT_EQ(failed.error.kind, BNC_ERROR_NETWORK);
    EXPECT_NE(std::string(failed.error.message).find("SOCKS5"), std::string::npos);
    EXPECT_NE(failed.error.transport_code, 0);
}

TEST(CApiProxy, WebsocketsGoThroughSocks5) {
    MockWsServer server(echo);
    MockSocks socks;
    const json::object proxy{{"host", "127.0.0.1"}, {"port", socks.port()}, {"protocol", "socks5"}};
    bnc_error error{};

    const auto api_config = json_text({{"url", server.url()}, {"proxy", proxy}});
    std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(
        bnc_wsapi_new(api_config.c_str(), &error), &bnc_wsapi_free);
    ASSERT_NE(api, nullptr) << error.message;
    std::promise<int> connected;
    ASSERT_EQ(bnc_wsapi_connect(api.get(), on_status, &connected, nullptr, &error), 0);
    EXPECT_EQ(status_of(connected), 0);
    EXPECT_EQ(socks.requests().size(), 1U);

    const auto streams_config = json_text({{"url", server.url()}, {"proxy", proxy}});
    auto streams =
        StreamsPtr(bnc_streams_new(streams_config.c_str(), nullptr, &error), &bnc_streams_free);
    ASSERT_NE(streams, nullptr) << error.message;
    connect(streams.get());
    EXPECT_EQ(socks.requests().size(), 2U);

    const auto bad =
        json_text({{"url", server.url()},
                   {"proxy", json::object{{"host", "h"}, {"port", 1}, {"protocol", "socks4"}}}});
    EXPECT_EQ(bnc_wsapi_new(bad.c_str(), &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

// ---- cancellation of connect, disconnect and subscribe -------------------------------------

namespace {

struct Calls {
    std::atomic<int> count{0};
    std::atomic<int> kind{-1};
    std::atomic<int> ws_kind{-1};
    std::atomic<int> request_sent{-1};
    std::atomic<bnc_stream*> stream{nullptr};
};

void on_status_counted(void* user, const bnc_error* error) {
    auto* calls = static_cast<Calls*>(user);
    calls->kind = error != nullptr ? error->kind : BNC_OK;
    calls->ws_kind = error != nullptr ? error->ws_kind : BNC_WS_NONE;
    calls->request_sent = error != nullptr ? error->request_sent : 0;
    ++calls->count;
}

void on_subscribe_counted(void* user, const bnc_error* error, const char*, size_t,
                          bnc_stream* stream) {
    auto* calls = static_cast<Calls*>(user);
    calls->kind = error != nullptr ? error->kind : BNC_OK;
    calls->ws_kind = error != nullptr ? error->ws_kind : BNC_WS_NONE;
    calls->request_sent = error != nullptr ? error->request_sent : 0;
    calls->stream = stream;
    ++calls->count;
}

} // namespace

TEST(CApi, ConnectingCanBeAbandoned) {
    MockWsServer::Options options;
    options.accept_delay = 1500ms;
    MockWsServer server(echo, options);
    bnc_error error{};

    const auto api_config = R"({"url":")" + server.url() + R"("})";
    std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(
        bnc_wsapi_new(api_config.c_str(), &error), &bnc_wsapi_free);
    ASSERT_NE(api, nullptr);
    Calls api_calls;
    bnc_request* api_request = nullptr;
    ASSERT_EQ(bnc_wsapi_connect(api.get(), on_status_counted, &api_calls, &api_request, &error), 0);
    ASSERT_NE(api_request, nullptr);

    auto streams = new_streams(server);
    Calls streams_calls;
    bnc_request* streams_request = nullptr;
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status_counted, &streams_calls,
                                  &streams_request, &error),
              0);
    ASSERT_NE(streams_request, nullptr);

    std::this_thread::sleep_for(100ms);
    const auto start = std::chrono::steady_clock::now();
    bnc_request_cancel(api_request);
    bnc_request_cancel(streams_request);
    bnc_request_cancel(api_request);
    ASSERT_TRUE(eventually([&] { return api_calls.count == 1 && streams_calls.count == 1; }));
    EXPECT_LT(std::chrono::steady_clock::now() - start, 1s);
    for (const auto* calls : {&api_calls, &streams_calls}) {
        EXPECT_EQ(calls->kind, BNC_ERROR_CANCELLED);
        EXPECT_EQ(calls->ws_kind, BNC_WS_CANCELLED);
        EXPECT_EQ(calls->request_sent, 0);
    }

    // The connection attempts go on, and their completions are dropped.
    ASSERT_TRUE(eventually([&] {
        return bnc_wsapi_is_connected(api.get()) == 1 &&
               bnc_streams_is_connected(streams.get()) == 1;
    }));
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(api_calls.count, 1);
    EXPECT_EQ(streams_calls.count, 1);
    bnc_request_release(api_request);
    bnc_request_release(streams_request);
}

TEST(CApi, ADisconnectCanBeAbandoned) {
    MockWsServer server([](MockWsServer::Session&, const std::string&) {}); // never answers
    WsApiPtr ws(server.url());
    std::promise<WsResult> pending;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_send(ws.api, R"({"method":"never"})", on_ws, &pending, nullptr, &error), 0);
    ASSERT_TRUE(server.wait([](const auto& s) { return !s.at(0).received.empty(); }));

    Calls calls;
    bnc_request* request = nullptr;
    ASSERT_EQ(bnc_wsapi_disconnect(ws.api, on_status_counted, &calls, &request, &error), 0);
    ASSERT_NE(request, nullptr);
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(calls.count, 0) << "the disconnect waits for the pending request";
    bnc_request_cancel(request);
    ASSERT_TRUE(eventually([&] { return calls.count == 1; }));
    EXPECT_EQ(calls.kind, BNC_ERROR_CANCELLED);
    EXPECT_EQ(calls.ws_kind, BNC_WS_CANCELLED);

    // The disconnect goes on, and its completion is dropped.
    ASSERT_TRUE(eventually([&] { return bnc_wsapi_is_connected(ws.api) == 0; }, 5s));
    EXPECT_EQ(pending.get_future().get().error.kind, BNC_ERROR_TIMEOUT);
    std::this_thread::sleep_for(100ms);
    EXPECT_EQ(calls.count, 1);
    bnc_request_release(request);
}

TEST(CApi, CancellingACompletedConnectOrDisconnectIsHarmless) {
    MockWsServer server;
    auto streams = new_streams(server);
    bnc_error error{};
    Calls connected;
    bnc_request* connect_request = nullptr;
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status_counted, &connected,
                                  &connect_request, &error),
              0);
    ASSERT_TRUE(eventually([&] { return connected.count == 1; }));
    bnc_request_cancel(connect_request);
    Calls closed;
    bnc_request* disconnect_request = nullptr;
    ASSERT_EQ(bnc_streams_disconnect(streams.get(), on_status_counted, &closed, &disconnect_request,
                                     &error),
              0);
    ASSERT_TRUE(eventually([&] { return closed.count == 1; }));
    bnc_request_cancel(disconnect_request);
    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(connected.count, 1);
    EXPECT_EQ(connected.kind, BNC_OK);
    EXPECT_EQ(closed.count, 1);
    EXPECT_EQ(closed.kind, BNC_OK);
    bnc_request_release(connect_request);
    bnc_request_release(disconnect_request);
}

TEST(CApi, ASubscribeCanBeAbandoned) {
    struct Held {
        std::mutex mutex;
        std::optional<MockWsServer::Session> session;
        std::string id;
    };
    Held held;
    MockWsServer server([&held](MockWsServer::Session& s, const std::string& text) {
        const std::lock_guard lock(held.mutex);
        held.session = s;
        held.id = std::string(json::parse(text).at("id").as_string());
    });
    WsApiPtr ws(server.url());
    Calls calls;
    Messages messages;
    bnc_request* request = nullptr;
    bnc_error error{};
    ASSERT_EQ(bnc_wsapi_subscribe(ws.api, R"({"method":"userDataStream.subscribe"})",
                                  on_subscribe_counted, &calls, on_message, &messages, &request,
                                  &error),
              0);
    ASSERT_NE(request, nullptr);
    ASSERT_TRUE(eventually([&] {
        const std::lock_guard lock(held.mutex);
        return held.session.has_value();
    }));
    bnc_request_cancel(request);
    ASSERT_TRUE(eventually([&] { return calls.count == 1; }));
    EXPECT_EQ(calls.kind, BNC_ERROR_CANCELLED);
    EXPECT_EQ(calls.ws_kind, BNC_WS_CANCELLED);
    EXPECT_EQ(calls.request_sent, 1);
    EXPECT_EQ(calls.stream, nullptr);

    // The server answers afterwards: nothing is delivered.
    {
        const std::lock_guard lock(held.mutex);
        held.session->send(R"({"id":")" + held.id +
                           R"(","status":200,"result":{"subscriptionId":1}})");
        held.session->send(R"({"subscriptionId":1,"event":{"e":"late"}})");
    }
    std::this_thread::sleep_for(200ms);
    EXPECT_EQ(calls.count, 1);
    EXPECT_EQ(messages.size(), 0U);
    // The library ends the subscription it opened.
    EXPECT_TRUE(server.wait([](const auto& s) {
        for (const auto& r : s.at(0).received) {
            const auto req = json::parse(r);
            if (req.at("method") == "userDataStream.unsubscribe") {
                return req.at("params").at("subscriptionId") == json::value(1);
            }
        }
        return false;
    }));
    bnc_request_release(request);
}

// ---- errors ------------------------------------------------------------------------------------

TEST(CApi, UnusableKeysAreConfigErrors) {
    bnc_error error{};
    const std::string rest_bad_pem = R"({"base_path":"http://x","private_key_pem":"not a key"})";
    EXPECT_EQ(bnc_rest_new(rest_bad_pem.c_str(), &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_NE(std::string(error.message), "");
    EXPECT_EQ(bnc_rest_new(R"({"base_path":"http://x","private_key_file":"/nonexistent/key.pem"})",
                           &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);

    EXPECT_EQ(bnc_wsapi_new(R"({"url":"ws://x","private_key_pem":"not a key"})", &error), nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(
        bnc_wsapi_new(R"({"url":"ws://x","private_key_file":"/nonexistent/key.pem"})", &error),
        nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);

    EXPECT_EQ(bnc_streams_new(
                  R"({"url":"ws://x","signed_streams":true,"api_key":"k","private_key_pem":"x"})",
                  nullptr, &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
    EXPECT_EQ(bnc_streams_new(R"({"url":"ws://x","signed_streams":true,"api_key":"k",)"
                              R"("private_key_file":"/nonexistent/key.pem"})",
                              nullptr, &error),
              nullptr);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, AnAnsweredRequestWasSent) {
    MockServer server([](const auto&) { return MockResponse{.status = 404, .body = "{}"}; });
    RestClientPtr rest(rest_config(server.url()));
    const auto result = send(rest.client, R"({"endpoint":"/x"})");
    ASSERT_FALSE(result.ok);
    EXPECT_EQ(result.error.kind, BNC_ERROR_NOT_FOUND);
    EXPECT_EQ(result.error.http_status, 404);
    EXPECT_EQ(result.error.request_sent, 1);

    MockWsServer ws_server(echo);
    WsApiPtr ws(ws_server.url());
    const auto failed = ws_send(ws.api, R"({"method":"fail"})");
    EXPECT_EQ(failed.error.http_status, 429);
    EXPECT_EQ(failed.error.request_sent, 1);

    MockWsServer::Options rejecting;
    rejecting.reject_status = 403;
    MockWsServer rejector({}, rejecting);
    auto streams = new_streams(rejector);
    std::promise<StatusResult> done;
    bnc_error error{};
    ASSERT_EQ(bnc_streams_connect(streams.get(), nullptr, on_status_full, &done, nullptr, &error),
              0);
    const auto upgrade = done.get_future().get();
    EXPECT_EQ(upgrade.error.http_status, 403);
    EXPECT_EQ(upgrade.error.request_sent, 1);
}

namespace {

/// The error of a send that fails at once or through the callback.
bnc_error send_error(bnc_wsapi* api, const std::string& request) {
    std::promise<WsResult> done;
    bnc_error error{};
    if (bnc_wsapi_send(api, request.c_str(), on_ws, &done, nullptr, &error) != 0) {
        return error;
    }
    return done.get_future().get().error;
}

bnc_wsapi* unconnected_api(const std::string& url, const char* extra = "") {
    bnc_error error{};
    const auto config = R"({"url":")" + url + R"(","api_key":"key","api_secret":"secret",)" +
                        extra + R"("timeout_ms":300})";
    auto* api = bnc_wsapi_new(config.c_str(), &error);
    EXPECT_NE(api, nullptr) << error.message;
    return api;
}

} // namespace

TEST(CApi, WebsocketErrorsCarryTheirKind) {
    bnc_error error{};

    {
        MockWsServer server(echo);
        WsApiPtr ws(server.url());
        const auto failure = ws_send(ws.api, R"({"method":"fail"})").error;
        EXPECT_EQ(failure.kind, BNC_ERROR_WEBSOCKET);
        EXPECT_EQ(failure.ws_kind, BNC_WS_RESPONSE_ERROR);
        // Other failures are not WebSocket ones.
        MockServer rest_server([](const auto&) { return MockResponse{.status = 500}; });
        RestClientPtr rest(rest_config(rest_server.url()));
        EXPECT_EQ(send(rest.client, R"({"endpoint":"/x"})").error.ws_kind, BNC_WS_NONE);
        // A subscription cannot be a session logon: a plain WebsocketError.
        std::promise<WsResult> done;
        Messages messages;
        ASSERT_EQ(bnc_wsapi_subscribe(ws.api, R"({"method":"x","auth":"session_logon"})",
                                      on_ws_subscribe, &done, on_message, &messages, nullptr,
                                      &error),
                  0);
        EXPECT_EQ(done.get_future().get().error.ws_kind, BNC_WS_OTHER);
    }
    {
        MockWsServer server([](MockWsServer::Session&, const std::string&) {}); // never answers
        WsApiPtr ws(server.url());
        std::promise<WsResult> done;
        ASSERT_EQ(bnc_wsapi_send(ws.api, R"({"method":"x"})", on_ws, &done, nullptr, &error), 0);
        const auto timeout = done.get_future().get().error;
        EXPECT_EQ(timeout.kind, BNC_ERROR_TIMEOUT);
        EXPECT_EQ(timeout.ws_kind, BNC_WS_TIMEOUT);
    }
    {
        MockWsServer server(echo);
        std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(unconnected_api(server.url()),
                                                                  &bnc_wsapi_free);
        const auto failure = send_error(api.get(), R"({"method":"x"})");
        EXPECT_EQ(failure.kind, BNC_ERROR_WEBSOCKET);
        EXPECT_EQ(failure.ws_kind, BNC_WS_NOT_CONNECTED);
    }
    {
        MockWsServer server([](MockWsServer::Session& s, const std::string&) { s.drop(); });
        WsApiPtr ws(server.url());
        const auto failure = ws_send(ws.api, R"({"method":"x"})").error;
        EXPECT_EQ(failure.ws_kind, BNC_WS_NO_RESPONSE);
        EXPECT_EQ(failure.request_sent, 1);
    }
    {
        MockWsServer::Options rejecting;
        rejecting.reject_status = 403;
        MockWsServer server({}, rejecting);
        std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(unconnected_api(server.url()),
                                                                  &bnc_wsapi_free);
        std::promise<StatusResult> done;
        ASSERT_EQ(bnc_wsapi_connect(api.get(), on_status_full, &done, nullptr, &error), 0);
        const auto failure = done.get_future().get().error;
        EXPECT_EQ(failure.kind, BNC_ERROR_WEBSOCKET);
        EXPECT_EQ(failure.ws_kind, BNC_WS_HANDSHAKE);
        EXPECT_EQ(failure.http_status, 403);
    }
    {
        std::string url;
        {
            MockWsServer server;
            url = server.url();
        }
        std::unique_ptr<bnc_wsapi, decltype(&bnc_wsapi_free)> api(unconnected_api(url),
                                                                  &bnc_wsapi_free);
        std::promise<StatusResult> done;
        ASSERT_EQ(bnc_wsapi_connect(api.get(), on_status_full, &done, nullptr, &error), 0);
        const auto failure = done.get_future().get().error;
        EXPECT_EQ(failure.kind, BNC_ERROR_NETWORK);
        EXPECT_EQ(failure.ws_kind, BNC_WS_NETWORK);
    }
    {
        MockWsServer server([](MockWsServer::Session&, const std::string&) {});
        WsApiPtr ws(server.url());
        std::promise<WsResult> done;
        bnc_request* request = nullptr;
        ASSERT_EQ(bnc_wsapi_send(ws.api, R"({"method":"x"})", on_ws, &done, &request, &error), 0);
        std::this_thread::sleep_for(50ms);
        bnc_request_cancel(request);
        const auto cancelled = done.get_future().get().error;
        EXPECT_EQ(cancelled.kind, BNC_ERROR_CANCELLED);
        EXPECT_EQ(cancelled.ws_kind, BNC_WS_CANCELLED);
        bnc_request_release(request);
    }
    {
        // An unknown URL path is a plain WebsocketError too.
        MockWsServer server;
        auto streams = new_streams(server);
        EXPECT_EQ(bnc_stream_new(streams.get(), "a@b", "nowhere", nullptr, on_message, nullptr,
                                 nullptr, nullptr, &error),
                  nullptr);
        EXPECT_EQ(error.ws_kind, BNC_WS_OTHER);
    }
}

// ---- WebSocket API request id ------------------------------------------------------------------

namespace {

const std::regex& request_id_pattern() {
    static const std::regex pattern("[0-9a-f]{32}");
    return pattern;
}

/// The id the server received for the last request.
std::string last_id(MockWsServer& server) {
    const auto sent = json::parse(server.sessions().front().received.back()).as_object();
    EXPECT_FALSE(sent.at("params").as_object().contains("id")) << "the id is not a parameter";
    return std::string(sent.at("id").as_string());
}

} // namespace

TEST(CApi, WebsocketApiHonoursAValidRequestId) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const std::string mine = "0123456789abcdef0123456789abcdef";
    ASSERT_EQ(ws_send(ws.api, R"({"method":"ping","id":")" + mine + R"("})").error.kind, BNC_OK);
    EXPECT_EQ(last_id(server), mine);

    // Inside the params it works the same, and the top-level one wins.
    const std::string other = "fedcba9876543210fedcba9876543210";
    ASSERT_EQ(ws_send(ws.api, R"({"method":"ping","params":{"id":")" + other + R"("}})").error.kind,
              BNC_OK);
    EXPECT_EQ(last_id(server), other);
    ASSERT_EQ(ws_send(ws.api, R"({"method":"ping","id":")" + mine + R"(","params":{"id":")" +
                                  other + R"("}})")
                  .error.kind,
              BNC_OK);
    EXPECT_EQ(last_id(server), mine);
}

TEST(CApi, WebsocketApiReplacesAnInvalidRequestId) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    for (const char* id :
         {R"("abc")", R"("0123456789ABCDEF0123456789ABCDEF")", "5", "-1", R"("")"}) {
        ASSERT_EQ(ws_send(ws.api, std::string(R"({"method":"ping","id":)") + id + "}").error.kind,
                  BNC_OK)
            << id;
        const auto used = last_id(server);
        EXPECT_TRUE(std::regex_match(used, request_id_pattern())) << id << " -> " << used;
    }
    bnc_error error{};
    EXPECT_NE(
        bnc_wsapi_send(ws.api, R"({"method":"ping","id":{}})", on_ws, nullptr, nullptr, &error), 0);
    EXPECT_EQ(error.kind, BNC_ERROR_CONFIG);
}

TEST(CApi, WebsocketApiSubscribeHonoursTheRequestId) {
    MockWsServer server(echo);
    WsApiPtr ws(server.url());
    const std::string mine = "0123456789abcdef0123456789abcdef";
    std::promise<WsResult> done;
    Messages messages;
    bnc_error error{};
    const auto request = R"({"method":"userDataStream.subscribe","id":")" + mine + R"("})";
    ASSERT_EQ(bnc_wsapi_subscribe(ws.api, request.c_str(), on_ws_subscribe, &done, on_message,
                                  &messages, nullptr, &error),
              0);
    auto result = done.get_future().get();
    ASSERT_EQ(result.error.kind, BNC_OK);
    EXPECT_EQ(last_id(server), mine);
    bnc_stream_free(result.stream);
}
