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

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_trading_quantitative_rules_indicators_response_indicators_account_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_trading_quantitative_rules_indicators_response_indicators_btcusdt_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

/// indicator: quantitative rules indicators, value: user's indicators value, triggerValue: trigger
/// indicator value threshold of quantitative rules.
struct FuturesTradingQuantitativeRulesIndicatorsResponseIndicators {
    std::optional<
        std::vector<FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner>>
        btcusdt;
    std::optional<
        std::vector<FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner>>
        ethusdt;
    std::optional<
        std::vector<FuturesTradingQuantitativeRulesIndicatorsResponseIndicatorsACCOUNTInner>>
        account;

    bool operator==(const FuturesTradingQuantitativeRulesIndicatorsResponseIndicators& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
FuturesTradingQuantitativeRulesIndicatorsResponseIndicators tag_invoke(
    boost::json::value_to_tag<FuturesTradingQuantitativeRulesIndicatorsResponseIndicators> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesTradingQuantitativeRulesIndicatorsResponseIndicators& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
