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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner {
    /// tier Floor.
    std::optional<std::string> tier_floor;
    /// tier Cap.
    std::optional<std::string> tier_cap;
    /// collateral Rate.
    std::optional<std::string> collateral_rate;
    /// account equity quick addition number
    std::optional<std::string> cum;

    bool operator==(
        const PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner
tag_invoke(boost::json::value_to_tag<
               PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
