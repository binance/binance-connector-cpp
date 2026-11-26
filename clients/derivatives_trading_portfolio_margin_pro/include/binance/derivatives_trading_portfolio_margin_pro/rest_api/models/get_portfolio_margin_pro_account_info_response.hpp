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

struct GetPortfolioMarginProAccountInfoResponse {
    /// Classic Portfolio margin account maintenance margin rate
    std::optional<std::string> uni_mmr;
    /// Account equity, unit：USD
    std::optional<std::string> account_equity;
    /// Actual equity, unit：USD
    std::optional<std::string> actual_equity;
    /// Classic Portfolio margin account maintenance margin, unit：USD
    std::optional<std::string> account_maint_margin;
    /// Ignored for PM PRO and PM PRO SPAN
    std::optional<std::string> account_initial_margin;
    /// Ignored for PM PRO and PM PRO SPAN
    std::optional<std::string> total_available_balance;
    /// Classic Portfolio margin account status:"NORMAL", "MARGIN_CALL", "SUPPLY_MARGIN",
    /// "REDUCE_ONLY", "ACTIVE_LIQUIDATION", "FORCE_LIQUIDATION", "BANKRUPTED"
    std::optional<std::string> account_status;
    /// PM_1 for PM PRO, PM_2 for PM, PM_3 for PM PRO SPAN
    std::optional<std::string> account_type;

    bool operator==(const GetPortfolioMarginProAccountInfoResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT GetPortfolioMarginProAccountInfoResponse
tag_invoke(boost::json::value_to_tag<GetPortfolioMarginProAccountInfoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetPortfolioMarginProAccountInfoResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
