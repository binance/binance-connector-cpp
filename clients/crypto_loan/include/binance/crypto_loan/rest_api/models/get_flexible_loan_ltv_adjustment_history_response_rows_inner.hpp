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

struct GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> collateral_coin;
    std::optional<std::string> direction;
    std::optional<std::string> collateral_amount;
    std::optional<std::string> pre_ltv;
    std::optional<std::string> after_ltv;
    std::optional<std::int64_t> adjust_time;

    bool operator==(const GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
