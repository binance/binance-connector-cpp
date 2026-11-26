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

struct MarginLevelStatusChange {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Margin level
    std::optional<std::string> l;
    /// Margin call status
    std::optional<std::string> s;

    bool operator==(const MarginLevelStatusChange& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT MarginLevelStatusChange tag_invoke(
    boost::json::value_to_tag<MarginLevelStatusChange> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const MarginLevelStatusChange& v);

} // namespace binance::margin_trading::websocket_streams
