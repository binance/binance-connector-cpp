//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quote_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetQuoteResponse tag_invoke(boost::json::value_to_tag<GetQuoteResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetQuoteResponse");
    GetQuoteResponse out;
    common::detail::json::read(obj, "quoteId", out.quote_id);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "chance", out.chance);
    common::detail::json::read(obj, "vendor", out.vendor);
    common::detail::json::read(obj, "marketTitle", out.market_title);
    common::detail::json::read(obj, "marketExtId", out.market_ext_id);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "amountIn", out.amount_in);
    common::detail::json::read(obj, "amountOut", out.amount_out);
    common::detail::json::read(obj, "isMinAmountOut", out.is_min_amount_out);
    common::detail::json::read(obj, "feeAmount", out.fee_amount);
    common::detail::json::read(obj, "feeDiscountBps", out.fee_discount_bps);
    common::detail::json::read(obj, "averagePrice", out.average_price);
    common::detail::json::read(obj, "lastPrice", out.last_price);
    common::detail::json::read(obj, "priceImpact", out.price_impact);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "userId", out.user_id);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "slippageBps", out.slippage_bps);
    common::detail::json::read(obj, "feeRateBps", out.fee_rate_bps);
    common::detail::json::read(obj, "minReceive", out.min_receive);
    common::detail::json::read(obj, "expireAt", out.expire_at);
    common::detail::json::read(obj, "priceLimit", out.price_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetQuoteResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "quoteId", v.quote_id);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "chance", v.chance);
    common::detail::json::write(obj, "vendor", v.vendor);
    common::detail::json::write(obj, "marketTitle", v.market_title);
    common::detail::json::write(obj, "marketExtId", v.market_ext_id);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "amountIn", v.amount_in);
    common::detail::json::write(obj, "amountOut", v.amount_out);
    common::detail::json::write(obj, "isMinAmountOut", v.is_min_amount_out);
    common::detail::json::write(obj, "feeAmount", v.fee_amount);
    common::detail::json::write(obj, "feeDiscountBps", v.fee_discount_bps);
    common::detail::json::write(obj, "averagePrice", v.average_price);
    common::detail::json::write(obj, "lastPrice", v.last_price);
    common::detail::json::write(obj, "priceImpact", v.price_impact);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "userId", v.user_id);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "slippageBps", v.slippage_bps);
    common::detail::json::write(obj, "feeRateBps", v.fee_rate_bps);
    common::detail::json::write(obj, "minReceive", v.min_receive);
    common::detail::json::write(obj, "expireAt", v.expire_at);
    common::detail::json::write(obj, "priceLimit", v.price_limit);
}

} // namespace binance::w3w_prediction::rest_api
