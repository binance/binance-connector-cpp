//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/algo_order_update.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

AlgoOrderUpdate tag_invoke(boost::json::value_to_tag<AlgoOrderUpdate> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AlgoOrderUpdate");
    AlgoOrderUpdate out;
    common::detail::json::read(obj, "T", out.t_uppercase);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "fs", out.fs);
    common::detail::json::read(obj, "ao", out.ao);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AlgoOrderUpdate& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "T", v.t_uppercase);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "fs", v.fs);
    common::detail::json::write(obj, "ao", v.ao);
}

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
