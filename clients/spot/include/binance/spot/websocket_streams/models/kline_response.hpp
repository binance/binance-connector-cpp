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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_streams/models/kline_response_k.hpp>

namespace binance::spot::websocket_streams {

struct KlineResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    std::optional<KlineResponseK> k;

    bool operator==(const KlineResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT KlineResponse tag_invoke(boost::json::value_to_tag<KlineResponse> /*tag*/,
                                             const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const KlineResponse& v);

} // namespace binance::spot::websocket_streams
