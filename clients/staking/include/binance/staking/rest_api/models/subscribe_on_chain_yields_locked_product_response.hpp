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

struct SubscribeOnChainYieldsLockedProductResponse {
    std::optional<std::int64_t> purchase_id;
    std::optional<std::string> position_id;
    std::optional<std::string> amount;
    std::optional<bool> success;

    bool operator==(const SubscribeOnChainYieldsLockedProductResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT SubscribeOnChainYieldsLockedProductResponse
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const SubscribeOnChainYieldsLockedProductResponse& v);

} // namespace binance::staking::rest_api
