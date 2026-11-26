//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>
#include <binance/alpha/websocket_streams/models/all_tokens24h_ticker_stream_response_d_inner.hpp>

namespace binance::alpha::websocket_streams {

struct AllTokens24hTickerStreamResponse {
    /// Event type
    std::optional<std::string> e;
    /// Per-token 24-hour ticker metrics
    std::optional<std::vector<AllTokens24hTickerStreamResponseDInner>> d;

    bool operator==(const AllTokens24hTickerStreamResponse& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT AllTokens24hTickerStreamResponse
tag_invoke(boost::json::value_to_tag<AllTokens24hTickerStreamResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const AllTokens24hTickerStreamResponse& v);

} // namespace binance::alpha::websocket_streams
