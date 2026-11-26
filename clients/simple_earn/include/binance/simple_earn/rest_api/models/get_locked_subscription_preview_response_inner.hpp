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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetLockedSubscriptionPreviewResponseInner {
    std::optional<std::string> reward_asset;
    std::optional<std::string> total_reward_amt;
    std::optional<std::string> extra_reward_asset;
    std::optional<std::string> est_total_extra_reward_amt;
    std::optional<std::string> boost_reward_asset;
    std::optional<std::string> est_daily_reward_amt;
    std::optional<std::string> next_pay;
    std::optional<std::int64_t> next_pay_date;
    std::optional<std::int64_t> value_date;
    std::optional<std::int64_t> rewards_end_date;
    std::optional<std::int64_t> deliver_date;
    std::optional<std::int64_t> next_subscription_date;

    bool operator==(const GetLockedSubscriptionPreviewResponseInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetLockedSubscriptionPreviewResponseInner
tag_invoke(boost::json::value_to_tag<GetLockedSubscriptionPreviewResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetLockedSubscriptionPreviewResponseInner& v);

} // namespace binance::simple_earn::rest_api
