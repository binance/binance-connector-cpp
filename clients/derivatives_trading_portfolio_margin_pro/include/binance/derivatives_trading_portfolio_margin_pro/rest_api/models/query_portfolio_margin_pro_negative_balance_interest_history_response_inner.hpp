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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// interest amount
    std::optional<std::string> interest;
    /// interest Accrued Time.
    std::optional<std::int64_t> interest_accrued_time;
    /// daily interest rate
    std::optional<std::string> interest_rate;
    /// principal.
    std::optional<std::string> principal;

    bool
    operator==(const QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
