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

#include <binance/crypto_loan/export.hpp>

namespace binance::crypto_loan::rest_api {

struct GetFlexibleLoanRepaymentHistoryResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> repay_amount;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> collateral_return;
    /// REPAID, REPAYING, FAILED
    std::optional<std::string> repay_status;
    std::optional<std::int64_t> repay_time;

    bool
    operator==(const GetFlexibleLoanRepaymentHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanRepaymentHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanRepaymentHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleLoanRepaymentHistoryResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
