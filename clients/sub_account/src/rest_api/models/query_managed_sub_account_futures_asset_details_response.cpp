//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_futures_asset_details_response.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountFuturesAssetDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountFuturesAssetDetailsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryManagedSubAccountFuturesAssetDetailsResponse");
    QueryManagedSubAccountFuturesAssetDetailsResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "snapshotVos", out.snapshot_vos);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountFuturesAssetDetailsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "snapshotVos", v.snapshot_vos);
}

} // namespace binance::sub_account::rest_api
