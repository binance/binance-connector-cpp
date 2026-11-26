//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_account_trade_list_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

CmAccountTradeListResponseInner
tag_invoke(boost::json::value_to_tag<CmAccountTradeListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CmAccountTradeListResponseInner");
    CmAccountTradeListResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "realizedPnl", out.realized_pnl);
    common::detail::json::read(obj, "marginAsset", out.margin_asset);
    common::detail::json::read(obj, "baseQty", out.base_qty);
    common::detail::json::read(obj, "commission", out.commission);
    common::detail::json::read(obj, "commissionAsset", out.commission_asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "positionSide", out.position_side);
    common::detail::json::read(obj, "buyer", out.buyer);
    common::detail::json::read(obj, "maker", out.maker);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CmAccountTradeListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "realizedPnl", v.realized_pnl);
    common::detail::json::write(obj, "marginAsset", v.margin_asset);
    common::detail::json::write(obj, "baseQty", v.base_qty);
    common::detail::json::write(obj, "commission", v.commission);
    common::detail::json::write(obj, "commissionAsset", v.commission_asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "positionSide", v.position_side);
    common::detail::json::write(obj, "buyer", v.buyer);
    common::detail::json::write(obj, "maker", v.maker);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
