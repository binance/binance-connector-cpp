//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response1.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response2.hpp>

namespace binance::spot::websocket_api {

struct TickerBookResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<TickerBookResponse1, TickerBookResponse2, boost::json::value> value;

    bool operator==(const TickerBookResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerBookResponse
tag_invoke(boost::json::value_to_tag<TickerBookResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerBookResponse& v);

} // namespace binance::spot::websocket_api
