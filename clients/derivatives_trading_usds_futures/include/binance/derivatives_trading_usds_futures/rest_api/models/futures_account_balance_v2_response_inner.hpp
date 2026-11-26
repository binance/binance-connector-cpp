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

struct FuturesAccountBalanceV2ResponseInner {
    /// Unique account alias.
    std::optional<std::string> account_alias;
    /// Asset name.
    std::optional<std::string> asset;
    /// Wallet balance.
    std::optional<std::string> balance;
    /// Cross wallet balance.
    std::optional<std::string> cross_wallet_balance;
    /// Unrealized PnL of cross positions.
    std::optional<std::string> cross_un_pnl;
    /// Available balance.
    std::optional<std::string> available_balance;
    /// Maximum transferable/withdrawable amount.
    std::optional<std::string> max_withdraw_amount;
    /// Whether the asset can be used as margin in multi-assets mode.
    std::optional<bool> margin_available;
    /// Last update time in milliseconds.
    std::optional<std::int64_t> update_time;

    bool operator==(const FuturesAccountBalanceV2ResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT FuturesAccountBalanceV2ResponseInner
tag_invoke(boost::json::value_to_tag<FuturesAccountBalanceV2ResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesAccountBalanceV2ResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
