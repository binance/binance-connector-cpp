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

struct CurrentOpenOptionOrdersResponseInner {
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
    /// Quote asset.
    std::optional<std::string> quote_asset;
    /// `BUY` / `SELL`.
    std::optional<std::string> side;
    /// Order type: `LIMIT`; `MARKET` for orders placed by the broker's automatic liquidation on the
    /// expiration date.
    std::optional<std::string> order_type;
    /// Limit price (premium per share).
    std::optional<std::string> limit_price;
    /// Order quantity (contracts).
    std::optional<std::string> qty;
    /// Cumulative filled quantity (contracts).
    std::optional<std::string> filled_qty;
    /// Cumulative filled amount.
    std::optional<std::string> filled_notional;
    /// Amount locked from the wallet when the order was placed (a snapshot, not updated after fills
    /// or cancellation): premium plus fees for buy-to-open and for buy-to-close of a covered call;
    /// for buy-to-close of a cash-secured put, only the shortfall remaining after the released
    /// collateral (usually `0`); the collateral for sell-to-open (number of shares for a covered
    /// call, cash for a cash-secured put); `0` for sell-to-close. Not returned for broker automatic
    /// liquidation orders.
    std::optional<std::string> total_cost;
    /// Fill progress percentage (0–100).
    std::optional<std::string> filled_percent;
    /// Order status: `NEW` / `PENDING_NEW` / `ACCEPTED` / `PARTIALLY_FILLED` / `PENDING_CANCEL` /
    /// `PENDING_REPLACE`.
    std::optional<std::string> status;
    /// Creation time (ms).
    std::optional<std::int64_t> created_at;
    /// Last update time (ms).
    std::optional<std::int64_t> updated_at;

    bool operator==(const CurrentOpenOptionOrdersResponseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT CurrentOpenOptionOrdersResponseInner
tag_invoke(boost::json::value_to_tag<CurrentOpenOptionOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const CurrentOpenOptionOrdersResponseInner& v);

} // namespace binance::stock_options::rest_api
