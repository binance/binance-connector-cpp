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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct StrategyUpdateSu {
    /// Strategy ID
    std::optional<std::int64_t> si;
    /// Strategy Type
    std::optional<std::string> st;
    /// Strategy Status
    std::optional<std::string> ss;
    /// Symbol
    std::optional<std::string> s;
    /// Update Time
    std::optional<std::int64_t> ut;
    /// opCode
    std::optional<std::int64_t> c;

    bool operator==(const StrategyUpdateSu& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT StrategyUpdateSu
tag_invoke(boost::json::value_to_tag<StrategyUpdateSu> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const StrategyUpdateSu& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
