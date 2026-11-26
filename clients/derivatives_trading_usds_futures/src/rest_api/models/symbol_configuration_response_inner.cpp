//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_configuration_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

SymbolConfigurationResponseInner
tag_invoke(boost::json::value_to_tag<SymbolConfigurationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SymbolConfigurationResponseInner");
    SymbolConfigurationResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "marginType", out.margin_type);
    common::detail::json::read(obj, "isAutoAddMargin", out.is_auto_add_margin);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "maxNotionalValue", out.max_notional_value);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolConfigurationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "marginType", v.margin_type);
    common::detail::json::write(obj, "isAutoAddMargin", v.is_auto_add_margin);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "maxNotionalValue", v.max_notional_value);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
