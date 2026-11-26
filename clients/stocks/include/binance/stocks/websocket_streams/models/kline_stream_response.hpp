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

#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/models/kline_stream_response_k.hpp>

namespace binance::stocks::websocket_streams {

struct KlineStreamResponse {
    /// Event type, always `"kline"`.
    std::optional<std::string> e;
    /// Event time (epoch milliseconds); server-side system time when the message is pushed.
    std::optional<std::int64_t> e_uppercase;
    /// Symbol (UPPERCASE ticker).
    std::optional<std::string> s;
    std::optional<KlineStreamResponseK> k;

    bool operator==(const KlineStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT KlineStreamResponse
tag_invoke(boost::json::value_to_tag<KlineStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const KlineStreamResponse& v);

} // namespace binance::stocks::websocket_streams
