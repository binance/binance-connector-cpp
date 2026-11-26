//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/execution_rules_response_result.hpp>

namespace binance::spot::websocket_api {

ExecutionRulesResponseResult
tag_invoke(boost::json::value_to_tag<ExecutionRulesResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExecutionRulesResponseResult");
    ExecutionRulesResponseResult out;
    common::detail::json::read(obj, "symbolRules", out.symbol_rules);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExecutionRulesResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbolRules", v.symbol_rules);
}

} // namespace binance::spot::websocket_api
