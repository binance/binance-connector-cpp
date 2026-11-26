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

#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_order_detail_response_trades_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionOrderDetailResponse {
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
    /// Time in force. Always `DAY`.
    std::optional<std::string> time_in_force;
    /// Commission.
    std::optional<std::string> commission;
    /// Platform fee.
    std::optional<std::string> platform_fee;
    /// SEC fee. Charged on sell orders only; `0` for buy orders.
    std::optional<std::string> sec;
    /// FINRA TAF. Charged on sell orders only; `0` for buy orders.
    std::optional<std::string> taf;
    /// FINRA CAT fee.
    std::optional<std::string> cat;
    /// Options Regulatory Fee (ORF).
    std::optional<std::string> orf;
    /// OCC clearing fee.
    std::optional<std::string> occ;
    /// Cumulative filled amount, same as `filledTotal` (average fill price × filled quantity ×
    /// multiplier), excluding fees.
    std::optional<std::string> total;
    /// Fully filled time (ms).
    std::optional<std::int64_t> filled_at;
    /// Cancel time (ms). Returned only for canceled orders.
    std::optional<std::int64_t> canceled_at;
    /// Expiry time (ms). Returned only for expired orders.
    std::optional<std::int64_t> expired_at;
    /// Millisecond timestamp of 14:00 ET on the settlement date. Returned only for sell orders with
    /// fills.
    std::optional<std::int64_t> settlement_date;
    /// Fills of this order, sorted by execution time in descending order. Individual fills carry no
    /// fee; see the order-level `fee` and itemized fees.
    std::optional<std::vector<OptionOrderDetailResponseTradesInner>> trades;

    bool operator==(const OptionOrderDetailResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionOrderDetailResponse tag_invoke(
    boost::json::value_to_tag<OptionOrderDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionOrderDetailResponse& v);

} // namespace binance::stock_options::rest_api
