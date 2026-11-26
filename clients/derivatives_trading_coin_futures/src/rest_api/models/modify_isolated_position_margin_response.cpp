//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_isolated_position_margin_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

ModifyIsolatedPositionMarginResponse
tag_invoke(boost::json::value_to_tag<ModifyIsolatedPositionMarginResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ModifyIsolatedPositionMarginResponse");
    ModifyIsolatedPositionMarginResponse out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    common::detail::json::read(obj, "type", out.type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ModifyIsolatedPositionMarginResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
    common::detail::json::write(obj, "type", v.type);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
