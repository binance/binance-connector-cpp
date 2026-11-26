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

struct GetWbethRewardsHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    /// Estimated rewards accrued within WBETH
    std::optional<std::string> amount_in_eth;
    /// WBETH holding balance
    std::optional<std::string> holding;
    std::optional<std::string> holding_in_eth;
    std::optional<std::string> annual_percentage_rate;

    bool operator==(const GetWbethRewardsHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetWbethRewardsHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetWbethRewardsHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetWbethRewardsHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
