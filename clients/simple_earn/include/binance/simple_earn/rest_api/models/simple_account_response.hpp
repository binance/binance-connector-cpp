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

struct SimpleAccountResponse {
    std::optional<std::string> total_amount_in_btc;
    std::optional<std::string> total_amount_in_usdt;
    std::optional<std::string> total_flexible_amount_in_btc;
    std::optional<std::string> total_flexible_amount_in_usdt;
    std::optional<std::string> total_locked_in_btc;
    std::optional<std::string> total_locked_in_usdt;

    bool operator==(const SimpleAccountResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT SimpleAccountResponse
tag_invoke(boost::json::value_to_tag<SimpleAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv, const SimpleAccountResponse& v);

} // namespace binance::simple_earn::rest_api
