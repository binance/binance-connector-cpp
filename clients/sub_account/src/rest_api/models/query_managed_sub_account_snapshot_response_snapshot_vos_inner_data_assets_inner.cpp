//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_assets_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner");
    QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "marginBalance", out.margin_balance);
    common::detail::json::read(obj, "walletBalance", out.wallet_balance);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataAssetsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "marginBalance", v.margin_balance);
    common::detail::json::write(obj, "walletBalance", v.wallet_balance);
}

} // namespace binance::sub_account::rest_api
