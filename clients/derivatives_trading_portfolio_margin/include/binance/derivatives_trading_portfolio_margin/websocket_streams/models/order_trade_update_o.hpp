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

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct OrderTradeUpdateO {
    /// Symbol
    std::optional<std::string> s;
    /// Client Order Id
    std::optional<std::string> c;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Order Type
    std::optional<std::string> o;
    /// Time in Force
    std::optional<std::string> f;
    /// Original Quantity
    std::optional<std::string> q;
    /// Original Price
    std::optional<std::string> p;
    /// Average Price
    std::optional<std::string> ap;
    /// Ignore
    std::optional<std::string> sp;
    /// Execution Type
    std::optional<std::string> x;
    /// Order Status
    std::optional<std::string> x_uppercase;
    /// Order Id
    std::optional<std::int64_t> i;
    /// modifyId, only pushed for AMENDMENT (order modification) events when a modifyId was provided
    /// in the request
    std::optional<std::string> m_uppercase;
    /// Order Last Filled Quantity
    std::optional<std::string> l;
    /// Order Filled Accumulated Quantity
    std::optional<std::string> z;
    /// Last Filled Price
    std::optional<std::string> l_uppercase;
    /// Commission Asset, will not push if no commission
    std::optional<std::string> n_uppercase;
    /// Commission, will not push if no commission
    std::optional<std::string> n;
    /// Order Trade Time
    std::optional<std::int64_t> t_uppercase;
    /// Trade Id
    std::optional<std::int64_t> t;
    /// Bids Notional
    std::optional<std::string> b;
    /// Ask Notional
    std::optional<std::string> a;
    /// Is this trade the maker side?
    std::optional<bool> m;
    /// Is this reduce only
    std::optional<bool> r_uppercase;
    /// Position Side
    std::optional<std::string> ps;
    /// Realized Profit of the trade
    std::optional<std::string> rp;
    /// Strategy type, only pushed with conditional order triggered
    std::optional<std::string> st;
    /// StrategyId, only pushed with conditional order triggered
    std::optional<std::int64_t> si;
    /// STP mode
    std::optional<std::string> v_uppercase;
    /// TIF GTD order auto cancel time
    std::optional<std::int64_t> gtd;

    bool operator==(const OrderTradeUpdateO& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT OrderTradeUpdateO
tag_invoke(boost::json::value_to_tag<OrderTradeUpdateO> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const OrderTradeUpdateO& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
