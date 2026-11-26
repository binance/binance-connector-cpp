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
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/conditional_order_trade_update_so.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct ConditionalOrderTradeUpdate {
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Event business unit
    std::optional<std::string> fs;
    std::optional<ConditionalOrderTradeUpdateSo> so;

    bool operator==(const ConditionalOrderTradeUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ConditionalOrderTradeUpdate tag_invoke(
    boost::json::value_to_tag<ConditionalOrderTradeUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ConditionalOrderTradeUpdate& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
