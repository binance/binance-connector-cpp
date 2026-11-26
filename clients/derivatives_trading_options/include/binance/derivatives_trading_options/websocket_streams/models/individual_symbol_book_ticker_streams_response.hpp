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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct IndividualSymbolBookTickerStreamsResponse {
    /// event type
    std::optional<std::string> e;
    /// order book updateId
    std::optional<std::int64_t> u;
    /// symbol
    std::optional<std::string> s;
    /// best bid price
    std::optional<std::string> b;
    /// bid bid quantity
    std::optional<std::string> b_uppercase;
    /// best ask price
    std::optional<std::string> a;
    /// best ask quantity
    std::optional<std::string> a_uppercase;
    /// transaction time
    std::optional<std::int64_t> t_uppercase;
    /// event time
    std::optional<std::int64_t> e_uppercase;

    bool operator==(const IndividualSymbolBookTickerStreamsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT IndividualSymbolBookTickerStreamsResponse
tag_invoke(boost::json::value_to_tag<IndividualSymbolBookTickerStreamsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndividualSymbolBookTickerStreamsResponse& v);

} // namespace binance::derivatives_trading_options::websocket_streams
