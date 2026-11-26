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

struct QueryUsersUmForceOrdersResponseInner {
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Status.
    std::optional<std::string> status;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// Price.
    std::optional<std::string> price;
    /// Avg Price.
    std::optional<std::string> avg_price;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Cum Quote.
    std::optional<std::string> cum_quote;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Normal order type after trigger if appliable
    std::optional<std::string> type;
    /// Reduce Only.
    std::optional<bool> reduce_only;
    /// Side.
    std::optional<std::string> side;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// Orig Type.
    std::optional<std::string> orig_type;
    /// Event time.
    std::optional<std::int64_t> time;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const QueryUsersUmForceOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUsersUmForceOrdersResponseInner
tag_invoke(boost::json::value_to_tag<QueryUsersUmForceOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUsersUmForceOrdersResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
