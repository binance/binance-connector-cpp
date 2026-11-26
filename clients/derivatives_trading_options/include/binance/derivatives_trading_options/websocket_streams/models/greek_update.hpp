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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/greek_update_g_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

struct GreekUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    std::optional<std::vector<GreekUpdateGInner>> g_uppercase;

    bool operator==(const GreekUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT GreekUpdate
tag_invoke(boost::json::value_to_tag<GreekUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const GreekUpdate& v);

} // namespace binance::derivatives_trading_options::websocket_streams
