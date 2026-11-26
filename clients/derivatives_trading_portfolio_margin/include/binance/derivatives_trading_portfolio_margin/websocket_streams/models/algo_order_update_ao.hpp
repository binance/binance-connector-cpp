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

/// Algo order info
struct AlgoOrderUpdateAo {
    /// Client Algo Id
    std::optional<std::string> caid;
    /// Algo Id
    std::optional<std::int64_t> aid;
    /// Algo Type
    std::optional<std::string> at;
    /// Order Type
    std::optional<std::string> o;
    /// Symbol
    std::optional<std::string> s;
    /// Side
    std::optional<std::string> s_uppercase;
    /// Position Side
    std::optional<std::string> ps;
    /// Time in Force
    std::optional<std::string> f;
    /// Quantity
    std::optional<std::string> q;
    /// Algo Status: NEW, CANCELED, TRIGGERING, TRIGGERED, FINISHED, REJECTED, EXPIRED
    std::optional<std::string> x_uppercase;
    /// Actual order ID in matching engine
    std::optional<std::string> ai;
    /// Avg fill price in matching engine
    std::optional<std::string> ap;
    /// Executed quantity in matching engine
    std::optional<std::string> aq;
    /// Actual order type in matching engine
    std::optional<std::string> act;
    /// Trigger Price
    std::optional<std::string> tp;
    /// Order Price
    std::optional<std::string> p;
    /// Self Trade Prevention Mode
    std::optional<std::string> v_uppercase;
    /// Working Type
    std::optional<std::string> wt;
    /// Price Match
    std::optional<std::string> pm;
    /// If Close-All
    std::optional<bool> cp;
    /// If price protection is on
    std::optional<bool> p_p;
    /// Is reduce only
    std::optional<bool> r_uppercase;
    /// Trigger Time
    std::optional<std::int64_t> tt;
    /// Good Till Date
    std::optional<std::int64_t> gtd;
    /// Algo order failed reason
    std::optional<std::string> rm;
    /// Is activated or not, only meaningful for trailing order
    std::optional<bool> ia;

    bool operator==(const AlgoOrderUpdateAo& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AlgoOrderUpdateAo
tag_invoke(boost::json::value_to_tag<AlgoOrderUpdateAo> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AlgoOrderUpdateAo& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
