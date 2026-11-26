//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/position_information_v2_response_result_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

PositionInformationV2ResponseResultInner
tag_invoke(boost::json::value_to_tag<PositionInformationV2ResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PositionInformationV2ResponseResultInner");
    PositionInformationV2ResponseResultInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "breakEvenPrice", out.break_even_price);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "unRealizedProfit", out.un_realized_profit);
    common::detail::json::read(obj, "liquidationPrice", out.liquidation_price);
    common::detail::json::read(obj, "isolatedMargin", out.isolated_margin);
    common::detail::json::read(obj, "notional", out.notional);
    common::detail::json::read(obj, "marginAsset", out.margin_asset);
    common::detail::json::read(obj, "isolatedWallet", out.isolated_wallet);
    common::detail::json::read(obj, "initialMargin", out.initial_margin);
    common::detail::json::read(obj, "maintMargin", out.maint_margin);
    common::detail::json::read(obj, "positionInitialMargin", out.position_initial_margin);
    common::detail::json::read(obj, "openOrderInitialMargin", out.open_order_initial_margin);
    common::detail::json::read(obj, "adl", out.adl);
    common::detail::json::read(obj, "bidNotional", out.bid_notional);
    common::detail::json::read(obj, "askNotional", out.ask_notional);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PositionInformationV2ResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "breakEvenPrice", v.break_even_price);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "unRealizedProfit", v.un_realized_profit);
    common::detail::json::write(obj, "liquidationPrice", v.liquidation_price);
    common::detail::json::write(obj, "isolatedMargin", v.isolated_margin);
    common::detail::json::write(obj, "notional", v.notional);
    common::detail::json::write(obj, "marginAsset", v.margin_asset);
    common::detail::json::write(obj, "isolatedWallet", v.isolated_wallet);
    common::detail::json::write(obj, "initialMargin", v.initial_margin);
    common::detail::json::write(obj, "maintMargin", v.maint_margin);
    common::detail::json::write(obj, "positionInitialMargin", v.position_initial_margin);
    common::detail::json::write(obj, "openOrderInitialMargin", v.open_order_initial_margin);
    common::detail::json::write(obj, "adl", v.adl);
    common::detail::json::write(obj, "bidNotional", v.bid_notional);
    common::detail::json::write(obj, "askNotional", v.ask_notional);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
