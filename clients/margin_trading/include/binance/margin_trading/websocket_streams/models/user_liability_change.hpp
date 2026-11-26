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

struct UserLiabilityChange {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Asset
    std::optional<std::string> a;
    /// Liability Update Type
    std::optional<std::string> t;
    /// Principle Quantity
    std::optional<std::string> p;
    /// Interest Quantity
    std::optional<std::string> i;

    bool operator==(const UserLiabilityChange& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT UserLiabilityChange
tag_invoke(boost::json::value_to_tag<UserLiabilityChange> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, const UserLiabilityChange& v);

} // namespace binance::margin_trading::websocket_streams
