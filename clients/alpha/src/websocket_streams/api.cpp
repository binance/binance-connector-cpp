//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <cctype>
#include <charconv>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include <binance/alpha/websocket_streams/api.hpp>
#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>

namespace binance::alpha::websocket_streams {

namespace {

// An all-digit id that fits 32 bits is sent as a number, anything else as a string.
common::StreamId to_stream_id(const std::string& id) {
    if (!id.empty() &&
        std::all_of(id.begin(), id.end(), [](unsigned char c) { return std::isdigit(c) != 0; })) {
        std::uint32_t number = 0;
        const auto [end, ec] = std::from_chars(id.data(), id.data() + id.size(), number);
        if (ec == std::errc() && end == id.data() + id.size()) {
            return number;
        }
    }
    return id;
}

// Fills the placeholders of `path` (`<symbol>@aggTrade`) from `params` and subscribes.
template <class T>
common::WebsocketStream<T> create_stream(common::WebsocketStreams& client, std::string_view path,
                                         const common::Params& params,
                                         std::optional<std::string> url_path) {
    std::map<std::string, std::string> variables;
    for (const auto& [key, value] : params) {
        variables.emplace(std::string(key), common::detail::param_to_string(value));
    }
    std::optional<common::StreamId> id;
    if (const auto it = variables.find("id"); it != variables.end()) {
        id = to_stream_id(it->second);
    }
    return common::WebsocketStream<T>(client.create_stream(
        common::detail::replace_websocket_streams_placeholders(path, variables), std::move(id),
        std::move(url_path)));
}

} // namespace

std::string_view to_string(ContractKlineStreamIntervalEnum value) noexcept {
    switch (value) {
    case ContractKlineStreamIntervalEnum::Interval1s:
        return "1s";
    case ContractKlineStreamIntervalEnum::Interval1m:
        return "1m";
    case ContractKlineStreamIntervalEnum::Interval5m:
        return "5m";
    case ContractKlineStreamIntervalEnum::Interval15m:
        return "15m";
    case ContractKlineStreamIntervalEnum::Interval1h:
        return "1h";
    case ContractKlineStreamIntervalEnum::Interval4h:
        return "4h";
    case ContractKlineStreamIntervalEnum::Interval1d:
        return "1d";
    case ContractKlineStreamIntervalEnum::Unknown:
        break;
    }
    return "";
}

ContractKlineStreamIntervalEnum
tag_invoke(boost::json::value_to_tag<ContractKlineStreamIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return ContractKlineStreamIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return ContractKlineStreamIntervalEnum::Interval1m;
    }
    if (s == "5m") {
        return ContractKlineStreamIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return ContractKlineStreamIntervalEnum::Interval15m;
    }
    if (s == "1h") {
        return ContractKlineStreamIntervalEnum::Interval1h;
    }
    if (s == "4h") {
        return ContractKlineStreamIntervalEnum::Interval4h;
    }
    if (s == "1d") {
        return ContractKlineStreamIntervalEnum::Interval1d;
    }
    return ContractKlineStreamIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ContractKlineStreamIntervalEnum value) {
    if (value == ContractKlineStreamIntervalEnum::Unknown) {
        throw std::invalid_argument("ContractKlineStreamIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(FullDepthStreamIntervalEnum value) noexcept {
    switch (value) {
    case FullDepthStreamIntervalEnum::Interval0ms:
        return "0ms";
    case FullDepthStreamIntervalEnum::Interval100ms:
        return "100ms";
    case FullDepthStreamIntervalEnum::Interval500ms:
        return "500ms";
    case FullDepthStreamIntervalEnum::Unknown:
        break;
    }
    return "";
}

FullDepthStreamIntervalEnum
tag_invoke(boost::json::value_to_tag<FullDepthStreamIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "0ms") {
        return FullDepthStreamIntervalEnum::Interval0ms;
    }
    if (s == "100ms") {
        return FullDepthStreamIntervalEnum::Interval100ms;
    }
    if (s == "500ms") {
        return FullDepthStreamIntervalEnum::Interval500ms;
    }
    return FullDepthStreamIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FullDepthStreamIntervalEnum value) {
    if (value == FullDepthStreamIntervalEnum::Unknown) {
        throw std::invalid_argument("FullDepthStreamIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlineStreamIntervalEnum value) noexcept {
    switch (value) {
    case KlineStreamIntervalEnum::Interval1m:
        return "1m";
    case KlineStreamIntervalEnum::Interval3m:
        return "3m";
    case KlineStreamIntervalEnum::Interval5m:
        return "5m";
    case KlineStreamIntervalEnum::Interval15m:
        return "15m";
    case KlineStreamIntervalEnum::Interval30m:
        return "30m";
    case KlineStreamIntervalEnum::Interval1h:
        return "1h";
    case KlineStreamIntervalEnum::Interval2h:
        return "2h";
    case KlineStreamIntervalEnum::Interval4h:
        return "4h";
    case KlineStreamIntervalEnum::Interval6h:
        return "6h";
    case KlineStreamIntervalEnum::Interval8h:
        return "8h";
    case KlineStreamIntervalEnum::Interval12h:
        return "12h";
    case KlineStreamIntervalEnum::Interval1d:
        return "1d";
    case KlineStreamIntervalEnum::Interval3d:
        return "3d";
    case KlineStreamIntervalEnum::Interval1w:
        return "1w";
    case KlineStreamIntervalEnum::Interval1Month:
        return "1M";
    case KlineStreamIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineStreamIntervalEnum tag_invoke(boost::json::value_to_tag<KlineStreamIntervalEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return KlineStreamIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineStreamIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineStreamIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineStreamIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineStreamIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineStreamIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineStreamIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineStreamIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineStreamIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineStreamIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineStreamIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineStreamIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineStreamIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineStreamIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineStreamIntervalEnum::Interval1Month;
    }
    return KlineStreamIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineStreamIntervalEnum value) {
    if (value == KlineStreamIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineStreamIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialDepthStreamLevelsEnum value) noexcept {
    switch (value) {
    case PartialDepthStreamLevelsEnum::Levels5:
        return "5";
    case PartialDepthStreamLevelsEnum::Levels10:
        return "10";
    case PartialDepthStreamLevelsEnum::Levels20:
        return "20";
    case PartialDepthStreamLevelsEnum::Unknown:
        break;
    }
    return "";
}

PartialDepthStreamLevelsEnum
tag_invoke(boost::json::value_to_tag<PartialDepthStreamLevelsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5") {
        return PartialDepthStreamLevelsEnum::Levels5;
    }
    if (s == "10") {
        return PartialDepthStreamLevelsEnum::Levels10;
    }
    if (s == "20") {
        return PartialDepthStreamLevelsEnum::Levels20;
    }
    return PartialDepthStreamLevelsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialDepthStreamLevelsEnum value) {
    if (value == PartialDepthStreamLevelsEnum::Unknown) {
        throw std::invalid_argument("PartialDepthStreamLevelsEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialDepthStreamIntervalEnum value) noexcept {
    switch (value) {
    case PartialDepthStreamIntervalEnum::Interval0ms:
        return "0ms";
    case PartialDepthStreamIntervalEnum::Interval100ms:
        return "100ms";
    case PartialDepthStreamIntervalEnum::Interval500ms:
        return "500ms";
    case PartialDepthStreamIntervalEnum::Unknown:
        break;
    }
    return "";
}

PartialDepthStreamIntervalEnum
tag_invoke(boost::json::value_to_tag<PartialDepthStreamIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "0ms") {
        return PartialDepthStreamIntervalEnum::Interval0ms;
    }
    if (s == "100ms") {
        return PartialDepthStreamIntervalEnum::Interval100ms;
    }
    if (s == "500ms") {
        return PartialDepthStreamIntervalEnum::Interval500ms;
    }
    return PartialDepthStreamIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialDepthStreamIntervalEnum value) {
    if (value == PartialDepthStreamIntervalEnum::Unknown) {
        throw std::invalid_argument("PartialDepthStreamIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

Api::Api(std::shared_ptr<common::WebsocketStreams> client) : client_(std::move(client)) {}

common::WebsocketStream<AggregateTradeStreamResponse>
Api::aggregate_trade_stream(const AggregateTradeStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AggregateTradeStreamResponse>(*client_, "/<symbol>@aggTrade", p,
                                                       std::nullopt);
}

common::WebsocketStream<AllBookTickerStreamResponse>
Api::all_book_ticker_stream(const AllBookTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllBookTickerStreamResponse>(*client_, "/!bookTicker", p, std::nullopt);
}

common::WebsocketStream<AllMiniTickerStreamResponse>
Api::all_mini_ticker_stream(const AllMiniTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllMiniTickerStreamResponse>(*client_, "/!miniTicker@arr", p,
                                                      std::nullopt);
}

common::WebsocketStream<AllTickerStreamResponse>
Api::all_ticker_stream(const AllTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllTickerStreamResponse>(*client_, "/!ticker@arr", p, std::nullopt);
}

common::WebsocketStream<AllTokens24hTickerStreamResponse>
Api::all_tokens24h_ticker_stream(const AllTokens24hTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllTokens24hTickerStreamResponse>(*client_, "/came@allTokens@ticker24", p,
                                                           std::nullopt);
}

common::WebsocketStream<BookTickerStreamResponse>
Api::book_ticker_stream(const BookTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<BookTickerStreamResponse>(*client_, "/<symbol>@bookTicker", p,
                                                   std::nullopt);
}

common::WebsocketStream<ContractKlineStreamResponse>
Api::contract_kline_stream(const ContractKlineStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "contractAddress", params.contract_address);
    common::detail::json::set_param(p, "chainId", params.chain_id);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ContractKlineStreamResponse>(
        *client_, "/came@<contractAddress>@<chainId>@kline_<interval>", p, std::nullopt);
}

common::WebsocketStream<FullDepthStreamResponse>
Api::full_depth_stream(const FullDepthStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<FullDepthStreamResponse>(*client_, "/<symbol>@fulldepth@<interval>", p,
                                                  std::nullopt);
}

common::WebsocketStream<KlineStreamResponse>
Api::kline_stream(const KlineStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineStreamResponse>(*client_, "/<symbol>@kline_<interval>", p,
                                              std::nullopt);
}

common::WebsocketStream<MiniTickerStreamResponse>
Api::mini_ticker_stream(const MiniTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<MiniTickerStreamResponse>(*client_, "/<symbol>@miniTicker", p,
                                                   std::nullopt);
}

common::WebsocketStream<PartialDepthStreamResponse>
Api::partial_depth_stream(const PartialDepthStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "levels", params.levels);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<PartialDepthStreamResponse>(*client_, "/<symbol>@depth<levels>@<interval>",
                                                     p, std::nullopt);
}

common::WebsocketStream<TickerStreamResponse>
Api::ticker_stream(const TickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TickerStreamResponse>(*client_, "/<symbol>@ticker", p, std::nullopt);
}

common::WebsocketStream<TradeStreamResponse>
Api::trade_stream(const TradeStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradeStreamResponse>(*client_, "/<symbol>@trade", p, std::nullopt);
}

} // namespace binance::alpha::websocket_streams
