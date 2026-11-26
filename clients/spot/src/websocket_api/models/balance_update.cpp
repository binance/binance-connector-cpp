//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/balance_update.hpp>

namespace binance::spot::websocket_api {

BalanceUpdate tag_invoke(boost::json::value_to_tag<BalanceUpdate> /*tag*/,
                         const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BalanceUpdate");
    BalanceUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "d", out.d);
    common::detail::json::read(obj, "T", out.t_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BalanceUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "d", v.d);
    common::detail::json::write(obj, "T", v.t_uppercase);
}

} // namespace binance::spot::websocket_api
