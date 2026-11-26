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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct QueryMarginAccountOrderResponse {
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Iceberg Qty.
    std::optional<std::string> iceberg_qty;
    /// Is Working.
    std::optional<bool> is_working;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Price.
    std::optional<std::string> price;
    /// Side.
    std::optional<std::string> side;
    /// Status.
    std::optional<std::string> status;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Event time.
    std::optional<std::int64_t> time;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;
    /// last update time
    std::optional<std::int64_t> update_time;
    /// Account ID.
    std::optional<std::int64_t> account_id;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// Prevented Match ID.
    std::optional<std::string> prevented_match_id;
    /// Prevented Quantity.
    std::optional<std::string> prevented_quantity;

    bool operator==(const QueryMarginAccountOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginAccountOrderResponse
tag_invoke(boost::json::value_to_tag<QueryMarginAccountOrderResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginAccountOrderResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
