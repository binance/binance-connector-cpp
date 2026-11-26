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

namespace binance::derivatives_trading_coin_futures::rest_api {

struct AccountTradeListResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// positionId
    std::optional<std::int64_t> id;
    /// Sub-order ID
    std::optional<std::int64_t> order_id;
    /// Pair
    std::optional<std::string> pair;
    /// Trading side
    std::optional<std::string> side;
    /// Latest token price.
    std::optional<std::string> price;
    /// Quantity.
    std::optional<std::string> qty;
    /// Realized PnL.
    std::optional<std::string> realized_pnl;
    /// Margin asset.
    std::optional<std::string> margin_asset;
    /// Base asset quantity. Populated for COIN-M symbols; returns "0" for USDⓈ-M symbols.
    std::optional<std::string> base_qty;
    /// Quote asset quantity. Populated for USDⓈ-M symbols; returns "0" for COIN-M symbols.
    std::optional<std::string> quote_qty;
    /// Transaction Fee (in Crypto)
    std::optional<std::string> commission;
    /// Commission asset.
    std::optional<std::string> commission_asset;
    /// Time
    std::optional<std::int64_t> time;
    /// Position side
    std::optional<std::string> position_side;
    /// Whether the trade is a buy side for the account.
    std::optional<bool> buyer;
    /// Whether the account is maker in this trade.
    std::optional<bool> maker;

    bool operator==(const AccountTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountTradeListResponseInner tag_invoke(
    boost::json::value_to_tag<AccountTradeListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountTradeListResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
