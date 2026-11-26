//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response.hpp>

namespace binance::simple_earn::rest_api {

GetYieldArenaActivitiesResponse
tag_invoke(boost::json::value_to_tag<GetYieldArenaActivitiesResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetYieldArenaActivitiesResponse");
    GetYieldArenaActivitiesResponse out;
    common::detail::json::read(obj, "activities", out.activities);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetYieldArenaActivitiesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "activities", v.activities);
}

} // namespace binance::simple_earn::rest_api
