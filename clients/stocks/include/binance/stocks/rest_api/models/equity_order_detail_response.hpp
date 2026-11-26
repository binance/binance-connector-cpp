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

#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/equity_order_detail_response_trades_inner.hpp>

namespace binance::stocks::rest_api {

/// Top-level fields mirror an order row from `/order/history` (orderId, symbol, quote, side,
/// orderType, limitPrice, avgFilledPrice, qty, notional, filledQty, filledTotal, fee, session,
/// status, createdAt, updatedAt), plus a `trades` array. `clientOrderId` is present only in Order
/// Detail, not in Order History.
struct EquityOrderDetailResponse {
    /// Equity order id.
    std::optional<std::string> order_id;
    /// Client-supplied order id. Present only in Order Detail, not in Order History.
    std::optional<std::string> client_order_id;
    /// US-equity ticker.
    std::optional<std::string> symbol;
    /// Quote asset.
    std::optional<std::string> quote;
    /// `BUY` / `SELL`.
    std::optional<std::string> side;
    /// `MARKET` / `LIMIT`.
    std::optional<std::string> order_type;
    /// Limit price (USD). Non-null for `LIMIT`, `null` for `MARKET`.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> limit_price;
    /// Average fill price (USD). Only present when the order has at least one fill.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> avg_filled_price;
    /// Requested quantity.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> qty;
    /// Requested notional.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> notional;
    /// Cumulative filled quantity.
    std::optional<std::string> filled_qty;
    /// Cumulative filled notional.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> filled_total;
    /// Total commission fee (USD).
    std::optional<std::string> fee;
    /// Trading session.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> session;
    /// Order lifecycle status.
    std::optional<std::string> status;
    /// Order creation time (ms epoch).
    std::optional<std::int64_t> created_at;
    /// Last update time (ms epoch).
    std::optional<std::int64_t> updated_at;
    /// Trade executions for this order, most recent first. Empty array when no fills.
    std::optional<std::vector<EquityOrderDetailResponseTradesInner>> trades;

    bool operator==(const EquityOrderDetailResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityOrderDetailResponse tag_invoke(
    boost::json::value_to_tag<EquityOrderDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityOrderDetailResponse& v);

} // namespace binance::stocks::rest_api
