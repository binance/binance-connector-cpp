//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/redeem_sol_response.hpp>

namespace binance::staking::rest_api {

RedeemSolResponse tag_invoke(boost::json::value_to_tag<RedeemSolResponse> /*tag*/,
                             const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RedeemSolResponse");
    RedeemSolResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "solAmount", out.sol_amount);
    common::detail::json::read(obj, "redeemId", out.redeem_id);
    common::detail::json::read(obj, "exchangeRate", out.exchange_rate);
    common::detail::json::read(obj, "arrivalTime", out.arrival_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RedeemSolResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "solAmount", v.sol_amount);
    common::detail::json::write(obj, "redeemId", v.redeem_id);
    common::detail::json::write(obj, "exchangeRate", v.exchange_rate);
    common::detail::json::write(obj, "arrivalTime", v.arrival_time);
}

} // namespace binance::staking::rest_api
