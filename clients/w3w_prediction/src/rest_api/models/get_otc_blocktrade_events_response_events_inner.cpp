//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_events_response_events_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetOtcBlocktradeEventsResponseEventsInner
tag_invoke(boost::json::value_to_tag<GetOtcBlocktradeEventsResponseEventsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOtcBlocktradeEventsResponseEventsInner");
    GetOtcBlocktradeEventsResponseEventsInner out;
    common::detail::json::read(obj, "event", out.event);
    common::detail::json::read(obj, "blocktradeId", out.blocktrade_id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "effectiveFee", out.effective_fee);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "transactionHash", out.transaction_hash);
    common::detail::json::read(obj, "reason", out.reason);
    common::detail::json::read(obj, "isMaker", out.is_maker);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOtcBlocktradeEventsResponseEventsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "event", v.event);
    common::detail::json::write(obj, "blocktradeId", v.blocktrade_id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "effectiveFee", v.effective_fee);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "transactionHash", v.transaction_hash);
    common::detail::json::write(obj, "reason", v.reason);
    common::detail::json::write(obj, "isMaker", v.is_maker);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::w3w_prediction::rest_api
