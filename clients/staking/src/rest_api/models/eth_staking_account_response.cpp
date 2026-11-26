//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response.hpp>

namespace binance::staking::rest_api {

EthStakingAccountResponse tag_invoke(boost::json::value_to_tag<EthStakingAccountResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EthStakingAccountResponse");
    EthStakingAccountResponse out;
    common::detail::json::read(obj, "holdingInETH", out.holding_in_eth);
    common::detail::json::read(obj, "holdings", out.holdings);
    common::detail::json::read(obj, "thirtyDaysProfitInETH", out.thirty_days_profit_in_eth);
    common::detail::json::read(obj, "profit", out.profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EthStakingAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "holdingInETH", v.holding_in_eth);
    common::detail::json::write(obj, "holdings", v.holdings);
    common::detail::json::write(obj, "thirtyDaysProfitInETH", v.thirty_days_profit_in_eth);
    common::detail::json::write(obj, "profit", v.profit);
}

} // namespace binance::staking::rest_api
