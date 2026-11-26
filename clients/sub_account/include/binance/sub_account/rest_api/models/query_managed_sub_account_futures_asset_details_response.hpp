//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response_snapshot_vos_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountFuturesAssetDetailsResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::vector<QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInner>>
        snapshot_vos;

    bool
    operator==(const QueryManagedSubAccountFuturesAssetDetailsResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountFuturesAssetDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountFuturesAssetDetailsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountFuturesAssetDetailsResponse& v);

} // namespace binance::sub_account::rest_api
