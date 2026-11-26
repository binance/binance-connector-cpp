//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_isolated_margin_capital_flow_response_inner.hpp>

namespace binance::margin_trading::rest_api {

QueryCrossIsolatedMarginCapitalFlowResponseInner
tag_invoke(boost::json::value_to_tag<QueryCrossIsolatedMarginCapitalFlowResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryCrossIsolatedMarginCapitalFlowResponseInner");
    QueryCrossIsolatedMarginCapitalFlowResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "note", out.note);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCrossIsolatedMarginCapitalFlowResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "note", v.note);
}

} // namespace binance::margin_trading::rest_api
