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
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner_tier_annual_percentage_rate.hpp>

namespace binance::simple_earn::rest_api {

struct GetFlexibleProductPositionResponseRowsInner {
    std::optional<std::string> total_amount;
    std::optional<GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate>
        tier_annual_percentage_rate;
    std::optional<std::string> latest_annual_percentage_rate;
    std::optional<std::string> yesterday_airdrop_percentage_rate;
    std::optional<std::string> asset;
    std::optional<std::string> air_drop_asset;
    std::optional<bool> can_redeem;
    std::optional<std::string> collateral_amount;
    std::optional<std::string> product_id;
    std::optional<std::string> yesterday_real_time_rewards;
    std::optional<std::string> cumulative_bonus_rewards;
    std::optional<std::string> cumulative_real_time_rewards;
    std::optional<std::string> cumulative_total_rewards;
    std::optional<bool> auto_subscribe;

    bool operator==(const GetFlexibleProductPositionResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetFlexibleProductPositionResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleProductPositionResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleProductPositionResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
