//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct GreekUpdateGInner {
    /// Underlying
    std::optional<std::string> u;
    /// Delta
    std::optional<std::string> d;
    /// Gamma
    std::optional<std::string> g;
    /// Theta
    std::optional<std::string> t;
    /// Vega
    std::optional<std::string> v;

    bool operator==(const GreekUpdateGInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT GreekUpdateGInner
tag_invoke(boost::json::value_to_tag<GreekUpdateGInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GreekUpdateGInner& v);

} // namespace binance::derivatives_trading_options::websocket_streams
