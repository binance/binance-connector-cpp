//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/yield_arena_api.hpp>

namespace binance::simple_earn::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

YieldArenaApi::YieldArenaApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest YieldArenaApi::get_yield_arena_activities_request(
    const GetYieldArenaActivitiesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/earn/arena/activities";
    common::detail::json::set_header(req.headers, "lang", params.lang);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetYieldArenaActivitiesResponse>
YieldArenaApi::get_yield_arena_activities(const GetYieldArenaActivitiesParams& params) const {
    return common::send<GetYieldArenaActivitiesResponse>(
        *client_, get_yield_arena_activities_request(params));
}

} // namespace binance::simple_earn::rest_api
