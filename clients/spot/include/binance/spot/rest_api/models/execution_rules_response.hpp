//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/execution_rules_response_symbol_rules_inner.hpp>

namespace binance::spot::rest_api {

struct ExecutionRulesResponse {
    std::optional<std::vector<ExecutionRulesResponseSymbolRulesInner>> symbol_rules;

    bool operator==(const ExecutionRulesResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExecutionRulesResponse
tag_invoke(boost::json::value_to_tag<ExecutionRulesResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExecutionRulesResponse& v);

} // namespace binance::spot::rest_api
