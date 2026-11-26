//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_symbol_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

NotionalBracketForSymbolResponseInner
tag_invoke(boost::json::value_to_tag<NotionalBracketForSymbolResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NotionalBracketForSymbolResponseInner");
    NotionalBracketForSymbolResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "notionalCoef", out.notional_coef);
    common::detail::json::read(obj, "brackets", out.brackets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NotionalBracketForSymbolResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "notionalCoef", v.notional_coef);
    common::detail::json::write(obj, "brackets", v.brackets);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
