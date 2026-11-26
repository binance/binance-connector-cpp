//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_redemption_record_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleRedemptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleRedemptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleRedemptionRecordResponseRowsInner");
    GetFlexibleRedemptionRecordResponseRowsInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "projectId", out.project_id);
    common::detail::json::read(obj, "redeemId", out.redeem_id);
    common::detail::json::read(obj, "destAccount", out.dest_account);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleRedemptionRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "projectId", v.project_id);
    common::detail::json::write(obj, "redeemId", v.redeem_id);
    common::detail::json::write(obj, "destAccount", v.dest_account);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::simple_earn::rest_api
