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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct AccountInformationV2ResponseResultAssetsInner {
    /// asset name
    std::optional<std::string> asset;
    /// wallet balance
    std::optional<std::string> wallet_balance;
    /// unrealized profit
    std::optional<std::string> unrealized_profit;
    /// margin balance
    std::optional<std::string> margin_balance;
    /// maintenance margin required
    std::optional<std::string> maint_margin;
    /// total initial margin required with current mark price
    std::optional<std::string> initial_margin;
    /// initial margin required for positions with current mark price
    std::optional<std::string> position_initial_margin;
    /// initial margin required for open orders with current mark price
    std::optional<std::string> open_order_initial_margin;
    /// crossed wallet balance
    std::optional<std::string> cross_wallet_balance;
    /// unrealized profit of crossed positions
    std::optional<std::string> cross_un_pnl;
    /// available balance, only for USDT asset
    std::optional<std::string> available_balance;
    /// maximum amount for transfer out, only for USDT asset
    std::optional<std::string> max_withdraw_amount;
    /// whether the asset can be used as margin in Multi-Assets mode
    std::optional<bool> margin_available;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationV2ResponseResultAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV2ResponseResultAssetsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseResultAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV2ResponseResultAssetsInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
