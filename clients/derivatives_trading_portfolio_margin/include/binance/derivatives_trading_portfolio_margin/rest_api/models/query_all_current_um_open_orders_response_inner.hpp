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

struct QueryAllCurrentUmOpenOrdersResponseInner {
    /// Avg Price.
    std::optional<std::string> avg_price;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Cum Quote.
    std::optional<std::string> cum_quote;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Orig Type.
    std::optional<std::string> orig_type;
    /// Price.
    std::optional<std::string> price;
    /// Reduce Only.
    std::optional<bool> reduce_only;
    /// Side.
    std::optional<std::string> side;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// Status.
    std::optional<std::string> status;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// order time
    std::optional<std::int64_t> time;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;
    /// update time
    std::optional<std::int64_t> update_time;
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// order pre-set auot cancel time for TIF GTD order
    std::optional<std::int64_t> good_till_date;
    /// Price Match.
    std::optional<std::string> price_match;

    bool operator==(const QueryAllCurrentUmOpenOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryAllCurrentUmOpenOrdersResponseInner
tag_invoke(boost::json::value_to_tag<QueryAllCurrentUmOpenOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryAllCurrentUmOpenOrdersResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
