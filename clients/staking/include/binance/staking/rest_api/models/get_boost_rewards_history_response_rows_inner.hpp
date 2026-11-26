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

struct GetBoostRewardsHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    std::optional<std::string> token;
    std::optional<std::string> amount;
    /// Display if the type is "DISTRIBUTE"
    std::optional<std::string> bnsol_holding;
    /// Display if the type is "CLAIM"
    std::optional<std::string> status;

    bool operator==(const GetBoostRewardsHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetBoostRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBoostRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetBoostRewardsHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
