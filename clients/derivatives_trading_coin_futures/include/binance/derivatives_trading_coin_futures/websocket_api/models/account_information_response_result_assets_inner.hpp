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

namespace binance::derivatives_trading_coin_futures::websocket_api {

struct AccountInformationResponseResultAssetsInner {
    /// asset name
    std::optional<std::string> asset;
    /// total wallet balance
    std::optional<std::string> wallet_balance;
    /// unrealized profit or loss
    std::optional<std::string> unrealized_profit;
    /// margin balance
    std::optional<std::string> margin_balance;
    /// maintenance margin
    std::optional<std::string> maint_margin;
    /// total intial margin required with the latest mark price
    std::optional<std::string> initial_margin;
    /// positions margin required with the latest mark price
    std::optional<std::string> position_initial_margin;
    /// open orders intial margin required with the latest mark price
    std::optional<std::string> open_order_initial_margin;
    /// maximum amount for transfer out
    std::optional<std::string> max_withdraw_amount;
    /// wallet balance for crossed margin
    std::optional<std::string> cross_wallet_balance;
    /// total unrealized profit or loss of crossed positions
    std::optional<std::string> cross_un_pnl;
    /// available margin balance
    std::optional<std::string> available_balance;
    /// update time
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationResponseResultAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountInformationResponseResultAssetsInner
tag_invoke(boost::json::value_to_tag<AccountInformationResponseResultAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponseResultAssetsInner& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
