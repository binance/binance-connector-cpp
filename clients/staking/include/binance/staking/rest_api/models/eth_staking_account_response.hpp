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
#include <binance/staking/rest_api/models/eth_staking_account_response_holdings.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response_profit.hpp>

namespace binance::staking::rest_api {

struct EthStakingAccountResponse {
    std::optional<std::string> holding_in_eth;
    std::optional<EthStakingAccountResponseHoldings> holdings;
    std::optional<std::string> thirty_days_profit_in_eth;
    std::optional<EthStakingAccountResponseProfit> profit;

    bool operator==(const EthStakingAccountResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT EthStakingAccountResponse tag_invoke(
    boost::json::value_to_tag<EthStakingAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const EthStakingAccountResponse& v);

} // namespace binance::staking::rest_api
