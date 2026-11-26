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
#include <binance/sub_account/rest_api/models/query_sub_account_api_key_response_rows_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountApiKeyResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<QuerySubAccountApiKeyResponseRowsInner>> rows;

    bool operator==(const QuerySubAccountApiKeyResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountApiKeyResponse tag_invoke(
    boost::json::value_to_tag<QuerySubAccountApiKeyResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountApiKeyResponse& v);

} // namespace binance::sub_account::rest_api
