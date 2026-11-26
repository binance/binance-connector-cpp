//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// `normalize_stream_id`, `remove_empty_value`, `replace_websocket_streams_placeholders` and
// `build_websocket_api_message`.

#include <array>
#include <map>
#include <string>

#include <gtest/gtest.h>
#include <openssl/hmac.h>

#include <binance/common/config.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/signer.hpp>

#include "utils.hpp"

using binance::common::Params;
using binance::common::SignatureGenerator;
using binance::common::StreamId;
using binance::common::WebsocketApiConfig;
using binance::common::WebsocketMessageSendOptions;
using binance::common::detail::build_websocket_api_message;
using binance::common::detail::is_valid_request_id;
using binance::common::detail::normalize_stream_id;
using binance::common::detail::remove_empty_value;
using binance::common::detail::replace_websocket_streams_placeholders;
using binance::common::detail::replace_websocket_streams_placeholders_preserve_case;
namespace json = boost::json;

namespace {

bool is_lower_hex32(const json::value& v) {
    return v.is_string() && is_valid_request_id(v.get_string());
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

WebsocketApiConfig make_config() {
    WebsocketApiConfig cfg;
    cfg.api_key = "api-key";
    cfg.api_secret = "api-secret";
    return cfg;
}

SignatureGenerator make_signer() {
    return {std::string("api-secret"), std::nullopt, std::nullopt};
}

WebsocketMessageSendOptions signed_options() {
    WebsocketMessageSendOptions o;
    o.with_api_key = true;
    o.is_signed = true;
    return o;
}

} // namespace

// ---- normalize_stream_id ----

TEST(NormalizeStreamId, ValidHexStringIsKept) {
    const std::string id = "0123456789abcdef0123456789abcdef";
    EXPECT_EQ(normalize_stream_id(StreamId(id)), json::value(id));
}

TEST(NormalizeStreamId, InvalidHexStringGeneratesRandomHex) {
    const auto out = normalize_stream_id(StreamId(std::string("not-hex")));
    EXPECT_TRUE(is_lower_hex32(out));
    EXPECT_NE(out, json::value("not-hex"));
}

TEST(NormalizeStreamId, NoneGeneratesRandomHex) {
    EXPECT_TRUE(is_lower_hex32(normalize_stream_id(std::nullopt)));
}

TEST(NormalizeStreamId, NumberIsKeptWhenNotStrict) {
    const auto out = normalize_stream_id(StreamId(std::uint32_t{42}));
    ASSERT_TRUE(out.is_number());
    EXPECT_EQ(out.to_number<std::uint64_t>(), 42U);
}

TEST(NormalizeStreamId, StrictNumberForcesNumberEvenForValidHexString) {
    EXPECT_TRUE(normalize_stream_id(StreamId(std::string("0123456789abcdef0123456789abcdef")), true)
                    .is_number());
}

TEST(NormalizeStreamId, StrictNumberKeepsNumberIfProvided) {
    EXPECT_EQ(normalize_stream_id(StreamId(std::uint32_t{7}), true).to_number<std::uint64_t>(), 7U);
}

TEST(NormalizeStreamId, StrictNumberGeneratesNumberWhenNone) {
    EXPECT_TRUE(normalize_stream_id(std::nullopt, true).is_number());
}

TEST(NormalizeStreamId, StrictNumberGeneratesNumberForInvalidHexString) {
    EXPECT_TRUE(normalize_stream_id(StreamId(std::string("nope")), true).is_number());
}

TEST(NormalizeStreamId, RandomIdsDiffer) {
    EXPECT_NE(normalize_stream_id(std::nullopt), normalize_stream_id(std::nullopt));
}

// ---- remove_empty_value ----

TEST(RemoveEmptyValue, FiltersOutNullAndEmptyStrings) {
    const auto out = remove_empty_value({{"key1", "value1"}, {"key2", nullptr}, {"key3", ""}});
    ASSERT_EQ(out.size(), 1U);
    EXPECT_EQ(out.at("key1"), json::value("value1"));
}

TEST(RemoveEmptyValue, RetainsOtherValueTypes) {
    const auto out = remove_empty_value({{"bool", true},
                                         {"num", 42},
                                         {"arr", json::array()},
                                         {"obj", json::object()},
                                         {"nil", nullptr},
                                         {"empty_str", ""}});
    EXPECT_EQ(out.size(), 4U);
    EXPECT_EQ(out.at("bool"), json::value(true));
    EXPECT_EQ(out.at("num"), json::value(42));
    EXPECT_EQ(out.at("arr"), json::value(json::array()));
    EXPECT_EQ(out.at("obj"), json::value(json::object()));
    EXPECT_FALSE(out.contains("nil"));
    EXPECT_FALSE(out.contains("empty_str"));
}

TEST(RemoveEmptyValue, EmptyInputReturnsEmpty) {
    EXPECT_TRUE(remove_empty_value({}).empty());
}

TEST(RemoveEmptyValue, KeysAreSorted) {
    const auto out = remove_empty_value({{"c", "foo"}, {"a", "bar"}, {"b", "baz"}});
    std::string keys;
    for (const auto& [k, v] : out) {
        keys += k;
    }
    EXPECT_EQ(keys, "abc");
}

// ---- replace_websocket_streams_placeholders ----

TEST(ReplaceWebsocketStreamsPlaceholders, EmptyStringUnchanged) {
    EXPECT_EQ(replace_websocket_streams_placeholders("", {}), "");
}

TEST(ReplaceWebsocketStreamsPlaceholders, UnknownPlaceholderBecomesEmpty) {
    EXPECT_EQ(replace_websocket_streams_placeholders("<foo>", {}), "");
}

TEST(ReplaceWebsocketStreamsPlaceholders, LeadingSlashSymbolLowercasesHead) {
    EXPECT_EQ(replace_websocket_streams_placeholders("/<symbol>", {{"symbol", "BTC"}}), "btc");
}

TEST(ReplaceWebsocketStreamsPlaceholders, ALeadingListenKeyKeepsItsCase) {
    EXPECT_EQ(replace_websocket_streams_placeholders("/<listenKey>@orderReportV2",
                                                     {{"listenKey", "AbC123xYz"}}),
              "AbC123xYz@orderReportV2");
    EXPECT_EQ(replace_websocket_streams_placeholders("/<listen_key>", {{"listenKey", "AbC"}}),
              "AbC");
    EXPECT_EQ(replace_websocket_streams_placeholders("/<listenKey>@<symbol>",
                                                     {{"listenKey", "Key"}, {"symbol", "BTCUSDT"}}),
              "Key@BTCUSDT");
}

TEST(ReplaceWebsocketStreamsPlaceholders, NoLowercaseWithoutSlash) {
    EXPECT_EQ(replace_websocket_streams_placeholders("<symbol>", {{"symbol", "BTC"}}), "BTC");
}

TEST(ReplaceWebsocketStreamsPlaceholders, MultiplePlaceholdersPreserveAts) {
    EXPECT_EQ(replace_websocket_streams_placeholders(
                  "/<symbol>@depth<levels>@<updateSpeed>",
                  {{"symbol", "BNBUSDT"}, {"levels", "10"}, {"updateSpeed", "1000ms"}}),
              "bnbusdt@depth10@1000ms");
}

TEST(ReplaceWebsocketStreamsPlaceholders, TrailingAtRemovedWhenVariableMissing) {
    EXPECT_EQ(replace_websocket_streams_placeholders("/<symbol>@depth<levels>@<updateSpeed>",
                                                     {{"symbol", "BNBUSDT"}, {"levels", "10"}}),
              "bnbusdt@depth10");
}

TEST(ReplaceWebsocketStreamsPlaceholders, KeyNormalization) {
    EXPECT_EQ(
        replace_websocket_streams_placeholders("<My_Stream-Key>", {{"my-stream_key", "Value"}}),
        "Value");
}

TEST(ReplaceWebsocketStreamsPlaceholders, TextAroundPlaceholdersIntact) {
    EXPECT_EQ(replace_websocket_streams_placeholders("pre-<symbol>-post", {{"symbol", "ABC"}}),
              "pre-ABC-post");
}

TEST(ReplaceWebsocketStreamsPlaceholders, PreserveCaseKeepsTheLeadingValue) {
    EXPECT_EQ(replace_websocket_streams_placeholders_preserve_case("/<symbol>@quote",
                                                                   {{"symbol", "AAPL"}}),
              "AAPL@quote");
    EXPECT_EQ(
        replace_websocket_streams_placeholders("/<symbol>@quote", {{"symbol", "AAPL"}}, false),
        "AAPL@quote");
    EXPECT_EQ(replace_websocket_streams_placeholders("/<symbol>@quote", {{"symbol", "AAPL"}}),
              "aapl@quote");
}

TEST(ReplaceWebsocketStreamsPlaceholders, PreserveCaseStillHandlesMissingVariables) {
    EXPECT_EQ(
        replace_websocket_streams_placeholders_preserve_case(
            "/<symbol>@depth<levels>@<updateSpeed>", {{"symbol", "BNBUSDT"}, {"levels", "10"}}),
        "BNBUSDT@depth10");
}

// ---- build_websocket_api_message ----

TEST(BuildWebsocketApiMessage, SkipAuthOmitsApiKeyAndSignatureButKeepsTimestamp) {
    const auto [id, req] = build_websocket_api_message(make_config(), make_signer(), "method",
                                                       {{"foo", "bar"}}, signed_options(), true);
    EXPECT_TRUE(is_valid_request_id(id));
    EXPECT_EQ(req.at("id"), json::value(id));
    EXPECT_EQ(req.at("method"), json::value("method"));
    const auto& p = req.at("params").as_object();
    EXPECT_EQ(p.at("foo"), json::value("bar"));
    EXPECT_FALSE(p.contains("apiKey"));
    EXPECT_FALSE(p.contains("signature"));
    EXPECT_TRUE(p.at("timestamp").is_number());
}

TEST(BuildWebsocketApiMessage, OnlyApiKeyWhenNotSigned) {
    WebsocketMessageSendOptions o;
    o.with_api_key = true;
    const auto [id, req] =
        build_websocket_api_message(make_config(), make_signer(), "method", {}, o, false);
    EXPECT_TRUE(is_valid_request_id(id));
    const auto& p = req.at("params").as_object();
    EXPECT_EQ(p.at("apiKey"), json::value("api-key"));
    EXPECT_FALSE(p.contains("timestamp"));
    EXPECT_FALSE(p.contains("signature"));
}

TEST(BuildWebsocketApiMessage, SignedIncludesTimestampAndSignature) {
    const auto [id, req] = build_websocket_api_message(make_config(), make_signer(), "method",
                                                       {{"foo", "bar"}}, signed_options(), false);
    const auto& p = req.at("params").as_object();
    EXPECT_EQ(p.at("apiKey"), json::value("api-key"));
    EXPECT_GT(p.at("timestamp").to_number<std::int64_t>(), 0);
    const auto& sig = p.at("signature").as_string();
    EXPECT_FALSE(sig.empty());
    const auto expected = "apiKey=api-key&foo=bar&timestamp=" +
                          std::to_string(p.at("timestamp").to_number<std::int64_t>());
    EXPECT_EQ(std::string(sig), hmac_hex("api-secret", expected));
}

TEST(BuildWebsocketApiMessage, SignedNonAsciiSymbolIsNotPercentEncodedInSignature) {
    const std::string symbol = "\xE6\x88\x91\xE8\xB8\x8F\xE9\xA9\xAC\xE6\x9D\xA5\xE4\xBA\x86USDT";
    const auto [id, req] =
        build_websocket_api_message(make_config(), make_signer(), "method",
                                    {{"symbol", json::string(symbol)}}, signed_options(), false);
    const auto& p = req.at("params").as_object();
    const auto timestamp = p.at("timestamp").to_number<std::int64_t>();
    const auto expected =
        "apiKey=api-key&symbol=" + symbol + "&timestamp=" + std::to_string(timestamp);
    EXPECT_EQ(std::string(p.at("signature").as_string()), hmac_hex("api-secret", expected));
}

TEST(BuildWebsocketApiMessage, RespectsProvidedValidIdAndRemovesItFromParams) {
    const std::string custom = "0123456789abcdef0123456789abcdef";
    const auto [id, req] =
        build_websocket_api_message(make_config(), make_signer(), "method",
                                    {{"id", json::string(custom)}, {"foo", 123}}, {}, true);
    EXPECT_EQ(id, custom);
    const auto& p = req.at("params").as_object();
    EXPECT_FALSE(p.contains("id"));
    EXPECT_EQ(p.at("foo"), json::value(123));
}

TEST(BuildWebsocketApiMessage, RandomIdChangesEachCall) {
    const auto a = build_websocket_api_message(make_config(), make_signer(), "m", {}, {}, true);
    const auto b = build_websocket_api_message(make_config(), make_signer(), "m", {}, {}, true);
    EXPECT_TRUE(is_valid_request_id(a.first));
    EXPECT_TRUE(is_valid_request_id(b.first));
    EXPECT_NE(a.first, b.first);
}

TEST(BuildWebsocketApiMessage, NullAndEmptyValuesAreStripped) {
    const auto [id, req] = build_websocket_api_message(
        make_config(), make_signer(), "method", {{"a", nullptr}, {"b", ""}, {"c", "ok"}}, {}, true);
    const auto& p = req.at("params").as_object();
    EXPECT_FALSE(p.contains("a"));
    EXPECT_FALSE(p.contains("b"));
    EXPECT_EQ(p.at("c"), json::value("ok"));
}

TEST(BuildWebsocketApiMessage, ProvidedInvalidIdGetsReplaced) {
    const auto [id, req] = build_websocket_api_message(make_config(), make_signer(), "method",
                                                       {{"id", "not-hex-32-chars"}}, {}, true);
    EXPECT_TRUE(is_valid_request_id(id));
    EXPECT_NE(id, "not-hex-32-chars");
}

TEST(BuildWebsocketApiMessage, SignedIncludesApiKeyEvenWithoutWithApiKey) {
    WebsocketMessageSendOptions o;
    o.is_signed = true;
    const auto [id, req] =
        build_websocket_api_message(make_config(), make_signer(), "method", {{"x", 1}}, o, false);
    const auto& p = req.at("params").as_object();
    EXPECT_EQ(p.at("apiKey"), json::value("api-key"));
    EXPECT_TRUE(p.at("timestamp").is_number());
    EXPECT_TRUE(p.at("signature").is_string());
}

TEST(BuildWebsocketApiMessage, NoAuthFlagsGiveEmptyParams) {
    const auto [id, req] =
        build_websocket_api_message(make_config(), make_signer(), "method", {}, {}, false);
    EXPECT_TRUE(req.at("params").as_object().empty());
}

TEST(BuildWebsocketApiMessage, MissingApiKeyThrows) {
    auto cfg = make_config();
    cfg.api_key.reset();
    EXPECT_THROW((void)build_websocket_api_message(cfg, make_signer(), "method", {},
                                                   signed_options(), false),
                 binance::common::ConnectorClientError);
}
