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
#include <binance/sub_account/rest_api/models/query_sub_account_assets_response_balances_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountAssetsResponse {
    std::optional<std::vector<QuerySubAccountAssetsResponseBalancesInner>> balances;

    bool operator==(const QuerySubAccountAssetsResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountAssetsResponse tag_invoke(
    boost::json::value_to_tag<QuerySubAccountAssetsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountAssetsResponse& v);

} // namespace binance::sub_account::rest_api
