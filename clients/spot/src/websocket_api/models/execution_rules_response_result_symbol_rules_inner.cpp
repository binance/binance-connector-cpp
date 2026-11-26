//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/execution_rules_response_result_symbol_rules_inner.hpp>

namespace binance::spot::websocket_api {

ExecutionRulesResponseResultSymbolRulesInner
tag_invoke(boost::json::value_to_tag<ExecutionRulesResponseResultSymbolRulesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ExecutionRulesResponseResultSymbolRulesInner");
    ExecutionRulesResponseResultSymbolRulesInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "rules", out.rules);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExecutionRulesResponseResultSymbolRulesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "rules", v.rules);
}

} // namespace binance::spot::websocket_api
