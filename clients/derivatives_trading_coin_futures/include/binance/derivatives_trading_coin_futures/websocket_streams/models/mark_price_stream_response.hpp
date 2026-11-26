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

struct MarkPriceStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// Mark Price
    std::optional<std::string> p;
    /// Estimated Settle Price, only useful in the last hour before the settlement starts.
    std::optional<std::string> p_uppercase;
    /// Index Price
    std::optional<std::string> i;
    /// funding rate for perpetual symbol, "" will be shown for delivery symbol
    std::optional<std::string> r;
    /// next funding time for perpetual symbol, 0 will be shown for delivery symbol
    std::optional<std::int64_t> t_uppercase;
    /// (After CM migration) Symbol type: 1 = UM, 2 = CM
    std::optional<std::int64_t> st;

    bool operator==(const MarkPriceStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceStreamResponse tag_invoke(
    boost::json::value_to_tag<MarkPriceStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const MarkPriceStreamResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
