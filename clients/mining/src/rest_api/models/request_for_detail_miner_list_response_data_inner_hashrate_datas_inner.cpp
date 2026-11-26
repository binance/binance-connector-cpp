//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/request_for_detail_miner_list_response_data_inner_hashrate_datas_inner.hpp>

namespace binance::mining::rest_api {

RequestForDetailMinerListResponseDataInnerHashrateDatasInner tag_invoke(
    boost::json::value_to_tag<RequestForDetailMinerListResponseDataInnerHashrateDatasInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "RequestForDetailMinerListResponseDataInnerHashrateDatasInner");
    RequestForDetailMinerListResponseDataInnerHashrateDatasInner out;
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "hashrate", out.hashrate);
    common::detail::json::read(obj, "reject", out.reject);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RequestForDetailMinerListResponseDataInnerHashrateDatasInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "hashrate", v.hashrate);
    common::detail::json::write(obj, "reject", v.reject);
}

} // namespace binance::mining::rest_api
