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
#include <binance/derivatives_trading_options/websocket_streams/market_api.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

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
    case KlineCandlestickStreamsIntervalEnum::Interval12h:
        return "12h";
    case KlineCandlestickStreamsIntervalEnum::Interval1d:
        return "1d";
    case KlineCandlestickStreamsIntervalEnum::Interval3d:
        return "3d";
    case KlineCandlestickStreamsIntervalEnum::Interval1w:
        return "1w";
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
    return KlineCandlestickStreamsIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineCandlestickStreamsIntervalEnum value) {
    if (value == KlineCandlestickStreamsIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineCandlestickStreamsIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketApi::MarketApi(std::shared_ptr<common::WebsocketStreams> client)
    : client_(std::move(client)) {}

common::WebsocketStream<std::vector<IndexPriceStreamsResponseInner>>
MarketApi::index_price_streams(const IndexPriceStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<IndexPriceStreamsResponseInner>>(
        *client_, "/!index@arr", p, std::optional<std::string>("market"));
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

common::WebsocketStream<NewSymbolInfoResponse>
MarketApi::new_symbol_info(const NewSymbolInfoParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<NewSymbolInfoResponse>(*client_, "/!optionSymbol", p,
                                                std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<OpenInterestResponseInner>>
MarketApi::open_interest(const OpenInterestParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "underlying", params.underlying);
    common::detail::json::set_param(p, "expirationDate", params.expiration_date);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<OpenInterestResponseInner>>(
        *client_, "/<underlying>@optionOpenInterest@<expirationDate>", p,
        std::optional<std::string>("market"));
}

common::WebsocketStream<std::vector<OptionMarkPriceResponseInner>>
MarketApi::option_mark_price(const OptionMarkPriceParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "underlying", params.underlying);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<OptionMarkPriceResponseInner>>(
        *client_, "/<underlying>@optionMarkPrice", p, std::optional<std::string>("market"));
}

} // namespace binance::derivatives_trading_options::websocket_streams
