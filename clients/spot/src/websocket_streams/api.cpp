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
#include <binance/spot/websocket_streams/api.hpp>

namespace binance::spot::websocket_streams {

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

std::string_view to_string(AllMarketRollingWindowTickerWindowSizeEnum value) noexcept {
    switch (value) {
    case AllMarketRollingWindowTickerWindowSizeEnum::WindowSize1h:
        return "1h";
    case AllMarketRollingWindowTickerWindowSizeEnum::WindowSize4h:
        return "4h";
    case AllMarketRollingWindowTickerWindowSizeEnum::WindowSize1d:
        return "1d";
    case AllMarketRollingWindowTickerWindowSizeEnum::Unknown:
        break;
    }
    return "";
}

AllMarketRollingWindowTickerWindowSizeEnum
tag_invoke(boost::json::value_to_tag<AllMarketRollingWindowTickerWindowSizeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1h") {
        return AllMarketRollingWindowTickerWindowSizeEnum::WindowSize1h;
    }
    if (s == "4h") {
        return AllMarketRollingWindowTickerWindowSizeEnum::WindowSize4h;
    }
    if (s == "1d") {
        return AllMarketRollingWindowTickerWindowSizeEnum::WindowSize1d;
    }
    return AllMarketRollingWindowTickerWindowSizeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                AllMarketRollingWindowTickerWindowSizeEnum value) {
    if (value == AllMarketRollingWindowTickerWindowSizeEnum::Unknown) {
        throw std::invalid_argument(
            "AllMarketRollingWindowTickerWindowSizeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(DiffBookDepthUpdateSpeedEnum value) noexcept {
    switch (value) {
    case DiffBookDepthUpdateSpeedEnum::UpdateSpeed100ms:
        return "100ms";
    case DiffBookDepthUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

DiffBookDepthUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<DiffBookDepthUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "100ms") {
        return DiffBookDepthUpdateSpeedEnum::UpdateSpeed100ms;
    }
    return DiffBookDepthUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DiffBookDepthUpdateSpeedEnum value) {
    if (value == DiffBookDepthUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument("DiffBookDepthUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlineIntervalEnum value) noexcept {
    switch (value) {
    case KlineIntervalEnum::Interval1s:
        return "1s";
    case KlineIntervalEnum::Interval1m:
        return "1m";
    case KlineIntervalEnum::Interval3m:
        return "3m";
    case KlineIntervalEnum::Interval5m:
        return "5m";
    case KlineIntervalEnum::Interval15m:
        return "15m";
    case KlineIntervalEnum::Interval30m:
        return "30m";
    case KlineIntervalEnum::Interval1h:
        return "1h";
    case KlineIntervalEnum::Interval2h:
        return "2h";
    case KlineIntervalEnum::Interval4h:
        return "4h";
    case KlineIntervalEnum::Interval6h:
        return "6h";
    case KlineIntervalEnum::Interval8h:
        return "8h";
    case KlineIntervalEnum::Interval12h:
        return "12h";
    case KlineIntervalEnum::Interval1d:
        return "1d";
    case KlineIntervalEnum::Interval3d:
        return "3d";
    case KlineIntervalEnum::Interval1w:
        return "1w";
    case KlineIntervalEnum::Interval1Month:
        return "1M";
    case KlineIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineIntervalEnum tag_invoke(boost::json::value_to_tag<KlineIntervalEnum> /*tag*/,
                             const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return KlineIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return KlineIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineIntervalEnum::Interval1Month;
    }
    return KlineIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineIntervalEnum value) {
    if (value == KlineIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlineOffsetIntervalEnum value) noexcept {
    switch (value) {
    case KlineOffsetIntervalEnum::Interval1s:
        return "1s";
    case KlineOffsetIntervalEnum::Interval1m:
        return "1m";
    case KlineOffsetIntervalEnum::Interval3m:
        return "3m";
    case KlineOffsetIntervalEnum::Interval5m:
        return "5m";
    case KlineOffsetIntervalEnum::Interval15m:
        return "15m";
    case KlineOffsetIntervalEnum::Interval30m:
        return "30m";
    case KlineOffsetIntervalEnum::Interval1h:
        return "1h";
    case KlineOffsetIntervalEnum::Interval2h:
        return "2h";
    case KlineOffsetIntervalEnum::Interval4h:
        return "4h";
    case KlineOffsetIntervalEnum::Interval6h:
        return "6h";
    case KlineOffsetIntervalEnum::Interval8h:
        return "8h";
    case KlineOffsetIntervalEnum::Interval12h:
        return "12h";
    case KlineOffsetIntervalEnum::Interval1d:
        return "1d";
    case KlineOffsetIntervalEnum::Interval3d:
        return "3d";
    case KlineOffsetIntervalEnum::Interval1w:
        return "1w";
    case KlineOffsetIntervalEnum::Interval1Month:
        return "1M";
    case KlineOffsetIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineOffsetIntervalEnum tag_invoke(boost::json::value_to_tag<KlineOffsetIntervalEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return KlineOffsetIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return KlineOffsetIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineOffsetIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineOffsetIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineOffsetIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineOffsetIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineOffsetIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineOffsetIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineOffsetIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineOffsetIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineOffsetIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineOffsetIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineOffsetIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineOffsetIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineOffsetIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineOffsetIntervalEnum::Interval1Month;
    }
    return KlineOffsetIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineOffsetIntervalEnum value) {
    if (value == KlineOffsetIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineOffsetIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialBookDepthLevelsEnum value) noexcept {
    switch (value) {
    case PartialBookDepthLevelsEnum::Levels5:
        return "5";
    case PartialBookDepthLevelsEnum::Levels10:
        return "10";
    case PartialBookDepthLevelsEnum::Levels20:
        return "20";
    case PartialBookDepthLevelsEnum::Unknown:
        break;
    }
    return "";
}

PartialBookDepthLevelsEnum tag_invoke(boost::json::value_to_tag<PartialBookDepthLevelsEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5") {
        return PartialBookDepthLevelsEnum::Levels5;
    }
    if (s == "10") {
        return PartialBookDepthLevelsEnum::Levels10;
    }
    if (s == "20") {
        return PartialBookDepthLevelsEnum::Levels20;
    }
    return PartialBookDepthLevelsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialBookDepthLevelsEnum value) {
    if (value == PartialBookDepthLevelsEnum::Unknown) {
        throw std::invalid_argument("PartialBookDepthLevelsEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialBookDepthUpdateSpeedEnum value) noexcept {
    switch (value) {
    case PartialBookDepthUpdateSpeedEnum::UpdateSpeed100ms:
        return "100ms";
    case PartialBookDepthUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

PartialBookDepthUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "100ms") {
        return PartialBookDepthUpdateSpeedEnum::UpdateSpeed100ms;
    }
    return PartialBookDepthUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialBookDepthUpdateSpeedEnum value) {
    if (value == PartialBookDepthUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument("PartialBookDepthUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(RollingWindowTickerWindowSizeEnum value) noexcept {
    switch (value) {
    case RollingWindowTickerWindowSizeEnum::WindowSize1h:
        return "1h";
    case RollingWindowTickerWindowSizeEnum::WindowSize4h:
        return "4h";
    case RollingWindowTickerWindowSizeEnum::WindowSize1d:
        return "1d";
    case RollingWindowTickerWindowSizeEnum::Unknown:
        break;
    }
    return "";
}

RollingWindowTickerWindowSizeEnum
tag_invoke(boost::json::value_to_tag<RollingWindowTickerWindowSizeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1h") {
        return RollingWindowTickerWindowSizeEnum::WindowSize1h;
    }
    if (s == "4h") {
        return RollingWindowTickerWindowSizeEnum::WindowSize4h;
    }
    if (s == "1d") {
        return RollingWindowTickerWindowSizeEnum::WindowSize1d;
    }
    return RollingWindowTickerWindowSizeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                RollingWindowTickerWindowSizeEnum value) {
    if (value == RollingWindowTickerWindowSizeEnum::Unknown) {
        throw std::invalid_argument("RollingWindowTickerWindowSizeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

Api::Api(std::shared_ptr<common::WebsocketStreams> client) : client_(std::move(client)) {}

common::WebsocketStream<AggTradeResponse> Api::agg_trade(const AggTradeParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AggTradeResponse>(*client_, "/<symbol>@aggTrade", p, std::nullopt);
}

common::WebsocketStream<std::vector<AllMarketRollingWindowTickerResponseInner>>
Api::all_market_rolling_window_ticker(const AllMarketRollingWindowTickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "windowSize", params.window_size);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMarketRollingWindowTickerResponseInner>>(
        *client_, "/!ticker_<windowSize>@arr", p, std::nullopt);
}

common::WebsocketStream<std::vector<AllMiniTickerResponseInner>>
Api::all_mini_ticker(const AllMiniTickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMiniTickerResponseInner>>(*client_, "/!miniTicker@arr", p,
                                                                  std::nullopt);
}

common::WebsocketStream<AvgPriceResponse> Api::avg_price(const AvgPriceParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AvgPriceResponse>(*client_, "/<symbol>@avgPrice", p, std::nullopt);
}

common::WebsocketStream<BlockTradeResponse> Api::block_trade(const BlockTradeParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<BlockTradeResponse>(*client_, "/<symbol>@blockTrade", p, std::nullopt);
}

common::WebsocketStream<BookTickerResponse> Api::book_ticker(const BookTickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<BookTickerResponse>(*client_, "/<symbol>@bookTicker", p, std::nullopt);
}

common::WebsocketStream<DiffBookDepthResponse>
Api::diff_book_depth(const DiffBookDepthParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<DiffBookDepthResponse>(*client_, "/<symbol>@depth@<updateSpeed>", p,
                                                std::nullopt);
}

common::WebsocketStream<KlineResponse> Api::kline(const KlineParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineResponse>(*client_, "/<symbol>@kline_<interval>", p, std::nullopt);
}

common::WebsocketStream<KlineOffsetResponse>
Api::kline_offset(const KlineOffsetParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineOffsetResponse>(*client_, "/<symbol>@kline_<interval>@+08:00", p,
                                              std::nullopt);
}

common::WebsocketStream<MiniTickerResponse> Api::mini_ticker(const MiniTickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<MiniTickerResponse>(*client_, "/<symbol>@miniTicker", p, std::nullopt);
}

common::WebsocketStream<PartialBookDepthResponse>
Api::partial_book_depth(const PartialBookDepthParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "levels", params.levels);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<PartialBookDepthResponse>(
        *client_, "/<symbol>@depth<levels>@<updateSpeed>", p, std::nullopt);
}

common::WebsocketStream<ReferencePriceResponse>
Api::reference_price(const ReferencePriceParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ReferencePriceResponse>(*client_, "/<symbol>@referencePrice", p,
                                                 std::nullopt);
}

common::WebsocketStream<RollingWindowTickerResponse>
Api::rolling_window_ticker(const RollingWindowTickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "windowSize", params.window_size);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<RollingWindowTickerResponse>(*client_, "/<symbol>@ticker_<windowSize>", p,
                                                      std::nullopt);
}

common::WebsocketStream<TickerResponse> Api::ticker(const TickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TickerResponse>(*client_, "/<symbol>@ticker", p, std::nullopt);
}

common::WebsocketStream<TradeResponse> Api::trade(const TradeParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradeResponse>(*client_, "/<symbol>@trade", p, std::nullopt);
}

} // namespace binance::spot::websocket_streams
