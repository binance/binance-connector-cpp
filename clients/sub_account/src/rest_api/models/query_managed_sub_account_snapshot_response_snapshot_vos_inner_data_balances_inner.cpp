//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_balances_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner");
    QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "free", out.free);
    common::detail::json::read(obj, "locked", out.locked);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataBalancesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "free", v.free);
    common::detail::json::write(obj, "locked", v.locked);
}

} // namespace binance::sub_account::rest_api
