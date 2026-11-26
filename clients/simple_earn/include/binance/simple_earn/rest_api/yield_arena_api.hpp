//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response.hpp>

namespace binance::simple_earn::rest_api {

struct GetYieldArenaActivitiesParams {
    /// Locale tag for `title` and `description` (e.g. `en`, `zh-CN`, `pt-BR`). Default: `en`. If
    /// the value is missing, malformed, or has no translation configured, content is returned in
    /// `en`.
    std::optional<std::string> lang = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SIMPLE_EARN_EXPORT YieldArenaApi {
public:
    explicit YieldArenaApi(std::shared_ptr<common::RestClient> client);

    /// Get Yield Arena Activities (USER_DATA)
    ///
    /// GET /sapi/v1/earn/arena/activities.
    ///
    /// Get the list of Earn Yield Arena giveaway activities currently available to the user.
    ///
    /// Weight(IP): 150
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-simple-earn/api/rest-api/yield-arena#get-yield-arena-activities
    [[nodiscard]] common::RestApiResponse<GetYieldArenaActivitiesResponse>
    get_yield_arena_activities(const GetYieldArenaActivitiesParams& params = {}) const;

    /// Asynchronous `get_yield_arena_activities()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetYieldArenaActivitiesResponse>)`.
    template <class CompletionToken>
    auto async_get_yield_arena_activities(const GetYieldArenaActivitiesParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<GetYieldArenaActivitiesResponse>(
            client_, get_yield_arena_activities_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_yield_arena_activities_request(const GetYieldArenaActivitiesParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::simple_earn::rest_api
