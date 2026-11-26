//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/max_num_orders_filter.hpp>

namespace binance::spot::rest_api {

MaxNumOrdersFilter tag_invoke(boost::json::value_to_tag<MaxNumOrdersFilter> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MaxNumOrdersFilter");
    MaxNumOrdersFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "maxNumOrders", out.max_num_orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MaxNumOrdersFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "maxNumOrders", v.max_num_orders);
}

} // namespace binance::spot::rest_api
