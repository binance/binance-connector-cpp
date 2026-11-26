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

struct GetBfusdRewardsHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    std::optional<std::string> reward_asset;
    std::optional<std::string> rewards_amount;
    std::optional<std::string> bfusd_position;
    std::optional<std::string> annual_percentage_rate;

    bool operator==(const GetBfusdRewardsHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBfusdRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetBfusdRewardsHistoryResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
