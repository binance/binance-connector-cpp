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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_pro_tiered_collateral_rate_response_inner_collateral_info_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct PortfolioMarginProTieredCollateralRateResponseInner {
    /// asset.
    std::optional<std::string> asset;
    std::optional<
        std::vector<PortfolioMarginProTieredCollateralRateResponseInnerCollateralInfoInner>>
        collateral_info;

    bool operator==(const PortfolioMarginProTieredCollateralRateResponseInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
PortfolioMarginProTieredCollateralRateResponseInner
tag_invoke(boost::json::value_to_tag<PortfolioMarginProTieredCollateralRateResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PortfolioMarginProTieredCollateralRateResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
