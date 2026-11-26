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
#include <binance/stocks/export.hpp>

namespace binance::stocks::websocket_streams {

struct OrderReportStreamResponse {
    /// Event type, always `"orderReport"`.
    std::optional<std::string> e;
    /// Event time (epoch milliseconds); server push time.
    std::optional<std::int64_t> e_uppercase;
    /// Execution type: `"ORDER_UPDATE"` (still open) or `"ORDER_TERMINAL"` (reached terminal
    /// state).
    std::optional<std::string> x;
    /// Order ID (UUID).
    std::optional<std::string> i;
    /// Asset ID (internal identifier).
    std::optional<std::string> ai;
    /// Base asset — the internal asset code with an `EQ_` prefix (e.g. `"EQ_AAPL"`), not the bare
    /// ticker used in REST responses / order input. Strip the `EQ_` prefix to match a symbol used
    /// elsewhere.
    std::optional<std::string> b;
    /// Quote currency, e.g. `"USD"`.
    std::optional<std::string> q;
    /// Order side: `"buy"` or `"sell"`. Note: lowercase, unlike REST responses.
    std::optional<std::string> s_uppercase;
    /// Order type: `"market"` / `"limit"` / `"stop"` / `"stop_limit"` / `"trailing_stop"`. Note:
    /// lowercase.
    std::optional<std::string> o;
    /// Limit price; null for market orders.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<common::Decimal>> p;
    /// Order quantity (shares); `0` when the order was submitted as notional.
    std::optional<common::Decimal> q_uppercase;
    /// Order notional; set when the order was submitted as notional (market buy), null when
    /// submitted as quantity. `std::nullopt` when the field is absent; holds `std::nullopt` when it
    /// is `null`.
    std::optional<std::optional<common::Decimal>> n_uppercase;
    /// Filled quantity.
    std::optional<common::Decimal> fq;
    /// Filled notional (= filledQty × filledAvgPrice).
    std::optional<common::Decimal> fn_uppercase;
    /// Total cost — cumulative buy-in cost including the commission fee.
    std::optional<common::Decimal> tc;
    /// Fill progress percentage (0–100, 2 dp). By notional: `FN / N × 100`. By qty: `fq / Q × 100`.
    std::optional<common::Decimal> z_uppercase;
    /// Trading session label, e.g. `"Regular"`, `"24 Hours Trading"`.
    std::optional<std::string> n;
    /// Order status, e.g. `"accepted"`, `"partially_filled"`, `"filled"`, `"canceled"`. Note:
    /// lowercase, unlike REST responses.
    std::optional<std::string> s;
    /// Order create time (epoch milliseconds).
    std::optional<std::int64_t> t_uppercase;
    /// Order update time (epoch milliseconds).
    std::optional<std::int64_t> u_uppercase;

    bool operator==(const OrderReportStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT OrderReportStreamResponse tag_invoke(
    boost::json::value_to_tag<OrderReportStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const OrderReportStreamResponse& v);

} // namespace binance::stocks::websocket_streams
