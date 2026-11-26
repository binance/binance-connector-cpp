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

struct PortfolioMarginCollateralRateResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// collateral Rate.
    std::optional<std::string> collateral_rate;

    bool operator==(const PortfolioMarginCollateralRateResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT PortfolioMarginCollateralRateResponseInner
tag_invoke(boost::json::value_to_tag<PortfolioMarginCollateralRateResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PortfolioMarginCollateralRateResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
