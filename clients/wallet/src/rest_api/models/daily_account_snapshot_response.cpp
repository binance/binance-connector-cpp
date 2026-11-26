//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response.hpp>

namespace binance::wallet::rest_api {

DailyAccountSnapshotResponse
tag_invoke(boost::json::value_to_tag<DailyAccountSnapshotResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DailyAccountSnapshotResponse");
    DailyAccountSnapshotResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    common::detail::json::read(obj, "snapshotVos", out.snapshot_vos);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DailyAccountSnapshotResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
    common::detail::json::write(obj, "snapshotVos", v.snapshot_vos);
}

} // namespace binance::wallet::rest_api
