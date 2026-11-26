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

struct FuturesAccountBalanceResponseResultInner {
    /// unique account code
    std::optional<std::string> account_alias;
    /// asset name
    std::optional<std::string> asset;
    /// Account balance.
    std::optional<std::string> balance;
    /// Available amount for withdrawal.
    std::optional<std::string> withdraw_available;
    /// wallet balance for crossed margin
    std::optional<std::string> cross_wallet_balance;
    /// total unrealized profit or loss of crossed positions
    std::optional<std::string> cross_un_pnl;
    /// available margin balance
    std::optional<std::string> available_balance;
    /// update time
    std::optional<std::int64_t> update_time;

    bool operator==(const FuturesAccountBalanceResponseResultInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT FuturesAccountBalanceResponseResultInner
tag_invoke(boost::json::value_to_tag<FuturesAccountBalanceResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FuturesAccountBalanceResponseResultInner& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
