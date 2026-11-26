//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_order_book_ticker_response1.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

SymbolOrderBookTickerResponse1
tag_invoke(boost::json::value_to_tag<SymbolOrderBookTickerResponse1> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SymbolOrderBookTickerResponse1");
    SymbolOrderBookTickerResponse1 out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "bidPrice", out.bid_price);
    common::detail::json::read(obj, "bidQty", out.bid_qty);
    common::detail::json::read(obj, "askPrice", out.ask_price);
    common::detail::json::read(obj, "askQty", out.ask_qty);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SymbolOrderBookTickerResponse1& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "bidPrice", v.bid_price);
    common::detail::json::write(obj, "bidQty", v.bid_qty);
    common::detail::json::write(obj, "askPrice", v.ask_price);
    common::detail::json::write(obj, "askQty", v.ask_qty);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
