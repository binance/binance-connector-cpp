//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/get_exchange_info_response_data_symbols_inner_filters_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

GetExchangeInfoResponseDataSymbolsInnerFiltersInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataSymbolsInnerFiltersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetExchangeInfoResponseDataSymbolsInnerFiltersInner");
    GetExchangeInfoResponseDataSymbolsInnerFiltersInner out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "minPrice", out.min_price);
    common::detail::json::read(obj, "maxPrice", out.max_price);
    common::detail::json::read(obj, "tickSize", out.tick_size);
    common::detail::json::read(obj, "stepSize", out.step_size);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "minNotional", out.min_notional);
    common::detail::json::read(obj, "maxNotional", out.max_notional);
    common::detail::json::read(obj, "multiplierDown", out.multiplier_down);
    common::detail::json::read(obj, "multiplierUp", out.multiplier_up);
    common::detail::json::read(obj, "bidMultiplierUp", out.bid_multiplier_up);
    common::detail::json::read(obj, "askMultiplierUp", out.ask_multiplier_up);
    common::detail::json::read(obj, "bidMultiplierDown", out.bid_multiplier_down);
    common::detail::json::read(obj, "askMultiplierDown", out.ask_multiplier_down);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetExchangeInfoResponseDataSymbolsInnerFiltersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "minPrice", v.min_price);
    common::detail::json::write(obj, "maxPrice", v.max_price);
    common::detail::json::write(obj, "tickSize", v.tick_size);
    common::detail::json::write(obj, "stepSize", v.step_size);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "minNotional", v.min_notional);
    common::detail::json::write(obj, "maxNotional", v.max_notional);
    common::detail::json::write(obj, "multiplierDown", v.multiplier_down);
    common::detail::json::write(obj, "multiplierUp", v.multiplier_up);
    common::detail::json::write(obj, "bidMultiplierUp", v.bid_multiplier_up);
    common::detail::json::write(obj, "askMultiplierUp", v.ask_multiplier_up);
    common::detail::json::write(obj, "bidMultiplierDown", v.bid_multiplier_down);
    common::detail::json::write(obj, "askMultiplierDown", v.ask_multiplier_down);
}

} // namespace binance::alpha::rest_api
