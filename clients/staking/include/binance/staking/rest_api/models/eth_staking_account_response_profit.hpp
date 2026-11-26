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

struct EthStakingAccountResponseProfit {
    std::optional<std::string> amount_from_wbeth;
    std::optional<std::string> amount_from_beth;

    bool operator==(const EthStakingAccountResponseProfit& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT EthStakingAccountResponseProfit
tag_invoke(boost::json::value_to_tag<EthStakingAccountResponseProfit> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const EthStakingAccountResponseProfit& v);

} // namespace binance::staking::rest_api
