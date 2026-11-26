//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/subscribe_sol_staking_response.hpp>

namespace binance::staking::rest_api {

SubscribeSolStakingResponse
tag_invoke(boost::json::value_to_tag<SubscribeSolStakingResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubscribeSolStakingResponse");
    SubscribeSolStakingResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "bnsolAmount", out.bnsol_amount);
    common::detail::json::read(obj, "purchaseId", out.purchase_id);
    common::detail::json::read(obj, "exchangeRate", out.exchange_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubscribeSolStakingResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "bnsolAmount", v.bnsol_amount);
    common::detail::json::write(obj, "purchaseId", v.purchase_id);
    common::detail::json::write(obj, "exchangeRate", v.exchange_rate);
}

} // namespace binance::staking::rest_api
