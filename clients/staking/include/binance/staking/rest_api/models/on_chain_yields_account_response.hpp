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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct OnChainYieldsAccountResponse {
    std::optional<std::string> total_amount_in_btc;
    std::optional<std::string> total_amount_in_usdt;
    std::optional<std::string> total_flexible_amount_in_btc;
    std::optional<std::string> total_flexible_amount_in_usdt;
    std::optional<std::string> total_locked_in_btc;
    std::optional<std::string> total_locked_in_usdt;

    bool operator==(const OnChainYieldsAccountResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT OnChainYieldsAccountResponse tag_invoke(
    boost::json::value_to_tag<OnChainYieldsAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const OnChainYieldsAccountResponse& v);

} // namespace binance::staking::rest_api
