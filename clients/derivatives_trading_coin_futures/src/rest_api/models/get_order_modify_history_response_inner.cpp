//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_order_modify_history_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

GetOrderModifyHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetOrderModifyHistoryResponseInner");
    GetOrderModifyHistoryResponseInner out;
    common::detail::json::read(obj, "amendmentId", out.amendment_id);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "clientOrderId", out.client_order_id);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "amendment", out.amendment);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOrderModifyHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amendmentId", v.amendment_id);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "clientOrderId", v.client_order_id);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "amendment", v.amendment);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
