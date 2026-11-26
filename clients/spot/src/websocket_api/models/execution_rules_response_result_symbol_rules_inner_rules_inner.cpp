//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/execution_rules_response_result_symbol_rules_inner_rules_inner.hpp>

namespace binance::spot::websocket_api {

ExecutionRulesResponseResultSymbolRulesInnerRulesInner tag_invoke(
    boost::json::value_to_tag<ExecutionRulesResponseResultSymbolRulesInnerRulesInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "ExecutionRulesResponseResultSymbolRulesInnerRulesInner");
    ExecutionRulesResponseResultSymbolRulesInnerRulesInner out;
    common::detail::json::read(obj, "ruleType", out.rule_type);
    common::detail::json::read(obj, "bidLimitMultUp", out.bid_limit_mult_up);
    common::detail::json::read(obj, "bidLimitMultDown", out.bid_limit_mult_down);
    common::detail::json::read(obj, "askLimitMultUp", out.ask_limit_mult_up);
    common::detail::json::read(obj, "askLimitMultDown", out.ask_limit_mult_down);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExecutionRulesResponseResultSymbolRulesInnerRulesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "ruleType", v.rule_type);
    common::detail::json::write(obj, "bidLimitMultUp", v.bid_limit_mult_up);
    common::detail::json::write(obj, "bidLimitMultDown", v.bid_limit_mult_down);
    common::detail::json::write(obj, "askLimitMultUp", v.ask_limit_mult_up);
    common::detail::json::write(obj, "askLimitMultDown", v.ask_limit_mult_down);
}

} // namespace binance::spot::websocket_api
