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
#include <binance/derivatives_trading_portfolio_margin/websocket_streams/models/algo_order_update_ao.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct AlgoOrderUpdate {
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Futures segment, `UM` for USDS-M Futures, `CM` for Coin-M Futures
    std::optional<std::string> fs;
    std::optional<AlgoOrderUpdateAo> ao;

    bool operator==(const AlgoOrderUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AlgoOrderUpdate
tag_invoke(boost::json::value_to_tag<AlgoOrderUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AlgoOrderUpdate& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
