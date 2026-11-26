//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/request_for_miner_list_response_data.hpp>

namespace binance::mining::rest_api {

RequestForMinerListResponseData
tag_invoke(boost::json::value_to_tag<RequestForMinerListResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RequestForMinerListResponseData");
    RequestForMinerListResponseData out;
    common::detail::json::read(obj, "workerDatas", out.worker_datas);
    common::detail::json::read(obj, "totalNum", out.total_num);
    common::detail::json::read(obj, "pageSize", out.page_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RequestForMinerListResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "workerDatas", v.worker_datas);
    common::detail::json::write(obj, "totalNum", v.total_num);
    common::detail::json::write(obj, "pageSize", v.page_size);
}

} // namespace binance::mining::rest_api
