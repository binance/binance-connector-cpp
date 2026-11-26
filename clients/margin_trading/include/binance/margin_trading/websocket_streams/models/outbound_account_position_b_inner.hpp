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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::websocket_streams {

struct OutboundAccountPositionBInner {
    /// Asset
    std::optional<std::string> a;
    /// Free
    std::optional<std::string> f;
    /// Locked
    std::optional<std::string> l;

    bool operator==(const OutboundAccountPositionBInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT OutboundAccountPositionBInner tag_invoke(
    boost::json::value_to_tag<OutboundAccountPositionBInner> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const OutboundAccountPositionBInner& v);

} // namespace binance::margin_trading::websocket_streams
