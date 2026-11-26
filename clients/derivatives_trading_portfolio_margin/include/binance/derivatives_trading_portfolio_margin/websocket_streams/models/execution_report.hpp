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
    /// Trailing Delta; This is only visible if the order was a trailing stop order.
    std::optional<std::int64_t> d;
    /// Iceberg quantity; Will not be visible if not iceberg order
    std::optional<std::string> f_uppercase;
    /// OrderListId
    std::optional<std::int64_t> g;
    /// Original client order ID; Only visible on cancellation of order, the ID of the order being
    /// canceled.
    std::optional<std::string> c_uppercase;
    /// Current execution type
    std::optional<std::string> x;
    /// Current order status
    std::optional<std::string> x_uppercase;
    /// Order reject reason; Only visible if there is a rejection, will be an error code.
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
    /// Commission asset; Only visible when there is a commission amount.
    std::optional<std::string> n_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Trade ID
    std::optional<std::int64_t> t;
    /// Prevented Match Id; This is only visible if the order expire due to STP trigger.
    std::optional<std::int64_t> v;
    /// updateId
    std::optional<std::int64_t> i_uppercase;
    /// Is the order on the book?
    std::optional<bool> w;
    /// Is this trade the maker side?
    std::optional<bool> m;
    /// Order creation time
    std::optional<std::int64_t> o_uppercase;
    /// Cumulative quote asset transacted quantity
    std::optional<std::string> z_uppercase;
    /// Last quote asset transacted quantity (i.e. lastPrice * lastQty)
    std::optional<std::string> y_uppercase;
    /// Quote Order Quantity; This is only visible if indicated in the order
    std::optional<std::string> q_uppercase;
    /// Trailing Time; This is only visible if the trailing stop order has been activated.
    std::optional<std::int64_t> d_uppercase;
    /// Strategy ID; This is only visible if the strategyId parameter was provided upon order
    /// placement
    std::optional<std::int64_t> j;
    /// Strategy Type; This is only visible if the strategyType parameter was provided upon order
    /// placement
    std::optional<std::int64_t> j_uppercase;
    /// Working Time; This is only visible if the order has been placed on the book.
    std::optional<std::int64_t> w_uppercase;
    /// selfTradePreventionMode
    std::optional<std::string> v_uppercase;
    /// TradeGroupId; This is only visible if the account is part of a trade group and the order
    /// expired due to STP trigger.
    std::optional<std::int64_t> u;
    /// CounterOrderId; This is only visible if the order expired due to STP trigger.
    std::optional<std::int64_t> u_uppercase;
    /// Prevented Quantity; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> a_uppercase;
    /// Last Prevented Quantity; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> b_uppercase;
    /// Counter Symbol; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> cs;
    /// Prevented Execution Quantity; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> pl;
    /// Prevented Execution Price; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> p_l;
    /// Prevented Execution Quote Qty; This is only visible if the order expired due to STP trigger.
    std::optional<std::string> p_y;
    /// Expiry Reason; This is only visible if the order has expired.
    std::optional<std::string> e_r;

    bool operator==(const ExecutionReport& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ExecutionReport
tag_invoke(boost::json::value_to_tag<ExecutionReport> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const ExecutionReport& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
