//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/account_config_update_ai.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

AccountConfigUpdateAi tag_invoke(boost::json::value_to_tag<AccountConfigUpdateAi> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountConfigUpdateAi");
    AccountConfigUpdateAi out;
    common::detail::json::read(obj, "j", out.j);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountConfigUpdateAi& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "j", v.j);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
