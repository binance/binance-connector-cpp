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
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner_tier_annual_percentage_rate.hpp>

namespace binance::simple_earn::rest_api {

struct GetSimpleEarnFlexibleProductListResponseRowsInner {
    std::optional<std::string> asset;
    std::optional<std::string> latest_annual_percentage_rate;
    std::optional<GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate>
        tier_annual_percentage_rate;
    std::optional<std::string> air_drop_percentage_rate;
    std::optional<bool> can_purchase;
    std::optional<bool> can_redeem;
    std::optional<bool> is_sold_out;
    std::optional<bool> hot;
    std::optional<std::string> min_purchase_amount;
    std::optional<std::string> product_id;
    std::optional<std::int64_t> subscription_start_time;
    /// PREHEATING,PURCHASING,END
    std::optional<std::string> status;

    bool
    operator==(const GetSimpleEarnFlexibleProductListResponseRowsInner& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetSimpleEarnFlexibleProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSimpleEarnFlexibleProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSimpleEarnFlexibleProductListResponseRowsInner& v);

} // namespace binance::simple_earn::rest_api
