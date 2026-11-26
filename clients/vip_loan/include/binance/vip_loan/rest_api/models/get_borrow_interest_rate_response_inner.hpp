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

struct GetBorrowInterestRateResponseInner {
    std::optional<std::string> asset;
    std::optional<std::string> flexible_daily_interest_rate;
    std::optional<std::string> flexible_yearly_interest_rate;
    std::optional<std::int64_t> time;

    bool operator==(const GetBorrowInterestRateResponseInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetBorrowInterestRateResponseInner
tag_invoke(boost::json::value_to_tag<GetBorrowInterestRateResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetBorrowInterestRateResponseInner& v);

} // namespace binance::vip_loan::rest_api
