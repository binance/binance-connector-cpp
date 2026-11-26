//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/account_status_response_result.hpp>

namespace binance::spot::websocket_api {

AccountStatusResponseResult
tag_invoke(boost::json::value_to_tag<AccountStatusResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountStatusResponseResult");
    AccountStatusResponseResult out;
    common::detail::json::read(obj, "makerCommission", out.maker_commission);
    common::detail::json::read(obj, "takerCommission", out.taker_commission);
    common::detail::json::read(obj, "buyerCommission", out.buyer_commission);
    common::detail::json::read(obj, "sellerCommission", out.seller_commission);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canWithdraw", out.can_withdraw);
    common::detail::json::read(obj, "canDeposit", out.can_deposit);
    common::detail::json::read(obj, "commissionRates", out.commission_rates);
    common::detail::json::read(obj, "brokered", out.brokered);
    common::detail::json::read(obj, "requireSelfTradePrevention",
                               out.require_self_trade_prevention);
    common::detail::json::read(obj, "preventSor", out.prevent_sor);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "accountType", out.account_type);
    common::detail::json::read(obj, "balances", out.balances);
    common::detail::json::read(obj, "permissions", out.permissions);
    common::detail::json::read(obj, "uid", out.uid);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountStatusResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "makerCommission", v.maker_commission);
    common::detail::json::write(obj, "takerCommission", v.taker_commission);
    common::detail::json::write(obj, "buyerCommission", v.buyer_commission);
    common::detail::json::write(obj, "sellerCommission", v.seller_commission);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canWithdraw", v.can_withdraw);
    common::detail::json::write(obj, "canDeposit", v.can_deposit);
    common::detail::json::write(obj, "commissionRates", v.commission_rates);
    common::detail::json::write(obj, "brokered", v.brokered);
    common::detail::json::write(obj, "requireSelfTradePrevention", v.require_self_trade_prevention);
    common::detail::json::write(obj, "preventSor", v.prevent_sor);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "accountType", v.account_type);
    common::detail::json::write(obj, "balances", v.balances);
    common::detail::json::write(obj, "permissions", v.permissions);
    common::detail::json::write(obj, "uid", v.uid);
}

} // namespace binance::spot::websocket_api
