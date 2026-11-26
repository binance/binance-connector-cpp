//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/market_api.hpp>

namespace binance::spot::rest_api {

namespace {
constexpr bool kHasTimeUnit = true;
} // namespace

std::string_view to_string(DepthSymbolStatusEnum value) noexcept {
    switch (value) {
    case DepthSymbolStatusEnum::Trading:
        return "TRADING";
    case DepthSymbolStatusEnum::Halt:
        return "HALT";
    case DepthSymbolStatusEnum::Break:
        return "BREAK";
    case DepthSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case DepthSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

DepthSymbolStatusEnum tag_invoke(boost::json::value_to_tag<DepthSymbolStatusEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return DepthSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return DepthSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return DepthSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return DepthSymbolStatusEnum::CancelOnly;
    }
    return DepthSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DepthSymbolStatusEnum value) {
    if (value == DepthSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("DepthSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlinesIntervalEnum value) noexcept {
    switch (value) {
    case KlinesIntervalEnum::Interval1s:
        return "1s";
    case KlinesIntervalEnum::Interval1m:
        return "1m";
    case KlinesIntervalEnum::Interval3m:
        return "3m";
    case KlinesIntervalEnum::Interval5m:
        return "5m";
    case KlinesIntervalEnum::Interval15m:
        return "15m";
    case KlinesIntervalEnum::Interval30m:
        return "30m";
    case KlinesIntervalEnum::Interval1h:
        return "1h";
    case KlinesIntervalEnum::Interval2h:
        return "2h";
    case KlinesIntervalEnum::Interval4h:
        return "4h";
    case KlinesIntervalEnum::Interval6h:
        return "6h";
    case KlinesIntervalEnum::Interval8h:
        return "8h";
    case KlinesIntervalEnum::Interval12h:
        return "12h";
    case KlinesIntervalEnum::Interval1d:
        return "1d";
    case KlinesIntervalEnum::Interval3d:
        return "3d";
    case KlinesIntervalEnum::Interval1w:
        return "1w";
    case KlinesIntervalEnum::Interval1Month:
        return "1M";
    case KlinesIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlinesIntervalEnum tag_invoke(boost::json::value_to_tag<KlinesIntervalEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return KlinesIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return KlinesIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlinesIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlinesIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlinesIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlinesIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlinesIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlinesIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlinesIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlinesIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlinesIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlinesIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlinesIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlinesIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlinesIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlinesIntervalEnum::Interval1Month;
    }
    return KlinesIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlinesIntervalEnum value) {
    if (value == KlinesIntervalEnum::Unknown) {
        throw std::invalid_argument("KlinesIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ReferencePriceCalculationSymbolStatusEnum value) noexcept {
    switch (value) {
    case ReferencePriceCalculationSymbolStatusEnum::Trading:
        return "TRADING";
    case ReferencePriceCalculationSymbolStatusEnum::Halt:
        return "HALT";
    case ReferencePriceCalculationSymbolStatusEnum::Break:
        return "BREAK";
    case ReferencePriceCalculationSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case ReferencePriceCalculationSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

ReferencePriceCalculationSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<ReferencePriceCalculationSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return ReferencePriceCalculationSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return ReferencePriceCalculationSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return ReferencePriceCalculationSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return ReferencePriceCalculationSymbolStatusEnum::CancelOnly;
    }
    return ReferencePriceCalculationSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ReferencePriceCalculationSymbolStatusEnum value) {
    if (value == ReferencePriceCalculationSymbolStatusEnum::Unknown) {
        throw std::invalid_argument(
            "ReferencePriceCalculationSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerWindowSizeEnum value) noexcept {
    switch (value) {
    case TickerWindowSizeEnum::WindowSize1m:
        return "1m";
    case TickerWindowSizeEnum::WindowSize2m:
        return "2m";
    case TickerWindowSizeEnum::WindowSize3m:
        return "3m";
    case TickerWindowSizeEnum::WindowSize4m:
        return "4m";
    case TickerWindowSizeEnum::WindowSize5m:
        return "5m";
    case TickerWindowSizeEnum::WindowSize6m:
        return "6m";
    case TickerWindowSizeEnum::WindowSize7m:
        return "7m";
    case TickerWindowSizeEnum::WindowSize8m:
        return "8m";
    case TickerWindowSizeEnum::WindowSize9m:
        return "9m";
    case TickerWindowSizeEnum::WindowSize10m:
        return "10m";
    case TickerWindowSizeEnum::WindowSize11m:
        return "11m";
    case TickerWindowSizeEnum::WindowSize12m:
        return "12m";
    case TickerWindowSizeEnum::WindowSize13m:
        return "13m";
    case TickerWindowSizeEnum::WindowSize14m:
        return "14m";
    case TickerWindowSizeEnum::WindowSize15m:
        return "15m";
    case TickerWindowSizeEnum::WindowSize16m:
        return "16m";
    case TickerWindowSizeEnum::WindowSize17m:
        return "17m";
    case TickerWindowSizeEnum::WindowSize18m:
        return "18m";
    case TickerWindowSizeEnum::WindowSize19m:
        return "19m";
    case TickerWindowSizeEnum::WindowSize20m:
        return "20m";
    case TickerWindowSizeEnum::WindowSize21m:
        return "21m";
    case TickerWindowSizeEnum::WindowSize22m:
        return "22m";
    case TickerWindowSizeEnum::WindowSize23m:
        return "23m";
    case TickerWindowSizeEnum::WindowSize24m:
        return "24m";
    case TickerWindowSizeEnum::WindowSize25m:
        return "25m";
    case TickerWindowSizeEnum::WindowSize26m:
        return "26m";
    case TickerWindowSizeEnum::WindowSize27m:
        return "27m";
    case TickerWindowSizeEnum::WindowSize28m:
        return "28m";
    case TickerWindowSizeEnum::WindowSize29m:
        return "29m";
    case TickerWindowSizeEnum::WindowSize30m:
        return "30m";
    case TickerWindowSizeEnum::WindowSize31m:
        return "31m";
    case TickerWindowSizeEnum::WindowSize32m:
        return "32m";
    case TickerWindowSizeEnum::WindowSize33m:
        return "33m";
    case TickerWindowSizeEnum::WindowSize34m:
        return "34m";
    case TickerWindowSizeEnum::WindowSize35m:
        return "35m";
    case TickerWindowSizeEnum::WindowSize36m:
        return "36m";
    case TickerWindowSizeEnum::WindowSize37m:
        return "37m";
    case TickerWindowSizeEnum::WindowSize38m:
        return "38m";
    case TickerWindowSizeEnum::WindowSize39m:
        return "39m";
    case TickerWindowSizeEnum::WindowSize40m:
        return "40m";
    case TickerWindowSizeEnum::WindowSize41m:
        return "41m";
    case TickerWindowSizeEnum::WindowSize42m:
        return "42m";
    case TickerWindowSizeEnum::WindowSize43m:
        return "43m";
    case TickerWindowSizeEnum::WindowSize44m:
        return "44m";
    case TickerWindowSizeEnum::WindowSize45m:
        return "45m";
    case TickerWindowSizeEnum::WindowSize46m:
        return "46m";
    case TickerWindowSizeEnum::WindowSize47m:
        return "47m";
    case TickerWindowSizeEnum::WindowSize48m:
        return "48m";
    case TickerWindowSizeEnum::WindowSize49m:
        return "49m";
    case TickerWindowSizeEnum::WindowSize50m:
        return "50m";
    case TickerWindowSizeEnum::WindowSize51m:
        return "51m";
    case TickerWindowSizeEnum::WindowSize52m:
        return "52m";
    case TickerWindowSizeEnum::WindowSize53m:
        return "53m";
    case TickerWindowSizeEnum::WindowSize54m:
        return "54m";
    case TickerWindowSizeEnum::WindowSize55m:
        return "55m";
    case TickerWindowSizeEnum::WindowSize56m:
        return "56m";
    case TickerWindowSizeEnum::WindowSize57m:
        return "57m";
    case TickerWindowSizeEnum::WindowSize58m:
        return "58m";
    case TickerWindowSizeEnum::WindowSize59m:
        return "59m";
    case TickerWindowSizeEnum::WindowSize1h:
        return "1h";
    case TickerWindowSizeEnum::WindowSize2h:
        return "2h";
    case TickerWindowSizeEnum::WindowSize3h:
        return "3h";
    case TickerWindowSizeEnum::WindowSize4h:
        return "4h";
    case TickerWindowSizeEnum::WindowSize5h:
        return "5h";
    case TickerWindowSizeEnum::WindowSize6h:
        return "6h";
    case TickerWindowSizeEnum::WindowSize7h:
        return "7h";
    case TickerWindowSizeEnum::WindowSize8h:
        return "8h";
    case TickerWindowSizeEnum::WindowSize9h:
        return "9h";
    case TickerWindowSizeEnum::WindowSize10h:
        return "10h";
    case TickerWindowSizeEnum::WindowSize11h:
        return "11h";
    case TickerWindowSizeEnum::WindowSize12h:
        return "12h";
    case TickerWindowSizeEnum::WindowSize13h:
        return "13h";
    case TickerWindowSizeEnum::WindowSize14h:
        return "14h";
    case TickerWindowSizeEnum::WindowSize15h:
        return "15h";
    case TickerWindowSizeEnum::WindowSize16h:
        return "16h";
    case TickerWindowSizeEnum::WindowSize17h:
        return "17h";
    case TickerWindowSizeEnum::WindowSize18h:
        return "18h";
    case TickerWindowSizeEnum::WindowSize19h:
        return "19h";
    case TickerWindowSizeEnum::WindowSize20h:
        return "20h";
    case TickerWindowSizeEnum::WindowSize21h:
        return "21h";
    case TickerWindowSizeEnum::WindowSize22h:
        return "22h";
    case TickerWindowSizeEnum::WindowSize23h:
        return "23h";
    case TickerWindowSizeEnum::WindowSize1d:
        return "1d";
    case TickerWindowSizeEnum::WindowSize2d:
        return "2d";
    case TickerWindowSizeEnum::WindowSize3d:
        return "3d";
    case TickerWindowSizeEnum::WindowSize4d:
        return "4d";
    case TickerWindowSizeEnum::WindowSize5d:
        return "5d";
    case TickerWindowSizeEnum::WindowSize6d:
        return "6d";
    case TickerWindowSizeEnum::WindowSize7d:
        return "7d";
    case TickerWindowSizeEnum::Unknown:
        break;
    }
    return "";
}

TickerWindowSizeEnum tag_invoke(boost::json::value_to_tag<TickerWindowSizeEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return TickerWindowSizeEnum::WindowSize1m;
    }
    if (s == "2m") {
        return TickerWindowSizeEnum::WindowSize2m;
    }
    if (s == "3m") {
        return TickerWindowSizeEnum::WindowSize3m;
    }
    if (s == "4m") {
        return TickerWindowSizeEnum::WindowSize4m;
    }
    if (s == "5m") {
        return TickerWindowSizeEnum::WindowSize5m;
    }
    if (s == "6m") {
        return TickerWindowSizeEnum::WindowSize6m;
    }
    if (s == "7m") {
        return TickerWindowSizeEnum::WindowSize7m;
    }
    if (s == "8m") {
        return TickerWindowSizeEnum::WindowSize8m;
    }
    if (s == "9m") {
        return TickerWindowSizeEnum::WindowSize9m;
    }
    if (s == "10m") {
        return TickerWindowSizeEnum::WindowSize10m;
    }
    if (s == "11m") {
        return TickerWindowSizeEnum::WindowSize11m;
    }
    if (s == "12m") {
        return TickerWindowSizeEnum::WindowSize12m;
    }
    if (s == "13m") {
        return TickerWindowSizeEnum::WindowSize13m;
    }
    if (s == "14m") {
        return TickerWindowSizeEnum::WindowSize14m;
    }
    if (s == "15m") {
        return TickerWindowSizeEnum::WindowSize15m;
    }
    if (s == "16m") {
        return TickerWindowSizeEnum::WindowSize16m;
    }
    if (s == "17m") {
        return TickerWindowSizeEnum::WindowSize17m;
    }
    if (s == "18m") {
        return TickerWindowSizeEnum::WindowSize18m;
    }
    if (s == "19m") {
        return TickerWindowSizeEnum::WindowSize19m;
    }
    if (s == "20m") {
        return TickerWindowSizeEnum::WindowSize20m;
    }
    if (s == "21m") {
        return TickerWindowSizeEnum::WindowSize21m;
    }
    if (s == "22m") {
        return TickerWindowSizeEnum::WindowSize22m;
    }
    if (s == "23m") {
        return TickerWindowSizeEnum::WindowSize23m;
    }
    if (s == "24m") {
        return TickerWindowSizeEnum::WindowSize24m;
    }
    if (s == "25m") {
        return TickerWindowSizeEnum::WindowSize25m;
    }
    if (s == "26m") {
        return TickerWindowSizeEnum::WindowSize26m;
    }
    if (s == "27m") {
        return TickerWindowSizeEnum::WindowSize27m;
    }
    if (s == "28m") {
        return TickerWindowSizeEnum::WindowSize28m;
    }
    if (s == "29m") {
        return TickerWindowSizeEnum::WindowSize29m;
    }
    if (s == "30m") {
        return TickerWindowSizeEnum::WindowSize30m;
    }
    if (s == "31m") {
        return TickerWindowSizeEnum::WindowSize31m;
    }
    if (s == "32m") {
        return TickerWindowSizeEnum::WindowSize32m;
    }
    if (s == "33m") {
        return TickerWindowSizeEnum::WindowSize33m;
    }
    if (s == "34m") {
        return TickerWindowSizeEnum::WindowSize34m;
    }
    if (s == "35m") {
        return TickerWindowSizeEnum::WindowSize35m;
    }
    if (s == "36m") {
        return TickerWindowSizeEnum::WindowSize36m;
    }
    if (s == "37m") {
        return TickerWindowSizeEnum::WindowSize37m;
    }
    if (s == "38m") {
        return TickerWindowSizeEnum::WindowSize38m;
    }
    if (s == "39m") {
        return TickerWindowSizeEnum::WindowSize39m;
    }
    if (s == "40m") {
        return TickerWindowSizeEnum::WindowSize40m;
    }
    if (s == "41m") {
        return TickerWindowSizeEnum::WindowSize41m;
    }
    if (s == "42m") {
        return TickerWindowSizeEnum::WindowSize42m;
    }
    if (s == "43m") {
        return TickerWindowSizeEnum::WindowSize43m;
    }
    if (s == "44m") {
        return TickerWindowSizeEnum::WindowSize44m;
    }
    if (s == "45m") {
        return TickerWindowSizeEnum::WindowSize45m;
    }
    if (s == "46m") {
        return TickerWindowSizeEnum::WindowSize46m;
    }
    if (s == "47m") {
        return TickerWindowSizeEnum::WindowSize47m;
    }
    if (s == "48m") {
        return TickerWindowSizeEnum::WindowSize48m;
    }
    if (s == "49m") {
        return TickerWindowSizeEnum::WindowSize49m;
    }
    if (s == "50m") {
        return TickerWindowSizeEnum::WindowSize50m;
    }
    if (s == "51m") {
        return TickerWindowSizeEnum::WindowSize51m;
    }
    if (s == "52m") {
        return TickerWindowSizeEnum::WindowSize52m;
    }
    if (s == "53m") {
        return TickerWindowSizeEnum::WindowSize53m;
    }
    if (s == "54m") {
        return TickerWindowSizeEnum::WindowSize54m;
    }
    if (s == "55m") {
        return TickerWindowSizeEnum::WindowSize55m;
    }
    if (s == "56m") {
        return TickerWindowSizeEnum::WindowSize56m;
    }
    if (s == "57m") {
        return TickerWindowSizeEnum::WindowSize57m;
    }
    if (s == "58m") {
        return TickerWindowSizeEnum::WindowSize58m;
    }
    if (s == "59m") {
        return TickerWindowSizeEnum::WindowSize59m;
    }
    if (s == "1h") {
        return TickerWindowSizeEnum::WindowSize1h;
    }
    if (s == "2h") {
        return TickerWindowSizeEnum::WindowSize2h;
    }
    if (s == "3h") {
        return TickerWindowSizeEnum::WindowSize3h;
    }
    if (s == "4h") {
        return TickerWindowSizeEnum::WindowSize4h;
    }
    if (s == "5h") {
        return TickerWindowSizeEnum::WindowSize5h;
    }
    if (s == "6h") {
        return TickerWindowSizeEnum::WindowSize6h;
    }
    if (s == "7h") {
        return TickerWindowSizeEnum::WindowSize7h;
    }
    if (s == "8h") {
        return TickerWindowSizeEnum::WindowSize8h;
    }
    if (s == "9h") {
        return TickerWindowSizeEnum::WindowSize9h;
    }
    if (s == "10h") {
        return TickerWindowSizeEnum::WindowSize10h;
    }
    if (s == "11h") {
        return TickerWindowSizeEnum::WindowSize11h;
    }
    if (s == "12h") {
        return TickerWindowSizeEnum::WindowSize12h;
    }
    if (s == "13h") {
        return TickerWindowSizeEnum::WindowSize13h;
    }
    if (s == "14h") {
        return TickerWindowSizeEnum::WindowSize14h;
    }
    if (s == "15h") {
        return TickerWindowSizeEnum::WindowSize15h;
    }
    if (s == "16h") {
        return TickerWindowSizeEnum::WindowSize16h;
    }
    if (s == "17h") {
        return TickerWindowSizeEnum::WindowSize17h;
    }
    if (s == "18h") {
        return TickerWindowSizeEnum::WindowSize18h;
    }
    if (s == "19h") {
        return TickerWindowSizeEnum::WindowSize19h;
    }
    if (s == "20h") {
        return TickerWindowSizeEnum::WindowSize20h;
    }
    if (s == "21h") {
        return TickerWindowSizeEnum::WindowSize21h;
    }
    if (s == "22h") {
        return TickerWindowSizeEnum::WindowSize22h;
    }
    if (s == "23h") {
        return TickerWindowSizeEnum::WindowSize23h;
    }
    if (s == "1d") {
        return TickerWindowSizeEnum::WindowSize1d;
    }
    if (s == "2d") {
        return TickerWindowSizeEnum::WindowSize2d;
    }
    if (s == "3d") {
        return TickerWindowSizeEnum::WindowSize3d;
    }
    if (s == "4d") {
        return TickerWindowSizeEnum::WindowSize4d;
    }
    if (s == "5d") {
        return TickerWindowSizeEnum::WindowSize5d;
    }
    if (s == "6d") {
        return TickerWindowSizeEnum::WindowSize6d;
    }
    if (s == "7d") {
        return TickerWindowSizeEnum::WindowSize7d;
    }
    return TickerWindowSizeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerWindowSizeEnum value) {
    if (value == TickerWindowSizeEnum::Unknown) {
        throw std::invalid_argument("TickerWindowSizeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerTypeEnum value) noexcept {
    switch (value) {
    case TickerTypeEnum::Full:
        return "FULL";
    case TickerTypeEnum::Mini:
        return "MINI";
    case TickerTypeEnum::Unknown:
        break;
    }
    return "";
}

TickerTypeEnum tag_invoke(boost::json::value_to_tag<TickerTypeEnum> /*tag*/,
                          const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "FULL") {
        return TickerTypeEnum::Full;
    }
    if (s == "MINI") {
        return TickerTypeEnum::Mini;
    }
    return TickerTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, TickerTypeEnum value) {
    if (value == TickerTypeEnum::Unknown) {
        throw std::invalid_argument("TickerTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerSymbolStatusEnum value) noexcept {
    switch (value) {
    case TickerSymbolStatusEnum::Trading:
        return "TRADING";
    case TickerSymbolStatusEnum::Halt:
        return "HALT";
    case TickerSymbolStatusEnum::Break:
        return "BREAK";
    case TickerSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case TickerSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

TickerSymbolStatusEnum tag_invoke(boost::json::value_to_tag<TickerSymbolStatusEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return TickerSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return TickerSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return TickerSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return TickerSymbolStatusEnum::CancelOnly;
    }
    return TickerSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerSymbolStatusEnum value) {
    if (value == TickerSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("TickerSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(Ticker24hrTypeEnum value) noexcept {
    switch (value) {
    case Ticker24hrTypeEnum::Full:
        return "FULL";
    case Ticker24hrTypeEnum::Mini:
        return "MINI";
    case Ticker24hrTypeEnum::Unknown:
        break;
    }
    return "";
}

Ticker24hrTypeEnum tag_invoke(boost::json::value_to_tag<Ticker24hrTypeEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "FULL") {
        return Ticker24hrTypeEnum::Full;
    }
    if (s == "MINI") {
        return Ticker24hrTypeEnum::Mini;
    }
    return Ticker24hrTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                Ticker24hrTypeEnum value) {
    if (value == Ticker24hrTypeEnum::Unknown) {
        throw std::invalid_argument("Ticker24hrTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(Ticker24hrSymbolStatusEnum value) noexcept {
    switch (value) {
    case Ticker24hrSymbolStatusEnum::Trading:
        return "TRADING";
    case Ticker24hrSymbolStatusEnum::Halt:
        return "HALT";
    case Ticker24hrSymbolStatusEnum::Break:
        return "BREAK";
    case Ticker24hrSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case Ticker24hrSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

Ticker24hrSymbolStatusEnum tag_invoke(boost::json::value_to_tag<Ticker24hrSymbolStatusEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return Ticker24hrSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return Ticker24hrSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return Ticker24hrSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return Ticker24hrSymbolStatusEnum::CancelOnly;
    }
    return Ticker24hrSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                Ticker24hrSymbolStatusEnum value) {
    if (value == Ticker24hrSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("Ticker24hrSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerBookTickerSymbolStatusEnum value) noexcept {
    switch (value) {
    case TickerBookTickerSymbolStatusEnum::Trading:
        return "TRADING";
    case TickerBookTickerSymbolStatusEnum::Halt:
        return "HALT";
    case TickerBookTickerSymbolStatusEnum::Break:
        return "BREAK";
    case TickerBookTickerSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case TickerBookTickerSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

TickerBookTickerSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerBookTickerSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return TickerBookTickerSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return TickerBookTickerSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return TickerBookTickerSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return TickerBookTickerSymbolStatusEnum::CancelOnly;
    }
    return TickerBookTickerSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerBookTickerSymbolStatusEnum value) {
    if (value == TickerBookTickerSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("TickerBookTickerSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerPriceSymbolStatusEnum value) noexcept {
    switch (value) {
    case TickerPriceSymbolStatusEnum::Trading:
        return "TRADING";
    case TickerPriceSymbolStatusEnum::Halt:
        return "HALT";
    case TickerPriceSymbolStatusEnum::Break:
        return "BREAK";
    case TickerPriceSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case TickerPriceSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

TickerPriceSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerPriceSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return TickerPriceSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return TickerPriceSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return TickerPriceSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return TickerPriceSymbolStatusEnum::CancelOnly;
    }
    return TickerPriceSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerPriceSymbolStatusEnum value) {
    if (value == TickerPriceSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("TickerPriceSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerTradingDayTypeEnum value) noexcept {
    switch (value) {
    case TickerTradingDayTypeEnum::Full:
        return "FULL";
    case TickerTradingDayTypeEnum::Mini:
        return "MINI";
    case TickerTradingDayTypeEnum::Unknown:
        break;
    }
    return "";
}

TickerTradingDayTypeEnum tag_invoke(boost::json::value_to_tag<TickerTradingDayTypeEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "FULL") {
        return TickerTradingDayTypeEnum::Full;
    }
    if (s == "MINI") {
        return TickerTradingDayTypeEnum::Mini;
    }
    return TickerTradingDayTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerTradingDayTypeEnum value) {
    if (value == TickerTradingDayTypeEnum::Unknown) {
        throw std::invalid_argument("TickerTradingDayTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TickerTradingDaySymbolStatusEnum value) noexcept {
    switch (value) {
    case TickerTradingDaySymbolStatusEnum::Trading:
        return "TRADING";
    case TickerTradingDaySymbolStatusEnum::Halt:
        return "HALT";
    case TickerTradingDaySymbolStatusEnum::Break:
        return "BREAK";
    case TickerTradingDaySymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case TickerTradingDaySymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

TickerTradingDaySymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerTradingDaySymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return TickerTradingDaySymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return TickerTradingDaySymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return TickerTradingDaySymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return TickerTradingDaySymbolStatusEnum::CancelOnly;
    }
    return TickerTradingDaySymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TickerTradingDaySymbolStatusEnum value) {
    if (value == TickerTradingDaySymbolStatusEnum::Unknown) {
        throw std::invalid_argument("TickerTradingDaySymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UiKlinesIntervalEnum value) noexcept {
    switch (value) {
    case UiKlinesIntervalEnum::Interval1s:
        return "1s";
    case UiKlinesIntervalEnum::Interval1m:
        return "1m";
    case UiKlinesIntervalEnum::Interval3m:
        return "3m";
    case UiKlinesIntervalEnum::Interval5m:
        return "5m";
    case UiKlinesIntervalEnum::Interval15m:
        return "15m";
    case UiKlinesIntervalEnum::Interval30m:
        return "30m";
    case UiKlinesIntervalEnum::Interval1h:
        return "1h";
    case UiKlinesIntervalEnum::Interval2h:
        return "2h";
    case UiKlinesIntervalEnum::Interval4h:
        return "4h";
    case UiKlinesIntervalEnum::Interval6h:
        return "6h";
    case UiKlinesIntervalEnum::Interval8h:
        return "8h";
    case UiKlinesIntervalEnum::Interval12h:
        return "12h";
    case UiKlinesIntervalEnum::Interval1d:
        return "1d";
    case UiKlinesIntervalEnum::Interval3d:
        return "3d";
    case UiKlinesIntervalEnum::Interval1w:
        return "1w";
    case UiKlinesIntervalEnum::Interval1Month:
        return "1M";
    case UiKlinesIntervalEnum::Unknown:
        break;
    }
    return "";
}

UiKlinesIntervalEnum tag_invoke(boost::json::value_to_tag<UiKlinesIntervalEnum> /*tag*/,
                                const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return UiKlinesIntervalEnum::Interval1s;
    }
    if (s == "1m") {
        return UiKlinesIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return UiKlinesIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return UiKlinesIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return UiKlinesIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return UiKlinesIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return UiKlinesIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return UiKlinesIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return UiKlinesIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return UiKlinesIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return UiKlinesIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return UiKlinesIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return UiKlinesIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return UiKlinesIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return UiKlinesIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return UiKlinesIntervalEnum::Interval1Month;
    }
    return UiKlinesIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UiKlinesIntervalEnum value) {
    if (value == UiKlinesIntervalEnum::Unknown) {
        throw std::invalid_argument("UiKlinesIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketApi::MarketApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest MarketApi::agg_trades_request(const AggTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/aggTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<AggTradesResponseInner>>
MarketApi::agg_trades(const AggTradesParams& params) const {
    return common::send<std::vector<AggTradesResponseInner>>(*client_, agg_trades_request(params));
}

common::RestRequest MarketApi::avg_price_request(const AvgPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/avgPrice";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<AvgPriceResponse> MarketApi::avg_price(const AvgPriceParams& params) const {
    return common::send<AvgPriceResponse>(*client_, avg_price_request(params));
}

common::RestRequest MarketApi::depth_request(const DepthParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/depth";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<DepthResponse> MarketApi::depth(const DepthParams& params) const {
    return common::send<DepthResponse>(*client_, depth_request(params));
}

common::RestRequest MarketApi::get_trades_request(const GetTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/trades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetTradesResponseInner>>
MarketApi::get_trades(const GetTradesParams& params) const {
    return common::send<std::vector<GetTradesResponseInner>>(*client_, get_trades_request(params));
}

common::RestRequest
MarketApi::historical_block_trades_request(const HistoricalBlockTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/historicalBlockTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<HistoricalBlockTradesResponseInner>>
MarketApi::historical_block_trades(const HistoricalBlockTradesParams& params) const {
    return common::send<std::vector<HistoricalBlockTradesResponseInner>>(
        *client_, historical_block_trades_request(params));
}

common::RestRequest
MarketApi::historical_trades_request(const HistoricalTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/historicalTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetTradesResponseInner>>
MarketApi::historical_trades(const HistoricalTradesParams& params) const {
    return common::send<std::vector<GetTradesResponseInner>>(*client_,
                                                             historical_trades_request(params));
}

common::RestRequest MarketApi::klines_request(const KlinesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/klines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "timeZone", params.time_zone);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
MarketApi::klines(const KlinesParams& params) const {
    return common::send<std::vector<std::vector<KlinesItemInner>>>(*client_,
                                                                   klines_request(params));
}

common::RestRequest MarketApi::reference_price_request(const ReferencePriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/referencePrice";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ReferencePriceResponse>
MarketApi::reference_price(const ReferencePriceParams& params) const {
    return common::send<ReferencePriceResponse>(*client_, reference_price_request(params));
}

common::RestRequest MarketApi::reference_price_calculation_request(
    const ReferencePriceCalculationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/referencePrice/calculation";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ReferencePriceCalculationResponse>
MarketApi::reference_price_calculation(const ReferencePriceCalculationParams& params) const {
    return common::send<ReferencePriceCalculationResponse>(
        *client_, reference_price_calculation_request(params));
}

common::RestRequest MarketApi::ticker_request(const TickerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ticker";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "windowSize", params.window_size);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TickerResponse> MarketApi::ticker(const TickerParams& params) const {
    return common::send<TickerResponse>(*client_, ticker_request(params));
}

common::RestRequest MarketApi::ticker24hr_request(const Ticker24hrParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ticker/24hr";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<Ticker24hrResponse>
MarketApi::ticker24hr(const Ticker24hrParams& params) const {
    return common::send<Ticker24hrResponse>(*client_, ticker24hr_request(params));
}

common::RestRequest
MarketApi::ticker_book_ticker_request(const TickerBookTickerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ticker/bookTicker";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TickerBookTickerResponse>
MarketApi::ticker_book_ticker(const TickerBookTickerParams& params) const {
    return common::send<TickerBookTickerResponse>(*client_, ticker_book_ticker_request(params));
}

common::RestRequest MarketApi::ticker_price_request(const TickerPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ticker/price";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TickerPriceResponse>
MarketApi::ticker_price(const TickerPriceParams& params) const {
    return common::send<TickerPriceResponse>(*client_, ticker_price_request(params));
}

common::RestRequest
MarketApi::ticker_trading_day_request(const TickerTradingDayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ticker/tradingDay";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "timeZone", params.time_zone);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TickerTradingDayResponse>
MarketApi::ticker_trading_day(const TickerTradingDayParams& params) const {
    return common::send<TickerTradingDayResponse>(*client_, ticker_trading_day_request(params));
}

common::RestRequest MarketApi::ui_klines_request(const UiKlinesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/uiKlines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "timeZone", params.time_zone);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
MarketApi::ui_klines(const UiKlinesParams& params) const {
    return common::send<std::vector<std::vector<KlinesItemInner>>>(*client_,
                                                                   ui_klines_request(params));
}

} // namespace binance::spot::rest_api
