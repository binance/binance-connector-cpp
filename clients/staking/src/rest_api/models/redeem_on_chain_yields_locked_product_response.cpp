//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/redeem_on_chain_yields_locked_product_response.hpp>

namespace binance::staking::rest_api {

RedeemOnChainYieldsLockedProductResponse
tag_invoke(boost::json::value_to_tag<RedeemOnChainYieldsLockedProductResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "RedeemOnChainYieldsLockedProductResponse");
    RedeemOnChainYieldsLockedProductResponse out;
    common::detail::json::read(obj, "redeemId", out.redeem_id);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RedeemOnChainYieldsLockedProductResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "redeemId", v.redeem_id);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::staking::rest_api
