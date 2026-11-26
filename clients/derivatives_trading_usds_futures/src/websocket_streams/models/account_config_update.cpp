//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/account_config_update.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AccountConfigUpdate tag_invoke(boost::json::value_to_tag<AccountConfigUpdate> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountConfigUpdate");
    AccountConfigUpdate out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "ac", out.ac);
    common::detail::json::read(obj, "ai", out.ai);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountConfigUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "ac", v.ac);
    common::detail::json::write(obj, "ai", v.ai);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
