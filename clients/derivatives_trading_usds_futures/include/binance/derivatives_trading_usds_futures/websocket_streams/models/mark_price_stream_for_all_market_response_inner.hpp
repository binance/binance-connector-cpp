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

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct MarkPriceStreamForAllMarketResponseInner {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Mark price
    std::optional<std::string> p;
    /// Index price
    std::optional<std::string> i;
    /// Estimated Settle Price, only useful in the last hour before the settlement starts
    std::optional<std::string> p_uppercase;
    /// Funding rate
    std::optional<std::string> r;
    /// Mark price moving average
    std::optional<std::string> ap;
    /// Next funding time
    std::optional<std::int64_t> t_uppercase;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const MarkPriceStreamForAllMarketResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceStreamForAllMarketResponseInner
tag_invoke(boost::json::value_to_tag<MarkPriceStreamForAllMarketResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const MarkPriceStreamForAllMarketResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
