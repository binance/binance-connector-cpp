//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string_view>
#include <variant>

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/symbol_filters.hpp>

namespace binance::spot::websocket_api {

SymbolFilters tag_invoke(boost::json::value_to_tag<SymbolFilters> /*tag*/,
                         const boost::json::value& jv) {
    SymbolFilters out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("filterType"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "ICEBERG_PARTS") {
                out.value = boost::json::value_to<IcebergPartsFilter>(jv);
                return out;
            }
            if (name == "LOT_SIZE") {
                out.value = boost::json::value_to<LotSizeFilter>(jv);
                return out;
            }
            if (name == "MARKET_LOT_SIZE") {
                out.value = boost::json::value_to<MarketLotSizeFilter>(jv);
                return out;
            }
            if (name == "MAX_NUM_ALGO_ORDERS") {
                out.value = boost::json::value_to<MaxNumAlgoOrdersFilter>(jv);
                return out;
            }
            if (name == "MAX_NUM_ICEBERG_ORDERS") {
                out.value = boost::json::value_to<MaxNumIcebergOrdersFilter>(jv);
                return out;
            }
            if (name == "MAX_NUM_ORDERS") {
                out.value = boost::json::value_to<MaxNumOrdersFilter>(jv);
                return out;
            }
            if (name == "MAX_NUM_ORDER_AMENDS") {
                out.value = boost::json::value_to<MaxNumOrderAmendsFilter>(jv);
                return out;
            }
            if (name == "MAX_NUM_ORDER_LISTS") {
                out.value = boost::json::value_to<MaxNumOrderListsFilter>(jv);
                return out;
            }
            if (name == "MAX_POSITION") {
                out.value = boost::json::value_to<MaxPositionFilter>(jv);
                return out;
            }
            if (name == "MIN_NOTIONAL") {
                out.value = boost::json::value_to<MinNotionalFilter>(jv);
                return out;
            }
            if (name == "NOTIONAL") {
                out.value = boost::json::value_to<NotionalFilter>(jv);
                return out;
            }
            if (name == "PERCENT_PRICE") {
                out.value = boost::json::value_to<PercentPriceFilter>(jv);
                return out;
            }
            if (name == "PERCENT_PRICE_BY_SIDE") {
                out.value = boost::json::value_to<PercentPriceBySideFilter>(jv);
                return out;
            }
            if (name == "PRICE_FILTER") {
                out.value = boost::json::value_to<PriceFilter>(jv);
                return out;
            }
            if (name == "TRAILING_DELTA") {
                out.value = boost::json::value_to<TrailingDeltaFilter>(jv);
                return out;
            }
            if (name == "T_PLUS_SELL") {
                out.value = boost::json::value_to<TPlusSellFilter>(jv);
                return out;
            }
        }
    }
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolFilters& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
    // The alternatives do not store the tag that selected them.
    auto* obj = jv.if_object();
    if (obj == nullptr || obj->contains("filterType")) {
        return;
    }
    if (std::holds_alternative<IcebergPartsFilter>(v.value)) {
        (*obj)["filterType"] = "ICEBERG_PARTS";
        return;
    }
    if (std::holds_alternative<LotSizeFilter>(v.value)) {
        (*obj)["filterType"] = "LOT_SIZE";
        return;
    }
    if (std::holds_alternative<MarketLotSizeFilter>(v.value)) {
        (*obj)["filterType"] = "MARKET_LOT_SIZE";
        return;
    }
    if (std::holds_alternative<MaxNumAlgoOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_NUM_ALGO_ORDERS";
        return;
    }
    if (std::holds_alternative<MaxNumIcebergOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_NUM_ICEBERG_ORDERS";
        return;
    }
    if (std::holds_alternative<MaxNumOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_NUM_ORDERS";
        return;
    }
    if (std::holds_alternative<MaxNumOrderAmendsFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_NUM_ORDER_AMENDS";
        return;
    }
    if (std::holds_alternative<MaxNumOrderListsFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_NUM_ORDER_LISTS";
        return;
    }
    if (std::holds_alternative<MaxPositionFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_POSITION";
        return;
    }
    if (std::holds_alternative<MinNotionalFilter>(v.value)) {
        (*obj)["filterType"] = "MIN_NOTIONAL";
        return;
    }
    if (std::holds_alternative<NotionalFilter>(v.value)) {
        (*obj)["filterType"] = "NOTIONAL";
        return;
    }
    if (std::holds_alternative<PercentPriceFilter>(v.value)) {
        (*obj)["filterType"] = "PERCENT_PRICE";
        return;
    }
    if (std::holds_alternative<PercentPriceBySideFilter>(v.value)) {
        (*obj)["filterType"] = "PERCENT_PRICE_BY_SIDE";
        return;
    }
    if (std::holds_alternative<PriceFilter>(v.value)) {
        (*obj)["filterType"] = "PRICE_FILTER";
        return;
    }
    if (std::holds_alternative<TrailingDeltaFilter>(v.value)) {
        (*obj)["filterType"] = "TRAILING_DELTA";
        return;
    }
    if (std::holds_alternative<TPlusSellFilter>(v.value)) {
        (*obj)["filterType"] = "T_PLUS_SELL";
        return;
    }
}

} // namespace binance::spot::websocket_api
