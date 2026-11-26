//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response_profit.hpp>

namespace binance::staking::rest_api {

EthStakingAccountResponseProfit
tag_invoke(boost::json::value_to_tag<EthStakingAccountResponseProfit> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EthStakingAccountResponseProfit");
    EthStakingAccountResponseProfit out;
    common::detail::json::read(obj, "amountFromWBETH", out.amount_from_wbeth);
    common::detail::json::read(obj, "amountFromBETH", out.amount_from_beth);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EthStakingAccountResponseProfit& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amountFromWBETH", v.amount_from_wbeth);
    common::detail::json::write(obj, "amountFromBETH", v.amount_from_beth);
}

} // namespace binance::staking::rest_api
