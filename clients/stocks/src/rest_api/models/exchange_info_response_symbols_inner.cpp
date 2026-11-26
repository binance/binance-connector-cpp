//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/exchange_info_response_symbols_inner.hpp>

namespace binance::stocks::rest_api {

ExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeInfoResponseSymbolsInner");
    ExchangeInfoResponseSymbolsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "tradability", out.tradability);
    common::detail::json::read(obj, "tradabilityUpdateTime", out.tradability_update_time);
    common::detail::json::read(obj, "overnightSupported", out.overnight_supported);
    common::detail::json::read(obj, "fractionable", out.fractionable);
    common::detail::json::read(obj, "fractionableEh", out.fractionable_eh);
    common::detail::json::read(obj, "extendedSession", out.extended_session);
    common::detail::json::read(obj, "maxNumOrders", out.max_num_orders);
    common::detail::json::read(obj, "stepSize", out.step_size);
    common::detail::json::read(obj, "multiplierUp", out.multiplier_up);
    common::detail::json::read(obj, "multiplierDown", out.multiplier_down);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "minNotional", out.min_notional);
    common::detail::json::read(obj, "maxNotional", out.max_notional);
    common::detail::json::read(obj, "listingTime", out.listing_time);
    common::detail::json::read(obj, "delistingTime", out.delisting_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInfoResponseSymbolsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "tradability", v.tradability);
    common::detail::json::write(obj, "tradabilityUpdateTime", v.tradability_update_time);
    common::detail::json::write(obj, "overnightSupported", v.overnight_supported);
    common::detail::json::write(obj, "fractionable", v.fractionable);
    common::detail::json::write(obj, "fractionableEh", v.fractionable_eh);
    common::detail::json::write(obj, "extendedSession", v.extended_session);
    common::detail::json::write(obj, "maxNumOrders", v.max_num_orders);
    common::detail::json::write(obj, "stepSize", v.step_size);
    common::detail::json::write(obj, "multiplierUp", v.multiplier_up);
    common::detail::json::write(obj, "multiplierDown", v.multiplier_down);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "minNotional", v.min_notional);
    common::detail::json::write(obj, "maxNotional", v.max_notional);
    common::detail::json::write(obj, "listingTime", v.listing_time);
    common::detail::json::write(obj, "delistingTime", v.delisting_time);
}

} // namespace binance::stocks::rest_api
