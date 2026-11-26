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

struct GetFlexibleLoanInterestRateHistoryResponseRowsInner {
    std::optional<std::string> coin;
    std::optional<std::string> annualized_interest_rate;
    std::optional<std::int64_t> time;

    bool operator==(const GetFlexibleLoanInterestRateHistoryResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanInterestRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanInterestRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleLoanInterestRateHistoryResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
