//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/statistic_list_response.hpp>

namespace binance::mining::rest_api {

StatisticListResponse tag_invoke(boost::json::value_to_tag<StatisticListResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StatisticListResponse");
    StatisticListResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StatisticListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::mining::rest_api
