//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/symbol_price_ticker_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

SymbolPriceTickerResponseInner
tag_invoke(boost::json::value_to_tag<SymbolPriceTickerResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SymbolPriceTickerResponseInner");
    SymbolPriceTickerResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolPriceTickerResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
