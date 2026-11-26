//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/account_update_a.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AccountUpdateA tag_invoke(boost::json::value_to_tag<AccountUpdateA> /*tag*/,
                          const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountUpdateA");
    AccountUpdateA out;
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "B", out.b_uppercase);
    common::detail::json::read(obj, "P", out.p_uppercase);
    common::detail::json::read(obj, "S", out.s_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountUpdateA& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "B", v.b_uppercase);
    common::detail::json::write(obj, "P", v.p_uppercase);
    common::detail::json::write(obj, "S", v.s_uppercase);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
