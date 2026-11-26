//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_assets_summary_response.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountSpotAssetsSummaryResponse
tag_invoke(boost::json::value_to_tag<QuerySubAccountSpotAssetsSummaryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountSpotAssetsSummaryResponse");
    QuerySubAccountSpotAssetsSummaryResponse out;
    common::detail::json::read(obj, "totalCount", out.total_count);
    common::detail::json::read(obj, "masterAccountTotalAsset", out.master_account_total_asset);
    common::detail::json::read(obj, "spotSubUserAssetBtcVoList",
                               out.spot_sub_user_asset_btc_vo_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountSpotAssetsSummaryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalCount", v.total_count);
    common::detail::json::write(obj, "masterAccountTotalAsset", v.master_account_total_asset);
    common::detail::json::write(obj, "spotSubUserAssetBtcVoList",
                                v.spot_sub_user_asset_btc_vo_list);
}

} // namespace binance::sub_account::rest_api
