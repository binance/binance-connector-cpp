//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/max_position_filter.hpp>

namespace binance::spot::rest_api {

MaxPositionFilter tag_invoke(boost::json::value_to_tag<MaxPositionFilter> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MaxPositionFilter");
    MaxPositionFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "qtyExponent", out.qty_exponent);
    common::detail::json::read(obj, "maxPosition", out.max_position);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MaxPositionFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "qtyExponent", v.qty_exponent);
    common::detail::json::write(obj, "maxPosition", v.max_position);
}

} // namespace binance::spot::rest_api
