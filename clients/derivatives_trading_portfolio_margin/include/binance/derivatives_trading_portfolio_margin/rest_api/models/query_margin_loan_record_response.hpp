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
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_loan_record_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryMarginLoanRecordResponse {
    /// Rows.
    std::optional<std::vector<QueryMarginLoanRecordResponseRowsInner>> rows;
    /// Total.
    std::optional<std::int64_t> total;

    bool operator==(const QueryMarginLoanRecordResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginLoanRecordResponse tag_invoke(
    boost::json::value_to_tag<QueryMarginLoanRecordResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginLoanRecordResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
