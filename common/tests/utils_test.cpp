//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// `build_user_agent`, `validate_time_unit`, `timestamp_ms`, `should_retry_request`,
// `parse_rate_limit_headers`, `random_string`, `random_integer` and the JSON helpers.
#include <algorithm>
#include <chrono>
#include <clocale>
#include <limits>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/json/serialize.hpp>
#include <boost/json/value_from.hpp>
#include <gtest/gtest.h>

#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/signer.hpp>
#include <binance/common/version.hpp>

#include "support/env.hpp"
#include "utils.hpp"

using namespace binance::common;
using binance::test::ScopedEnv;

namespace {

constexpr const char* kUaEnv = "BINANCE_CONNECTOR_CPP_USER_AGENT";

std::int64_t now_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

} // namespace

TEST(BuildUserAgent, ContainsSdkProductAndPlatform) {
    const ScopedEnv env(kUaEnv, std::nullopt);
    const auto ua = binance::common::detail::build_user_agent("product");
    EXPECT_TRUE(ua.starts_with("binance-connector-cpp/product/" + std::string(kVersion) + " (C++/"))
        << ua;
#if defined(__APPLE__)
    EXPECT_NE(ua.find("; macos; "), std::string::npos) << ua;
#elif defined(__linux__)
    EXPECT_NE(ua.find("; linux; "), std::string::npos) << ua;
#elif defined(_WIN32)
    EXPECT_NE(ua.find("; windows; "), std::string::npos) << ua;
#endif
#if defined(__aarch64__) || defined(_M_ARM64)
    EXPECT_TRUE(ua.ends_with("; aarch64)")) << ua;
#elif defined(__x86_64__) || defined(_M_X64)
    EXPECT_TRUE(ua.ends_with("; x86_64)")) << ua;
#endif
}

TEST(BuildUserAgent, IsDeterministic) {
    const ScopedEnv env(kUaEnv, std::nullopt);
    EXPECT_EQ(binance::common::detail::build_user_agent("product"),
              binance::common::detail::build_user_agent("product"));
}

TEST(BuildUserAgent, EnvOverrideCliIsUsedWhenValid) {
    const std::string valid = "binance-cli/1.2.3 (linux; x86_64; extra)";
    const ScopedEnv env(kUaEnv, valid);
    EXPECT_EQ(binance::common::detail::build_user_agent("spot"), valid);
}

TEST(BuildUserAgent, EnvOverrideSkillIsUsedWhenValid) {
    const std::string valid = "binance-skill/2.0 (darwin; aarch64; v2)";
    const ScopedEnv env(kUaEnv, valid);
    EXPECT_EQ(binance::common::detail::build_user_agent("spot"), valid);
}

TEST(BuildUserAgent, EnvOverrideWithWhitespaceIsTrimmed) {
    const std::string valid = "binance-cli/1.0 (linux; x86_64; v1)";
    const ScopedEnv env(kUaEnv, "  " + valid + "  ");
    EXPECT_EQ(binance::common::detail::build_user_agent("spot"), valid);
}

TEST(BuildUserAgent, InvalidEnvOverrideFallsBackToDefault) {
    for (const char* bad : {"not-binance-cli/1.0 (linux; x86_64; v1)", "",
                            "binance-cli/1.0 (linux; x86_64; v1)\r\nX-Evil: 1"}) {
        const ScopedEnv env(kUaEnv, std::string(bad));
        EXPECT_TRUE(
            binance::common::detail::build_user_agent("spot").starts_with("binance-connector-cpp/"))
            << bad;
    }
}

TEST(ValidateTimeUnit, AcceptsKnownUnits) {
    EXPECT_EQ(binance::common::detail::validate_time_unit(""), std::nullopt);
    EXPECT_EQ(binance::common::detail::validate_time_unit("MILLISECOND"), TimeUnit::Millisecond);
    EXPECT_EQ(binance::common::detail::validate_time_unit("MICROSECOND"), TimeUnit::Microsecond);
    EXPECT_EQ(binance::common::detail::validate_time_unit("millisecond"), TimeUnit::Millisecond);
    EXPECT_EQ(binance::common::detail::validate_time_unit("microsecond"), TimeUnit::Microsecond);
}

TEST(ValidateTimeUnit, RejectsOtherValues) {
    for (const char* bad : {"SECOND", "MILLI"}) {
        try {
            (void)binance::common::detail::validate_time_unit(bad);
            ADD_FAILURE() << bad;
        } catch (const ConfigError& e) {
            EXPECT_NE(std::string(e.what()).find(
                          "time_unit must be either 'MILLISECOND' or 'MICROSECOND'"),
                      std::string::npos);
        }
    }
}

TEST(GetTimestamp, IsWithinSystemTimeBounds) {
    const auto before = now_ms();
    EXPECT_EQ(binance::common::detail::timestamp_ms([] { return std::int64_t{42}; }), 42);
    const auto ts = binance::common::detail::timestamp_ms();
    const auto after = now_ms();
    EXPECT_GE(ts, before);
    EXPECT_LE(ts, after);
}

TEST(GetTimestamp, IsMonotonic) {
    const auto t1 = binance::common::detail::timestamp_ms();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    EXPECT_GE(binance::common::detail::timestamp_ms(), t1);
}

TEST(ShouldRetryRequest, RetriesOnRetriableStatusAndMethod) {
    EXPECT_TRUE(binance::common::detail::should_retry_request("GET", 500, 1));
    EXPECT_TRUE(binance::common::detail::should_retry_request("delete", 500, 2));
    for (const int status : {502, 503, 504}) {
        EXPECT_TRUE(binance::common::detail::should_retry_request(
            "GET", static_cast<std::uint16_t>(status), 1))
            << status;
    }
}

TEST(ShouldRetryRequest, RetriesNetworkErrorsForRetriableMethods) {
    EXPECT_TRUE(binance::common::detail::should_retry_request("GET", std::nullopt, 1));
    EXPECT_TRUE(binance::common::detail::should_retry_request("DELETE", std::nullopt, 1));
}

TEST(ShouldRetryRequest, NoRetryWhenNoRetriesLeft) {
    EXPECT_FALSE(binance::common::detail::should_retry_request("GET", 503, 0));
    EXPECT_FALSE(binance::common::detail::should_retry_request("GET", 503, -1));
}

TEST(ShouldRetryRequest, NoRetryOnNonRetriableStatus) {
    for (const int status : {400, 401, 404, 422, 501}) {
        EXPECT_FALSE(binance::common::detail::should_retry_request(
            "GET", static_cast<std::uint16_t>(status), 2))
            << status;
    }
}

TEST(ShouldRetryRequest, NoRetryOnNonRetriableMethod) {
    for (const char* method : {"POST", "PUT", "PATCH"}) {
        EXPECT_FALSE(binance::common::detail::should_retry_request(method, 500, 2)) << method;
        EXPECT_FALSE(binance::common::detail::should_retry_request(method, std::nullopt, 1))
            << method;
    }
}

TEST(ParseRateLimitHeaders, SingleWeightHeader) {
    const auto limits =
        binance::common::detail::parse_rate_limit_headers({{"x-mbx-used-weight-1s", "123"}});
    ASSERT_EQ(limits.size(), 1U);
    EXPECT_EQ(limits[0], (RestApiRateLimit{RateLimitType::RequestWeight, Interval::Second, 1, 123,
                                           std::nullopt}));
}

TEST(ParseRateLimitHeaders, SingleOrderCountWithRetryAfter) {
    const auto limits = binance::common::detail::parse_rate_limit_headers(
        {{"x-mbx-order-count-5m", "42"}, {"retry-after", "7"}});
    ASSERT_EQ(limits.size(), 1U);
    EXPECT_EQ(limits[0], (RestApiRateLimit{RateLimitType::Orders, Interval::Minute, 5, 42, 7}));
}

TEST(ParseRateLimitHeaders, MultipleHeaders) {
    auto limits = binance::common::detail::parse_rate_limit_headers(
        {{"X-MBX-USED-WEIGHT-1h", "10"}, {"x-mbx-order-count-2d", "20"}});
    std::sort(limits.begin(), limits.end(),
              [](const auto& a, const auto& b) { return a.interval_num < b.interval_num; });
    ASSERT_EQ(limits.size(), 2U);
    EXPECT_EQ(limits[0], (RestApiRateLimit{RateLimitType::RequestWeight, Interval::Hour, 1, 10,
                                           std::nullopt}));
    EXPECT_EQ(limits[1],
              (RestApiRateLimit{RateLimitType::Orders, Interval::Day, 2, 20, std::nullopt}));
}

TEST(ParseRateLimitHeaders, IgnoresUnknownAndMalformed) {
    EXPECT_TRUE(
        binance::common::detail::parse_rate_limit_headers(
            {{"x-mbx-used-weight-3x", "5"}, {"random-header", "100"}, {"x-mbx-used-weight-m", "1"}})
            .empty());
}

TEST(ParseRateLimitHeaders, NonNumericCountIsZero) {
    const auto limits =
        binance::common::detail::parse_rate_limit_headers({{"x-mbx-used-weight-1m", "abc"}});
    ASSERT_EQ(limits.size(), 1U);
    EXPECT_EQ(limits[0].count, 0U);
}

TEST(RateLimit, ConvertsToJson) {
    EXPECT_EQ(boost::json::serialize(boost::json::value_from(
                  RestApiRateLimit{RateLimitType::Orders, Interval::Minute, 5, 42, 7})),
              R"({"rateLimitType":"ORDERS","interval":"MINUTE","intervalNum":5,"count":42,)"
              R"("retryAfter":7})");
    EXPECT_EQ(
        boost::json::serialize(boost::json::value_from(
            RestApiRateLimit{RateLimitType::RequestWeight, Interval::Second, 1, 3, {}})),
        R"({"rateLimitType":"REQUEST_WEIGHT","interval":"SECOND","intervalNum":1,"count":3})");
    EXPECT_EQ(boost::json::serialize(boost::json::value_from(WebsocketApiRateLimit{
                  RateLimitType::RequestWeight, Interval::Minute, 1, 6000, 2})),
              R"({"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,)"
              R"("limit":6000,"count":2})");
}

TEST(RandomString, IsLowercaseHex) {
    const auto s = binance::common::detail::random_string();
    EXPECT_EQ(s.size(), 32U);
    EXPECT_TRUE(std::all_of(s.begin(), s.end(), [](char c) {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
    })) << s;
}

TEST(RandomString, TwoCallsAreDifferent) {
    EXPECT_NE(binance::common::detail::random_string(), binance::common::detail::random_string());
}

TEST(RandomInteger, CallsCanDiffer) {
    const auto first = binance::common::detail::random_integer();
    bool differs = false;
    for (int i = 0; i < 8 && !differs; ++i) {
        differs = binance::common::detail::random_integer() != first;
    }
    EXPECT_TRUE(differs);
}

TEST(FormUrlencode, MatchesWhatwgFormEncoding) {
    EXPECT_EQ(binance::common::detail::form_urlencode("AZaz09*-._"), "AZaz09*-._");
    EXPECT_EQ(binance::common::detail::form_urlencode("a b~!'()"), "a+b%7E%21%27%28%29");
    EXPECT_EQ(binance::common::detail::form_urlencode("é"), "%C3%A9");
}

TEST(FormUrlencode, EncodesEveryNonAsciiByte) {
    for (int byte = 0x80; byte <= 0xFF; ++byte) {
        const std::string text(1, static_cast<char>(byte));
        const auto encoded = binance::common::detail::form_urlencode(text);
        EXPECT_EQ(encoded.size(), 3U) << byte;
        EXPECT_EQ(encoded.front(), '%') << byte;
    }
}

TEST(FormUrlencode, IgnoresTheLocale) {
    // Single-byte locales class bytes such as 0xE9 (é) as alphanumeric.
    const std::string previous = std::setlocale(LC_ALL, nullptr);
    bool set = false;
    for (const char* name : {"en_US.ISO8859-1", "en_US.ISO-8859-1", "de_DE.ISO8859-1",
                             "fr_FR.ISO8859-1", "en_US.UTF-8", "C.UTF-8"}) {
        if (std::setlocale(LC_ALL, name) != nullptr) {
            set = true;
            break;
        }
    }
    const auto encoded = binance::common::detail::form_urlencode("\xE9\xC3\xA9 a");
    const auto json = binance::common::detail::to_json_string(boost::json::value(0.5));
    const auto limits =
        binance::common::detail::parse_rate_limit_headers({{"X-MBX-USED-WEIGHT-1M", "\xA0"
                                                                                    "7"}});
    std::setlocale(LC_ALL, previous.c_str());
    if (!set) {
        GTEST_SKIP() << "no non-C locale available";
    }
    EXPECT_EQ(encoded, "%E9%C3%A9+a");
    EXPECT_EQ(json, "0.5");
    // 0xA0 is a space in Latin-1 locales, but not in ASCII.
    ASSERT_EQ(limits.size(), 1U);
    EXPECT_EQ(limits[0].count, 0U);
}

TEST(FormatDouble, MatchesShortestFixedNotation) {
    using binance::common::detail::format_double;
    EXPECT_EQ(format_double(0.0), "0");
    EXPECT_EQ(format_double(-0.0), "-0");
    EXPECT_EQ(format_double(12.0), "12");
    EXPECT_EQ(format_double(-0.000123), "-0.000123");
    EXPECT_EQ(format_double(123456789012345.67), "123456789012345.67");
    EXPECT_EQ(format_double(5e-324), "0." + std::string(323, '0') + "5");
    // Integers from 2^53 up are written exactly.
    EXPECT_EQ(format_double(9007199254740992.0), "9007199254740992");
    EXPECT_EQ(format_double(1e23), "99999999999999991611392");
    EXPECT_EQ(format_double(-1e23), "-99999999999999991611392");
    const auto max = format_double(std::numeric_limits<double>::max());
    EXPECT_EQ(max.size(), 309U);
    EXPECT_TRUE(max.starts_with("17976931348623157081452742373170435679"));
    EXPECT_TRUE(max.ends_with("858368"));
    EXPECT_EQ(format_double(std::numeric_limits<double>::quiet_NaN()), "null");
}

TEST(ParamText, UsesPlainNotationForDoubles) {
    namespace json = binance::common::detail::json;
    EXPECT_EQ(json::param_text(boost::json::value(1e-7)), "0.0000001");
    EXPECT_EQ(json::param_text(boost::json::value("1e-7")), "1e-7");
    std::string endpoint = "/x/{v}";
    json::set_path_param(endpoint, "v", 1e-7);
    EXPECT_EQ(endpoint, "/x/0.0000001");
    std::vector<std::pair<std::string, std::string>> headers;
    json::set_header(headers, "h", 2.5e-8);
    EXPECT_EQ(headers.at(0).second, "0.000000025");
}

TEST(BuildWebsocketApiMessage, SignsTheDoubleTextThatIsSent) {
    WebsocketApiConfig config;
    config.api_key = "k";
    const SignatureGenerator signer(std::string("s"), std::nullopt, std::nullopt);
    const auto [id, request] = binance::common::detail::build_websocket_api_message(
        config, signer, "order.place",
        {{"price", 0.1},
         {"quantity", 1e-7},
         {"big", 1e21},
         {"nan", std::numeric_limits<double>::quiet_NaN()}},
        WebsocketMessageSendOptions{.is_signed = true}, false);
    const auto& params = request.at("params").as_object();
    EXPECT_EQ(params.at("price"), boost::json::value("0.1"));
    EXPECT_EQ(params.at("quantity"), boost::json::value("0.0000001"));
    EXPECT_EQ(params.at("big"), boost::json::value("1000000000000000000000"));
    EXPECT_FALSE(params.contains("nan"));
    const auto wire = boost::json::serialize(request);
    EXPECT_EQ(wire.find("E-"), std::string::npos) << wire;
    const auto timestamp = std::to_string(params.at("timestamp").as_int64());
    EXPECT_EQ(params.at("signature").as_string(),
              signer.sign_payload("apiKey=k&big=1000000000000000000000&price=0.1&"
                                  "quantity=0.0000001&timestamp=" +
                                  timestamp));
}

TEST(BuildWebsocketApiMessage, SortsNestedObjectKeysBeforeSigning) {
    WebsocketApiConfig config;
    config.api_key = "k";
    const SignatureGenerator signer(std::string("s"), std::nullopt, std::nullopt);
    const boost::json::value filter = {{"s", {"BTCUSDT"}}, {"e", {"executionReport"}}};
    const auto [id, request] = binance::common::detail::build_websocket_api_message(
        config, signer, "userDataStream.subscribe.signature", {{"filter", filter}},
        WebsocketMessageSendOptions{.is_signed = true}, false);
    const auto& params = request.at("params").as_object();
    EXPECT_EQ(boost::json::serialize(params.at("filter")),
              R"({"e":["executionReport"],"s":["BTCUSDT"]})");
    const auto timestamp = std::to_string(params.at("timestamp").as_int64());
    EXPECT_EQ(params.at("signature").as_string(),
              signer.sign_payload(R"(apiKey=k&filter={"e":["executionReport"],"s":["BTCUSDT"]}&)"
                                  "timestamp=" +
                                  timestamp));
}

TEST(BuildWebsocketApiMessage, SignsWithTheTimestampProvider) {
    WebsocketApiConfig config;
    config.api_key = "k";
    config.timestamp_provider = [] { return std::int64_t{1700000000123}; };
    const SignatureGenerator signer(std::string("s"), std::nullopt, std::nullopt);
    const auto [id, request] = binance::common::detail::build_websocket_api_message(
        config, signer, "account.status", {}, WebsocketMessageSendOptions{.is_signed = true},
        false);
    const auto& params = request.at("params").as_object();
    EXPECT_EQ(params.at("timestamp").as_int64(), 1700000000123);
    EXPECT_EQ(params.at("signature").as_string(),
              signer.sign_payload("apiKey=k&timestamp=1700000000123"));
}

TEST(BuildWebsocketApiMessage, SignsUtf8ParametersAsTheyAreSent) {
    WebsocketApiConfig config;
    config.api_key = "k";
    config.timestamp_provider = [] { return std::int64_t{1700000000123}; };
    const SignatureGenerator signer(std::string("s"), std::nullopt, std::nullopt);
    const auto [id, request] = binance::common::detail::build_websocket_api_message(
        config, signer, "order.place", {{"newClientOrderId", "caf\xC3\xA9-\xE2\x82\xAC"}},
        WebsocketMessageSendOptions{.is_signed = true}, false);
    const auto& params = request.at("params").as_object();
    EXPECT_EQ(params.at("newClientOrderId").as_string(), "caf\xC3\xA9-\xE2\x82\xAC");
    EXPECT_EQ(params.at("signature").as_string(),
              signer.sign_payload("apiKey=k&newClientOrderId=caf\xC3\xA9-\xE2\x82\xAC&"
                                  "timestamp=1700000000123"));
}

TEST(BuildWebsocketApiMessage, SignsTheNestedDoubleTextThatIsSent) {
    WebsocketApiConfig config;
    config.api_key = "k";
    const SignatureGenerator signer(std::string("s"), std::nullopt, std::nullopt);
    boost::json::array orders;
    orders.push_back(
        boost::json::object{{"price", 1e-7}, {"levels", boost::json::array{2.5, 1e21}}});
    const auto [id, request] = binance::common::detail::build_websocket_api_message(
        config, signer, "batch", {{"orders", orders}},
        WebsocketMessageSendOptions{.is_signed = true}, false);
    const auto& params = request.at("params").as_object();
    const auto& order = params.at("orders").as_array().at(0).as_object();
    EXPECT_EQ(order.at("price"), boost::json::value("0.0000001"));
    EXPECT_EQ(order.at("levels"), (boost::json::array{"2.5", "1000000000000000000000"}));
    const auto wire = boost::json::serialize(request);
    EXPECT_EQ(wire.find("E-"), std::string::npos) << wire;
    EXPECT_EQ(wire.find("E+"), std::string::npos) << wire;
    const auto timestamp = std::to_string(params.at("timestamp").as_int64());
    EXPECT_EQ(params.at("signature").as_string(),
              signer.sign_payload(R"(apiKey=k&orders=[{"levels":["2.5","1000000000000000000000"],)"
                                  R"("price":"0.0000001"}]&timestamp=)" +
                                  timestamp));
}

TEST(ToJsonString, UsesShortestNumbersAndKeepsOrder) {
    boost::json::object obj;
    obj["z"] = 1.5;
    obj["a"] = "x\"y";
    obj["n"] = nullptr;
    EXPECT_EQ(binance::common::detail::to_json_string(obj), R"({"z":1.5,"a":"x\"y","n":null})");
    EXPECT_EQ(binance::common::detail::param_to_string(0.1), "0.1");
    // Plain notation: Binance rejects exponent form ("1e-7").
    EXPECT_EQ(binance::common::detail::param_to_string(1e21), "1000000000000000000000");
    EXPECT_EQ(binance::common::detail::param_to_string(100000.0), "100000");
    EXPECT_EQ(binance::common::detail::param_to_string(1e-7), "0.0000001");
    EXPECT_EQ(binance::common::detail::param_to_string(-2.5), "-2.5");
    EXPECT_EQ(binance::common::detail::param_to_string(std::numeric_limits<double>::infinity()),
              "null");
    EXPECT_EQ(binance::common::detail::param_to_string("plain"), "plain");
}

TEST(Errors, WebsocketMsgOmitsTheKindPrefix) {
    const WebsocketProtocolError protocol("bad frame");
    EXPECT_STREQ(protocol.what(), "WebSocket protocol error: bad frame");
    EXPECT_EQ(protocol.msg(), "bad frame");
    EXPECT_EQ(WebsocketHandshakeError("rejected", 403).msg(), "rejected");
    EXPECT_EQ(WebsocketNetworkError("reset", true).msg(), "reset");
    EXPECT_TRUE(WebsocketNetworkError("reset", true).request_sent());
    EXPECT_EQ(WebsocketServerError("down").msg(), "down");
    EXPECT_EQ(WebsocketTimeoutError().msg(), "WebSocket timeout error");
}
