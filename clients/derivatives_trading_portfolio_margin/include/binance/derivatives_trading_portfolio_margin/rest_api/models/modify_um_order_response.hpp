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

struct ModifyUmOrderResponse {
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Status.
    std::optional<std::string> status;
    /// Client Order ID.
    std::optional<std::string> client_order_id;
    /// user-defined modification identifier, only returned if provided in the request
    std::optional<std::int64_t> modify_id;
    /// Price.
    std::optional<std::string> price;
    /// Orig Qty.
    std::optional<std::string> orig_qty;
    /// Executed Qty.
    std::optional<std::string> executed_qty;
    /// Cum Qty.
    std::optional<std::string> cum_qty;
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
    /// self trading preventation mode
    std::optional<std::string> self_trade_prevention_mode;
    /// order pre-set auot cancel time for TIF GTD order
    std::optional<std::int64_t> good_till_date;
    /// last update time
    std::optional<std::int64_t> update_time;
    /// Price Match.
    std::optional<std::string> price_match;

    bool operator==(const ModifyUmOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ModifyUmOrderResponse
tag_invoke(boost::json::value_to_tag<ModifyUmOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ModifyUmOrderResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
