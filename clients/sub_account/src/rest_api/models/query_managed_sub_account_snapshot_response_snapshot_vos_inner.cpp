//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountSnapshotResponseSnapshotVosInner tag_invoke(
    boost::json::value_to_tag<QueryManagedSubAccountSnapshotResponseSnapshotVosInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountSnapshotResponseSnapshotVosInner");
    QueryManagedSubAccountSnapshotResponseSnapshotVosInner out;
    common::detail::json::read(obj, "data", out.data);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountSnapshotResponseSnapshotVosInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "data", v.data);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::sub_account::rest_api
