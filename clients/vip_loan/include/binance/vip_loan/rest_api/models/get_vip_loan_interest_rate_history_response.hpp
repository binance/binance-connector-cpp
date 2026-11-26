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

#include <binance/vip_loan/export.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_interest_rate_history_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

struct GetVIPLoanInterestRateHistoryResponse {
    std::optional<std::vector<GetVIPLoanInterestRateHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetVIPLoanInterestRateHistoryResponse& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetVIPLoanInterestRateHistoryResponse
tag_invoke(boost::json::value_to_tag<GetVIPLoanInterestRateHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetVIPLoanInterestRateHistoryResponse& v);

} // namespace binance::vip_loan::rest_api
