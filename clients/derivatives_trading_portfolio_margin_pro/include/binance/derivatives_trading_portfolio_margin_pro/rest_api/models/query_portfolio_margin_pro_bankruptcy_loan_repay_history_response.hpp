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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_bankruptcy_loan_repay_history_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse {
    /// total.
    std::optional<std::int64_t> total;
    std::optional<std::vector<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner>>
        rows;

    bool operator==(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse tag_invoke(
    boost::json::value_to_tag<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
