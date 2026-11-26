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
#include <binance/derivatives_trading_usds_futures/websocket_api/models/account_information_response_result_assets_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/account_information_response_result_positions_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct AccountInformationResponseResult {
    /// account commission tier
    std::optional<std::int64_t> fee_tier;
    /// if can trade
    std::optional<bool> can_trade;
    /// if can transfer in asset
    std::optional<bool> can_deposit;
    /// if can transfer out asset
    std::optional<bool> can_withdraw;
    /// reserved property, please ignore
    std::optional<std::int64_t> update_time;
    std::optional<bool> multi_assets_margin;
    std::optional<std::int64_t> trade_group_id;
    /// total initial margin required with current mark price (useless with isolated positions),
    /// only for USDT asset
    std::optional<std::string> total_initial_margin;
    /// the sum of USD value of all cross positions maintenance margin
    std::optional<std::string> total_maint_margin;
    /// total wallet balance, only for USDT asset
    std::optional<std::string> total_wallet_balance;
    /// total unrealized profit, only for USDT asset
    std::optional<std::string> total_unrealized_profit;
    /// total margin balance, only for USDT asset
    std::optional<std::string> total_margin_balance;
    /// initial margin required for positions with current mark price, only for USDT asset
    std::optional<std::string> total_position_initial_margin;
    /// initial margin required for open orders with current mark price, only for USDT asset
    std::optional<std::string> total_open_order_initial_margin;
    /// crossed wallet balance, only for USDT asset
    std::optional<std::string> total_cross_wallet_balance;
    /// unrealized profit of crossed positions, only for USDT asset
    std::optional<std::string> total_cross_un_pnl;
    /// available balance, only for USDT asset
    std::optional<std::string> available_balance;
    /// maximum amount for transfer out, only for USDT asset
    std::optional<std::string> max_withdraw_amount;
    std::optional<std::vector<AccountInformationResponseResultAssetsInner>> assets;
    /// positions of all symbols in the market are returned
    std::optional<std::vector<AccountInformationResponseResultPositionsInner>> positions;

    bool operator==(const AccountInformationResponseResult& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationResponseResult
tag_invoke(boost::json::value_to_tag<AccountInformationResponseResult> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponseResult& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
