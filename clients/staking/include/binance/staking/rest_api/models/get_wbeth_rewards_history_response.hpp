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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetWbethRewardsHistoryResponse {
    std::optional<std::string> est_rewards_in_eth;
    std::optional<std::vector<GetWbethRewardsHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetWbethRewardsHistoryResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetWbethRewardsHistoryResponse
tag_invoke(boost::json::value_to_tag<GetWbethRewardsHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetWbethRewardsHistoryResponse& v);

} // namespace binance::staking::rest_api
