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

struct FlexibleLoanBorrowResponse {
    std::optional<std::string> loan_coin;
    std::optional<std::string> loan_amount;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> collateral_amount;
    /// Succeeds, Failed, Processing
    std::optional<std::string> status;

    bool operator==(const FlexibleLoanBorrowResponse& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT FlexibleLoanBorrowResponse tag_invoke(
    boost::json::value_to_tag<FlexibleLoanBorrowResponse> /*tag*/, const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const FlexibleLoanBorrowResponse& v);

} // namespace binance::crypto_loan::rest_api
