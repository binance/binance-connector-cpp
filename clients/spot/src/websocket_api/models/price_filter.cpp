//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/price_filter.hpp>

namespace binance::spot::websocket_api {

PriceFilter tag_invoke(boost::json::value_to_tag<PriceFilter> /*tag*/,
                       const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PriceFilter");
    PriceFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "priceExponent", out.price_exponent);
    common::detail::json::read(obj, "minPrice", out.min_price);
    common::detail::json::read(obj, "maxPrice", out.max_price);
    common::detail::json::read(obj, "tickSize", out.tick_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const PriceFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "priceExponent", v.price_exponent);
    common::detail::json::write(obj, "minPrice", v.min_price);
    common::detail::json::write(obj, "maxPrice", v.max_price);
    common::detail::json::write(obj, "tickSize", v.tick_size);
}

} // namespace binance::spot::websocket_api
