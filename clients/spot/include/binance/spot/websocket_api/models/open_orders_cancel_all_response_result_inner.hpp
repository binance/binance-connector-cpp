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

struct OpenOrdersCancelAllResponseResultInner {
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> contingency_type;
    std::optional<std::string> list_status_type;
    std::optional<std::string> list_order_status;
    std::optional<std::string> list_client_order_id;
    std::optional<std::int64_t> transaction_time;
    std::optional<std::string> symbol;
    std::optional<std::vector<OpenOrdersCancelAllResponseResultInnerOrdersInner>> orders;
    std::optional<std::vector<OpenOrdersCancelAllResponseResultInnerOrderReportsInner>>
        order_reports;
    std::optional<std::string> orig_client_order_id;
    std::optional<std::int64_t> order_id;
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
    /// Appears for STOP_LOSS, TAKE_PROFIT, STOP_LOSS_LIMIT, and TAKE_PROFIT_LIMIT orders.
    std::optional<std::string> stop_price;
    /// Delta price change required before order activation.
    std::optional<std::int64_t> trailing_delta;
    /// Time when the trailing order is now active and tracking price changes.
    std::optional<std::int64_t> trailing_time;
    /// Appears only if the parameter icebergQty was sent in the request.
    std::optional<std::string> iceberg_qty;
    /// Appears only if the strategyId parameter was provided upon order placement.
    std::optional<std::int64_t> strategy_id;
    /// Appears only if the strategyType parameter was provided upon order placement.
    std::optional<std::int64_t> strategy_type;
    std::optional<std::string> self_trade_prevention_mode;
    /// Appears only if the order expired due to STP.
    std::optional<std::int64_t> prevented_match_id;
    /// Order quantity that expired due to STP.
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

    bool operator==(const OpenOrdersCancelAllResponseResultInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OpenOrdersCancelAllResponseResultInner
tag_invoke(boost::json::value_to_tag<OpenOrdersCancelAllResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OpenOrdersCancelAllResponseResultInner& v);

} // namespace binance::spot::websocket_api
