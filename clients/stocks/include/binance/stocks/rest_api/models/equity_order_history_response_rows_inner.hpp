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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct EquityOrderHistoryResponseRowsInner {
    /// Equity order id.
    std::optional<std::string> order_id;
    /// US-equity ticker.
    std::optional<std::string> symbol;
    /// Quote asset (e.g. `USDC`).
    std::optional<std::string> quote;
    /// `BUY` / `SELL`.
    std::optional<std::string> side;
    /// `MARKET` / `LIMIT`; stop-limit orders placed in the app are `STOP_LOSS_LIMIT` /
    /// `TAKE_PROFIT_LIMIT`, and stop-limit orders not placed through Binance are `STOP_LIMIT`.
    std::optional<std::string> order_type;
    /// Limit price (USD). Returned for `LIMIT` and stop-limit orders; `MARKET` orders have no limit
    /// price (`null`). `std::nullopt` when the field is absent; holds `std::nullopt` when it is
    /// `null`.
    std::optional<std::optional<std::string>> limit_price;
    /// Average fill price (USD) as reported by the broker, returned for all order types. `null`
    /// until the first fill. `std::nullopt` when the field is absent; holds `std::nullopt` when it
    /// is `null`.
    std::optional<std::optional<std::string>> avg_filled_price;
    /// Requested quantity. `null` for `BUY MARKET` (use `notional` instead).
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> qty;
    /// Requested notional. Non-null for `BUY MARKET`; `null` otherwise.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> notional;
    /// Cumulative filled quantity.
    std::optional<std::string> filled_qty;
    /// Cumulative filled notional. Populated only for `BUY MARKET`.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> filled_total;
    /// Total commission fee (USD).
    std::optional<std::string> fee;
    /// Trading session the order was placed under: `RTH` / `EXTENDED` / `24H`. `null` for `MARKET`
    /// orders. `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> session;
    /// Order lifecycle status — one of `NEW` / `ACCEPTED` / `PARTIALLY_FILLED` / `FILLED` /
    /// `CANCELED` / `EXPIRED` / `REJECTED`.
    std::optional<std::string> status;
    /// Order creation time (ms epoch).
    std::optional<std::int64_t> created_at;
    /// Last update time (ms epoch).
    std::optional<std::int64_t> updated_at;

    bool operator==(const EquityOrderHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityOrderHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<EquityOrderHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityOrderHistoryResponseRowsInner& v);

} // namespace binance::stocks::rest_api
