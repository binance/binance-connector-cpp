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
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/grid_update_gu.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct GridUpdate {
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    std::optional<GridUpdateGu> gu;

    bool operator==(const GridUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GridUpdate
tag_invoke(boost::json::value_to_tag<GridUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GridUpdate& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
