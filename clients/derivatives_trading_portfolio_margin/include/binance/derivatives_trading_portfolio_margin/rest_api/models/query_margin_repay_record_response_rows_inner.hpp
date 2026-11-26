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

struct QueryMarginRepayRecordResponseRowsInner {
    /// Total amount repaid
    std::optional<std::string> amount;
    /// asset name
    std::optional<std::string> asset;
    /// Interest repaid
    std::optional<std::string> interest;
    /// Principal repaid
    std::optional<std::string> principal;
    /// one of PENDING (pending execution), CONFIRMED (successfully execution), FAILED (execution
    /// failed, nothing happened to your account)
    std::optional<std::string> status;
    /// Timestamp.
    std::optional<std::int64_t> timestamp;
    /// Tx ID.
    std::optional<std::int64_t> tx_id;

    bool operator==(const QueryMarginRepayRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginRepayRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryMarginRepayRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginRepayRecordResponseRowsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
