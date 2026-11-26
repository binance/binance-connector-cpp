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

struct QueryCurrentOpenOrderResponse {
    /// Average execution price
    std::optional<std::string> avg_price;
    /// Client order ID.
    std::optional<std::string> client_order_id;
    /// Cumulative base asset amount.
    std::optional<std::string> cum_base;
    /// Executed quantity
    std::optional<std::string> executed_qty;
    /// Sub-order ID
    std::optional<std::int64_t> order_id;
    /// Original order quantity
    std::optional<std::string> orig_qty;
    /// Original order type.
    std::optional<std::string> orig_type;
    /// Latest token price.
    std::optional<std::string> price;
    /// Whether the order is reduce-only.
    std::optional<bool> reduce_only;
    /// Trading side
    std::optional<std::string> side;
    /// Position side
    std::optional<std::string> position_side;
    /// Status.
    std::optional<std::string> status;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// if Close-All
    std::optional<bool> close_position;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// Time
    std::optional<std::int64_t> time;
    /// Time in force
    std::optional<std::string> time_in_force;
    /// Order type.
    std::optional<std::string> type;
    /// activation price, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> activate_price;
    /// callback rate, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> price_rate;
    /// update time
    std::optional<std::int64_t> update_time;
    /// Stop trigger price type.
    std::optional<std::string> working_type;
    /// if conditional order trigger is protected
    std::optional<bool> price_protect;
    /// price match mode
    std::optional<std::string> price_match;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;

    bool operator==(const QueryCurrentOpenOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT QueryCurrentOpenOrderResponse tag_invoke(
    boost::json::value_to_tag<QueryCurrentOpenOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCurrentOpenOrderResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
