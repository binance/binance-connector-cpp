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

struct QueryUsersMarginForceOrdersResponseRowsInner {
    /// Avg Price.
    std::optional<std::string> avg_price;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Price.
    std::optional<std::string> price;
    /// Qty.
    std::optional<std::string> qty;
    /// Side.
    std::optional<std::string> side;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// Updated Time.
    std::optional<std::int64_t> updated_time;

    bool operator==(const QueryUsersMarginForceOrdersResponseRowsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryUsersMarginForceOrdersResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryUsersMarginForceOrdersResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryUsersMarginForceOrdersResponseRowsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
