//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/strategy_update.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

StrategyUpdate tag_invoke(boost::json::value_to_tag<StrategyUpdate> /*tag*/,
                          const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StrategyUpdate");
    StrategyUpdate out;
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "su", out.su);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StrategyUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "su", v.su);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
