//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/t_plus_sell_filter.hpp>

namespace binance::spot::rest_api {

TPlusSellFilter tag_invoke(boost::json::value_to_tag<TPlusSellFilter> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TPlusSellFilter");
    TPlusSellFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "endTime", out.end_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TPlusSellFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "endTime", v.end_time);
}

} // namespace binance::spot::rest_api
