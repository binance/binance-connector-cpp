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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct ListenKeyExpired {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;

    bool operator==(const ListenKeyExpired& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ListenKeyExpired
tag_invoke(boost::json::value_to_tag<ListenKeyExpired> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const ListenKeyExpired& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
