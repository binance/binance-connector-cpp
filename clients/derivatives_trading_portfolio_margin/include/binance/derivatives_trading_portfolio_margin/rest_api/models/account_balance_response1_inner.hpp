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

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct AccountBalanceResponse1Inner {
    /// asset name
    std::optional<std::string> asset;
    /// Total Wallet Balance.
    std::optional<std::string> total_wallet_balance;
    /// Cross Margin Asset. Equal to crossMarginFree + crossMarginLocked.
    std::optional<std::string> cross_margin_asset;
    /// Cross Margin Borrowed.
    std::optional<std::string> cross_margin_borrowed;
    /// Cross Margin Free.
    std::optional<std::string> cross_margin_free;
    /// Cross Margin Interest.
    std::optional<std::string> cross_margin_interest;
    /// Cross Margin Locked.
    std::optional<std::string> cross_margin_locked;
    /// Um Wallet Balance.
    std::optional<std::string> um_wallet_balance;
    /// Um Unrealized PNL.
    std::optional<std::string> um_unrealized_pnl;
    /// Cm Wallet Balance.
    std::optional<std::string> cm_wallet_balance;
    /// Cm Unrealized PNL.
    std::optional<std::string> cm_unrealized_pnl;
    /// last update time
    std::optional<std::int64_t> update_time;
    /// negative balance amount
    std::optional<std::string> negative_balance;

    bool operator==(const AccountBalanceResponse1Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountBalanceResponse1Inner tag_invoke(
    boost::json::value_to_tag<AccountBalanceResponse1Inner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountBalanceResponse1Inner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
