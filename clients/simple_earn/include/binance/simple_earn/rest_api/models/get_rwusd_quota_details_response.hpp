//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_fast_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_standard_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_subscription_quota.hpp>

namespace binance::simple_earn::rest_api {

struct GetRwusdQuotaDetailsResponse {
    std::optional<GetRwusdQuotaDetailsResponseSubscriptionQuota> subscription_quota;
    std::optional<GetRwusdQuotaDetailsResponseFastRedemptionQuota> fast_redemption_quota;
    std::optional<GetRwusdQuotaDetailsResponseStandardRedemptionQuota> standard_redemption_quota;
    std::optional<bool> subscribe_enable;
    std::optional<bool> redeem_enable;

    bool operator==(const GetRwusdQuotaDetailsResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetRwusdQuotaDetailsResponse tag_invoke(
    boost::json::value_to_tag<GetRwusdQuotaDetailsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetRwusdQuotaDetailsResponse& v);

} // namespace binance::simple_earn::rest_api
