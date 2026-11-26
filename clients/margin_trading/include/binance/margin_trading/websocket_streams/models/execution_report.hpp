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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::websocket_streams {

struct ExecutionReport {
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Client order ID
    std::optional<std::string> c;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Order type
    std::optional<std::string> o;
    /// Time in force
    std::optional<std::string> f;
    /// Order quantity
    std::optional<std::string> q;
    /// Order price
    std::optional<std::string> p;
    /// Stop price
    std::optional<std::string> p_uppercase;
    /// Iceberg quantity
    std::optional<std::string> f_uppercase;
    /// OrderListId
    std::optional<std::int64_t> g;
    /// Original client order ID; This is the ID of the order being canceled
    std::optional<std::string> c_uppercase;
    /// Current execution type
    std::optional<std::string> x;
    /// Current order status
    std::optional<std::string> x_uppercase;
    /// Order reject reason; will be an error code.
    std::optional<std::string> r;
    /// Order ID
    std::optional<std::int64_t> i;
    /// Last executed quantity
    std::optional<std::string> l;
    /// Cumulative filled quantity
    std::optional<std::string> z;
    /// Last executed price
    std::optional<std::string> l_uppercase;
    /// Commission amount
    std::optional<std::string> n;
    /// Commission asset
    std::optional<std::string> n_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Trade ID
    std::optional<std::int64_t> t;
    /// Ignore
    std::optional<std::int64_t> i_uppercase;
    /// Is the order on the book?
    std::optional<bool> w;
    /// Is this trade the maker side?
    std::optional<bool> m;
    /// Ignore
    std::optional<bool> m_uppercase;
    /// Order creation time
    std::optional<std::int64_t> o_uppercase;
    /// Cumulative quote asset transacted quantity
    std::optional<std::string> z_uppercase;
    /// Last quote asset transacted quantity (i.e. lastPrice * lastQty)
    std::optional<std::string> y_uppercase;
    /// Quote Order Quantity
    std::optional<std::string> q_uppercase;
    /// Working Time; This is only visible if the order has been placed on the book.
    std::optional<std::int64_t> w_uppercase;
    /// selfTradePreventionMode
    std::optional<std::string> v_uppercase;
    /// Trailing Delta; This is only visible if the order was a trailing stop order.
    std::optional<std::int64_t> d;
    /// Trailing Time
    std::optional<std::int64_t> d_uppercase;
    /// Strategy Id
    std::optional<std::int64_t> j;
    /// Strategy Type
    std::optional<std::int64_t> j_uppercase;
    /// Prevented Match Id
    std::optional<std::int64_t> v;
    /// Prevented Quantity
    std::optional<std::string> a_uppercase;
    /// Last Prevented Quantity
    std::optional<std::string> b_uppercase;
    /// Trade Group Id
    std::optional<std::int64_t> u;
    /// Counter Order Id
    std::optional<std::int64_t> u_uppercase;
    /// Counter Symbol
    std::optional<std::string> cs;
    /// Prevented Execution Quantity
    std::optional<std::string> pl;
    /// Prevented Execution Price
    std::optional<std::string> p_l;
    /// Prevented Execution Quote Qty
    std::optional<std::string> p_y;
    /// Match Type
    std::optional<std::string> b;
    /// Allocation ID
    std::optional<std::int64_t> a;
    /// Working Floor
    std::optional<std::string> k;
    /// UsedSor
    std::optional<bool> u_s;

    bool operator==(const ExecutionReport& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT ExecutionReport
tag_invoke(boost::json::value_to_tag<ExecutionReport> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, const ExecutionReport& v);

} // namespace binance::margin_trading::websocket_streams
