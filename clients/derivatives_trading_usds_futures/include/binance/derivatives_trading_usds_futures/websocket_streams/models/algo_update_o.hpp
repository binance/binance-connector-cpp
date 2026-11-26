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

struct AlgoUpdateO {
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
    /// Time in force
    std::optional<std::string> f;
    /// Quantity
    std::optional<std::string> q;
    /// Algo Status
    std::optional<std::string> x_uppercase;
    /// Order Id
    std::optional<std::string> ai;
    /// Avg fill price in matching engine, only display when order is triggered and placed in
    /// matching engine
    std::optional<std::string> ap;
    /// Executed quantity in matching engine, only display when order is triggered and placed in
    /// matching engine
    std::optional<std::string> aq;
    /// Actual order type in matching engine, only display when order is triggered and placed in
    /// matching engine
    std::optional<std::string> act;
    /// Trigger Price
    std::optional<std::string> tp;
    /// Order Price
    std::optional<std::string> p;
    /// STP mode
    std::optional<std::string> v_uppercase;
    /// Working type
    std::optional<std::string> wt;
    /// Price match mode
    std::optional<std::string> pm;
    /// If Close-All
    std::optional<bool> cp;
    /// If price protection is turned on
    std::optional<bool> p_p;
    /// Is this reduce only
    std::optional<bool> r_uppercase;
    /// Trigger time
    std::optional<std::int64_t> tt;
    /// Good till time for GTD time in force
    std::optional<std::int64_t> gtd;
    /// Algo order failed reason
    std::optional<std::string> rm;
    /// Is activated or not, only meaningful for trailing order
    std::optional<bool> ia;
    /// Sub price type, only meaningful for CHASE order
    std::optional<std::string> spt;
    /// Sub price value, only meaningful for CHASE order
    std::optional<std::string> spv;
    /// Sub price limit value, only meaningful for CHASE order
    std::optional<std::string> splv;

    bool operator==(const AlgoUpdateO& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AlgoUpdateO
tag_invoke(boost::json::value_to_tag<AlgoUpdateO> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const AlgoUpdateO& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
