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

struct RiskLevelChange {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Risk level. This feature only applies to VIP and Market Maker accounts. Risk level is
    /// re-evaluated on: funds transfer, trade fill, option expiry.
    std::optional<std::string> s;
    /// Margin balance
    std::optional<std::string> mb;
    /// Maintenance margin
    std::optional<std::string> mm;

    bool operator==(const RiskLevelChange& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT RiskLevelChange
tag_invoke(boost::json::value_to_tag<RiskLevelChange> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const RiskLevelChange& v);

} // namespace binance::derivatives_trading_options::websocket_streams
