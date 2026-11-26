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

#include <binance/vip_loan/export.hpp>

namespace binance::vip_loan::rest_api {

struct VipLoanFixedRateBorrowResponse {
    /// Echo of input parameter
    std::optional<std::string> borrow_coin;
    /// Actual total borrow amount (aggregated when multiple supplyRequest)
    std::optional<std::string> borrow_amount;
    /// Actual received amount
    std::optional<std::string> actual_received_amount;
    /// Echo of input parameter, comma-separated
    std::optional<std::string> collateral_coin;
    /// Echo of input parameter, comma-separated
    std::optional<std::string> collateral_account_id;
    /// Actual borrow interest rate (weighted average when multiple)
    std::optional<std::string> borrow_interest_rate;
    /// `{loanTerm}Days`, e.g. "30Days"
    std::optional<std::string> duration;
    /// Echo of input parameter
    std::optional<bool> auto_repay;
    /// Order ID
    std::optional<std::int64_t> order_id;
    /// `Succeeds` / `Failed` / `Processing`
    std::optional<std::string> status;

    bool operator==(const VipLoanFixedRateBorrowResponse& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT VipLoanFixedRateBorrowResponse
tag_invoke(boost::json::value_to_tag<VipLoanFixedRateBorrowResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const VipLoanFixedRateBorrowResponse& v);

} // namespace binance::vip_loan::rest_api
