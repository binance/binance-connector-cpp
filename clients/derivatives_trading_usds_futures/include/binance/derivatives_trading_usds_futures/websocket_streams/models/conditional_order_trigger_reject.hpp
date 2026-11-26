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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/conditional_order_trigger_reject_or.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct ConditionalOrderTriggerReject {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Message send time
    std::optional<std::int64_t> t_uppercase;
    std::optional<ConditionalOrderTriggerRejectOr> r_or;

    bool operator==(const ConditionalOrderTriggerReject& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ConditionalOrderTriggerReject tag_invoke(
    boost::json::value_to_tag<ConditionalOrderTriggerReject> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ConditionalOrderTriggerReject& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
