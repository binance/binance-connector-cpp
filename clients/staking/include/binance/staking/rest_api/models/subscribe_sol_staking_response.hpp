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

struct SubscribeSolStakingResponse {
    std::optional<bool> success;
    std::optional<std::string> bnsol_amount;
    std::optional<std::int64_t> purchase_id;
    /// SOL amount per 1 BNSOL
    std::optional<std::string> exchange_rate;

    bool operator==(const SubscribeSolStakingResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT SubscribeSolStakingResponse tag_invoke(
    boost::json::value_to_tag<SubscribeSolStakingResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const SubscribeSolStakingResponse& v);

} // namespace binance::staking::rest_api
