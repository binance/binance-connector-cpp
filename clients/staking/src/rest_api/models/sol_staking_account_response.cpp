//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/sol_staking_account_response.hpp>

namespace binance::staking::rest_api {

SolStakingAccountResponse tag_invoke(boost::json::value_to_tag<SolStakingAccountResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SolStakingAccountResponse");
    SolStakingAccountResponse out;
    common::detail::json::read(obj, "bnsolAmount", out.bnsol_amount);
    common::detail::json::read(obj, "holdingInSOL", out.holding_in_sol);
    common::detail::json::read(obj, "thirtyDaysProfitInSOL", out.thirty_days_profit_in_sol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SolStakingAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bnsolAmount", v.bnsol_amount);
    common::detail::json::write(obj, "holdingInSOL", v.holding_in_sol);
    common::detail::json::write(obj, "thirtyDaysProfitInSOL", v.thirty_days_profit_in_sol);
}

} // namespace binance::staking::rest_api
