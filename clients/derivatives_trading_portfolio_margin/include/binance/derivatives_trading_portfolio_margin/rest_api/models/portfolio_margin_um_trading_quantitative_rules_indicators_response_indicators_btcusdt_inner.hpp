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

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner {
    /// Is Locked.
    std::optional<bool> is_locked;
    /// Planned Recover Time.
    std::optional<std::int64_t> planned_recover_time;
    /// Indicator.
    std::optional<std::string> indicator;
    /// Value.
    std::optional<common::Decimal> value;
    /// Trigger Value.
    std::optional<common::Decimal> trigger_value;

    bool operator==(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner tag_invoke(
    boost::json::value_to_tag<
        PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponseIndicatorsBTCUSDTInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
