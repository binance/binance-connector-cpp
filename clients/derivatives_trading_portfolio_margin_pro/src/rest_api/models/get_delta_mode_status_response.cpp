//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_delta_mode_status_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetDeltaModeStatusResponse tag_invoke(boost::json::value_to_tag<GetDeltaModeStatusResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetDeltaModeStatusResponse");
    GetDeltaModeStatusResponse out;
    common::detail::json::read(obj, "deltaEnabled", out.delta_enabled);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDeltaModeStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "deltaEnabled", v.delta_enabled);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
