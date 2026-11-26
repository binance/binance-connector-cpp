//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/trades_historical_response_result_inner.hpp>

namespace binance::spot::websocket_api {

TradesHistoricalResponseResultInner
tag_invoke(boost::json::value_to_tag<TradesHistoricalResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TradesHistoricalResponseResultInner");
    TradesHistoricalResponseResultInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "quoteQty", out.quote_qty);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "isBuyerMaker", out.is_buyer_maker);
    common::detail::json::read(obj, "isBestMatch", out.is_best_match);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TradesHistoricalResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "quoteQty", v.quote_qty);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "isBuyerMaker", v.is_buyer_maker);
    common::detail::json::write(obj, "isBestMatch", v.is_best_match);
}

} // namespace binance::spot::websocket_api
