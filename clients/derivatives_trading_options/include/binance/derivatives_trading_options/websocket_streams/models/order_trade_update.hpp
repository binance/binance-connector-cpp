//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/order_trade_update_o.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct OrderTradeUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    std::optional<OrderTradeUpdateO> o;

    bool operator==(const OrderTradeUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OrderTradeUpdate
tag_invoke(boost::json::value_to_tag<OrderTradeUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const OrderTradeUpdate& v);

} // namespace binance::derivatives_trading_options::websocket_streams
