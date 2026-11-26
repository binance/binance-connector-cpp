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

struct ModifyMultipleOrdersResponseInner {
    /// Sub-order ID
    std::optional<std::int64_t> order_id;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// Status.
    std::optional<std::string> status;
    /// Client order ID.
    std::optional<std::string> client_order_id;
    /// user-defined modification identifier, only returned if provided in the request
    std::optional<std::int64_t> modify_id;
    /// Latest token price.
    std::optional<std::string> price;
    /// Original order quantity
    std::optional<std::string> orig_qty;
    /// Executed quantity
    std::optional<std::string> executed_qty;
    /// Cumulative filled quantity.
    std::optional<std::string> cum_qty;
    /// Time in force
    std::optional<std::string> time_in_force;
    /// Order type.
    std::optional<std::string> type;
    /// Whether the order is reduce-only.
    std::optional<bool> reduce_only;
    /// if Close-All
    std::optional<bool> close_position;
    /// Trading side
    std::optional<std::string> side;
    /// Position side
    std::optional<std::string> position_side;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// Stop trigger price type.
    std::optional<std::string> working_type;
    /// if conditional order trigger is protected
    std::optional<bool> price_protect;
    /// Original order type.
    std::optional<std::string> orig_type;
    /// price match mode
    std::optional<std::string> price_match;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// update time
    std::optional<std::int64_t> update_time;
    /// API response code. "000000" indicates success.
    std::optional<std::int64_t> code;
    /// Message details.
    std::optional<std::string> msg;

    bool operator==(const ModifyMultipleOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyMultipleOrdersResponseInner
tag_invoke(boost::json::value_to_tag<ModifyMultipleOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ModifyMultipleOrdersResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
