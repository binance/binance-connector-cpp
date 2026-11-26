//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/trailing_delta_filter.hpp>

namespace binance::spot::rest_api {

TrailingDeltaFilter tag_invoke(boost::json::value_to_tag<TrailingDeltaFilter> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TrailingDeltaFilter");
    TrailingDeltaFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "minTrailingAboveDelta", out.min_trailing_above_delta);
    common::detail::json::read(obj, "maxTrailingAboveDelta", out.max_trailing_above_delta);
    common::detail::json::read(obj, "minTrailingBelowDelta", out.min_trailing_below_delta);
    common::detail::json::read(obj, "maxTrailingBelowDelta", out.max_trailing_below_delta);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TrailingDeltaFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "minTrailingAboveDelta", v.min_trailing_above_delta);
    common::detail::json::write(obj, "maxTrailingAboveDelta", v.max_trailing_above_delta);
    common::detail::json::write(obj, "minTrailingBelowDelta", v.min_trailing_below_delta);
    common::detail::json::write(obj, "maxTrailingBelowDelta", v.max_trailing_below_delta);
}

} // namespace binance::spot::rest_api
