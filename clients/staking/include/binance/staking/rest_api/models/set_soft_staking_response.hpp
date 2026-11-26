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

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct SetSoftStakingResponse {
    std::optional<bool> success;

    bool operator==(const SetSoftStakingResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT SetSoftStakingResponse
tag_invoke(boost::json::value_to_tag<SetSoftStakingResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const SetSoftStakingResponse& v);

} // namespace binance::staking::rest_api
