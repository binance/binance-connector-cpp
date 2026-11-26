//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_account_balance_v2_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

FuturesAccountBalanceV2ResponseInner
tag_invoke(boost::json::value_to_tag<FuturesAccountBalanceV2ResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FuturesAccountBalanceV2ResponseInner");
    FuturesAccountBalanceV2ResponseInner out;
    common::detail::json::read(obj, "accountAlias", out.account_alias);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "balance", out.balance);
    common::detail::json::read(obj, "crossWalletBalance", out.cross_wallet_balance);
    common::detail::json::read(obj, "crossUnPnl", out.cross_un_pnl);
    common::detail::json::read(obj, "availableBalance", out.available_balance);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    common::detail::json::read(obj, "marginAvailable", out.margin_available);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FuturesAccountBalanceV2ResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "accountAlias", v.account_alias);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "balance", v.balance);
    common::detail::json::write(obj, "crossWalletBalance", v.cross_wallet_balance);
    common::detail::json::write(obj, "crossUnPnl", v.cross_un_pnl);
    common::detail::json::write(obj, "availableBalance", v.available_balance);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
    common::detail::json::write(obj, "marginAvailable", v.margin_available);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
