//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_asset_transfer_history_response_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountSpotAssetTransferHistoryResponseInner
tag_invoke(boost::json::value_to_tag<QuerySubAccountSpotAssetTransferHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuerySubAccountSpotAssetTransferHistoryResponseInner");
    QuerySubAccountSpotAssetTransferHistoryResponseInner out;
    common::detail::json::read(obj, "from", out.from);
    common::detail::json::read(obj, "to", out.to);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "qty", out.qty);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountSpotAssetTransferHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "from", v.from);
    common::detail::json::write(obj, "to", v.to);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "qty", v.qty);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::sub_account::rest_api
