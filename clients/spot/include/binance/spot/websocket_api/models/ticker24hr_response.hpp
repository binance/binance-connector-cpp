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
#include <binance/spot/websocket_api/models/ticker24hr_response1.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response2.hpp>

namespace binance::spot::websocket_api {

struct Ticker24hrResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<Ticker24hrResponse1, Ticker24hrResponse2, boost::json::value> value;

    bool operator==(const Ticker24hrResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT Ticker24hrResponse
tag_invoke(boost::json::value_to_tag<Ticker24hrResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const Ticker24hrResponse& v);

} // namespace binance::spot::websocket_api
