//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response_positions_inner.hpp>

namespace binance::w3w_prediction::rest_api {

GetPortfolioResponsePositionsInner
tag_invoke(boost::json::value_to_tag<GetPortfolioResponsePositionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetPortfolioResponsePositionsInner");
    GetPortfolioResponsePositionsInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "marketTopicId", out.market_topic_id);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "vendor", out.vendor);
    common::detail::json::read(obj, "currentShares", out.current_shares);
    common::detail::json::read(obj, "avgPrice", out.avg_price);
    common::detail::json::read(obj, "currentPrice", out.current_price);
    common::detail::json::read(obj, "realizedPnl", out.realized_pnl);
    common::detail::json::read(obj, "unrealizedPnl", out.unrealized_pnl);
    common::detail::json::read(obj, "totalPnl", out.total_pnl);
    common::detail::json::read(obj, "pnlPercentage", out.pnl_percentage);
    common::detail::json::read(obj, "isResolved", out.is_resolved);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioResponsePositionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "marketTopicId", v.market_topic_id);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "vendor", v.vendor);
    common::detail::json::write(obj, "currentShares", v.current_shares);
    common::detail::json::write(obj, "avgPrice", v.avg_price);
    common::detail::json::write(obj, "currentPrice", v.current_price);
    common::detail::json::write(obj, "realizedPnl", v.realized_pnl);
    common::detail::json::write(obj, "unrealizedPnl", v.unrealized_pnl);
    common::detail::json::write(obj, "totalPnl", v.total_pnl);
    common::detail::json::write(obj, "pnlPercentage", v.pnl_percentage);
    common::detail::json::write(obj, "isResolved", v.is_resolved);
}

} // namespace binance::w3w_prediction::rest_api
