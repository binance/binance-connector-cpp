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

struct GetBfusdQuotaDetailsResponseStandardRedemptionQuota {
    std::optional<std::string> left_quota;
    std::optional<std::string> minimum;
    std::optional<std::string> fee;
    std::optional<std::int64_t> redeem_period;

    bool operator==(const GetBfusdQuotaDetailsResponseStandardRedemptionQuota& /*other*/) const =
        default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdQuotaDetailsResponseStandardRedemptionQuota
tag_invoke(boost::json::value_to_tag<GetBfusdQuotaDetailsResponseStandardRedemptionQuota> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetBfusdQuotaDetailsResponseStandardRedemptionQuota& v);

} // namespace binance::simple_earn::rest_api
