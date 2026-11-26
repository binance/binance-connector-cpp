//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_list_response_data_config_details_inner.hpp>

namespace binance::mining::rest_api {

HashrateResaleListResponseDataConfigDetailsInner
tag_invoke(boost::json::value_to_tag<HashrateResaleListResponseDataConfigDetailsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "HashrateResaleListResponseDataConfigDetailsInner");
    HashrateResaleListResponseDataConfigDetailsInner out;
    common::detail::json::read(obj, "configId", out.config_id);
    common::detail::json::read(obj, "poolUsername", out.pool_username);
    common::detail::json::read(obj, "toPoolUsername", out.to_pool_username);
    common::detail::json::read(obj, "algoName", out.algo_name);
    common::detail::json::read(obj, "hashRate", out.hash_rate);
    common::detail::json::read(obj, "startDay", out.start_day);
    common::detail::json::read(obj, "endDay", out.end_day);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "type", out.type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const HashrateResaleListResponseDataConfigDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "configId", v.config_id);
    common::detail::json::write(obj, "poolUsername", v.pool_username);
    common::detail::json::write(obj, "toPoolUsername", v.to_pool_username);
    common::detail::json::write(obj, "algoName", v.algo_name);
    common::detail::json::write(obj, "hashRate", v.hash_rate);
    common::detail::json::write(obj, "startDay", v.start_day);
    common::detail::json::write(obj, "endDay", v.end_day);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "type", v.type);
}

} // namespace binance::mining::rest_api
