//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/order_book_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

OrderBookResponse tag_invoke(boost::json::value_to_tag<OrderBookResponse> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OrderBookResponse");
    OrderBookResponse out;
    common::detail::json::read(obj, "lastUpdateId", out.last_update_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "bids", out.bids);
    common::detail::json::read(obj, "asks", out.asks);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OrderBookResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "lastUpdateId", v.last_update_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "bids", v.bids);
    common::detail::json::write(obj, "asks", v.asks);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
