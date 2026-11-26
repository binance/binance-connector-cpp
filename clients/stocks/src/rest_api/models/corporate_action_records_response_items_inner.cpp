//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/corporate_action_records_response_items_inner.hpp>

namespace binance::stocks::rest_api {

CorporateActionRecordsResponseItemsInner
tag_invoke(boost::json::value_to_tag<CorporateActionRecordsResponseItemsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CorporateActionRecordsResponseItemsInner");
    CorporateActionRecordsResponseItemsInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "userId", out.user_id);
    common::detail::json::read(obj, "assetCode", out.asset_code);
    common::detail::json::read(obj, "eventType", out.event_type);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "dbModifyTime", out.db_modify_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CorporateActionRecordsResponseItemsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "userId", v.user_id);
    common::detail::json::write(obj, "assetCode", v.asset_code);
    common::detail::json::write(obj, "eventType", v.event_type);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "dbModifyTime", v.db_modify_time);
}

} // namespace binance::stocks::rest_api
