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

struct IndexPriceStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Pair
    std::optional<std::string> i;
    /// Index Price
    std::optional<std::string> p;

    bool operator==(const IndexPriceStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexPriceStreamResponse tag_invoke(
    boost::json::value_to_tag<IndexPriceStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const IndexPriceStreamResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
