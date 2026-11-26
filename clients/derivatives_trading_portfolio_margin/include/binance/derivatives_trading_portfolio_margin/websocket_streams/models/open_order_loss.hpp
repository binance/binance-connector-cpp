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

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct OpenOrderLoss {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Aggregated account-level open order loss, in USD
    std::optional<std::string> o;

    bool operator==(const OpenOrderLoss& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT OpenOrderLoss
tag_invoke(boost::json::value_to_tag<OpenOrderLoss> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const OpenOrderLoss& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
