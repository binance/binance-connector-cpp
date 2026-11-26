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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct OrderStatusResponseResult {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> order_id;
    /// Present only for orders that belong to an order list.
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> client_order_id;
    std::optional<std::string> price;
    std::optional<std::string> orig_qty;
    std::optional<std::string> executed_qty;
    /// Always present. Zero if the order type does not use `quoteOrderQty`.
    std::optional<std::string> orig_quote_order_qty;
    std::optional<std::string> cummulative_quote_qty;
    std::optional<std::string> status;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    std::optional<std::string> side;
    /// Always present. Zero if the order type does not use `stopPrice`.
    std::optional<std::string> stop_price;
    /// Present only if `trailingDelta` was set on the order.
    std::optional<std::int64_t> trailing_delta;
    /// Present only if `trailingDelta` was set on the order.
    std::optional<std::int64_t> trailing_time;
    /// Always present. Zero for non-iceberg orders.
    std::optional<std::string> iceberg_qty;
    /// Order placement time.
    std::optional<std::int64_t> time;
    /// Time of the last update to the order.
    std::optional<std::int64_t> update_time;
    std::optional<bool> is_working;
    std::optional<std::int64_t> working_time;
    /// Present only if `strategyId` was set on the order.
    std::optional<std::int64_t> strategy_id;
    /// Present only if `strategyType` was set on the order.
    std::optional<std::int64_t> strategy_type;
    std::optional<std::string> self_trade_prevention_mode;
    /// Present only if the order expired due to STP.
    std::optional<std::int64_t> prevented_match_id;
    /// Present only if the order expired due to STP.
    std::optional<std::string> prevented_quantity;
    /// Field that determines whether order used SOR.
    std::optional<bool> used_sor;
    /// Determines whether the order is being filled by the SOR or by the order book.
    std::optional<std::string> working_floor;
    /// Price peg type. Only for pegged orders.
    std::optional<std::string> peg_price_type;
    /// Price peg offset type. Only for pegged orders, if requested.
    std::optional<std::string> peg_offset_type;
    /// Price peg offset value. Only for pegged orders, if requested.
    std::optional<std::int64_t> peg_offset_value;
    /// Current price order is pegged at. Only for pegged orders, once determined.
    std::optional<std::string> pegged_price;
    /// Cause of the order's expiration. Appears when an order has expired.
    std::optional<std::string> expiry_reason;

    bool operator==(const OrderStatusResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderStatusResponseResult tag_invoke(
    boost::json::value_to_tag<OrderStatusResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderStatusResponseResult& v);

} // namespace binance::spot::websocket_api
