//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_current_position_mode_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetCmCurrentPositionModeResponse
tag_invoke(boost::json::value_to_tag<GetCmCurrentPositionModeResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCmCurrentPositionModeResponse");
    GetCmCurrentPositionModeResponse out;
    common::detail::json::read(obj, "dualSidePosition", out.dual_side_position);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCmCurrentPositionModeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "dualSidePosition", v.dual_side_position);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
