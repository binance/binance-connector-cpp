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

struct QueryVIPLoanFixedRateMarketResponseRowsInner {
    /// Supply request ID
    std::optional<std::int64_t> request_id;
    /// Request number
    std::optional<std::int64_t> request_no;
    /// Coin
    std::optional<std::string> coin;
    /// Annual interest rate
    std::optional<std::string> interest_rate;
    /// Duration in days
    std::optional<std::int64_t> duration;
    /// Minimum borrow amount
    std::optional<std::string> minimum_amount;
    /// Maximum available borrow amount
    std::optional<std::string> available_amount;
    /// Estimated interest
    std::optional<std::string> estimated_interest;

    bool operator==(const QueryVIPLoanFixedRateMarketResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT QueryVIPLoanFixedRateMarketResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryVIPLoanFixedRateMarketResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const QueryVIPLoanFixedRateMarketResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
