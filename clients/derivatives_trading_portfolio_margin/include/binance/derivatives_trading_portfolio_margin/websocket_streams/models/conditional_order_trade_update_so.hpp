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

struct ConditionalOrderTradeUpdateSo {
    /// Symbol
    std::optional<std::string> s;
    /// Strategy Client Order Id
    std::optional<std::string> c;
    /// Strategy ID
    std::optional<std::int64_t> si;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Strategy Type
    std::optional<std::string> st;
    /// Time in Force
    std::optional<std::string> f;
    /// Quantity
    std::optional<std::string> q;
    /// Price
    std::optional<std::string> p;
    /// Stop Price. Please ignore with TRAILING_STOP_MARKET order
    std::optional<std::string> sp;
    /// Strategy Order Status
    std::optional<std::string> os;
    /// Order book Time
    std::optional<std::int64_t> t_uppercase;
    /// Order update Time
    std::optional<std::int64_t> ut;
    /// Is this reduce only
    std::optional<bool> r_uppercase;
    /// Stop Price Working Type
    std::optional<std::string> wt;
    /// Position Side
    std::optional<std::string> ps;
    /// If Close-All, pushed with conditional order
    std::optional<bool> cp;
    /// Activation Price, only pushed with TRAILING_STOP_MARKET order
    std::optional<std::string> ap_uppercase;
    /// Callback Rate, only pushed with TRAILING_STOP_MARKET order
    std::optional<std::string> cr;
    /// Order Id
    std::optional<std::int64_t> i;
    /// STP mode
    std::optional<std::string> v_uppercase;
    /// TIF GTD order auto cancel time
    std::optional<std::int64_t> gtd;

    bool operator==(const ConditionalOrderTradeUpdateSo& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ConditionalOrderTradeUpdateSo tag_invoke(
    boost::json::value_to_tag<ConditionalOrderTradeUpdateSo> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ConditionalOrderTradeUpdateSo& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
