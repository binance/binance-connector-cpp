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

struct AccountUpdateABInner {
    /// Asset
    std::optional<std::string> a;
    /// Wallet Balance
    std::optional<std::string> wb;
    /// Cross Wallet Balance
    std::optional<std::string> cw;
    /// Balance Change except PnL and Commission
    std::optional<std::string> bc;

    bool operator==(const AccountUpdateABInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountUpdateABInner
tag_invoke(boost::json::value_to_tag<AccountUpdateABInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountUpdateABInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
