//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_user_commission_rate_for_cm_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetUserCommissionRateForCmResponse
tag_invoke(boost::json::value_to_tag<GetUserCommissionRateForCmResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetUserCommissionRateForCmResponse");
    GetUserCommissionRateForCmResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "makerCommissionRate", out.maker_commission_rate);
    common::detail::json::read(obj, "takerCommissionRate", out.taker_commission_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUserCommissionRateForCmResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "makerCommissionRate", v.maker_commission_rate);
    common::detail::json::write(obj, "takerCommissionRate", v.taker_commission_rate);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
