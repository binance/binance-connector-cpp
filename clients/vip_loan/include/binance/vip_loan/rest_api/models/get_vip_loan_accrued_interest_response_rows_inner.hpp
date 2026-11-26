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

struct GetVIPLoanAccruedInterestResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> principal_amount;
    std::optional<std::string> interest_amount;
    std::optional<std::string> annual_interest_rate;
    std::optional<std::int64_t> accrual_time;
    /// Latest order ID for the renewal order.
    std::optional<std::int64_t> order_id;

    bool operator==(const GetVIPLoanAccruedInterestResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetVIPLoanAccruedInterestResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanAccruedInterestResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetVIPLoanAccruedInterestResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
