//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/account_information_response_positions_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

AccountInformationResponsePositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationResponsePositionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "AccountInformationResponsePositionsInner");
    AccountInformationResponsePositionsInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "unrealizedProfit", out.unrealized_profit);
    common::detail::json::read(obj, "positionInitialMargin", out.position_initial_margin);
    common::detail::json::read(obj, "openOrderInitialMargin", out.open_order_initial_margin);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "isolated", out.isolated);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "breakEvenPrice", out.break_even_price);
    common::detail::json::read(obj, "maxQty", out.max_qty);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "notionalValue", out.notional_value);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInformationResponsePositionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "unrealizedProfit", v.unrealized_profit);
    common::detail::json::write(obj, "positionInitialMargin", v.position_initial_margin);
    common::detail::json::write(obj, "openOrderInitialMargin", v.open_order_initial_margin);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "isolated", v.isolated);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "breakEvenPrice", v.break_even_price);
    common::detail::json::write(obj, "maxQty", v.max_qty);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "notionalValue", v.notional_value);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
