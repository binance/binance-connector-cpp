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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_trading_quantitative_rules_indicators_response_indicators.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct FuturesTradingQuantitativeRulesIndicatorsResponse {
    std::optional<FuturesTradingQuantitativeRulesIndicatorsResponseIndicators> indicators;
    /// Update Time.
    std::optional<std::int64_t> update_time;

    bool
    operator==(const FuturesTradingQuantitativeRulesIndicatorsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT FuturesTradingQuantitativeRulesIndicatorsResponse
tag_invoke(boost::json::value_to_tag<FuturesTradingQuantitativeRulesIndicatorsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesTradingQuantitativeRulesIndicatorsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
