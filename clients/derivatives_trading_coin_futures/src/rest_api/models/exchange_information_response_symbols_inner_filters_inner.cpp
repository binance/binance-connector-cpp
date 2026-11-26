//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response_symbols_inner_filters_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

ExchangeInformationResponseSymbolsInnerFiltersInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseSymbolsInnerFiltersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExchangeInformationResponseSymbolsInnerFiltersInner");
    ExchangeInformationResponseSymbolsInnerFiltersInner out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "maxPrice", out.max_price);
    common::detail::json::read(obj, "minPrice", out.min_price);
    common::detail::json::read(obj, "tickSize", out.tick_size);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "stepSize", out.step_size);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "multiplierUp", out.multiplier_up);
    common::detail::json::read(obj, "multiplierDown", out.multiplier_down);
    common::detail::json::read(obj, "multiplierDecimal", out.multiplier_decimal);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseSymbolsInnerFiltersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "maxPrice", v.max_price);
    common::detail::json::write(obj, "minPrice", v.min_price);
    common::detail::json::write(obj, "tickSize", v.tick_size);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "stepSize", v.step_size);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "multiplierUp", v.multiplier_up);
    common::detail::json::write(obj, "multiplierDown", v.multiplier_down);
    common::detail::json::write(obj, "multiplierDecimal", v.multiplier_decimal);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
