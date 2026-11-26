//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_prevented_matches_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryPreventedMatchesResponseInner
tag_invoke(boost::json::value_to_tag<QueryPreventedMatchesResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryPreventedMatchesResponseInner");
    QueryPreventedMatchesResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "preventedMatchId", out.prevented_match_id);
    common::detail::json::read(obj, "takerOrderId", out.taker_order_id);
    common::detail::json::read(obj, "makerSymbol", out.maker_symbol);
    common::detail::json::read(obj, "makerOrderId", out.maker_order_id);
    common::detail::json::read(obj, "tradeGroupId", out.trade_group_id);
    common::detail::json::read(obj, "selfTradePreventionMode", out.self_trade_prevention_mode);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "makerPreventedQuantity", out.maker_prevented_quantity);
    common::detail::json::read(obj, "transactTime", out.transact_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPreventedMatchesResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "preventedMatchId", v.prevented_match_id);
    common::detail::json::write(obj, "takerOrderId", v.taker_order_id);
    common::detail::json::write(obj, "makerSymbol", v.maker_symbol);
    common::detail::json::write(obj, "makerOrderId", v.maker_order_id);
    common::detail::json::write(obj, "tradeGroupId", v.trade_group_id);
    common::detail::json::write(obj, "selfTradePreventionMode", v.self_trade_prevention_mode);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "makerPreventedQuantity", v.maker_prevented_quantity);
    common::detail::json::write(obj, "transactTime", v.transact_time);
}

} // namespace binance::margin_trading::rest_api
