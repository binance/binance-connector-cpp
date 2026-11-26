//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_available_inventory_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMarginAvailableInventoryResponse
tag_invoke(boost::json::value_to_tag<QueryMarginAvailableInventoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginAvailableInventoryResponse");
    QueryMarginAvailableInventoryResponse out;
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginAvailableInventoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::margin_trading::rest_api
