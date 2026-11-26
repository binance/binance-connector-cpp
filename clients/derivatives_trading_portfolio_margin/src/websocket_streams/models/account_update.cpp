//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_update.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

AccountUpdate tag_invoke(boost::json::value_to_tag<AccountUpdate> /*tag*/,
                         const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountUpdate");
    AccountUpdate out;
    common::detail::json::read(obj, "fs", out.fs);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "a", out.a);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "fs", v.fs);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "a", v.a);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
