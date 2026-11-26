//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_record_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

GetFlexibleSubscriptionRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleSubscriptionRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleSubscriptionRecordResponseRowsInner");
    GetFlexibleSubscriptionRecordResponseRowsInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "purchaseId", out.purchase_id);
    common::detail::json::read(obj, "productId", out.product_id);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "sourceAccount", out.source_account);
    common::detail::json::read(obj, "amtFromSpot", out.amt_from_spot);
    common::detail::json::read(obj, "amtFromFunding", out.amt_from_funding);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleSubscriptionRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "purchaseId", v.purchase_id);
    common::detail::json::write(obj, "productId", v.product_id);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "sourceAccount", v.source_account);
    common::detail::json::write(obj, "amtFromSpot", v.amt_from_spot);
    common::detail::json::write(obj, "amtFromFunding", v.amt_from_funding);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::simple_earn::rest_api
