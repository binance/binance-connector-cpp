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

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_universal_transfer_history_response_result_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryUniversalTransferHistoryResponse {
    std::optional<std::vector<QueryUniversalTransferHistoryResponseResultInner>> result;
    std::optional<std::int64_t> total_count;

    bool operator==(const QueryUniversalTransferHistoryResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryUniversalTransferHistoryResponse
tag_invoke(boost::json::value_to_tag<QueryUniversalTransferHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QueryUniversalTransferHistoryResponse& v);

} // namespace binance::sub_account::rest_api
