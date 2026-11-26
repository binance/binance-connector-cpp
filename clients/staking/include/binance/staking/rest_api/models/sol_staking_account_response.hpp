//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct SolStakingAccountResponse {
    std::optional<std::string> bnsol_amount;
    std::optional<std::string> holding_in_sol;
    std::optional<std::string> thirty_days_profit_in_sol;

    bool operator==(const SolStakingAccountResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT SolStakingAccountResponse tag_invoke(
    boost::json::value_to_tag<SolStakingAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const SolStakingAccountResponse& v);

} // namespace binance::staking::rest_api
