//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/websocket_streams/models/prediction_order_book_by_market_id_response.hpp>

namespace binance::w3w_prediction::websocket_streams {

PredictionOrderBookByMarketIdResponse
tag_invoke(boost::json::value_to_tag<PredictionOrderBookByMarketIdResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PredictionOrderBookByMarketIdResponse");
    PredictionOrderBookByMarketIdResponse out;
    common::detail::json::read(obj, "msgType", out.msg_type);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "updateTimestampMs", out.update_timestamp_ms);
    common::detail::json::read(obj, "asks", out.asks);
    common::detail::json::read(obj, "bids", out.bids);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PredictionOrderBookByMarketIdResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "msgType", v.msg_type);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "updateTimestampMs", v.update_timestamp_ms);
    common::detail::json::write(obj, "asks", v.asks);
    common::detail::json::write(obj, "bids", v.bids);
}

} // namespace binance::w3w_prediction::websocket_streams
