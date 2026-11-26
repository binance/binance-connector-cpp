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

#include <binance/alpha/export.hpp>

namespace binance::alpha::websocket_streams {

struct TradeStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// tradeTime
    std::optional<std::int64_t> t_uppercase;
    /// symbol
    std::optional<std::string> s;
    /// tradeId
    std::optional<std::int64_t> t;
    /// fillPrice
    std::optional<std::string> p;
    /// fillQty
    std::optional<std::string> q;
    /// isBuyerMaker
    std::optional<bool> m;

    bool operator==(const TradeStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT TradeStreamResponse
tag_invoke(boost::json::value_to_tag<TradeStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const TradeStreamResponse& v);

} // namespace binance::alpha::websocket_streams
