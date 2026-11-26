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
#include <binance/vip_loan/rest_api/models/query_vip_loan_fixed_rate_market_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

struct QueryVIPLoanFixedRateMarketResponse {
    /// Total number of records
    std::optional<std::int64_t> total;
    /// Current page data
    std::optional<std::vector<QueryVIPLoanFixedRateMarketResponseRowsInner>> rows;

    bool operator==(const QueryVIPLoanFixedRateMarketResponse& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT QueryVIPLoanFixedRateMarketResponse
tag_invoke(boost::json::value_to_tag<QueryVIPLoanFixedRateMarketResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const QueryVIPLoanFixedRateMarketResponse& v);

} // namespace binance::vip_loan::rest_api
