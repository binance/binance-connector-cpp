//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_response.hpp>

namespace binance::sub_account::rest_api {

GetSummaryOfSubAccountsFuturesAccountResponse
tag_invoke(boost::json::value_to_tag<GetSummaryOfSubAccountsFuturesAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSummaryOfSubAccountsFuturesAccountResponse");
    GetSummaryOfSubAccountsFuturesAccountResponse out;
    common::detail::json::read(obj, "totalInitialMargin", out.total_initial_margin);
    common::detail::json::read(obj, "totalMaintenanceMargin", out.total_maintenance_margin);
    common::detail::json::read(obj, "totalMarginBalance", out.total_margin_balance);
    common::detail::json::read(obj, "totalOpenOrderInitialMargin",
                               out.total_open_order_initial_margin);
    common::detail::json::read(obj, "totalPositionInitialMargin",
                               out.total_position_initial_margin);
    common::detail::json::read(obj, "totalUnrealizedProfit", out.total_unrealized_profit);
    common::detail::json::read(obj, "totalWalletBalance", out.total_wallet_balance);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "subAccountList", out.sub_account_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSummaryOfSubAccountsFuturesAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalInitialMargin", v.total_initial_margin);
    common::detail::json::write(obj, "totalMaintenanceMargin", v.total_maintenance_margin);
    common::detail::json::write(obj, "totalMarginBalance", v.total_margin_balance);
    common::detail::json::write(obj, "totalOpenOrderInitialMargin",
                                v.total_open_order_initial_margin);
    common::detail::json::write(obj, "totalPositionInitialMargin", v.total_position_initial_margin);
    common::detail::json::write(obj, "totalUnrealizedProfit", v.total_unrealized_profit);
    common::detail::json::write(obj, "totalWalletBalance", v.total_wallet_balance);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "subAccountList", v.sub_account_list);
}

} // namespace binance::sub_account::rest_api
