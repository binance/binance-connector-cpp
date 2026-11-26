//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_managed_sub_account_snapshot_response_snapshot_vos_inner_data_position_inner.hpp>

namespace binance::sub_account::rest_api {

QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner
tag_invoke(boost::json::value_to_tag<
               QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner");
    QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner out;
    common::detail::json::read(obj, "entryPrice", out.entry_price);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "positionAmt", out.position_amt);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "unRealizedProfit", out.un_realized_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryManagedSubAccountSnapshotResponseSnapshotVosInnerDataPositionInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "entryPrice", v.entry_price);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "positionAmt", v.position_amt);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "unRealizedProfit", v.un_realized_profit);
}

} // namespace binance::sub_account::rest_api
