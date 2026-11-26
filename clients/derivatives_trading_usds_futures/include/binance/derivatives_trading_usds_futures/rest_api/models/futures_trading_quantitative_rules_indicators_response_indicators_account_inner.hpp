//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner {
    /// Too many violations under multiple symbols trigger account violation
    std::optional<std::string> indicator;
    /// Current value
    std::optional<std::int64_t> value;
    /// Trigger value
    std::optional<std::int64_t> trigger_value;
    /// Planned Recover Time.
    std::optional<std::int64_t> planned_recover_time;
    /// Is Locked.
    std::optional<bool> is_locked;

    bool operator==(
        const FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner
tag_invoke(boost::json::value_to_tag<
               FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
