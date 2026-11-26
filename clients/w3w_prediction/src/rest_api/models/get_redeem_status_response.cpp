//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_redeem_status_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetRedeemStatusResponse tag_invoke(boost::json::value_to_tag<GetRedeemStatusResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetRedeemStatusResponse");
    GetRedeemStatusResponse out;
    common::detail::json::read(obj, "txHash", out.tx_hash);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRedeemStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "txHash", v.tx_hash);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::w3w_prediction::rest_api
