//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/user_commission_rate_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

UserCommissionRateResponse tag_invoke(boost::json::value_to_tag<UserCommissionRateResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserCommissionRateResponse");
    UserCommissionRateResponse out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "makerCommissionRate", out.maker_commission_rate);
    common::detail::json::read(obj, "takerCommissionRate", out.taker_commission_rate);
    common::detail::json::read(obj, "rpiCommissionRate", out.rpi_commission_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserCommissionRateResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "makerCommissionRate", v.maker_commission_rate);
    common::detail::json::write(obj, "takerCommissionRate", v.taker_commission_rate);
    common::detail::json::write(obj, "rpiCommissionRate", v.rpi_commission_rate);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
