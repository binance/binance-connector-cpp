//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/set_on_chain_yields_locked_product_redeem_option_response.hpp>

namespace binance::staking::rest_api {

SetOnChainYieldsLockedProductRedeemOptionResponse
tag_invoke(boost::json::value_to_tag<SetOnChainYieldsLockedProductRedeemOptionResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "SetOnChainYieldsLockedProductRedeemOptionResponse");
    SetOnChainYieldsLockedProductRedeemOptionResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SetOnChainYieldsLockedProductRedeemOptionResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::staking::rest_api
