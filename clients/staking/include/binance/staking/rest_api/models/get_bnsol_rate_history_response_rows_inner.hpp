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
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response_rows_inner_boost_rewards_inner.hpp>

namespace binance::staking::rest_api {

struct GetBnsolRateHistoryResponseRowsInner {
    /// BNSOL APR
    std::optional<std::string> annual_percentage_rate;
    /// SOL amount per 1 BNSOL
    std::optional<std::string> exchange_rate;
    std::optional<std::vector<GetBnsolRateHistoryResponseRowsInnerBoostRewardsInner>> boost_rewards;
    std::optional<std::int64_t> time;

    bool operator==(const GetBnsolRateHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetBnsolRateHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetBnsolRateHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetBnsolRateHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
