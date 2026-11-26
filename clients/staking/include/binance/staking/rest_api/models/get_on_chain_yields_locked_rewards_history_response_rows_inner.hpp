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

struct GetOnChainYieldsLockedRewardsHistoryResponseRowsInner {
    std::optional<std::string> position_id;
    std::optional<std::int64_t> time;
    std::optional<std::string> asset;
    std::optional<std::string> lock_period;
    std::optional<std::string> amount;

    bool operator==(const GetOnChainYieldsLockedRewardsHistoryResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedRewardsHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
