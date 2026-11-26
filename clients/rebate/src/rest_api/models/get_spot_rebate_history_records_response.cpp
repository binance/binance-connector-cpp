//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response.hpp>

namespace binance::rebate::rest_api {

GetSpotRebateHistoryRecordsResponse
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetSpotRebateHistoryRecordsResponse");
    GetSpotRebateHistoryRecordsResponse out;
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSpotRebateHistoryRecordsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::rebate::rest_api
