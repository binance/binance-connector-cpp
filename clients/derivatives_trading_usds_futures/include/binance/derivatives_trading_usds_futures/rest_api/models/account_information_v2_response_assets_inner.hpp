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

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AccountInformationV2ResponseAssetsInner {
    /// Asset name.
    std::optional<std::string> asset;
    /// Wallet balance.
    std::optional<std::string> wallet_balance;
    /// Unrealized profit.
    std::optional<std::string> unrealized_profit;
    /// Margin balance.
    std::optional<std::string> margin_balance;
    /// Maintenance margin requirement.
    std::optional<std::string> maint_margin;
    /// Total initial margin requirement.
    std::optional<std::string> initial_margin;
    /// Initial margin required for positions.
    std::optional<std::string> position_initial_margin;
    /// Initial margin required for open orders.
    std::optional<std::string> open_order_initial_margin;
    /// Cross wallet balance.
    std::optional<std::string> cross_wallet_balance;
    /// Unrealized PnL for cross positions.
    std::optional<std::string> cross_un_pnl;
    /// Available balance.
    std::optional<std::string> available_balance;
    /// Maximum transferable/withdrawable amount.
    std::optional<std::string> max_withdraw_amount;
    /// Whether the asset can be used as margin in multi-assets mode.
    std::optional<bool> margin_available;
    /// Last update time in milliseconds.
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationV2ResponseAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV2ResponseAssetsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponseAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV2ResponseAssetsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
