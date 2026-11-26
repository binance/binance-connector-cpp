//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_assets_summary_response_spot_sub_user_asset_btc_vo_list_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner
tag_invoke(boost::json::value_to_tag<
               QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner");
    QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "totalAsset", out.total_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountSpotAssetsSummaryResponseSpotSubUserAssetBtcVoListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "totalAsset", v.total_asset);
}

} // namespace binance::sub_account::rest_api
