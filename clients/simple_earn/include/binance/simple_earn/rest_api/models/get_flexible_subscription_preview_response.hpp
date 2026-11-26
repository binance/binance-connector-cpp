//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetFlexibleSubscriptionPreviewResponse {
    std::optional<std::string> total_amount;
    std::optional<std::string> reward_asset;
    std::optional<std::string> air_drop_asset;
    std::optional<std::string> est_daily_bonus_rewards;
    std::optional<std::string> est_daily_real_time_rewards;
    std::optional<std::string> est_daily_airdrop_rewards;

    bool operator==(const GetFlexibleSubscriptionPreviewResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetFlexibleSubscriptionPreviewResponse
tag_invoke(boost::json::value_to_tag<GetFlexibleSubscriptionPreviewResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleSubscriptionPreviewResponse& v);

} // namespace binance::simple_earn::rest_api
