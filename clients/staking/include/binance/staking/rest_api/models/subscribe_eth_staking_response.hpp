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

struct SubscribeEthStakingResponse {
    std::optional<bool> success;
    std::optional<std::string> wbeth_amount;
    std::optional<std::int64_t> purchase_id;
    /// ETH amount per 1 WBETH
    std::optional<std::string> conversion_ratio;

    bool operator==(const SubscribeEthStakingResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT SubscribeEthStakingResponse tag_invoke(
    boost::json::value_to_tag<SubscribeEthStakingResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const SubscribeEthStakingResponse& v);

} // namespace binance::staking::rest_api
