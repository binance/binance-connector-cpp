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

struct GetSolRedemptionHistoryResponseRowsInner {
    std::optional<std::int64_t> time;
    std::optional<std::int64_t> arrival_time;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> distribute_asset;
    std::optional<std::string> distribute_amount;
    std::optional<std::string> exchange_rate;
    std::optional<std::string> status;

    bool operator==(const GetSolRedemptionHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetSolRedemptionHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetSolRedemptionHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetSolRedemptionHistoryResponseRowsInner& v);

} // namespace binance::staking::rest_api
