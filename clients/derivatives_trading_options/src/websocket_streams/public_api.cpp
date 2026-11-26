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
#include <binance/derivatives_trading_options/websocket_streams/public_api.hpp>

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

std::string_view to_string(DiffBookDepthStreamsUpdateSpeedEnum value) noexcept {
    switch (value) {
    case DiffBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms:
        return "100ms";
    case DiffBookDepthStreamsUpdateSpeedEnum::UpdateSpeed500ms:
        return "500ms";
    case DiffBookDepthStreamsUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

DiffBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<DiffBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "100ms") {
        return DiffBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms;
    }
    if (s == "500ms") {
        return DiffBookDepthStreamsUpdateSpeedEnum::UpdateSpeed500ms;
    }
    return DiffBookDepthStreamsUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DiffBookDepthStreamsUpdateSpeedEnum value) {
    if (value == DiffBookDepthStreamsUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument("DiffBookDepthStreamsUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialBookDepthStreamsLevelEnum value) noexcept {
    switch (value) {
    case PartialBookDepthStreamsLevelEnum::Level5:
        return "5";
    case PartialBookDepthStreamsLevelEnum::Level10:
        return "10";
    case PartialBookDepthStreamsLevelEnum::Level20:
        return "20";
    case PartialBookDepthStreamsLevelEnum::Unknown:
        break;
    }
    return "";
}

PartialBookDepthStreamsLevelEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsLevelEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5") {
        return PartialBookDepthStreamsLevelEnum::Level5;
    }
    if (s == "10") {
        return PartialBookDepthStreamsLevelEnum::Level10;
    }
    if (s == "20") {
        return PartialBookDepthStreamsLevelEnum::Level20;
    }
    return PartialBookDepthStreamsLevelEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialBookDepthStreamsLevelEnum value) {
    if (value == PartialBookDepthStreamsLevelEnum::Unknown) {
        throw std::invalid_argument("PartialBookDepthStreamsLevelEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PartialBookDepthStreamsUpdateSpeedEnum value) noexcept {
    switch (value) {
    case PartialBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms:
        return "100ms";
    case PartialBookDepthStreamsUpdateSpeedEnum::UpdateSpeed500ms:
        return "500ms";
    case PartialBookDepthStreamsUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

PartialBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "100ms") {
        return PartialBookDepthStreamsUpdateSpeedEnum::UpdateSpeed100ms;
    }
    if (s == "500ms") {
        return PartialBookDepthStreamsUpdateSpeedEnum::UpdateSpeed500ms;
    }
    return PartialBookDepthStreamsUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialBookDepthStreamsUpdateSpeedEnum value) {
    if (value == PartialBookDepthStreamsUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument(
            "PartialBookDepthStreamsUpdateSpeedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

PublicApi::PublicApi(std::shared_ptr<common::WebsocketStreams> client)
    : client_(std::move(client)) {}

common::WebsocketStream<DiffBookDepthStreamsResponse>
PublicApi::diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<DiffBookDepthStreamsResponse>(*client_, "/<symbol>@depth@<updateSpeed>", p,
                                                       std::optional<std::string>("public"));
}

common::WebsocketStream<Hour24TickerResponse>
PublicApi::hour24_ticker(const Hour24TickerParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "expirationDate", params.expiration_date);
    return create_stream<Hour24TickerResponse>(*client_, "/<symbol>@optionTicker<expirationDate>",
                                               p, std::optional<std::string>("public"));
}

common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
PublicApi::individual_symbol_book_ticker_streams(
    const IndividualSymbolBookTickerStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolBookTickerStreamsResponse>(
        *client_, "/<symbol>@bookTicker", p, std::optional<std::string>("public"));
}

common::WebsocketStream<PartialBookDepthStreamsResponse>
PublicApi::partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "level", params.level);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<PartialBookDepthStreamsResponse>(
        *client_, "/<symbol>@depth<level>@<updateSpeed>", p, std::optional<std::string>("public"));
}

common::WebsocketStream<TradeStreamsResponse>
PublicApi::trade_streams(const TradeStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<TradeStreamsResponse>(*client_, "/<symbol>@optionTrade", p,
                                               std::optional<std::string>("public"));
}

} // namespace binance::derivatives_trading_options::websocket_streams
