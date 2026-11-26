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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

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
    /// Stop Price. Please ignore with TRAILING_STOP_MARKET order
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
    /// Commission Asset
    std::optional<std::string> n_uppercase;
    /// Commission
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
    /// Stop Price Working Type
    std::optional<std::string> wt;
    /// Original Order Type
    std::optional<std::string> ot;
    /// Position Side
    std::optional<std::string> ps;
    /// If Close-All, pushed with conditional order
    std::optional<bool> cp;
    /// Activation Price, only pushed with TRAILING_STOP_MARKET order
    std::optional<std::string> ap_uppercase;
    /// Callback Rate, only pushed with TRAILING_STOP_MARKET order
    std::optional<std::string> cr;
    /// If price protection is turned on
    std::optional<bool> p_p;
    /// ignore
    std::optional<std::int64_t> si;
    /// ignore
    std::optional<std::int64_t> ss;
    /// Realized Profit of the trade
    std::optional<std::string> rp;
    /// STP mode
    std::optional<std::string> v_uppercase;
    /// Price match mode
    std::optional<std::string> pm;
    /// TIF GTD order auto cancel time
    std::optional<std::int64_t> gtd;
    /// Expiry Reason
    std::optional<std::string> er;

    bool operator==(const OrderTradeUpdateO& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT OrderTradeUpdateO
tag_invoke(boost::json::value_to_tag<OrderTradeUpdateO> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const OrderTradeUpdateO& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
