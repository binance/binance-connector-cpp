//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/account_information_v2_response_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

AccountInformationV2ResponseResult
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountInformationV2ResponseResult");
    AccountInformationV2ResponseResult out;
    common::detail::json::read(obj, "totalInitialMargin", out.total_initial_margin);
    common::detail::json::read(obj, "totalMaintMargin", out.total_maint_margin);
    common::detail::json::read(obj, "totalWalletBalance", out.total_wallet_balance);
    common::detail::json::read(obj, "totalUnrealizedProfit", out.total_unrealized_profit);
    common::detail::json::read(obj, "totalMarginBalance", out.total_margin_balance);
    common::detail::json::read(obj, "totalPositionInitialMargin",
                               out.total_position_initial_margin);
    common::detail::json::read(obj, "totalOpenOrderInitialMargin",
                               out.total_open_order_initial_margin);
    common::detail::json::read(obj, "totalCrossWalletBalance", out.total_cross_wallet_balance);
    common::detail::json::read(obj, "totalCrossUnPnl", out.total_cross_un_pnl);
    common::detail::json::read(obj, "availableBalance", out.available_balance);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    common::detail::json::read(obj, "assets", out.assets);
    common::detail::json::read(obj, "positions", out.positions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInformationV2ResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalInitialMargin", v.total_initial_margin);
    common::detail::json::write(obj, "totalMaintMargin", v.total_maint_margin);
    common::detail::json::write(obj, "totalWalletBalance", v.total_wallet_balance);
    common::detail::json::write(obj, "totalUnrealizedProfit", v.total_unrealized_profit);
    common::detail::json::write(obj, "totalMarginBalance", v.total_margin_balance);
    common::detail::json::write(obj, "totalPositionInitialMargin", v.total_position_initial_margin);
    common::detail::json::write(obj, "totalOpenOrderInitialMargin",
                                v.total_open_order_initial_margin);
    common::detail::json::write(obj, "totalCrossWalletBalance", v.total_cross_wallet_balance);
    common::detail::json::write(obj, "totalCrossUnPnl", v.total_cross_un_pnl);
    common::detail::json::write(obj, "availableBalance", v.available_balance);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
    common::detail::json::write(obj, "assets", v.assets);
    common::detail::json::write(obj, "positions", v.positions);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
