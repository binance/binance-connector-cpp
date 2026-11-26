//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/request_for_miner_list_response_data_worker_datas_inner.hpp>

namespace binance::mining::rest_api {

RequestForMinerListResponseDataWorkerDatasInner
tag_invoke(boost::json::value_to_tag<RequestForMinerListResponseDataWorkerDatasInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "RequestForMinerListResponseDataWorkerDatasInner");
    RequestForMinerListResponseDataWorkerDatasInner out;
    common::detail::json::read(obj, "workerId", out.worker_id);
    common::detail::json::read(obj, "workerName", out.worker_name);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "hashRate", out.hash_rate);
    common::detail::json::read(obj, "dayHashRate", out.day_hash_rate);
    common::detail::json::read(obj, "rejectRate", out.reject_rate);
    common::detail::json::read(obj, "lastShareTime", out.last_share_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RequestForMinerListResponseDataWorkerDatasInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "workerId", v.worker_id);
    common::detail::json::write(obj, "workerName", v.worker_name);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "hashRate", v.hash_rate);
    common::detail::json::write(obj, "dayHashRate", v.day_hash_rate);
    common::detail::json::write(obj, "rejectRate", v.reject_rate);
    common::detail::json::write(obj, "lastShareTime", v.last_share_time);
}

} // namespace binance::mining::rest_api
