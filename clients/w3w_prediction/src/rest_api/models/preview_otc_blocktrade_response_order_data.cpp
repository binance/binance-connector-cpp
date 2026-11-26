//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/preview_otc_blocktrade_response_order_data.hpp>

namespace binance::w3w_prediction::rest_api {

PreviewOtcBlocktradeResponseOrderData
tag_invoke(boost::json::value_to_tag<PreviewOtcBlocktradeResponseOrderData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PreviewOtcBlocktradeResponseOrderData");
    PreviewOtcBlocktradeResponseOrderData out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "maker", out.maker);
    common::detail::json::read(obj, "taker", out.taker);
    common::detail::json::read(obj, "makerAmount", out.maker_amount);
    common::detail::json::read(obj, "takerAmount", out.taker_amount);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "timeInForce", out.time_in_force);
    common::detail::json::read(obj, "expiration", out.expiration);
    common::detail::json::read(obj, "filledAmount", out.filled_amount);
    common::detail::json::read(obj, "quoteType", out.quote_type);
    common::detail::json::read(obj, "createdAt", out.created_at);
    common::detail::json::read(obj, "isNegRisk", out.is_neg_risk);
    common::detail::json::read(obj, "isYieldBearing", out.is_yield_bearing);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PreviewOtcBlocktradeResponseOrderData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "maker", v.maker);
    common::detail::json::write(obj, "taker", v.taker);
    common::detail::json::write(obj, "makerAmount", v.maker_amount);
    common::detail::json::write(obj, "takerAmount", v.taker_amount);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "timeInForce", v.time_in_force);
    common::detail::json::write(obj, "expiration", v.expiration);
    common::detail::json::write(obj, "filledAmount", v.filled_amount);
    common::detail::json::write(obj, "quoteType", v.quote_type);
    common::detail::json::write(obj, "createdAt", v.created_at);
    common::detail::json::write(obj, "isNegRisk", v.is_neg_risk);
    common::detail::json::write(obj, "isYieldBearing", v.is_yield_bearing);
}

} // namespace binance::w3w_prediction::rest_api
