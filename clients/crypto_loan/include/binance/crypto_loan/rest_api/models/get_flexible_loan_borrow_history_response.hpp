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

#include <binance/crypto_loan/export.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_borrow_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

struct GetFlexibleLoanBorrowHistoryResponse {
    std::optional<std::vector<GetFlexibleLoanBorrowHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetFlexibleLoanBorrowHistoryResponse& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanBorrowHistoryResponse
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanBorrowHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleLoanBorrowHistoryResponse& v);

} // namespace binance::crypto_loan::rest_api
