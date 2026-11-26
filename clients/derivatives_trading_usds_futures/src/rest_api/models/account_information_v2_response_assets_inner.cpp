//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v2_response_assets_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

AccountInformationV2ResponseAssetsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountInformationV2ResponseAssetsInner");
    AccountInformationV2ResponseAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "walletBalance", out.wallet_balance);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    common::detail::json::read(obj, "marginBalance", out.margin_balance);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "positionInitialMargin", out.position_initial_margin);
    common::detail::json::read(obj, "openOrderInitialMargin", out.open_order_initial_margin);
    common::detail::json::read(obj, "crossWalletBalance", out.cross_wallet_balance);
    common::detail::json::read(obj, "crossUnPnl", out.cross_un_pnl);
    common::detail::json::read(obj, "availableBalance", out.available_balance);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    common::detail::json::read(obj, "marginAvailable", out.margin_available);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInformationV2ResponseAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "walletBalance", v.wallet_balance);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
    common::detail::json::write(obj, "marginBalance", v.margin_balance);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "positionInitialMargin", v.position_initial_margin);
    common::detail::json::write(obj, "openOrderInitialMargin", v.open_order_initial_margin);
    common::detail::json::write(obj, "crossWalletBalance", v.cross_wallet_balance);
    common::detail::json::write(obj, "crossUnPnl", v.cross_un_pnl);
    common::detail::json::write(obj, "availableBalance", v.available_balance);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
    common::detail::json::write(obj, "marginAvailable", v.margin_available);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
