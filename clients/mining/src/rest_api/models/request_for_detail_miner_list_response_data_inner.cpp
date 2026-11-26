//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/request_for_detail_miner_list_response_data_inner.hpp>

namespace binance::mining::rest_api {

RequestForDetailMinerListResponseDataInner
tag_invoke(boost::json::value_to_tag<RequestForDetailMinerListResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "RequestForDetailMinerListResponseDataInner");
    RequestForDetailMinerListResponseDataInner out;
    common::detail::json::read(obj, "workerName", out.worker_name);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "hashrateDatas", out.hashrate_datas);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RequestForDetailMinerListResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "workerName", v.worker_name);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "hashrateDatas", v.hashrate_datas);
}

} // namespace binance::mining::rest_api
