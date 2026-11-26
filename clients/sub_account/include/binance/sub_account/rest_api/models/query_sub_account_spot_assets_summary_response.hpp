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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_assets_summary_response_spot_sub_user_asset_btc_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

struct QuerySubAccountSpotAssetsSummaryResponse {
    std::optional<std::int64_t> total_count;
    std::optional<std::string> master_account_total_asset;
    std::optional<
        std::vector<QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner>>
        spot_sub_user_asset_btc_vo_list;

    bool operator==(const QuerySubAccountSpotAssetsSummaryResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QuerySubAccountSpotAssetsSummaryResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountSpotAssetsSummaryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const QuerySubAccountSpotAssetsSummaryResponse& v);

} // namespace binance::sub_account::rest_api
