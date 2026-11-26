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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner {
    /// asset name
    std::optional<std::string> asset;
    /// interest amount
    std::optional<std::string> interest;
    /// Interest Accured Time.
    std::optional<std::int64_t> interest_accured_time;
    /// daily interest rate
    std::optional<std::string> interest_rate;
    /// Principal repaid
    std::optional<std::string> principal;

    bool
    operator==(const QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
