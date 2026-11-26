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

#include <binance/common/decimal.hpp>
#include <binance/stock_options/export.hpp>

namespace binance::stock_options::websocket_streams {

struct OrderReportV2StreamResponse {
    /// Event type, always `"orderReportV2"`.
    std::optional<std::string> e;
    /// Push time (ms).
    std::optional<std::int64_t> e_uppercase;
    /// `ORDER_UPDATE`: the order is open (new, accepted by the broker, partially filled, cancel
    /// pending, etc.). `ORDER_TERMINAL`: the order reached a terminal state and will not be pushed
    /// again.
    std::optional<std::string> x;
    /// Order ID. REST field `orderId`.
    std::optional<std::string> i;
    /// Client order ID. REST field `clientOrderId`.
    std::optional<std::string> ci;
    /// Broker-side asset ID. Not needed by callers.
    std::optional<std::string> ai;
    /// Internal asset code (e.g. `EQ_SPCX`). Not needed by callers; read the underlying from `u`.
    /// May be `null` for expiration-day auto-liquidation orders. `std::nullopt` when the field is
    /// absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> b;
    /// Quote asset; `USDC` for options. REST field `quoteAsset`. May be `null` for expiration-day
    /// auto-liquidation orders. `std::nullopt` when the field is absent; holds `std::nullopt` when
    /// it is `null`.
    std::optional<std::optional<std::string>> q;
    /// Side: `"buy"` / `"sell"`. Note: lowercase, unlike REST `side`.
    std::optional<std::string> s_uppercase;
    /// Order type, lowercase: `"limit"` for user orders; `"market"` for expiration-day
    /// auto-liquidation orders by the broker. REST `orderType` is uppercase.
    std::optional<std::string> o;
    /// Limit price (premium per share). REST field `limitPrice`. May be `null` for expiration-day
    /// auto-liquidation orders. `std::nullopt` when the field is absent; holds `std::nullopt` when
    /// it is `null`.
    std::optional<std::optional<common::Decimal>> p;
    /// Order quantity (contracts). REST field `qty`.
    std::optional<common::Decimal> q_uppercase;
    /// Order notional. Always `null` for options.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<common::Decimal>> n_uppercase;
    /// Cumulative filled quantity (contracts). REST field `filledQty`.
    std::optional<common::Decimal> fq;
    /// Cumulative filled amount (USD) = average fill price × filled contracts × multiplier. REST
    /// field `filledNotional`.
    std::optional<common::Decimal> fn_uppercase;
    /// Amount locked from the wallet at placement: premium plus fees for buy to open and buy to
    /// close (covered call); for buy to close (cash-secured put), only the shortfall after the
    /// collateral is released (usually `0`); the collateral for sell to open (shares for a covered
    /// call, cash for a cash-secured put); `0` for sell to close. REST field `totalCost`. May be
    /// `null` for expiration-day auto-liquidation orders. `std::nullopt` when the field is absent;
    /// holds `std::nullopt` when it is `null`.
    std::optional<std::optional<common::Decimal>> tc;
    /// Fill progress percentage (0–100, 2 dp) = `fq` / `Q` × 100. REST field `filledPercent`.
    std::optional<common::Decimal> z_uppercase;
    /// Trading session; always `RTH` for options.
    std::optional<std::string> n;
    /// Order status, lowercase. With `ORDER_UPDATE`: `new` / `pending_new` / `accepted` /
    /// `partially_filled` / `pending_cancel` / `pending_replace`. With `ORDER_TERMINAL`: `filled` /
    /// `canceled` / `expired` / `rejected` / `replaced`. REST field `status` is uppercase.
    std::optional<std::string> s;
    /// Order creation time (ms). REST field `createdAt`.
    std::optional<std::int64_t> t_uppercase;
    /// Order last update time (ms). REST field `updatedAt`.
    std::optional<std::int64_t> u_uppercase;
    /// Asset class: `us_option` (US stock options) / `us_equity` (US stocks).
    std::optional<std::string> ac;
    /// OCC contract symbol. REST field `symbol`.
    std::optional<std::string> os;
    /// Underlying US-equity ticker. REST field `underlyingSymbol`. May be `null` for expiration-day
    /// auto-liquidation orders. `std::nullopt` when the field is absent; holds `std::nullopt` when
    /// it is `null`.
    std::optional<std::optional<std::string>> u;
    /// OCC root; differs from `u` for contracts adjusted by a corporate action. REST field
    /// `rootSymbol`.
    std::optional<std::string> rs;
    /// `CALL` / `PUT`. REST field `contractType`. May be `null` for expiration-day auto-liquidation
    /// orders. `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> ct;
    /// Strike price. REST field `strikePrice`. May be `null` for expiration-day auto-liquidation
    /// orders. `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<common::Decimal>> sp;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day, same as REST
    /// `expirationDate`. May be `null` for expiration-day auto-liquidation orders. `std::nullopt`
    /// when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> ed;
    /// Contract multiplier. REST field `multiplier`.
    std::optional<common::Decimal> m;
    /// Position intent, lowercase: `buy_to_open` / `sell_to_close` / `sell_to_open` /
    /// `buy_to_close`. REST field `positionIntent` is uppercase.
    std::optional<std::string> pi;

    bool operator==(const OrderReportV2StreamResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OrderReportV2StreamResponse tag_invoke(
    boost::json::value_to_tag<OrderReportV2StreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OrderReportV2StreamResponse& v);

} // namespace binance::stock_options::websocket_streams
