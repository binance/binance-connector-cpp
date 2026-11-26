//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/crypto_loan/export.hpp>

namespace binance::crypto_loan::rest_api {

struct FlexibleLoanRepayResponse {
    std::optional<std::string> loan_coin;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> remaining_debt;
    std::optional<std::string> remaining_collateral;
    std::optional<bool> full_repayment;
    std::optional<std::string> current_ltv;
    /// REPAID, REPAYING, FAILED
    std::optional<std::string> repay_status;

    bool operator==(const FlexibleLoanRepayResponse& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT FlexibleLoanRepayResponse tag_invoke(
    boost::json::value_to_tag<FlexibleLoanRepayResponse> /*tag*/, const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const FlexibleLoanRepayResponse& v);

} // namespace binance::crypto_loan::rest_api
