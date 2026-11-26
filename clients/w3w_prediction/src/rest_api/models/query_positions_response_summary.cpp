//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_summary.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPositionsResponseSummary
tag_invoke(boost::json::value_to_tag<QueryPositionsResponseSummary> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPositionsResponseSummary");
    QueryPositionsResponseSummary out;
    common::detail::json::read(obj, "totalValue", out.total_value);
    common::detail::json::read(obj, "positionValue", out.position_value);
    common::detail::json::read(obj, "walletBalance", out.wallet_balance);
    common::detail::json::read(obj, "totalClaimableAmount", out.total_claimable_amount);
    common::detail::json::read(obj, "todayRealizedPnl", out.today_realized_pnl);
    common::detail::json::read(obj, "todayRealizedPnlPercent", out.today_realized_pnl_percent);
    common::detail::json::read(obj, "todayTotalCost", out.today_total_cost);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPositionsResponseSummary& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalValue", v.total_value);
    common::detail::json::write(obj, "positionValue", v.position_value);
    common::detail::json::write(obj, "walletBalance", v.wallet_balance);
    common::detail::json::write(obj, "totalClaimableAmount", v.total_claimable_amount);
    common::detail::json::write(obj, "todayRealizedPnl", v.today_realized_pnl);
    common::detail::json::write(obj, "todayRealizedPnlPercent", v.today_realized_pnl_percent);
    common::detail::json::write(obj, "todayTotalCost", v.today_total_cost);
}

} // namespace binance::w3w_prediction::rest_api
