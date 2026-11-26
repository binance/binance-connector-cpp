//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/execution_rules_response_symbol_rules_inner_rules_inner.hpp>

namespace binance::spot::rest_api {

struct ExecutionRulesResponseSymbolRulesInner {
    std::optional<std::string> symbol;
    std::optional<std::vector<ExecutionRulesResponseSymbolRulesInnerRulesInner>> rules;

    bool operator==(const ExecutionRulesResponseSymbolRulesInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExecutionRulesResponseSymbolRulesInner
tag_invoke(boost::json::value_to_tag<ExecutionRulesResponseSymbolRulesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExecutionRulesResponseSymbolRulesInner& v);

} // namespace binance::spot::rest_api
