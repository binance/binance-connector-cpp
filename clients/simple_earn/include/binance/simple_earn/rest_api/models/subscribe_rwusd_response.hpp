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

struct SubscribeRwusdResponse {
    std::optional<bool> success;
    std::optional<std::string> rwusd_amount;

    bool operator==(const SubscribeRwusdResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT SubscribeRwusdResponse
tag_invoke(boost::json::value_to_tag<SubscribeRwusdResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv, const SubscribeRwusdResponse& v);

} // namespace binance::simple_earn::rest_api
