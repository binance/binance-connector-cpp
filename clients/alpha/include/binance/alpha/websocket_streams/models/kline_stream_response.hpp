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
#include <binance/alpha/websocket_streams/models/kline_stream_response_k.hpp>

namespace binance::alpha::websocket_streams {

struct KlineStreamResponse {
    /// eventType
    std::optional<std::string> e;
    /// eventTime
    std::optional<std::int64_t> e_uppercase;
    /// symbol
    std::optional<std::string> s;
    std::optional<KlineStreamResponseK> k;

    bool operator==(const KlineStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT KlineStreamResponse
tag_invoke(boost::json::value_to_tag<KlineStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const KlineStreamResponse& v);

} // namespace binance::alpha::websocket_streams
