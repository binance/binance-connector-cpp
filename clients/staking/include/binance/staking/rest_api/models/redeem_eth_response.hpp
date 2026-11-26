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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct RedeemEthResponse {
    std::optional<bool> success;
    std::optional<std::string> eth_amount;
    std::optional<std::int64_t> redeem_id;
    std::optional<std::string> conversion_ratio;
    std::optional<std::int64_t> arrival_time;

    bool operator==(const RedeemEthResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT RedeemEthResponse
tag_invoke(boost::json::value_to_tag<RedeemEthResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const RedeemEthResponse& v);

} // namespace binance::staking::rest_api
