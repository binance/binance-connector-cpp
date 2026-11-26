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

struct AccountInformationResponsePositionsInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// position amount
    std::optional<std::string> position_amt;
    /// total intial margin required with the latest mark price
    std::optional<std::string> initial_margin;
    /// maintenance margin
    std::optional<std::string> maint_margin;
    /// unrealized profit or loss
    std::optional<std::string> unrealized_profit;
    /// positions margin required with the latest mark price
    std::optional<std::string> position_initial_margin;
    /// open orders intial margin required with the latest mark price
    std::optional<std::string> open_order_initial_margin;
    /// Leverage value.
    std::optional<std::string> leverage;
    /// Whether isolated margin mode is enabled.
    std::optional<bool> isolated;
    /// Position side
    std::optional<std::string> position_side;
    /// Position entry price.
    std::optional<std::string> entry_price;
    /// break-even price
    std::optional<std::string> break_even_price;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// update time
    std::optional<std::int64_t> update_time;
    /// Notional value.
    std::optional<std::string> notional_value;

    bool operator==(const AccountInformationResponsePositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountInformationResponsePositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponsePositionsInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
