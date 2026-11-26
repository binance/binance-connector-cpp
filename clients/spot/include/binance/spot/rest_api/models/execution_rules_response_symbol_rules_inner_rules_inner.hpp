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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct ExecutionRulesResponseSymbolRulesInnerRulesInner {
    std::optional<std::string> rule_type;
    std::optional<std::string> bid_limit_mult_up;
    std::optional<std::string> bid_limit_mult_down;
    std::optional<std::string> ask_limit_mult_up;
    std::optional<std::string> ask_limit_mult_down;

    bool
    operator==(const ExecutionRulesResponseSymbolRulesInnerRulesInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExecutionRulesResponseSymbolRulesInnerRulesInner
tag_invoke(boost::json::value_to_tag<ExecutionRulesResponseSymbolRulesInnerRulesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExecutionRulesResponseSymbolRulesInnerRulesInner& v);

} // namespace binance::spot::rest_api
