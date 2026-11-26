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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v3_response_assets_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v3_response_positions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AccountInformationV3Response {
    /// Total initial margin requirement. USDT only in single-asset mode; the sum of USD value of
    /// all cross positions/open order initial margin in multi-assets mode.
    std::optional<std::string> total_initial_margin;
    /// Total maintenance margin requirement. USDT only in single-asset mode; the sum of USD value
    /// of all cross positions maintenance margin in multi-assets mode.
    std::optional<std::string> total_maint_margin;
    /// Total wallet balance. USDT only in single-asset mode; USD-denominated in multi-assets mode.
    std::optional<std::string> total_wallet_balance;
    /// Total unrealized profit. USDT only in single-asset mode; USD-denominated in multi-assets
    /// mode.
    std::optional<std::string> total_unrealized_profit;
    /// Total margin balance. USDT only in single-asset mode; USD-denominated in multi-assets mode.
    std::optional<std::string> total_margin_balance;
    /// Initial margin required for positions. USDT only in single-asset mode; the sum of USD value
    /// of all cross positions initial margin in multi-assets mode.
    std::optional<std::string> total_position_initial_margin;
    /// Initial margin required for open orders. USDT only in single-asset mode; USD-denominated in
    /// multi-assets mode.
    std::optional<std::string> total_open_order_initial_margin;
    /// Cross wallet balance. USDT only in single-asset mode; USD-denominated in multi-assets mode.
    std::optional<std::string> total_cross_wallet_balance;
    /// Unrealized PnL for cross positions. USDT only in single-asset mode; USD-denominated in
    /// multi-assets mode.
    std::optional<std::string> total_cross_un_pnl;
    /// Available balance. USDT only in single-asset mode; USD-denominated in multi-assets mode.
    std::optional<std::string> available_balance;
    /// Maximum transferable/withdrawable amount. USDT only in single-asset mode; a maximum virtual
    /// USD amount in multi-assets mode.
    std::optional<std::string> max_withdraw_amount;
    /// Asset-level account details.
    std::optional<std::vector<AccountInformationV3ResponseAssetsInner>> assets;
    /// Position details for symbols.
    std::optional<std::vector<AccountInformationV3ResponsePositionsInner>> positions;

    bool operator==(const AccountInformationV3Response& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV3Response tag_invoke(
    boost::json::value_to_tag<AccountInformationV3Response> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV3Response& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
