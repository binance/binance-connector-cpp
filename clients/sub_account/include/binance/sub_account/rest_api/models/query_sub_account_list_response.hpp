//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_list_response_sub_accounts_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountListResponse {
    std::optional<std::vector<QuerySubAccountListResponseSubAccountsInner>> sub_accounts;

    bool operator==(const QuerySubAccountListResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountListResponse tag_invoke(
    boost::json::value_to_tag<QuerySubAccountListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountListResponse& v);

} // namespace binance::sub_account::rest_api
