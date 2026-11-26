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
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/stocks/websocket_streams/market_streams_api.hpp>

namespace binance::stocks::websocket_streams {

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

MarketStreamsApi::MarketStreamsApi(std::shared_ptr<common::WebsocketStreams> client)
    : client_(std::move(client)) {}

common::WebsocketStream<CalendarStreamResponse>
MarketStreamsApi::calendar_stream(const CalendarStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<CalendarStreamResponse>(*client_, "calendar", p, std::nullopt);
}

common::WebsocketStream<KlineStreamResponse>
MarketStreamsApi::kline_stream(const KlineStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineStreamResponse>(*client_, "<symbol>@kline_<interval>", p,
                                              std::nullopt);
}

common::WebsocketStream<PriceStreamResponse>
MarketStreamsApi::price_stream(const PriceStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<PriceStreamResponse>(*client_, "price", p, std::nullopt);
}

common::WebsocketStream<QuoteStreamResponse>
MarketStreamsApi::quote_stream(const QuoteStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<QuoteStreamResponse>(*client_, "<symbol>@quote", p, std::nullopt);
}

common::WebsocketStream<TradabilityStreamResponse>
MarketStreamsApi::tradability_stream(const TradabilityStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradabilityStreamResponse>(*client_, "<symbol>@tradability", p,
                                                    std::nullopt);
}

common::WebsocketStream<TradingStatusStreamResponse>
MarketStreamsApi::trading_status_stream(const TradingStatusStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradingStatusStreamResponse>(*client_, "<symbol>@tradingStatus", p,
                                                      std::nullopt);
}

} // namespace binance::stocks::websocket_streams
