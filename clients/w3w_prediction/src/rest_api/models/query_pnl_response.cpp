//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_pnl_response.hpp>

namespace binance::w3w_prediction::rest_api {

QueryPnLResponse tag_invoke(boost::json::value_to_tag<QueryPnLResponse> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPnLResponse");
    QueryPnLResponse out;
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "pnl", out.pnl);
    common::detail::json::read(obj, "pnlList", out.pnl_list);
    common::detail::json::read(obj, "totalCount", out.total_count);
    common::detail::json::read(obj, "totalRealizedPnl", out.total_realized_pnl);
    common::detail::json::read(obj, "totalUnrealizedPnl", out.total_unrealized_pnl);
    common::detail::json::read(obj, "totalPnl", out.total_pnl);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPnLResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "pnl", v.pnl);
    common::detail::json::write(obj, "pnlList", v.pnl_list);
    common::detail::json::write(obj, "totalCount", v.total_count);
    common::detail::json::write(obj, "totalRealizedPnl", v.total_realized_pnl);
    common::detail::json::write(obj, "totalUnrealizedPnl", v.total_unrealized_pnl);
    common::detail::json::write(obj, "totalPnl", v.total_pnl);
}

} // namespace binance::w3w_prediction::rest_api
