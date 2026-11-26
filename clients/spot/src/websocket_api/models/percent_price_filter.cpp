//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/percent_price_filter.hpp>

namespace binance::spot::websocket_api {

PercentPriceFilter tag_invoke(boost::json::value_to_tag<PercentPriceFilter> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PercentPriceFilter");
    PercentPriceFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "multiplierExponent", out.multiplier_exponent);
    common::detail::json::read(obj, "multiplierUp", out.multiplier_up);
    common::detail::json::read(obj, "multiplierDown", out.multiplier_down);
    common::detail::json::read(obj, "avgPriceMins", out.avg_price_mins);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PercentPriceFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "multiplierExponent", v.multiplier_exponent);
    common::detail::json::write(obj, "multiplierUp", v.multiplier_up);
    common::detail::json::write(obj, "multiplierDown", v.multiplier_down);
    common::detail::json::write(obj, "avgPriceMins", v.avg_price_mins);
}

} // namespace binance::spot::websocket_api
