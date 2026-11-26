//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/account_update.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

AccountUpdate tag_invoke(boost::json::value_to_tag<AccountUpdate> /*tag*/,
                         const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountUpdate");
    AccountUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "eq", out.eq);
    common::detail::json::read(obj, "aeq", out.aeq);
    common::detail::json::read(obj, "b", out.b);
    common::detail::json::read(obj, "m", out.m);
    common::detail::json::read(obj, "u", out.u);
    common::detail::json::read(obj, "i", out.i);
    common::detail::json::read(obj, "M", out.m_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "eq", v.eq);
    common::detail::json::write(obj, "aeq", v.aeq);
    common::detail::json::write(obj, "b", v.b);
    common::detail::json::write(obj, "m", v.m);
    common::detail::json::write(obj, "u", v.u);
    common::detail::json::write(obj, "i", v.i);
    common::detail::json::write(obj, "M", v.m_uppercase);
}

} // namespace binance::derivatives_trading_options::websocket_streams
