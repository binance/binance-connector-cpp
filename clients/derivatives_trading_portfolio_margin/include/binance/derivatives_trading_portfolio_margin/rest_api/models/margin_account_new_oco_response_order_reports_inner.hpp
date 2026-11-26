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

struct MarginAccountNewOcoResponseOrderReportsInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Order List ID.
    std::optional<std::int64_t> order_list_id;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Transact Time.
    std::optional<std::int64_t> transact_time;
    /// Price.
    std::optional<std::string> price;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Cummulative Quote Qty.
    std::optional<std::string> cummulative_quote_qty;
    /// Status.
    std::optional<std::string> status;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;
    /// Side.
    std::optional<std::string> side;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;

    bool operator==(const MarginAccountNewOcoResponseOrderReportsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarginAccountNewOcoResponseOrderReportsInner
tag_invoke(boost::json::value_to_tag<MarginAccountNewOcoResponseOrderReportsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarginAccountNewOcoResponseOrderReportsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
