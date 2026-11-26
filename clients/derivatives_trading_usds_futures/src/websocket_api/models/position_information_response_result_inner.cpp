//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/position_information_response_result_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

PositionInformationResponseResultInner
tag_invoke(boost::json::value_to_tag<PositionInformationResponseResultInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "PositionInformationResponseResultInner");
    PositionInformationResponseResultInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "breakEvenPrice", out.break_even_price);
    common::detail::json::read(obj, "marginType", out.margin_type);
    common::detail::json::read(obj, "isAutoAddMargin", out.is_auto_add_margin);
    common::detail::json::read(obj, "isolatedMargin", out.isolated_margin);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "liquidationPrice", out.liquidation_price);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "maxNotionalValue", out.max_notional_value);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "notional", out.notional);
    common::detail::json::read(obj, "isolatedWallet", out.isolated_wallet);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "unRealizedProfit", out.un_realized_profit);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PositionInformationResponseResultInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "breakEvenPrice", v.break_even_price);
    common::detail::json::write(obj, "marginType", v.margin_type);
    common::detail::json::write(obj, "isAutoAddMargin", v.is_auto_add_margin);
    common::detail::json::write(obj, "isolatedMargin", v.isolated_margin);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "liquidationPrice", v.liquidation_price);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "maxNotionalValue", v.max_notional_value);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "notional", v.notional);
    common::detail::json::write(obj, "isolatedWallet", v.isolated_wallet);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "unRealizedProfit", v.un_realized_profit);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
