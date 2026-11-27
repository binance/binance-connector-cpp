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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

struct ConditionalOrderTriggerRejectOr {
    /// Symbol
    std::optional<std::string> s;
    /// Order Id
    std::optional<std::int64_t> i;
    /// Reject Reason
    std::optional<std::string> r;

    bool operator==(const ConditionalOrderTriggerRejectOr& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ConditionalOrderTriggerRejectOr
tag_invoke(boost::json::value_to_tag<ConditionalOrderTriggerRejectOr> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ConditionalOrderTriggerRejectOr& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
