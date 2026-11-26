//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_position_by_token_response.hpp>

namespace binance::w3w_prediction::rest_api {

GetPositionByTokenResponse tag_invoke(boost::json::value_to_tag<GetPositionByTokenResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetPositionByTokenResponse");
    GetPositionByTokenResponse out;
    common::detail::json::read(obj, "position", out.position);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPositionByTokenResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "position", v.position);
}

} // namespace binance::w3w_prediction::rest_api
