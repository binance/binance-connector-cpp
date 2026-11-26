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

#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/market_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

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

std::string_view
to_string(ContinuousContractKlineCandlestickStreamsContractTypeEnum value) noexcept {
    switch (value) {
    case ContinuousContractKlineCandlestickStreamsContractTypeEnum::Perpetual:
        return "perpetual";
    case ContinuousContractKlineCandlestickStreamsContractTypeEnum::CurrentQuarter:
        return "current_quarter";
    case ContinuousContractKlineCandlestickStreamsContractTypeEnum::NextQuarter:
        return "next_quarter";
    case ContinuousContractKlineCandlestickStreamsContractTypeEnum::TradifiPerpetual:
        return "tradifi_perpetual";
    case ContinuousContractKlineCandlestickStreamsContractTypeEnum::Unknown:
        break;
    }
    return "";
}

ContinuousContractKlineCandlestickStreamsContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsContractTypeEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "perpetual") {
        return ContinuousContractKlineCandlestickStreamsContractTypeEnum::Perpetual;
    }
    if (s == "current_quarter") {
        return ContinuousContractKlineCandlestickStreamsContractTypeEnum::CurrentQuarter;
    }
    if (s == "next_quarter") {
        return ContinuousContractKlineCandlestickStreamsContractTypeEnum::NextQuarter;
    }
    if (s == "tradifi_perpetual") {
        return ContinuousContractKlineCandlestickStreamsContractTypeEnum::TradifiPerpetual;
    }
    return ContinuousContractKlineCandlestickStreamsContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ContinuousContractKlineCandlestickStreamsContractTypeEnum value) {
    if (value == ContinuousContractKlineCandlestickStreamsContractTypeEnum::Unknown) {
        throw std::invalid_argument(
            "ContinuousContractKlineCandlestickStreamsContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ContinuousContractKlineCandlestickStreamsIntervalEnum value) noexcept {
    switch (value) {
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1s:
        return "1s";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1m:
        return "1m";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval3m:
        return "3m";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval5m:
        return "5m";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval15m:
        return "15m";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval30m:
        return "30m";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1h:
        return "1h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval2h:
        return "2h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval4h:
        return "4h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval6h:
        return "6h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval8h:
        return "8h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval12h:
        return "12h";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1d:
        return "1d";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval3d:
        return "3d";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1w:
        return "1w";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1Month:
        return "1M";
    case ContinuousContractKlineCandlestickStreamsIntervalEnum::Unknown:
        break;
    }
    return "";
}

ContinuousContractKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return ContinuousContractKlineCandlestickStreamsIntervalEnum::Interval1Month;
    }
    return ContinuousContractKlineCandlestickStreamsIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ContinuousContractKlineCandlestickStreamsIntervalEnum value) {
    if (value == ContinuousContractKlineCandlestickStreamsIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "ContinuousContractKlineCandlestickStreamsIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlineCandlestickStreamsIntervalEnum value) noexcept {
    switch (value) {
    case KlineCandlestickStreamsIntervalEnum::Interval1m:
        return "1m";
    case KlineCandlestickStreamsIntervalEnum::Interval3m:
        return "3m";
    case KlineCandlestickStreamsIntervalEnum::Interval5m:
        return "5m";
    case KlineCandlestickStreamsIntervalEnum::Interval15m:
        return "15m";
    case KlineCandlestickStreamsIntervalEnum::Interval30m:
        return "30m";
    case KlineCandlestickStreamsIntervalEnum::Interval1h:
        return "1h";
    case KlineCandlestickStreamsIntervalEnum::Interval2h:
        return "2h";
    case KlineCandlestickStreamsIntervalEnum::Interval4h:
        return "4h";
    case KlineCandlestickStreamsIntervalEnum::Interval6h:
        return "6h";
    case KlineCandlestickStreamsIntervalEnum::Interval8h:
        return "8h";
    case KlineCandlestickStreamsIntervalEnum::Interval12h:
        return "12h";
    case KlineCandlestickStreamsIntervalEnum::Interval1d:
        return "1d";
    case KlineCandlestickStreamsIntervalEnum::Interval3d:
        return "3d";
    case KlineCandlestickStreamsIntervalEnum::Interval1w:
        return "1w";
    case KlineCandlestickStreamsIntervalEnum::Interval1Month:
        return "1M";
    case KlineCandlestickStreamsIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return KlineCandlestickStreamsIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineCandlestickStreamsIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineCandlestickStreamsIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineCandlestickStreamsIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineCandlestickStreamsIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineCandlestickStreamsIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineCandlestickStreamsIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineCandlestickStreamsIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineCandlestickStreamsIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineCandlestickStreamsIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineCandlestickStreamsIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineCandlestickStreamsIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineCandlestickStreamsIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineCandlestickStreamsIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineCandlestickStreamsIntervalEnum::Interval1Month;
    }
    return KlineCandlestickStreamsIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineCandlestickStreamsIntervalEnum value) {
    if (value == KlineCandlestickStreamsIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineCandlestickStreamsIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarkPriceStreamUpdateSpeedEnum value) noexcept {
    switch (value) {
    case MarkPriceStreamUpdateSpeedEnum::UpdateSpeed1s:
        return "1s";
    case MarkPriceStreamUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

MarkPriceStreamUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceStreamUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return MarkPriceStreamUpdateSpeedEnum::UpdateSpeed1s;
    }
    return MarkPriceStreamUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarkPriceStreamUpdateSpeedEnum value) {
    if (value == MarkPriceStreamUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument("MarkPriceStreamUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarkPriceStreamForAllMarketUpdateSpeedEnum value) noexcept {
    switch (value) {
    case MarkPriceStreamForAllMarketUpdateSpeedEnum::UpdateSpeed1s:
        return "1s";
    case MarkPriceStreamForAllMarketUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

MarkPriceStreamForAllMarketUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceStreamForAllMarketUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return MarkPriceStreamForAllMarketUpdateSpeedEnum::UpdateSpeed1s;
    }
    return MarkPriceStreamForAllMarketUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarkPriceStreamForAllMarketUpdateSpeedEnum value) {
    if (value == MarkPriceStreamForAllMarketUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument(
            "MarkPriceStreamForAllMarketUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketApi::MarketApi(std::shared_ptr<common::WebsocketStreams> client)
    : client_(std::move(client)) {}

common::WebsocketStream<AggregateTradeStreamsResponse>
MarketApi::aggregate_trade_streams(const AggregateTradeStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AggregateTradeStreamsResponse>(*client_, "/<symbol>@aggTrade", p,
                                                        std::optional<std::string>("market"));
}

common::WebsocketStream<AllMarketLiquidationOrderStreamsResponse>
MarketApi::all_market_liquidation_order_streams(
    const AllMarketLiquidationOrderStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllMarketLiquidationOrderStreamsResponse>(
        *client_, "/!forceOrder@arr", p, std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<AllMarketMiniTickersStreamResponseInner>>
MarketApi::all_market_mini_tickers_stream(const AllMarketMiniTickersStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMarketMiniTickersStreamResponseInner>>(
        *client_, "/!miniTicker@arr", p, std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
MarketApi::all_market_tickers_streams(const AllMarketTickersStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMarketTickersStreamsResponseInner>>(
        *client_, "/!ticker@arr", p, std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<AssetIndexResponseInner>>
MarketApi::asset_index(const AssetIndexParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AssetIndexResponseInner>>(
        *client_, "/!assetIndex@arr", p, std::optional<std::string>("market"));
}

common::WebsocketStream<CompositeIndexSymbolInformationStreamsResponse>
MarketApi::composite_index_symbol_information_streams(
    const CompositeIndexSymbolInformationStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<CompositeIndexSymbolInformationStreamsResponse>(
        *client_, "/<symbol>@compositeIndex", p, std::optional<std::string>("market"));
}

common::WebsocketStream<ContinuousContractKlineCandlestickStreamsResponse>
MarketApi::continuous_contract_kline_candlestick_streams(
    const ContinuousContractKlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "contractType", params.contract_type);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ContinuousContractKlineCandlestickStreamsResponse>(
        *client_, "/<pair>_<contractType>@continuousKline_<interval>", p,
        std::optional<std::string>("market"));
}

common::WebsocketStream<ContractInfoStreamResponse>
MarketApi::contract_info_stream(const ContractInfoStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ContractInfoStreamResponse>(*client_, "/!contractInfo", p,
                                                     std::optional<std::string>("market"));
}

common::WebsocketStream<IndividualSymbolMiniTickerStreamResponse>
MarketApi::individual_symbol_mini_ticker_stream(
    const IndividualSymbolMiniTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolMiniTickerStreamResponse>(
        *client_, "/<symbol>@miniTicker", p, std::optional<std::string>("market"));
}

common::WebsocketStream<IndividualSymbolTickerStreamsResponse>
MarketApi::individual_symbol_ticker_streams(
    const IndividualSymbolTickerStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolTickerStreamsResponse>(
        *client_, "/<symbol>@ticker", p, std::optional<std::string>("market"));
}

common::WebsocketStream<KlineCandlestickStreamsResponse>
MarketApi::kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineCandlestickStreamsResponse>(*client_, "/<symbol>@kline_<interval>", p,
                                                          std::optional<std::string>("market"));
}

common::WebsocketStream<LiquidationOrderStreamsResponse>
MarketApi::liquidation_order_streams(const LiquidationOrderStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<LiquidationOrderStreamsResponse>(*client_, "/<symbol>@forceOrder", p,
                                                          std::optional<std::string>("market"));
}

common::WebsocketStream<MarkPriceStreamResponse>
MarketApi::mark_price_stream(const MarkPriceStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<MarkPriceStreamResponse>(*client_, "/<symbol>@markPrice@<updateSpeed>", p,
                                                  std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<MarkPriceStreamForAllMarketResponseInner>>
MarketApi::mark_price_stream_for_all_market(const MarkPriceStreamForAllMarketParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<std::vector<MarkPriceStreamForAllMarketResponseInner>>(
        *client_, "/!markPrice@arr@<updateSpeed>", p, std::optional<std::string>("market"));
}

common::WebsocketStream<TradingSessionStreamResponse>
MarketApi::trading_session_stream(const TradingSessionStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradingSessionStreamResponse>(*client_, "/tradingSession", p,
                                                       std::optional<std::string>("market"));
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
