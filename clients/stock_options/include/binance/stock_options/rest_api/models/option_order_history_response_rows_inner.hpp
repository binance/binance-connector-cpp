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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionOrderHistoryResponseRowsInner {
    /// Option order ID.
    std::optional<std::string> order_id;
    /// Client order ID.
    std::optional<std::string> client_order_id;
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// OCC root symbol. Differs from `underlyingSymbol` for contracts adjusted by a corporate
    /// action (e.g. `GOOG1`).
    std::optional<std::string> root_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Premium multiplier. Order cost = price × quantity × multiplier.
    std::optional<std::string> multiplier;
    /// Position intent: `BUY_TO_OPEN` / `SELL_TO_CLOSE` / `SELL_TO_OPEN` / `BUY_TO_CLOSE`.
    std::optional<std::string> position_intent;
    /// `true` if the order was initiated by the broker's automatic liquidation rather than by the
    /// user.
    std::optional<bool> auto_liquidation;
    /// Quote asset (named `quoteAsset` in Current Open Option Orders).
    std::optional<std::string> quote;
    /// `BUY` / `SELL`.
    std::optional<std::string> side;
    /// Order type: `LIMIT`; `MARKET` for orders placed by the broker's automatic liquidation on the
    /// expiration date.
    std::optional<std::string> order_type;
    /// Limit price (premium per share). Returned as reported by the broker regardless of order
    /// type; not returned for `MARKET` orders, which have no limit price.
    std::optional<std::string> limit_price;
    /// Average fill price (premium per share) as reported by the broker, returned for all order
    /// types. Not returned if the order has no fills.
    std::optional<std::string> avg_filled_price;
    /// Order quantity (contracts).
    std::optional<std::string> qty;
    /// Cumulative filled quantity (contracts).
    std::optional<std::string> filled_qty;
    /// Cumulative filled amount.
    std::optional<std::string> filled_total;
    /// Cumulative fees = `commission` + `sec` + `taf` + `cat` + `orf` + `occ` (excluding
    /// `platformFee`). Fees are returned at the order level only; individual fills carry no fee.
    std::optional<std::string> fee;
    /// Order status, e.g. `FILLED` / `PARTIALLY_FILLED` / `CANCELED` / `EXPIRED` / `REJECTED`.
    std::optional<std::string> status;
    /// Creation time (ms).
    std::optional<std::int64_t> created_at;
    /// Last update time (ms).
    std::optional<std::int64_t> updated_at;

    bool operator==(const OptionOrderHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionOrderHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<OptionOrderHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionOrderHistoryResponseRowsInner& v);

} // namespace binance::stock_options::rest_api
