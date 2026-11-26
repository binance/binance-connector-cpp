//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetOtcReservedBalancesResponse
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetOtcReservedBalancesResponse");
    GetOtcReservedBalancesResponse out;
    common::detail::json::read(obj, "balances", out.balances);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOtcReservedBalancesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "balances", v.balances);
}

} // namespace binance::w3w_prediction::rest_api
