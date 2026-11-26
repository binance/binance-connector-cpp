//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response_data.hpp>

namespace binance::rebate::rest_api {

GetSpotRebateHistoryRecordsResponseData
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSpotRebateHistoryRecordsResponseData");
    GetSpotRebateHistoryRecordsResponseData out;
    common::detail::json::read(obj, "page", out.page);
    common::detail::json::read(obj, "totalRecords", out.total_records);
    common::detail::json::read(obj, "totalPageNum", out.total_page_num);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSpotRebateHistoryRecordsResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "page", v.page);
    common::detail::json::write(obj, "totalRecords", v.total_records);
    common::detail::json::write(obj, "totalPageNum", v.total_page_num);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::rebate::rest_api
