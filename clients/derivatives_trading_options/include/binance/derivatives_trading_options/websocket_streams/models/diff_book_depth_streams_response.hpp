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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct DiffBookDepthStreamsResponse {
    /// event type
    std::optional<std::string> e;
    /// event time
    std::optional<std::int64_t> e_uppercase;
    /// transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Option symbol
    std::optional<std::string> s;
    /// First update ID in event
    std::optional<std::int64_t> u_uppercase;
    /// Final update ID in event
    std::optional<std::int64_t> u;
    /// Final update Id in last stream(ie `u` in last stream)
    std::optional<std::int64_t> pu;
    /// Buy order
    std::optional<std::vector<std::vector<std::string>>> b;
    /// Sell order
    std::optional<std::vector<std::vector<std::string>>> a;

    bool operator==(const DiffBookDepthStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT DiffBookDepthStreamsResponse tag_invoke(
    boost::json::value_to_tag<DiffBookDepthStreamsResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const DiffBookDepthStreamsResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
