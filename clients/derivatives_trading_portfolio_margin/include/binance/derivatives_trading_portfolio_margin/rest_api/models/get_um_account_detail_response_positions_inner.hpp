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

struct GetUmAccountDetailResponsePositionsInner {
    /// symbol name
    std::optional<std::string> symbol;
    /// total initial margin required with current mark price
    std::optional<std::string> initial_margin;
    /// maintenance margin required
    std::optional<std::string> maint_margin;
    /// unrealized profit
    std::optional<std::string> unrealized_profit;
    /// initial margin required for positions with current mark price
    std::optional<std::string> position_initial_margin;
    /// initial margin required for open orders with current mark price
    std::optional<std::string> open_order_initial_margin;
    /// current initial leverage
    std::optional<std::string> leverage;
    /// average entry price
    std::optional<std::string> entry_price;
    /// maximum available notional with current leverage
    std::optional<std::string> max_notional;
    /// bids notional, ignore
    std::optional<std::string> bid_notional;
    /// ask notional, ignore
    std::optional<std::string> ask_notional;
    /// position side
    std::optional<std::string> position_side;
    /// position amount
    std::optional<std::string> position_amt;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const GetUmAccountDetailResponsePositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUmAccountDetailResponsePositionsInner
tag_invoke(boost::json::value_to_tag<GetUmAccountDetailResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetUmAccountDetailResponsePositionsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
