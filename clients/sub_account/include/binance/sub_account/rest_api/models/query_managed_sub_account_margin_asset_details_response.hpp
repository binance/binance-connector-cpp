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
#include <binance/sub_account/rest_api/models/query_managed_sub_account_margin_asset_details_response_user_assets_inner.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountMarginAssetDetailsResponse {
    std::optional<std::string> margin_level;
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;
    std::optional<std::vector<QueryManagedSubAccountMarginAssetDetailsResponseUserAssetsInner>>
        user_assets;

    bool
    operator==(const QueryManagedSubAccountMarginAssetDetailsResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountMarginAssetDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountMarginAssetDetailsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountMarginAssetDetailsResponse& v);

} // namespace binance::sub_account::rest_api
