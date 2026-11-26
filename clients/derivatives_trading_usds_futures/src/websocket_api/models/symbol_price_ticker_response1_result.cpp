//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_price_ticker_response1_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

SymbolPriceTickerResponse1Result
tag_invoke(boost::json::value_to_tag<SymbolPriceTickerResponse1Result> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SymbolPriceTickerResponse1Result");
    SymbolPriceTickerResponse1Result out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolPriceTickerResponse1Result& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
