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

struct QueryCurrentCmOpenConditionalOrderResponse {
    /// New Client Strategy ID.
    std::optional<std::string> new_client_strategy_id;
    /// Strategy ID.
    std::optional<std::int64_t> strategy_id;
    /// Strategy Status.
    std::optional<std::string> strategy_status;
    /// Strategy Type.
    std::optional<std::string> strategy_type;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Price.
    std::optional<std::string> price;
    /// Reduce Only.
    std::optional<bool> reduce_only;
    /// Side.
    std::optional<std::string> side;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// order time
    std::optional<std::int64_t> book_time;
    /// last update time
    std::optional<std::int64_t> update_time;
    /// Time In Force.
    std::optional<std::string> time_in_force;
    /// activation price, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> activate_price;
    /// callback rate, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> price_rate;

    bool operator==(const QueryCurrentCmOpenConditionalOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryCurrentCmOpenConditionalOrderResponse
tag_invoke(boost::json::value_to_tag<QueryCurrentCmOpenConditionalOrderResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCurrentCmOpenConditionalOrderResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
