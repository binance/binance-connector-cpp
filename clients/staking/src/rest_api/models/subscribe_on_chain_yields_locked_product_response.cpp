//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/subscribe_on_chain_yields_locked_product_response.hpp>

namespace binance::staking::rest_api {

SubscribeOnChainYieldsLockedProductResponse
tag_invoke(boost::json::value_to_tag<SubscribeOnChainYieldsLockedProductResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "SubscribeOnChainYieldsLockedProductResponse");
    SubscribeOnChainYieldsLockedProductResponse out;
    common::detail::json::read(obj, "purchaseId", out.purchase_id);
    common::detail::json::read(obj, "positionId", out.position_id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SubscribeOnChainYieldsLockedProductResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "purchaseId", v.purchase_id);
    common::detail::json::write(obj, "positionId", v.position_id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::staking::rest_api
