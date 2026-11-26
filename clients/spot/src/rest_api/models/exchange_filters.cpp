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
#include <binance/spot/rest_api/models/exchange_filters.hpp>

namespace binance::spot::rest_api {

ExchangeFilters tag_invoke(boost::json::value_to_tag<ExchangeFilters> /*tag*/,
                           const boost::json::value& jv) {
    ExchangeFilters out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("filterType"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "EXCHANGE_MAX_NUM_ALGO_ORDERS") {
                out.value = boost::json::value_to<ExchangeMaxNumAlgoOrdersFilter>(jv);
                return out;
            }
            if (name == "EXCHANGE_MAX_NUM_ICEBERG_ORDERS") {
                out.value = boost::json::value_to<ExchangeMaxNumIcebergOrdersFilter>(jv);
                return out;
            }
            if (name == "EXCHANGE_MAX_NUM_ORDERS") {
                out.value = boost::json::value_to<ExchangeMaxNumOrdersFilter>(jv);
                return out;
            }
            if (name == "EXCHANGE_MAX_NUM_ORDER_LISTS") {
                out.value = boost::json::value_to<ExchangeMaxNumOrderListsFilter>(jv);
                return out;
            }
        }
    }
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeFilters& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
    // The alternatives do not store the tag that selected them.
    auto* obj = jv.if_object();
    if (obj == nullptr || obj->contains("filterType")) {
        return;
    }
    if (std::holds_alternative<ExchangeMaxNumAlgoOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "EXCHANGE_MAX_NUM_ALGO_ORDERS";
        return;
    }
    if (std::holds_alternative<ExchangeMaxNumIcebergOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "EXCHANGE_MAX_NUM_ICEBERG_ORDERS";
        return;
    }
    if (std::holds_alternative<ExchangeMaxNumOrdersFilter>(v.value)) {
        (*obj)["filterType"] = "EXCHANGE_MAX_NUM_ORDERS";
        return;
    }
    if (std::holds_alternative<ExchangeMaxNumOrderListsFilter>(v.value)) {
        (*obj)["filterType"] = "EXCHANGE_MAX_NUM_ORDER_LISTS";
        return;
    }
}

} // namespace binance::spot::rest_api
