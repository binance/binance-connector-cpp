//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response_data_data_inner.hpp>

namespace binance::rebate::rest_api {

GetSpotRebateHistoryRecordsResponseDataDataInner
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponseDataDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSpotRebateHistoryRecordsResponseDataDataInner");
    GetSpotRebateHistoryRecordsResponseDataDataInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSpotRebateHistoryRecordsResponseDataDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::rebate::rest_api
