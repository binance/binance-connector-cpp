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

struct GetBfusdQuotaDetailsResponseFastRedemptionQuota {
    std::optional<std::string> left_quota;
    std::optional<std::string> minimum;
    std::optional<std::string> fee;
    std::optional<std::string> free_quota;

    bool
    operator==(const GetBfusdQuotaDetailsResponseFastRedemptionQuota& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdQuotaDetailsResponseFastRedemptionQuota
tag_invoke(boost::json::value_to_tag<GetBfusdQuotaDetailsResponseFastRedemptionQuota> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetBfusdQuotaDetailsResponseFastRedemptionQuota& v);

} // namespace binance::simple_earn::rest_api
