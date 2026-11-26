//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetYieldArenaActivitiesResponseActivitiesInner {
    /// Activity ID.
    std::optional<std::int64_t> activity_id;
    /// Activity category: `AIRDROP`, `LEADERBOARD`, or `EVENT`.
    std::optional<std::string> activity_type;
    /// Activity title, localized via the `lang` header.
    std::optional<std::string> title;
    /// Activity description, localized via the `lang` header.
    std::optional<std::string> description;
    /// USD value of the reward pool.
    std::optional<std::string> reward_pool_in_usd;
    /// Reward token symbols (e.g. `["BNB"]`); may be empty.
    std::optional<std::vector<std::string>> reward_token;
    /// Web URL to the activity landing page.
    std::optional<std::string> redirect_url;
    /// Activity start time in milliseconds; may be null for activities that are immediately
    /// effective.
    std::optional<std::int64_t> start_time;
    /// Activity end time in milliseconds; may be null for activities with no fixed end.
    std::optional<std::int64_t> end_time;

    bool
    operator==(const GetYieldArenaActivitiesResponseActivitiesInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetYieldArenaActivitiesResponseActivitiesInner
tag_invoke(boost::json::value_to_tag<GetYieldArenaActivitiesResponseActivitiesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetYieldArenaActivitiesResponseActivitiesInner& v);

} // namespace binance::simple_earn::rest_api
