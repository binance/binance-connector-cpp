//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetPortfolioResponse tag_invoke(boost::json::value_to_tag<GetPortfolioResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetPortfolioResponse");
    GetPortfolioResponse out;
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "activePositionsCount", out.active_positions_count);
    common::detail::json::read(obj, "totalRealizedPnl", out.total_realized_pnl);
    common::detail::json::read(obj, "totalUnrealizedPnl", out.total_unrealized_pnl);
    common::detail::json::read(obj, "totalPnl", out.total_pnl);
    common::detail::json::read(obj, "totalCostBasis", out.total_cost_basis);
    common::detail::json::read(obj, "totalCurrentValue", out.total_current_value);
    common::detail::json::read(obj, "positions", out.positions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "activePositionsCount", v.active_positions_count);
    common::detail::json::write(obj, "totalRealizedPnl", v.total_realized_pnl);
    common::detail::json::write(obj, "totalUnrealizedPnl", v.total_unrealized_pnl);
    common::detail::json::write(obj, "totalPnl", v.total_pnl);
    common::detail::json::write(obj, "totalCostBasis", v.total_cost_basis);
    common::detail::json::write(obj, "totalCurrentValue", v.total_current_value);
    common::detail::json::write(obj, "positions", v.positions);
}

} // namespace binance::w3w_prediction::rest_api
