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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_margin_borrow_loan_interest_history_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetMarginBorrowLoanInterestHistoryResponse {
    /// Rows.
    std::optional<std::vector<GetMarginBorrowLoanInterestHistoryResponseRowsInner>> rows;
    /// Total.
    std::optional<std::int64_t> total;

    bool operator==(const GetMarginBorrowLoanInterestHistoryResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetMarginBorrowLoanInterestHistoryResponse
tag_invoke(boost::json::value_to_tag<GetMarginBorrowLoanInterestHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetMarginBorrowLoanInterestHistoryResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
