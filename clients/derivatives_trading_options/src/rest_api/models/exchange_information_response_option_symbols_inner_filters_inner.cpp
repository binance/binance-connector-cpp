//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner_filters_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

ExchangeInformationResponseOptionSymbolsInnerFiltersInner tag_invoke(
    boost::json::value_to_tag<ExchangeInformationResponseOptionSymbolsInnerFiltersInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "ExchangeInformationResponseOptionSymbolsInnerFiltersInner");
    ExchangeInformationResponseOptionSymbolsInnerFiltersInner out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "minPrice", out.min_price);
    common::detail::json::read(obj, "maxPrice", out.max_price);
    common::detail::json::read(obj, "tickSize", out.tick_size);
    common::detail::json::read(obj, "minQty", out.min_qty);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "stepSize", out.step_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeInformationResponseOptionSymbolsInnerFiltersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "minPrice", v.min_price);
    common::detail::json::write(obj, "maxPrice", v.max_price);
    common::detail::json::write(obj, "tickSize", v.tick_size);
    common::detail::json::write(obj, "minQty", v.min_qty);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "stepSize", v.step_size);
}

} // namespace binance::derivatives_trading_options::rest_api
