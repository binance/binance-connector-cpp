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

struct GetCmAccountDetailResponsePositionsInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// position amount
    std::optional<std::string> position_amt;
    /// total intial margin required with the latest mark price
    std::optional<std::string> initial_margin;
    /// maintenance margin
    std::optional<std::string> maint_margin;
    /// unrealized profit
    std::optional<std::string> unrealized_profit;
    /// positions margin required with the latest mark price
    std::optional<std::string> position_initial_margin;
    /// open orders intial margin required with the latest mark price
    std::optional<std::string> open_order_initial_margin;
    /// current initial leverage
    std::optional<std::string> leverage;
    /// BOTH means that it is the position of One-way Mode
    std::optional<std::string> position_side;
    /// average entry price
    std::optional<std::string> entry_price;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const GetCmAccountDetailResponsePositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetCmAccountDetailResponsePositionsInner
tag_invoke(boost::json::value_to_tag<GetCmAccountDetailResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCmAccountDetailResponsePositionsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
