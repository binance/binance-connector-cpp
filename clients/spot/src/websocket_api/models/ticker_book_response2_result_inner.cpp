//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response2_result_inner.hpp>

namespace binance::spot::websocket_api {

TickerBookResponse2ResultInner
tag_invoke(boost::json::value_to_tag<TickerBookResponse2ResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TickerBookResponse2ResultInner");
    TickerBookResponse2ResultInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "bidPrice", out.bid_price);
    common::detail::json::read(obj, "bidQty", out.bid_qty);
    common::detail::json::read(obj, "askPrice", out.ask_price);
    common::detail::json::read(obj, "askQty", out.ask_qty);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TickerBookResponse2ResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "bidPrice", v.bid_price);
    common::detail::json::write(obj, "bidQty", v.bid_qty);
    common::detail::json::write(obj, "askPrice", v.ask_price);
    common::detail::json::write(obj, "askQty", v.ask_qty);
}

} // namespace binance::spot::websocket_api
