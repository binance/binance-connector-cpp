//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_update_ap_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

AccountUpdateAPInner tag_invoke(boost::json::value_to_tag<AccountUpdateAPInner> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountUpdateAPInner");
    AccountUpdateAPInner out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "pa", out.pa);
    common::detail::json::read(obj, "ep", out.ep);
    common::detail::json::read(obj, "cr", out.cr);
    common::detail::json::read(obj, "up", out.up);
    common::detail::json::read(obj, "ps", out.ps);
    common::detail::json::read(obj, "bep", out.bep);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountUpdateAPInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "pa", v.pa);
    common::detail::json::write(obj, "ep", v.ep);
    common::detail::json::write(obj, "cr", v.cr);
    common::detail::json::write(obj, "up", v.up);
    common::detail::json::write(obj, "ps", v.ps);
    common::detail::json::write(obj, "bep", v.bep);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
