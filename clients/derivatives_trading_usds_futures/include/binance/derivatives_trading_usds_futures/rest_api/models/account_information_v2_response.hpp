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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v2_response_assets_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v2_response_positions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AccountInformationV2Response {
    /// Account commission tier.
    std::optional<std::int64_t> fee_tier;
    /// Whether fee discount is enabled.
    std::optional<bool> fee_burn;
    /// Whether trading is enabled.
    std::optional<bool> can_trade;
    /// Whether transfer-in is enabled.
    std::optional<bool> can_deposit;
    /// Whether transfer-out is enabled.
    std::optional<bool> can_withdraw;
    /// Reserved field, ignore.
    std::optional<std::int64_t> update_time;
    /// Whether multi-assets mode is enabled.
    std::optional<bool> multi_assets_margin;
    /// Trade group identifier.
    std::optional<std::int64_t> trade_group_id;
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
    std::optional<std::vector<AccountInformationV2ResponseAssetsInner>> assets;
    /// Position details for symbols. One-way mode returns BOTH; hedge mode returns LONG/SHORT.
    std::optional<std::vector<AccountInformationV2ResponsePositionsInner>> positions;

    bool operator==(const AccountInformationV2Response& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV2Response tag_invoke(
    boost::json::value_to_tag<AccountInformationV2Response> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV2Response& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
