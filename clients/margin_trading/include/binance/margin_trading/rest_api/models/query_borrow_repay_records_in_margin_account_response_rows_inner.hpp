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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryBorrowRepayRecordsInMarginAccountResponseRowsInner {
    /// AUTO,MANUAL for Cross Margin Borrow; MANUAL，AUTO，BNB_AUTO_REPAY，POINT_AUTO_REPAY for
    /// Cross Margin Repay; AUTO，MANUAL for Isolated Margin Borrow/Repay;
    std::optional<std::string> type;
    /// isolated symbol, will not be returned for crossed margin
    std::optional<std::string> isolated_symbol;
    /// Total amount borrowed/repaid
    std::optional<std::string> amount;
    /// asset.
    std::optional<std::string> asset;
    /// Interest repaid
    std::optional<std::string> interest;
    /// Principal repaid
    std::optional<std::string> principal;
    /// one of PENDING (pending execution), CONFIRMED (successfully execution), FAILED (execution
    /// failed, nothing happened to your account);
    std::optional<std::string> status;
    /// timestamp.
    std::optional<std::int64_t> timestamp;
    /// tx Id.
    std::optional<std::int64_t> tx_id;

    bool operator==(
        const QueryBorrowRepayRecordsInMarginAccountResponseRowsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryBorrowRepayRecordsInMarginAccountResponseRowsInner tag_invoke(
    boost::json::value_to_tag<QueryBorrowRepayRecordsInMarginAccountResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryBorrowRepayRecordsInMarginAccountResponseRowsInner& v);

} // namespace binance::margin_trading::rest_api
