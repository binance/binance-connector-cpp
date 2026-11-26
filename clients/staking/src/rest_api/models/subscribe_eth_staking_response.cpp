//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/subscribe_eth_staking_response.hpp>

namespace binance::staking::rest_api {

SubscribeEthStakingResponse
tag_invoke(boost::json::value_to_tag<SubscribeEthStakingResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SubscribeEthStakingResponse");
    SubscribeEthStakingResponse out;
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "wbethAmount", out.wbeth_amount);
    common::detail::json::read(obj, "purchaseId", out.purchase_id);
    common::detail::json::read(obj, "conversionRatio", out.conversion_ratio);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubscribeEthStakingResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "wbethAmount", v.wbeth_amount);
    common::detail::json::write(obj, "purchaseId", v.purchase_id);
    common::detail::json::write(obj, "conversionRatio", v.conversion_ratio);
}

} // namespace binance::staking::rest_api
