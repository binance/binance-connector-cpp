//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response_positions_inner.hpp>

namespace binance::w3w_prediction::rest_api {

QuerySettledPositionHistoryResponsePositionsInner
tag_invoke(boost::json::value_to_tag<QuerySettledPositionHistoryResponsePositionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySettledPositionHistoryResponsePositionsInner");
    QuerySettledPositionHistoryResponsePositionsInner out;
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "vendor", out.vendor);
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "collateralSymbol", out.collateral_symbol);
    common::detail::json::read(obj, "topicType", out.topic_type);
    common::detail::json::read(obj, "marketTopicId", out.market_topic_id);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "marketTopicTitle", out.market_topic_title);
    common::detail::json::read(obj, "marketTitle", out.market_title);
    common::detail::json::read(obj, "outcomeName", out.outcome_name);
    common::detail::json::read(obj, "outcomeIndex", out.outcome_index);
    common::detail::json::read(obj, "shares", out.shares);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "totalCost", out.total_cost);
    common::detail::json::read(obj, "value", out.value);
    common::detail::json::read(obj, "currentPrice", out.current_price);
    common::detail::json::read(obj, "toWin", out.to_win);
    common::detail::json::read(obj, "positionStatus", out.position_status);
    common::detail::json::read(obj, "isWinner", out.is_winner);
    common::detail::json::read(obj, "redeemStatus", out.redeem_status);
    common::detail::json::read(obj, "endDate", out.end_date);
    common::detail::json::read(obj, "finalOutcome", out.final_outcome);
    common::detail::json::read(obj, "realizedPnl", out.realized_pnl);
    common::detail::json::read(obj, "pnl", out.pnl);
    common::detail::json::read(obj, "claimAmount", out.claim_amount);
    common::detail::json::read(obj, "settledDate", out.settled_date);
    common::detail::json::read(obj, "createdTime", out.created_time);
    common::detail::json::read(obj, "updatedTime", out.updated_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySettledPositionHistoryResponsePositionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "vendor", v.vendor);
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "collateralSymbol", v.collateral_symbol);
    common::detail::json::write(obj, "topicType", v.topic_type);
    common::detail::json::write(obj, "marketTopicId", v.market_topic_id);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "marketTopicTitle", v.market_topic_title);
    common::detail::json::write(obj, "marketTitle", v.market_title);
    common::detail::json::write(obj, "outcomeName", v.outcome_name);
    common::detail::json::write(obj, "outcomeIndex", v.outcome_index);
    common::detail::json::write(obj, "shares", v.shares);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "totalCost", v.total_cost);
    common::detail::json::write(obj, "value", v.value);
    common::detail::json::write(obj, "currentPrice", v.current_price);
    common::detail::json::write(obj, "toWin", v.to_win);
    common::detail::json::write(obj, "positionStatus", v.position_status);
    common::detail::json::write(obj, "isWinner", v.is_winner);
    common::detail::json::write(obj, "redeemStatus", v.redeem_status);
    common::detail::json::write(obj, "endDate", v.end_date);
    common::detail::json::write(obj, "finalOutcome", v.final_outcome);
    common::detail::json::write(obj, "realizedPnl", v.realized_pnl);
    common::detail::json::write(obj, "pnl", v.pnl);
    common::detail::json::write(obj, "claimAmount", v.claim_amount);
    common::detail::json::write(obj, "settledDate", v.settled_date);
    common::detail::json::write(obj, "createdTime", v.created_time);
    common::detail::json::write(obj, "updatedTime", v.updated_time);
}

} // namespace binance::w3w_prediction::rest_api
