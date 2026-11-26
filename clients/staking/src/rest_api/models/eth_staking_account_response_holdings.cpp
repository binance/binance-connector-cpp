//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response_holdings.hpp>

namespace binance::staking::rest_api {

EthStakingAccountResponseHoldings
tag_invoke(boost::json::value_to_tag<EthStakingAccountResponseHoldings> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EthStakingAccountResponseHoldings");
    EthStakingAccountResponseHoldings out;
    common::detail::json::read(obj, "wbethAmount", out.wbeth_amount);
    common::detail::json::read(obj, "bethAmount", out.beth_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EthStakingAccountResponseHoldings& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "wbethAmount", v.wbeth_amount);
    common::detail::json::write(obj, "bethAmount", v.beth_amount);
}

} // namespace binance::staking::rest_api
