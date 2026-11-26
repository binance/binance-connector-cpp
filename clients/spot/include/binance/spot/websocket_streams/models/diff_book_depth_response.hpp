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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_streams {

struct DiffBookDepthResponse {
    /// Event type
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// First update ID in event
    std::optional<std::int64_t> u_uppercase;
    /// Final update ID in event
    std::optional<std::int64_t> u;
    /// Bids to be updated
    std::optional<std::vector<std::vector<std::string>>> b;
    /// Asks to be updated
    std::optional<std::vector<std::vector<std::string>>> a;

    bool operator==(const DiffBookDepthResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT DiffBookDepthResponse
tag_invoke(boost::json::value_to_tag<DiffBookDepthResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const DiffBookDepthResponse& v);

} // namespace binance::spot::websocket_streams
