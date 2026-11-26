//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/change_initial_leverage_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

ChangeInitialLeverageResponse
tag_invoke(boost::json::value_to_tag<ChangeInitialLeverageResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ChangeInitialLeverageResponse");
    ChangeInitialLeverageResponse out;
    common::detail::json::read(obj, "leverage", out.leverage);
    common::detail::json::read(obj, "maxNotionalValue", out.max_notional_value);
    common::detail::json::read(obj, "symbol", out.symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ChangeInitialLeverageResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "leverage", v.leverage);
    common::detail::json::write(obj, "maxNotionalValue", v.max_notional_value);
    common::detail::json::write(obj, "symbol", v.symbol);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
