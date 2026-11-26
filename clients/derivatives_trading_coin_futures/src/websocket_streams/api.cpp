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
#include <binance/derivatives_trading_coin_futures/websocket_streams/api.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

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

std::string_view to_string(IndexKlineCandlestickStreamsIntervalEnum value) noexcept {
    switch (value) {
    case IndexKlineCandlestickStreamsIntervalEnum::Interval1m:
        return "1m";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval3m:
        return "3m";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval5m:
        return "5m";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval15m:
        return "15m";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval30m:
        return "30m";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval1h:
        return "1h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval2h:
        return "2h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval4h:
        return "4h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval6h:
        return "6h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval8h:
        return "8h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval12h:
        return "12h";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval1d:
        return "1d";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval3d:
        return "3d";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval1w:
        return "1w";
    case IndexKlineCandlestickStreamsIntervalEnum::Interval1Month:
        return "1M";
    case IndexKlineCandlestickStreamsIntervalEnum::Unknown:
        break;
    }
    return "";
}

IndexKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<IndexKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return IndexKlineCandlestickStreamsIntervalEnum::Interval1Month;
    }
    return IndexKlineCandlestickStreamsIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                IndexKlineCandlestickStreamsIntervalEnum value) {
    if (value == IndexKlineCandlestickStreamsIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "IndexKlineCandlestickStreamsIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(IndexPriceStreamUpdateSpeedEnum value) noexcept {
    switch (value) {
    case IndexPriceStreamUpdateSpeedEnum::UpdateSpeed1s:
        return "1s";
    case IndexPriceStreamUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

IndexPriceStreamUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<IndexPriceStreamUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return IndexPriceStreamUpdateSpeedEnum::UpdateSpeed1s;
    }
    return IndexPriceStreamUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                IndexPriceStreamUpdateSpeedEnum value) {
    if (value == IndexPriceStreamUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument("IndexPriceStreamUpdateSpeedEnum::Unknown cannot be sent");
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

std::string_view to_string(MarkPriceKlineCandlestickStreamsIntervalEnum value) noexcept {
    switch (value) {
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1m:
        return "1m";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval3m:
        return "3m";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval5m:
        return "5m";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval15m:
        return "15m";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval30m:
        return "30m";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1h:
        return "1h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval2h:
        return "2h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval4h:
        return "4h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval6h:
        return "6h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval8h:
        return "8h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval12h:
        return "12h";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1d:
        return "1d";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval3d:
        return "3d";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1w:
        return "1w";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1Month:
        return "1M";
    case MarkPriceKlineCandlestickStreamsIntervalEnum::Unknown:
        break;
    }
    return "";
}

MarkPriceKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return MarkPriceKlineCandlestickStreamsIntervalEnum::Interval1Month;
    }
    return MarkPriceKlineCandlestickStreamsIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarkPriceKlineCandlestickStreamsIntervalEnum value) {
    if (value == MarkPriceKlineCandlestickStreamsIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "MarkPriceKlineCandlestickStreamsIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum value) noexcept {
    switch (value) {
    case MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::UpdateSpeed1s:
        return "1s";
    case MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::Unknown:
        break;
    }
    return "";
}

MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::UpdateSpeed1s;
    }
    return MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum value) {
    if (value == MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::Unknown) {
        throw std::invalid_argument(
            "MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum::Unknown cannot be sent");
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

std::string_view to_string(PartialBookDepthStreamsLevelsEnum value) noexcept {
    switch (value) {
    case PartialBookDepthStreamsLevelsEnum::Levels5:
        return "5";
    case PartialBookDepthStreamsLevelsEnum::Levels10:
        return "10";
    case PartialBookDepthStreamsLevelsEnum::Levels20:
        return "20";
    case PartialBookDepthStreamsLevelsEnum::Unknown:
        break;
    }
    return "";
}

PartialBookDepthStreamsLevelsEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsLevelsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5") {
        return PartialBookDepthStreamsLevelsEnum::Levels5;
    }
    if (s == "10") {
        return PartialBookDepthStreamsLevelsEnum::Levels10;
    }
    if (s == "20") {
        return PartialBookDepthStreamsLevelsEnum::Levels20;
    }
    return PartialBookDepthStreamsLevelsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PartialBookDepthStreamsLevelsEnum value) {
    if (value == PartialBookDepthStreamsLevelsEnum::Unknown) {
        throw std::invalid_argument("PartialBookDepthStreamsLevelsEnum::Unknown cannot be sent");
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

Api::Api(std::shared_ptr<common::WebsocketStreams> client) : client_(std::move(client)) {}

common::WebsocketStream<AggregateTradeStreamsResponse>
Api::aggregate_trade_streams(const AggregateTradeStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AggregateTradeStreamsResponse>(*client_, "/<symbol>@aggTrade", p,
                                                        std::nullopt);
}

common::WebsocketStream<AllBookTickersStreamResponse>
Api::all_book_tickers_stream(const AllBookTickersStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllBookTickersStreamResponse>(*client_, "/!bookTicker", p, std::nullopt);
}

common::WebsocketStream<AllMarketLiquidationOrderStreamsResponse>
Api::all_market_liquidation_order_streams(
    const AllMarketLiquidationOrderStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<AllMarketLiquidationOrderStreamsResponse>(*client_, "/!forceOrder@arr", p,
                                                                   std::nullopt);
}

common::WebsocketStream<std::vector<AllMarketMiniTickersStreamResponseInner>>
Api::all_market_mini_tickers_stream(const AllMarketMiniTickersStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMarketMiniTickersStreamResponseInner>>(
        *client_, "/!miniTicker@arr", p, std::nullopt);
}

common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
Api::all_market_tickers_streams(const AllMarketTickersStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<std::vector<AllMarketTickersStreamsResponseInner>>(
        *client_, "/!ticker@arr", p, std::nullopt);
}

common::WebsocketStream<ContinuousContractKlineCandlestickStreamsResponse>
Api::continuous_contract_kline_candlestick_streams(
    const ContinuousContractKlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "contractType", params.contract_type);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ContinuousContractKlineCandlestickStreamsResponse>(
        *client_, "/<pair>_<contractType>@continuousKline_<interval>", p, std::nullopt);
}

common::WebsocketStream<ContractInfoStreamResponse>
Api::contract_info_stream(const ContractInfoStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<ContractInfoStreamResponse>(*client_, "/!contractInfo", p, std::nullopt);
}

common::WebsocketStream<DiffBookDepthStreamsResponse>
Api::diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<DiffBookDepthStreamsResponse>(*client_, "/<symbol>@depth@<updateSpeed>", p,
                                                       std::nullopt);
}

common::WebsocketStream<IndexKlineCandlestickStreamsResponse>
Api::index_kline_candlestick_streams(const IndexKlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndexKlineCandlestickStreamsResponse>(
        *client_, "/<pair>@indexPriceKline_<interval>", p, std::nullopt);
}

common::WebsocketStream<IndexPriceStreamResponse>
Api::index_price_stream(const IndexPriceStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<IndexPriceStreamResponse>(*client_, "/<pair>@indexPrice@<updateSpeed>", p,
                                                   std::nullopt);
}

common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
Api::individual_symbol_book_ticker_streams(
    const IndividualSymbolBookTickerStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolBookTickerStreamsResponse>(
        *client_, "/<symbol>@bookTicker", p, std::nullopt);
}

common::WebsocketStream<IndividualSymbolMiniTickerStreamResponse>
Api::individual_symbol_mini_ticker_stream(
    const IndividualSymbolMiniTickerStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolMiniTickerStreamResponse>(*client_, "/<symbol>@miniTicker",
                                                                   p, std::nullopt);
}

common::WebsocketStream<IndividualSymbolTickerStreamsResponse>
Api::individual_symbol_ticker_streams(const IndividualSymbolTickerStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<IndividualSymbolTickerStreamsResponse>(*client_, "/<symbol>@ticker", p,
                                                                std::nullopt);
}

common::WebsocketStream<KlineCandlestickStreamsResponse>
Api::kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<KlineCandlestickStreamsResponse>(*client_, "/<symbol>@kline_<interval>", p,
                                                          std::nullopt);
}

common::WebsocketStream<MarkPriceKlineCandlestickStreamsResponse>
Api::mark_price_kline_candlestick_streams(
    const MarkPriceKlineCandlestickStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "interval", params.interval);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<MarkPriceKlineCandlestickStreamsResponse>(
        *client_, "/<symbol>@markPriceKline_<interval>", p, std::nullopt);
}

common::WebsocketStream<std::vector<MarkPriceOfAllSymbolsOfAPairResponseInner>>
Api::mark_price_of_all_symbols_of_a_pair(const MarkPriceOfAllSymbolsOfAPairParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "pair", params.pair);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<std::vector<MarkPriceOfAllSymbolsOfAPairResponseInner>>(
        *client_, "/<pair>@markPrice@<updateSpeed>", p, std::nullopt);
}

common::WebsocketStream<MarkPriceStreamResponse>
Api::mark_price_stream(const MarkPriceStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<MarkPriceStreamResponse>(*client_, "/<symbol>@markPrice@<updateSpeed>", p,
                                                  std::nullopt);
}

common::WebsocketStream<MarketLiquidationOrderStreamsResponse>
Api::market_liquidation_order_streams(const MarketLiquidationOrderStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<MarketLiquidationOrderStreamsResponse>(*client_, "/<symbol>@forceOrder", p,
                                                                std::nullopt);
}

common::WebsocketStream<PartialBookDepthStreamsResponse>
Api::partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "levels", params.levels);
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "updateSpeed", params.update_speed);
    return create_stream<PartialBookDepthStreamsResponse>(
        *client_, "/<symbol>@depth<levels>@<updateSpeed>", p, std::nullopt);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
