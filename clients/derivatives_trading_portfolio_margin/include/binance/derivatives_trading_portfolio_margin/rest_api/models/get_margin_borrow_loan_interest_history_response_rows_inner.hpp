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

struct GetMarginBorrowLoanInterestHistoryResponseRowsInner {
    /// Tx ID.
    std::optional<std::int64_t> tx_id;
    /// Interest Accured Time.
    std::optional<std::int64_t> interest_accured_time;
    /// asset name
    std::optional<std::string> asset;
    /// Raw Asset.
    std::optional<std::string> raw_asset;
    /// Principal repaid
    std::optional<std::string> principal;
    /// Interest repaid
    std::optional<std::string> interest;
    /// daily interest rate
    std::optional<std::string> interest_rate;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;

    bool operator==(const GetMarginBorrowLoanInterestHistoryResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
GetMarginBorrowLoanInterestHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetMarginBorrowLoanInterestHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetMarginBorrowLoanInterestHistoryResponseRowsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
