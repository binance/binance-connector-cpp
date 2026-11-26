//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/max_num_order_lists_filter.hpp>

namespace binance::spot::rest_api {

MaxNumOrderListsFilter tag_invoke(boost::json::value_to_tag<MaxNumOrderListsFilter> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MaxNumOrderListsFilter");
    MaxNumOrderListsFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "maxNumOrderLists", out.max_num_order_lists);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MaxNumOrderListsFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "maxNumOrderLists", v.max_num_order_lists);
}

} // namespace binance::spot::rest_api
