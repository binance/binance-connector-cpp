//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_current_position_mode_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetUmCurrentPositionModeResponse
tag_invoke(boost::json::value_to_tag<GetUmCurrentPositionModeResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetUmCurrentPositionModeResponse");
    GetUmCurrentPositionModeResponse out;
    common::detail::json::read(obj, "dualSidePosition", out.dual_side_position);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUmCurrentPositionModeResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "dualSidePosition", v.dual_side_position);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
