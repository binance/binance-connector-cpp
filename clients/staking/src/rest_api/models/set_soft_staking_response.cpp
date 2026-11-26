//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/set_soft_staking_response.hpp>

namespace binance::staking::rest_api {

SetSoftStakingResponse tag_invoke(boost::json::value_to_tag<SetSoftStakingResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SetSoftStakingResponse");
    SetSoftStakingResponse out;
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SetSoftStakingResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::staking::rest_api
