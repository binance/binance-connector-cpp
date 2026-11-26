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

#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/models/price_stream_response_rates_inner.hpp>

namespace binance::stocks::websocket_streams {

struct PriceStreamResponse {
    /// Event type, always `"price"`.
    std::optional<std::string> e;
    /// One entry per symbol.
    std::optional<std::vector<PriceStreamResponseRatesInner>> rates;

    bool operator==(const PriceStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT PriceStreamResponse
tag_invoke(boost::json::value_to_tag<PriceStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const PriceStreamResponse& v);

} // namespace binance::stocks::websocket_streams
