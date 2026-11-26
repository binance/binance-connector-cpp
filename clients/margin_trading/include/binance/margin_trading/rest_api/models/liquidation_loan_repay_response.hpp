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

struct LiquidationLoanRepayResponse {
    /// Unique identifier for this repayment transaction
    std::optional<std::int64_t> repay_id;
    /// Asset used for repayment
    std::optional<std::string> asset;
    /// Actual repayment amount
    std::optional<std::string> amount;
    /// Repayment status: `SUCCESS` (completed) or `PENDING` (processing)
    std::optional<std::string> status;
    /// Unix timestamp (milliseconds) when the repayment was created
    std::optional<std::int64_t> create_time;

    bool operator==(const LiquidationLoanRepayResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT LiquidationLoanRepayResponse tag_invoke(
    boost::json::value_to_tag<LiquidationLoanRepayResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const LiquidationLoanRepayResponse& v);

} // namespace binance::margin_trading::rest_api
