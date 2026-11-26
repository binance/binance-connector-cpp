//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/listen_key_expired.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

ListenKeyExpired tag_invoke(boost::json::value_to_tag<ListenKeyExpired> /*tag*/,
                            const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListenKeyExpired");
    ListenKeyExpired out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListenKeyExpired& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
