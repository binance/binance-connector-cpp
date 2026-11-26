//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_response_assets_inner.hpp>

namespace binance::sub_account::rest_api {

GetDetailOnSubAccountsFuturesAccountResponseAssetsInner tag_invoke(
    boost::json::value_to_tag<GetDetailOnSubAccountsFuturesAccountResponseAssetsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetDetailOnSubAccountsFuturesAccountResponseAssetsInner");
    GetDetailOnSubAccountsFuturesAccountResponseAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintenanceMargin", out.maintenance_margin);
    common::detail::json::read(obj, "marginBalance", out.margin_balance);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    common::detail::json::read(obj, "openOrderInitialMargin", out.open_order_initial_margin);
    common::detail::json::read(obj, "positionInitialMargin", out.position_initial_margin);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    common::detail::json::read(obj, "walletBalance", out.wallet_balance);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDetailOnSubAccountsFuturesAccountResponseAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintenanceMargin", v.maintenance_margin);
    common::detail::json::write(obj, "marginBalance", v.margin_balance);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
    common::detail::json::write(obj, "openOrderInitialMargin", v.open_order_initial_margin);
    common::detail::json::write(obj, "positionInitialMargin", v.position_initial_margin);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
    common::detail::json::write(obj, "walletBalance", v.wallet_balance);
}

} // namespace binance::sub_account::rest_api
