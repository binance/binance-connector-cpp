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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct OrderBookResponseRateLimitsInner {
    std::optional<std::string> rate_limit_type;
    std::optional<std::string> interval;
    std::optional<std::int64_t> interval_num;
    std::optional<std::int64_t> limit;
    std::optional<std::int64_t> count;

    bool operator==(const OrderBookResponseRateLimitsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT OrderBookResponseRateLimitsInner
tag_invoke(boost::json::value_to_tag<OrderBookResponseRateLimitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OrderBookResponseRateLimitsInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
