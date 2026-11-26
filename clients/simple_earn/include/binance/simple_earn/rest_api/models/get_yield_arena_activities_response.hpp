//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response_activities_inner.hpp>

namespace binance::simple_earn::rest_api {

struct GetYieldArenaActivitiesResponse {
    std::optional<std::vector<GetYieldArenaActivitiesResponseActivitiesInner>> activities;

    bool operator==(const GetYieldArenaActivitiesResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetYieldArenaActivitiesResponse
tag_invoke(boost::json::value_to_tag<GetYieldArenaActivitiesResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetYieldArenaActivitiesResponse& v);

} // namespace binance::simple_earn::rest_api
