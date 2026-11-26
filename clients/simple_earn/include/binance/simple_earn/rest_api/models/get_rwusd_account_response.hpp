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

struct GetRwusdAccountResponse {
    std::optional<std::string> rwusd_amount;
    std::optional<std::string> total_profit;

    bool operator==(const GetRwusdAccountResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetRwusdAccountResponse tag_invoke(
    boost::json::value_to_tag<GetRwusdAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetRwusdAccountResponse& v);

} // namespace binance::simple_earn::rest_api
