//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/account_config_update_ac.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

AccountConfigUpdateAc tag_invoke(boost::json::value_to_tag<AccountConfigUpdateAc> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountConfigUpdateAc");
    AccountConfigUpdateAc out;
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "l", out.l);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountConfigUpdateAc& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "l", v.l);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
