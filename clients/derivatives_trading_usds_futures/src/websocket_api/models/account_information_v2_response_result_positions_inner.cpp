//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/account_information_v2_response_result_positions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

AccountInformationV2ResponseResultPositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseResultPositionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountInformationV2ResponseResultPositionsInner");
    AccountInformationV2ResponseResultPositionsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    common::detail::json::read(obj, "isolatedMargin", out.isolated_margin);
    common::detail::json::read(obj, "notional", out.notional);
    common::detail::json::read(obj, "isolatedWallet", out.isolated_wallet);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInformationV2ResponseResultPositionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
    common::detail::json::write(obj, "isolatedMargin", v.isolated_margin);
    common::detail::json::write(obj, "notional", v.notional);
    common::detail::json::write(obj, "isolatedWallet", v.isolated_wallet);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
