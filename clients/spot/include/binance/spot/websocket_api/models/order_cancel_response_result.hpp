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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/open_orders_cancel_all_response_result_inner_order_reports_inner.hpp>
#include <binance/spot/websocket_api/models/open_orders_cancel_all_response_result_inner_orders_inner.hpp>

namespace binance::spot::websocket_api {

struct OrderCancelResponseResult {
    std::optional<std::string> symbol;
    /// clientOrderId that was canceled
    std::optional<std::string> orig_client_order_id;
    std::optional<std::int64_t> order_id;
    /// set only for legs of an order list
    std::optional<std::int64_t> order_list_id;
    /// newClientOrderId from request
    std::optional<std::string> client_order_id;
    std::optional<std::int64_t> transact_time;
    std::optional<std::string> price;
    std::optional<std::string> orig_qty;
    std::optional<std::string> executed_qty;
    std::optional<std::string> orig_quote_order_qty;
    std::optional<std::string> cummulative_quote_qty;
    std::optional<std::string> status;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    std::optional<std::string> side;
    /// present only if stopPrice set for the order
    std::optional<std::string> stop_price;
    /// present only if trailingDelta set for the order
    std::optional<std::int64_t> trailing_delta;
    /// present only if icebergQty set for the order
    std::optional<std::string> iceberg_qty;
    /// present only if strategyId set for the order
    std::optional<std::int64_t> strategy_id;
    /// present only if strategyType set for the order
    std::optional<std::int64_t> strategy_type;
    std::optional<std::string> self_trade_prevention_mode;
    /// Appears only if the order expired due to STP.
    std::optional<std::int64_t> prevented_match_id;
    /// Order quantity that expired due to STP.
    std::optional<std::string> prevented_quantity;
    /// Time when the trailing order is now active and tracking price changes.
    std::optional<std::int64_t> trailing_time;
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
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::vector<OpenOrdersCancelAllResponseResultInnerOrdersInner>> orders;
    /// order list order's status format is the same as for individual orders.
    std::optional<std::vector<OpenOrdersCancelAllResponseResultInnerOrderReportsInner>>
        order_reports;

    bool operator==(const OrderCancelResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderCancelResponseResult tag_invoke(
    boost::json::value_to_tag<OrderCancelResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderCancelResponseResult& v);

} // namespace binance::spot::websocket_api
