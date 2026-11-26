//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_response.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsFuturesAccountResponse
tag_invoke(boost::json::value_to_tag<GetDetailOnSubAccountsFuturesAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetDetailOnSubAccountsFuturesAccountResponse");
    GetDetailOnSubAccountsFuturesAccountResponse out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "canDeposit", out.can_deposit);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canWithdraw", out.can_withdraw);
    common::detail::json::read(obj, "feeTier", out.fee_tier);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    common::detail::json::read(obj, "totalInitialMargin", out.total_initial_margin);
    common::detail::json::read(obj, "totalMaintenanceMargin", out.total_maintenance_margin);
    common::detail::json::read(obj, "totalMarginBalance", out.total_margin_balance);
    common::detail::json::read(obj, "totalOpenOrderInitialMargin",
                               out.total_open_order_initial_margin);
    common::detail::json::read(obj, "totalPositionInitialMargin",
                               out.total_position_initial_margin);
    common::detail::json::read(obj, "totalUnrealizedProfit", out.total_unrealized_profit);
    common::detail::json::read(obj, "totalWalletBalance", out.total_wallet_balance);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsFuturesAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "canDeposit", v.can_deposit);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canWithdraw", v.can_withdraw);
    common::detail::json::write(obj, "feeTier", v.fee_tier);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
    common::detail::json::write(obj, "totalInitialMargin", v.total_initial_margin);
    common::detail::json::write(obj, "totalMaintenanceMargin", v.total_maintenance_margin);
    common::detail::json::write(obj, "totalMarginBalance", v.total_margin_balance);
    common::detail::json::write(obj, "totalOpenOrderInitialMargin",
                                v.total_open_order_initial_margin);
    common::detail::json::write(obj, "totalPositionInitialMargin", v.total_position_initial_margin);
    common::detail::json::write(obj, "totalUnrealizedProfit", v.total_unrealized_profit);
    common::detail::json::write(obj, "totalWalletBalance", v.total_wallet_balance);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::sub_account::rest_api
