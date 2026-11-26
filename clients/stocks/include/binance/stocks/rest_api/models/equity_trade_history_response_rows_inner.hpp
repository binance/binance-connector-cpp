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

struct EquityTradeHistoryResponseRowsInner {
    /// Execution (per-fill) id.
    std::optional<std::string> execution_id;
    /// The owning order's id.
    std::optional<std::string> order_id;
    /// US-equity ticker.
    std::optional<std::string> symbol;
    /// Quote asset.
    std::optional<std::string> quote;
    /// `BUY` / `SELL`.
    std::optional<std::string> side;
    /// `MARKET` / `LIMIT`.
    std::optional<std::string> order_type;
    /// Execution price (USD).
    std::optional<std::string> price;
    /// Executed quantity.
    std::optional<std::string> qty;
    /// Notional of this execution (`qty × price`).
    std::optional<std::string> total;
    /// Execution time (ms epoch).
    std::optional<std::int64_t> execution_at;
    /// Last update time (ms epoch).
    std::optional<std::int64_t> updated_at;

    bool operator==(const EquityTradeHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT EquityTradeHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<EquityTradeHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EquityTradeHistoryResponseRowsInner& v);

} // namespace binance::stocks::rest_api
