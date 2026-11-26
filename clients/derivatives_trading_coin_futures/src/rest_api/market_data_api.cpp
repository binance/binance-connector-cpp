//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/market_data_api.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(BasisContractTypeEnum value) noexcept {
    switch (value) {
    case BasisContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case BasisContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case BasisContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case BasisContractTypeEnum::Unknown:
        break;
    }
    return "";
}

BasisContractTypeEnum tag_invoke(boost::json::value_to_tag<BasisContractTypeEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return BasisContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return BasisContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return BasisContractTypeEnum::NextQuarter;
    }
    return BasisContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                BasisContractTypeEnum value) {
    if (value == BasisContractTypeEnum::Unknown) {
        throw std::invalid_argument("BasisContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(BasisPeriodEnum value) noexcept {
    switch (value) {
    case BasisPeriodEnum::Period5m:
        return "5m";
    case BasisPeriodEnum::Period15m:
        return "15m";
    case BasisPeriodEnum::Period30m:
        return "30m";
    case BasisPeriodEnum::Period1h:
        return "1h";
    case BasisPeriodEnum::Period2h:
        return "2h";
    case BasisPeriodEnum::Period4h:
        return "4h";
    case BasisPeriodEnum::Period6h:
        return "6h";
    case BasisPeriodEnum::Period12h:
        return "12h";
    case BasisPeriodEnum::Period1d:
        return "1d";
    case BasisPeriodEnum::Unknown:
        break;
    }
    return "";
}

BasisPeriodEnum tag_invoke(boost::json::value_to_tag<BasisPeriodEnum> /*tag*/,
                           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return BasisPeriodEnum::Period5m;
    }
    if (s == "15m") {
        return BasisPeriodEnum::Period15m;
    }
    if (s == "30m") {
        return BasisPeriodEnum::Period30m;
    }
    if (s == "1h") {
        return BasisPeriodEnum::Period1h;
    }
    if (s == "2h") {
        return BasisPeriodEnum::Period2h;
    }
    if (s == "4h") {
        return BasisPeriodEnum::Period4h;
    }
    if (s == "6h") {
        return BasisPeriodEnum::Period6h;
    }
    if (s == "12h") {
        return BasisPeriodEnum::Period12h;
    }
    if (s == "1d") {
        return BasisPeriodEnum::Period1d;
    }
    return BasisPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                BasisPeriodEnum value) {
    if (value == BasisPeriodEnum::Unknown) {
        throw std::invalid_argument("BasisPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ContinuousContractKlineCandlestickDataContractTypeEnum value) noexcept {
    switch (value) {
    case ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case ContinuousContractKlineCandlestickDataContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case ContinuousContractKlineCandlestickDataContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case ContinuousContractKlineCandlestickDataContractTypeEnum::Unknown:
        break;
    }
    return "";
}

ContinuousContractKlineCandlestickDataContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickDataContractTypeEnum> /*tag*/,
    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return ContinuousContractKlineCandlestickDataContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return ContinuousContractKlineCandlestickDataContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return ContinuousContractKlineCandlestickDataContractTypeEnum::NextQuarter;
    }
    return ContinuousContractKlineCandlestickDataContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ContinuousContractKlineCandlestickDataContractTypeEnum value) {
    if (value == ContinuousContractKlineCandlestickDataContractTypeEnum::Unknown) {
        throw std::invalid_argument(
            "ContinuousContractKlineCandlestickDataContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ContinuousContractKlineCandlestickDataIntervalEnum value) noexcept {
    switch (value) {
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval1m:
        return "1m";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval3m:
        return "3m";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval5m:
        return "5m";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval15m:
        return "15m";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval30m:
        return "30m";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval1h:
        return "1h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval2h:
        return "2h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval4h:
        return "4h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval6h:
        return "6h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval8h:
        return "8h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval12h:
        return "12h";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval1d:
        return "1d";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval3d:
        return "3d";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval1w:
        return "1w";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Interval1Month:
        return "1M";
    case ContinuousContractKlineCandlestickDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

ContinuousContractKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return ContinuousContractKlineCandlestickDataIntervalEnum::Interval1Month;
    }
    return ContinuousContractKlineCandlestickDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ContinuousContractKlineCandlestickDataIntervalEnum value) {
    if (value == ContinuousContractKlineCandlestickDataIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "ContinuousContractKlineCandlestickDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(IndexPriceKlineCandlestickDataIntervalEnum value) noexcept {
    switch (value) {
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval1m:
        return "1m";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval3m:
        return "3m";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval5m:
        return "5m";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval15m:
        return "15m";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval30m:
        return "30m";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval1h:
        return "1h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval2h:
        return "2h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval4h:
        return "4h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval6h:
        return "6h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval8h:
        return "8h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval12h:
        return "12h";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval1d:
        return "1d";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval3d:
        return "3d";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval1w:
        return "1w";
    case IndexPriceKlineCandlestickDataIntervalEnum::Interval1Month:
        return "1M";
    case IndexPriceKlineCandlestickDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

IndexPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<IndexPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return IndexPriceKlineCandlestickDataIntervalEnum::Interval1Month;
    }
    return IndexPriceKlineCandlestickDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                IndexPriceKlineCandlestickDataIntervalEnum value) {
    if (value == IndexPriceKlineCandlestickDataIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "IndexPriceKlineCandlestickDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlineCandlestickDataIntervalEnum value) noexcept {
    switch (value) {
    case KlineCandlestickDataIntervalEnum::Interval1m:
        return "1m";
    case KlineCandlestickDataIntervalEnum::Interval3m:
        return "3m";
    case KlineCandlestickDataIntervalEnum::Interval5m:
        return "5m";
    case KlineCandlestickDataIntervalEnum::Interval15m:
        return "15m";
    case KlineCandlestickDataIntervalEnum::Interval30m:
        return "30m";
    case KlineCandlestickDataIntervalEnum::Interval1h:
        return "1h";
    case KlineCandlestickDataIntervalEnum::Interval2h:
        return "2h";
    case KlineCandlestickDataIntervalEnum::Interval4h:
        return "4h";
    case KlineCandlestickDataIntervalEnum::Interval6h:
        return "6h";
    case KlineCandlestickDataIntervalEnum::Interval8h:
        return "8h";
    case KlineCandlestickDataIntervalEnum::Interval12h:
        return "12h";
    case KlineCandlestickDataIntervalEnum::Interval1d:
        return "1d";
    case KlineCandlestickDataIntervalEnum::Interval3d:
        return "3d";
    case KlineCandlestickDataIntervalEnum::Interval1w:
        return "1w";
    case KlineCandlestickDataIntervalEnum::Interval1Month:
        return "1M";
    case KlineCandlestickDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return KlineCandlestickDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineCandlestickDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineCandlestickDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineCandlestickDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineCandlestickDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineCandlestickDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineCandlestickDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineCandlestickDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineCandlestickDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineCandlestickDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineCandlestickDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineCandlestickDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineCandlestickDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineCandlestickDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineCandlestickDataIntervalEnum::Interval1Month;
    }
    return KlineCandlestickDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineCandlestickDataIntervalEnum value) {
    if (value == KlineCandlestickDataIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineCandlestickDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(LongShortRatioPeriodEnum value) noexcept {
    switch (value) {
    case LongShortRatioPeriodEnum::Period5m:
        return "5m";
    case LongShortRatioPeriodEnum::Period15m:
        return "15m";
    case LongShortRatioPeriodEnum::Period30m:
        return "30m";
    case LongShortRatioPeriodEnum::Period1h:
        return "1h";
    case LongShortRatioPeriodEnum::Period2h:
        return "2h";
    case LongShortRatioPeriodEnum::Period4h:
        return "4h";
    case LongShortRatioPeriodEnum::Period6h:
        return "6h";
    case LongShortRatioPeriodEnum::Period12h:
        return "12h";
    case LongShortRatioPeriodEnum::Period1d:
        return "1d";
    case LongShortRatioPeriodEnum::Unknown:
        break;
    }
    return "";
}

LongShortRatioPeriodEnum tag_invoke(boost::json::value_to_tag<LongShortRatioPeriodEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return LongShortRatioPeriodEnum::Period5m;
    }
    if (s == "15m") {
        return LongShortRatioPeriodEnum::Period15m;
    }
    if (s == "30m") {
        return LongShortRatioPeriodEnum::Period30m;
    }
    if (s == "1h") {
        return LongShortRatioPeriodEnum::Period1h;
    }
    if (s == "2h") {
        return LongShortRatioPeriodEnum::Period2h;
    }
    if (s == "4h") {
        return LongShortRatioPeriodEnum::Period4h;
    }
    if (s == "6h") {
        return LongShortRatioPeriodEnum::Period6h;
    }
    if (s == "12h") {
        return LongShortRatioPeriodEnum::Period12h;
    }
    if (s == "1d") {
        return LongShortRatioPeriodEnum::Period1d;
    }
    return LongShortRatioPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                LongShortRatioPeriodEnum value) {
    if (value == LongShortRatioPeriodEnum::Unknown) {
        throw std::invalid_argument("LongShortRatioPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(LongShortRatioContractTypeEnum value) noexcept {
    switch (value) {
    case LongShortRatioContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case LongShortRatioContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case LongShortRatioContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case LongShortRatioContractTypeEnum::Unknown:
        break;
    }
    return "";
}

LongShortRatioContractTypeEnum
tag_invoke(boost::json::value_to_tag<LongShortRatioContractTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return LongShortRatioContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return LongShortRatioContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return LongShortRatioContractTypeEnum::NextQuarter;
    }
    return LongShortRatioContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                LongShortRatioContractTypeEnum value) {
    if (value == LongShortRatioContractTypeEnum::Unknown) {
        throw std::invalid_argument("LongShortRatioContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarkPriceKlineCandlestickDataIntervalEnum value) noexcept {
    switch (value) {
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval1m:
        return "1m";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval3m:
        return "3m";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval5m:
        return "5m";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval15m:
        return "15m";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval30m:
        return "30m";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval1h:
        return "1h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval2h:
        return "2h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval4h:
        return "4h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval6h:
        return "6h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval8h:
        return "8h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval12h:
        return "12h";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval1d:
        return "1d";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval3d:
        return "3d";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval1w:
        return "1w";
    case MarkPriceKlineCandlestickDataIntervalEnum::Interval1Month:
        return "1M";
    case MarkPriceKlineCandlestickDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

MarkPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return MarkPriceKlineCandlestickDataIntervalEnum::Interval1Month;
    }
    return MarkPriceKlineCandlestickDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarkPriceKlineCandlestickDataIntervalEnum value) {
    if (value == MarkPriceKlineCandlestickDataIntervalEnum::Unknown) {
        throw std::invalid_argument(
            "MarkPriceKlineCandlestickDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OpenInterestStatisticsPeriodEnum value) noexcept {
    switch (value) {
    case OpenInterestStatisticsPeriodEnum::Period5m:
        return "5m";
    case OpenInterestStatisticsPeriodEnum::Period15m:
        return "15m";
    case OpenInterestStatisticsPeriodEnum::Period30m:
        return "30m";
    case OpenInterestStatisticsPeriodEnum::Period1h:
        return "1h";
    case OpenInterestStatisticsPeriodEnum::Period2h:
        return "2h";
    case OpenInterestStatisticsPeriodEnum::Period4h:
        return "4h";
    case OpenInterestStatisticsPeriodEnum::Period6h:
        return "6h";
    case OpenInterestStatisticsPeriodEnum::Period12h:
        return "12h";
    case OpenInterestStatisticsPeriodEnum::Period1d:
        return "1d";
    case OpenInterestStatisticsPeriodEnum::Unknown:
        break;
    }
    return "";
}

OpenInterestStatisticsPeriodEnum
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsPeriodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return OpenInterestStatisticsPeriodEnum::Period5m;
    }
    if (s == "15m") {
        return OpenInterestStatisticsPeriodEnum::Period15m;
    }
    if (s == "30m") {
        return OpenInterestStatisticsPeriodEnum::Period30m;
    }
    if (s == "1h") {
        return OpenInterestStatisticsPeriodEnum::Period1h;
    }
    if (s == "2h") {
        return OpenInterestStatisticsPeriodEnum::Period2h;
    }
    if (s == "4h") {
        return OpenInterestStatisticsPeriodEnum::Period4h;
    }
    if (s == "6h") {
        return OpenInterestStatisticsPeriodEnum::Period6h;
    }
    if (s == "12h") {
        return OpenInterestStatisticsPeriodEnum::Period12h;
    }
    if (s == "1d") {
        return OpenInterestStatisticsPeriodEnum::Period1d;
    }
    return OpenInterestStatisticsPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OpenInterestStatisticsPeriodEnum value) {
    if (value == OpenInterestStatisticsPeriodEnum::Unknown) {
        throw std::invalid_argument("OpenInterestStatisticsPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OpenInterestStatisticsContractTypeEnum value) noexcept {
    switch (value) {
    case OpenInterestStatisticsContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case OpenInterestStatisticsContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case OpenInterestStatisticsContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case OpenInterestStatisticsContractTypeEnum::Unknown:
        break;
    }
    return "";
}

OpenInterestStatisticsContractTypeEnum
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsContractTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return OpenInterestStatisticsContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return OpenInterestStatisticsContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return OpenInterestStatisticsContractTypeEnum::NextQuarter;
    }
    return OpenInterestStatisticsContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OpenInterestStatisticsContractTypeEnum value) {
    if (value == OpenInterestStatisticsContractTypeEnum::Unknown) {
        throw std::invalid_argument(
            "OpenInterestStatisticsContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PremiumIndexKlineDataIntervalEnum value) noexcept {
    switch (value) {
    case PremiumIndexKlineDataIntervalEnum::Interval1m:
        return "1m";
    case PremiumIndexKlineDataIntervalEnum::Interval3m:
        return "3m";
    case PremiumIndexKlineDataIntervalEnum::Interval5m:
        return "5m";
    case PremiumIndexKlineDataIntervalEnum::Interval15m:
        return "15m";
    case PremiumIndexKlineDataIntervalEnum::Interval30m:
        return "30m";
    case PremiumIndexKlineDataIntervalEnum::Interval1h:
        return "1h";
    case PremiumIndexKlineDataIntervalEnum::Interval2h:
        return "2h";
    case PremiumIndexKlineDataIntervalEnum::Interval4h:
        return "4h";
    case PremiumIndexKlineDataIntervalEnum::Interval6h:
        return "6h";
    case PremiumIndexKlineDataIntervalEnum::Interval8h:
        return "8h";
    case PremiumIndexKlineDataIntervalEnum::Interval12h:
        return "12h";
    case PremiumIndexKlineDataIntervalEnum::Interval1d:
        return "1d";
    case PremiumIndexKlineDataIntervalEnum::Interval3d:
        return "3d";
    case PremiumIndexKlineDataIntervalEnum::Interval1w:
        return "1w";
    case PremiumIndexKlineDataIntervalEnum::Interval1Month:
        return "1M";
    case PremiumIndexKlineDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

PremiumIndexKlineDataIntervalEnum
tag_invoke(boost::json::value_to_tag<PremiumIndexKlineDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return PremiumIndexKlineDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return PremiumIndexKlineDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return PremiumIndexKlineDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return PremiumIndexKlineDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return PremiumIndexKlineDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return PremiumIndexKlineDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return PremiumIndexKlineDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return PremiumIndexKlineDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return PremiumIndexKlineDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return PremiumIndexKlineDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return PremiumIndexKlineDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return PremiumIndexKlineDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return PremiumIndexKlineDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return PremiumIndexKlineDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return PremiumIndexKlineDataIntervalEnum::Interval1Month;
    }
    return PremiumIndexKlineDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PremiumIndexKlineDataIntervalEnum value) {
    if (value == PremiumIndexKlineDataIntervalEnum::Unknown) {
        throw std::invalid_argument("PremiumIndexKlineDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TakerBuySellVolumeContractTypeEnum value) noexcept {
    switch (value) {
    case TakerBuySellVolumeContractTypeEnum::All:
        return "ALL";
    case TakerBuySellVolumeContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case TakerBuySellVolumeContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case TakerBuySellVolumeContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case TakerBuySellVolumeContractTypeEnum::Unknown:
        break;
    }
    return "";
}

TakerBuySellVolumeContractTypeEnum
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumeContractTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ALL") {
        return TakerBuySellVolumeContractTypeEnum::All;
    }
    if (s == "PERPETUAL") {
        return TakerBuySellVolumeContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return TakerBuySellVolumeContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return TakerBuySellVolumeContractTypeEnum::NextQuarter;
    }
    return TakerBuySellVolumeContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TakerBuySellVolumeContractTypeEnum value) {
    if (value == TakerBuySellVolumeContractTypeEnum::Unknown) {
        throw std::invalid_argument("TakerBuySellVolumeContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TakerBuySellVolumePeriodEnum value) noexcept {
    switch (value) {
    case TakerBuySellVolumePeriodEnum::Period5m:
        return "5m";
    case TakerBuySellVolumePeriodEnum::Period15m:
        return "15m";
    case TakerBuySellVolumePeriodEnum::Period30m:
        return "30m";
    case TakerBuySellVolumePeriodEnum::Period1h:
        return "1h";
    case TakerBuySellVolumePeriodEnum::Period2h:
        return "2h";
    case TakerBuySellVolumePeriodEnum::Period4h:
        return "4h";
    case TakerBuySellVolumePeriodEnum::Period6h:
        return "6h";
    case TakerBuySellVolumePeriodEnum::Period12h:
        return "12h";
    case TakerBuySellVolumePeriodEnum::Period1d:
        return "1d";
    case TakerBuySellVolumePeriodEnum::Unknown:
        break;
    }
    return "";
}

TakerBuySellVolumePeriodEnum
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumePeriodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return TakerBuySellVolumePeriodEnum::Period5m;
    }
    if (s == "15m") {
        return TakerBuySellVolumePeriodEnum::Period15m;
    }
    if (s == "30m") {
        return TakerBuySellVolumePeriodEnum::Period30m;
    }
    if (s == "1h") {
        return TakerBuySellVolumePeriodEnum::Period1h;
    }
    if (s == "2h") {
        return TakerBuySellVolumePeriodEnum::Period2h;
    }
    if (s == "4h") {
        return TakerBuySellVolumePeriodEnum::Period4h;
    }
    if (s == "6h") {
        return TakerBuySellVolumePeriodEnum::Period6h;
    }
    if (s == "12h") {
        return TakerBuySellVolumePeriodEnum::Period12h;
    }
    if (s == "1d") {
        return TakerBuySellVolumePeriodEnum::Period1d;
    }
    return TakerBuySellVolumePeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TakerBuySellVolumePeriodEnum value) {
    if (value == TakerBuySellVolumePeriodEnum::Unknown) {
        throw std::invalid_argument("TakerBuySellVolumePeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TopTraderLongShortRatioAccountsPeriodEnum value) noexcept {
    switch (value) {
    case TopTraderLongShortRatioAccountsPeriodEnum::Period5m:
        return "5m";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period15m:
        return "15m";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period30m:
        return "30m";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period1h:
        return "1h";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period2h:
        return "2h";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period4h:
        return "4h";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period6h:
        return "6h";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period12h:
        return "12h";
    case TopTraderLongShortRatioAccountsPeriodEnum::Period1d:
        return "1d";
    case TopTraderLongShortRatioAccountsPeriodEnum::Unknown:
        break;
    }
    return "";
}

TopTraderLongShortRatioAccountsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioAccountsPeriodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period5m;
    }
    if (s == "15m") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period15m;
    }
    if (s == "30m") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period30m;
    }
    if (s == "1h") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period1h;
    }
    if (s == "2h") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period2h;
    }
    if (s == "4h") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period4h;
    }
    if (s == "6h") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period6h;
    }
    if (s == "12h") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period12h;
    }
    if (s == "1d") {
        return TopTraderLongShortRatioAccountsPeriodEnum::Period1d;
    }
    return TopTraderLongShortRatioAccountsPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TopTraderLongShortRatioAccountsPeriodEnum value) {
    if (value == TopTraderLongShortRatioAccountsPeriodEnum::Unknown) {
        throw std::invalid_argument(
            "TopTraderLongShortRatioAccountsPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TopTraderLongShortRatioAccountsContractTypeEnum value) noexcept {
    switch (value) {
    case TopTraderLongShortRatioAccountsContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case TopTraderLongShortRatioAccountsContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case TopTraderLongShortRatioAccountsContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case TopTraderLongShortRatioAccountsContractTypeEnum::Unknown:
        break;
    }
    return "";
}

TopTraderLongShortRatioAccountsContractTypeEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioAccountsContractTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return TopTraderLongShortRatioAccountsContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return TopTraderLongShortRatioAccountsContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return TopTraderLongShortRatioAccountsContractTypeEnum::NextQuarter;
    }
    return TopTraderLongShortRatioAccountsContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TopTraderLongShortRatioAccountsContractTypeEnum value) {
    if (value == TopTraderLongShortRatioAccountsContractTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TopTraderLongShortRatioAccountsContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TopTraderLongShortRatioPositionsPeriodEnum value) noexcept {
    switch (value) {
    case TopTraderLongShortRatioPositionsPeriodEnum::Period5m:
        return "5m";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period15m:
        return "15m";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period30m:
        return "30m";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period1h:
        return "1h";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period2h:
        return "2h";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period4h:
        return "4h";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period6h:
        return "6h";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period12h:
        return "12h";
    case TopTraderLongShortRatioPositionsPeriodEnum::Period1d:
        return "1d";
    case TopTraderLongShortRatioPositionsPeriodEnum::Unknown:
        break;
    }
    return "";
}

TopTraderLongShortRatioPositionsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsPeriodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5m") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period5m;
    }
    if (s == "15m") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period15m;
    }
    if (s == "30m") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period30m;
    }
    if (s == "1h") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period1h;
    }
    if (s == "2h") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period2h;
    }
    if (s == "4h") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period4h;
    }
    if (s == "6h") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period6h;
    }
    if (s == "12h") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period12h;
    }
    if (s == "1d") {
        return TopTraderLongShortRatioPositionsPeriodEnum::Period1d;
    }
    return TopTraderLongShortRatioPositionsPeriodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TopTraderLongShortRatioPositionsPeriodEnum value) {
    if (value == TopTraderLongShortRatioPositionsPeriodEnum::Unknown) {
        throw std::invalid_argument(
            "TopTraderLongShortRatioPositionsPeriodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TopTraderLongShortRatioPositionsContractTypeEnum value) noexcept {
    switch (value) {
    case TopTraderLongShortRatioPositionsContractTypeEnum::Perpetual:
        return "PERPETUAL";
    case TopTraderLongShortRatioPositionsContractTypeEnum::CurrentQuarter:
        return "CURRENT_QUARTER";
    case TopTraderLongShortRatioPositionsContractTypeEnum::NextQuarter:
        return "NEXT_QUARTER";
    case TopTraderLongShortRatioPositionsContractTypeEnum::Unknown:
        break;
    }
    return "";
}

TopTraderLongShortRatioPositionsContractTypeEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsContractTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PERPETUAL") {
        return TopTraderLongShortRatioPositionsContractTypeEnum::Perpetual;
    }
    if (s == "CURRENT_QUARTER") {
        return TopTraderLongShortRatioPositionsContractTypeEnum::CurrentQuarter;
    }
    if (s == "NEXT_QUARTER") {
        return TopTraderLongShortRatioPositionsContractTypeEnum::NextQuarter;
    }
    return TopTraderLongShortRatioPositionsContractTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TopTraderLongShortRatioPositionsContractTypeEnum value) {
    if (value == TopTraderLongShortRatioPositionsContractTypeEnum::Unknown) {
        throw std::invalid_argument(
            "TopTraderLongShortRatioPositionsContractTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::basis_request(const BasisParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/basis";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<BasisResponseInner>>
MarketDataApi::basis(const BasisParams& params) const {
    return common::send<std::vector<BasisResponseInner>>(*client_, basis_request(params));
}

common::RestRequest MarketDataApi::check_server_time_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/time";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<CheckServerTimeResponse> MarketDataApi::check_server_time() const {
    return common::send<CheckServerTimeResponse>(*client_, check_server_time_request());
}

common::RestRequest MarketDataApi::compressed_aggregate_trades_list_request(
    const CompressedAggregateTradesListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/aggTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<CompressedAggregateTradesListResponseInner>>
MarketDataApi::compressed_aggregate_trades_list(
    const CompressedAggregateTradesListParams& params) const {
    return common::send<std::vector<CompressedAggregateTradesListResponseInner>>(
        *client_, compressed_aggregate_trades_list_request(params));
}

common::RestRequest MarketDataApi::continuous_contract_kline_candlestick_data_request(
    const ContinuousContractKlineCandlestickDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/continuousKlines";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
MarketDataApi::continuous_contract_kline_candlestick_data(
    const ContinuousContractKlineCandlestickDataParams& params) const {
    return common::send<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>(
        *client_, continuous_contract_kline_candlestick_data_request(params));
}

common::RestRequest MarketDataApi::exchange_information_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/exchangeInfo";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ExchangeInformationResponse> MarketDataApi::exchange_information() const {
    return common::send<ExchangeInformationResponse>(*client_, exchange_information_request());
}

common::RestRequest MarketDataApi::get_funding_rate_history_of_perpetual_futures_request(
    const GetFundingRateHistoryOfPerpetualFuturesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/fundingRate";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>
MarketDataApi::get_funding_rate_history_of_perpetual_futures(
    const GetFundingRateHistoryOfPerpetualFuturesParams& params) const {
    return common::send<std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>(
        *client_, get_funding_rate_history_of_perpetual_futures_request(params));
}

common::RestRequest MarketDataApi::get_funding_rate_info_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/fundingInfo";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetFundingRateInfoResponseInner>>
MarketDataApi::get_funding_rate_info() const {
    return common::send<std::vector<GetFundingRateInfoResponseInner>>(
        *client_, get_funding_rate_info_request());
}

common::RestRequest MarketDataApi::index_price_and_mark_price_request(
    const IndexPriceAndMarkPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/premiumIndex";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<IndexPriceAndMarkPriceResponseInner>>
MarketDataApi::index_price_and_mark_price(const IndexPriceAndMarkPriceParams& params) const {
    return common::send<std::vector<IndexPriceAndMarkPriceResponseInner>>(
        *client_, index_price_and_mark_price_request(params));
}

common::RestRequest MarketDataApi::index_price_kline_candlestick_data_request(
    const IndexPriceKlineCandlestickDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/indexPriceKlines";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
MarketDataApi::index_price_kline_candlestick_data(
    const IndexPriceKlineCandlestickDataParams& params) const {
    return common::send<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>(
        *client_, index_price_kline_candlestick_data_request(params));
}

common::RestRequest
MarketDataApi::kline_candlestick_data_request(const KlineCandlestickDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/klines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
MarketDataApi::kline_candlestick_data(const KlineCandlestickDataParams& params) const {
    return common::send<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>(
        *client_, kline_candlestick_data_request(params));
}

common::RestRequest
MarketDataApi::long_short_ratio_request(const LongShortRatioParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/globalLongShortAccountRatio";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<LongShortRatioResponseInner>>
MarketDataApi::long_short_ratio(const LongShortRatioParams& params) const {
    return common::send<std::vector<LongShortRatioResponseInner>>(*client_,
                                                                  long_short_ratio_request(params));
}

common::RestRequest MarketDataApi::mark_price_kline_candlestick_data_request(
    const MarkPriceKlineCandlestickDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/markPriceKlines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
MarketDataApi::mark_price_kline_candlestick_data(
    const MarkPriceKlineCandlestickDataParams& params) const {
    return common::send<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>(
        *client_, mark_price_kline_candlestick_data_request(params));
}

common::RestRequest
MarketDataApi::old_trades_lookup_request(const OldTradesLookupParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/historicalTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OldTradesLookupResponseInner>>
MarketDataApi::old_trades_lookup(const OldTradesLookupParams& params) const {
    return common::send<std::vector<OldTradesLookupResponseInner>>(
        *client_, old_trades_lookup_request(params));
}

common::RestRequest MarketDataApi::open_interest_request(const OpenInterestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/openInterest";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<OpenInterestResponse>
MarketDataApi::open_interest(const OpenInterestParams& params) const {
    return common::send<OpenInterestResponse>(*client_, open_interest_request(params));
}

common::RestRequest
MarketDataApi::open_interest_statistics_request(const OpenInterestStatisticsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/openInterestHist";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OpenInterestStatisticsResponseInner>>
MarketDataApi::open_interest_statistics(const OpenInterestStatisticsParams& params) const {
    return common::send<std::vector<OpenInterestStatisticsResponseInner>>(
        *client_, open_interest_statistics_request(params));
}

common::RestRequest MarketDataApi::order_book_request(const OrderBookParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/depth";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<OrderBookResponse>
MarketDataApi::order_book(const OrderBookParams& params) const {
    return common::send<OrderBookResponse>(*client_, order_book_request(params));
}

common::RestRequest
MarketDataApi::premium_index_kline_data_request(const PremiumIndexKlineDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/premiumIndexKlines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>
MarketDataApi::premium_index_kline_data(const PremiumIndexKlineDataParams& params) const {
    return common::send<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>(
        *client_, premium_index_kline_data_request(params));
}

common::RestRequest MarketDataApi::query_index_price_constituents_request(
    const QueryIndexPriceConstituentsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/constituents";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<QueryIndexPriceConstituentsResponse>
MarketDataApi::query_index_price_constituents(
    const QueryIndexPriceConstituentsParams& params) const {
    return common::send<QueryIndexPriceConstituentsResponse>(
        *client_, query_index_price_constituents_request(params));
}

common::RestRequest
MarketDataApi::recent_trades_list_request(const RecentTradesListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/trades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<RecentTradesListResponseInner>>
MarketDataApi::recent_trades_list(const RecentTradesListParams& params) const {
    return common::send<std::vector<RecentTradesListResponseInner>>(
        *client_, recent_trades_list_request(params));
}

common::RestRequest
MarketDataApi::symbol_order_book_ticker_request(const SymbolOrderBookTickerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/ticker/bookTicker";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<SymbolOrderBookTickerResponseInner>>
MarketDataApi::symbol_order_book_ticker(const SymbolOrderBookTickerParams& params) const {
    return common::send<std::vector<SymbolOrderBookTickerResponseInner>>(
        *client_, symbol_order_book_ticker_request(params));
}

common::RestRequest
MarketDataApi::symbol_price_ticker_request(const SymbolPriceTickerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/ticker/price";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<SymbolPriceTickerResponseInner>>
MarketDataApi::symbol_price_ticker(const SymbolPriceTickerParams& params) const {
    return common::send<std::vector<SymbolPriceTickerResponseInner>>(
        *client_, symbol_price_ticker_request(params));
}

common::RestRequest
MarketDataApi::taker_buy_sell_volume_request(const TakerBuySellVolumeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/takerBuySellVol";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<TakerBuySellVolumeResponseInner>>
MarketDataApi::taker_buy_sell_volume(const TakerBuySellVolumeParams& params) const {
    return common::send<std::vector<TakerBuySellVolumeResponseInner>>(
        *client_, taker_buy_sell_volume_request(params));
}

common::RestRequest MarketDataApi::test_connectivity_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/ping";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> MarketDataApi::test_connectivity() const {
    return common::send<boost::json::value>(*client_, test_connectivity_request());
}

common::RestRequest MarketDataApi::ticker24hr_price_change_statistics_request(
    const Ticker24hrPriceChangeStatisticsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/ticker/24hr";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>
MarketDataApi::ticker24hr_price_change_statistics(
    const Ticker24hrPriceChangeStatisticsParams& params) const {
    return common::send<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>(
        *client_, ticker24hr_price_change_statistics_request(params));
}

common::RestRequest MarketDataApi::top_trader_long_short_ratio_accounts_request(
    const TopTraderLongShortRatioAccountsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/topLongShortAccountRatio";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<TopTraderLongShortRatioAccountsResponseInner>>
MarketDataApi::top_trader_long_short_ratio_accounts(
    const TopTraderLongShortRatioAccountsParams& params) const {
    return common::send<std::vector<TopTraderLongShortRatioAccountsResponseInner>>(
        *client_, top_trader_long_short_ratio_accounts_request(params));
}

common::RestRequest MarketDataApi::top_trader_long_short_ratio_positions_request(
    const TopTraderLongShortRatioPositionsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/futures/data/topLongShortPositionRatio";
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "period", params.period);
    common::detail::json::set_param(req.query, "contractType", params.contract_type);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<TopTraderLongShortRatioPositionsResponseInner>>
MarketDataApi::top_trader_long_short_ratio_positions(
    const TopTraderLongShortRatioPositionsParams& params) const {
    return common::send<std::vector<TopTraderLongShortRatioPositionsResponseInner>>(
        *client_, top_trader_long_short_ratio_positions_request(params));
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
