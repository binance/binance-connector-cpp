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

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/strategy_update_su.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct StrategyUpdate {
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    std::optional<StrategyUpdateSu> su;

    bool operator==(const StrategyUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT StrategyUpdate
tag_invoke(boost::json::value_to_tag<StrategyUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const StrategyUpdate& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
