//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/notional_filter.hpp>

namespace binance::spot::websocket_api {

NotionalFilter tag_invoke(boost::json::value_to_tag<NotionalFilter> /*tag*/,
                          const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NotionalFilter");
    NotionalFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "priceExponent", out.price_exponent);
    common::detail::json::read(obj, "minNotional", out.min_notional);
    common::detail::json::read(obj, "applyMinToMarket", out.apply_min_to_market);
    common::detail::json::read(obj, "maxNotional", out.max_notional);
    common::detail::json::read(obj, "applyMaxToMarket", out.apply_max_to_market);
    common::detail::json::read(obj, "avgPriceMins", out.avg_price_mins);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NotionalFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "priceExponent", v.price_exponent);
    common::detail::json::write(obj, "minNotional", v.min_notional);
    common::detail::json::write(obj, "applyMinToMarket", v.apply_min_to_market);
    common::detail::json::write(obj, "maxNotional", v.max_notional);
    common::detail::json::write(obj, "applyMaxToMarket", v.apply_max_to_market);
    common::detail::json::write(obj, "avgPriceMins", v.avg_price_mins);
}

} // namespace binance::spot::websocket_api
