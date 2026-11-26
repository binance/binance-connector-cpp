//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct AccountUpdateAPInner {
    /// Symbol
    std::optional<std::string> s;
    /// Position Amount
    std::optional<std::string> pa;
    /// Entry Price
    std::optional<std::string> ep;
    /// (Pre-fee) Accumulated Realized
    std::optional<std::string> cr;
    /// Unrealized PnL
    std::optional<std::string> up;
    /// Position Side
    std::optional<std::string> ps;
    /// Breakeven Price
    std::optional<std::string> bep;

    bool operator==(const AccountUpdateAPInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountUpdateAPInner
tag_invoke(boost::json::value_to_tag<AccountUpdateAPInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountUpdateAPInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
