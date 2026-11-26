//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_um_position_information_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryUmPositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<QueryUmPositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryUmPositionInformationResponseInner");
    QueryUmPositionInformationResponseInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "maxNotionalValue", out.max_notional_value);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "notional", out.notional);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "unRealizedProfit", out.un_realized_profit);
    common::detail::json::read(obj, "liquidationPrice", out.liquidation_price);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUmPositionInformationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "maxNotionalValue", v.max_notional_value);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "notional", v.notional);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "unRealizedProfit", v.un_realized_profit);
    common::detail::json::write(obj, "liquidationPrice", v.liquidation_price);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
