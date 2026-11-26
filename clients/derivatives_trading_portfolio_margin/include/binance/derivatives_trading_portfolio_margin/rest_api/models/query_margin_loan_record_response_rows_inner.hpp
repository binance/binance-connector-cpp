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

struct QueryMarginLoanRecordResponseRowsInner {
    /// Tx ID.
    std::optional<std::int64_t> tx_id;
    /// asset name
    std::optional<std::string> asset;
    /// Principal repaid
    std::optional<std::string> principal;
    /// Timestamp.
    std::optional<std::int64_t> timestamp;
    /// one of PENDING (pending execution), CONFIRMED (successfully loaned), FAILED (execution
    /// failed, nothing happened to your account);
    std::optional<std::string> status;

    bool operator==(const QueryMarginLoanRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginLoanRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryMarginLoanRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginLoanRecordResponseRowsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
