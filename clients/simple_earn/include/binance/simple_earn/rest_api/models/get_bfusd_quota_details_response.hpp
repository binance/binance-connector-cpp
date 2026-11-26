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
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_fast_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_standard_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_subscription_quota.hpp>

namespace binance::simple_earn::rest_api {

struct GetBfusdQuotaDetailsResponse {
    std::optional<GetBfusdQuotaDetailsResponseSubscriptionQuota> subscription_quota;
    std::optional<GetBfusdQuotaDetailsResponseFastRedemptionQuota> fast_redemption_quota;
    std::optional<GetBfusdQuotaDetailsResponseStandardRedemptionQuota> standard_redemption_quota;

    bool operator==(const GetBfusdQuotaDetailsResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdQuotaDetailsResponse tag_invoke(
    boost::json::value_to_tag<GetBfusdQuotaDetailsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetBfusdQuotaDetailsResponse& v);

} // namespace binance::simple_earn::rest_api
