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

struct PartialBookDepthResponse {
    /// Last update ID
    std::optional<std::int64_t> last_update_id;
    /// Bids to be updated
    std::optional<std::vector<std::vector<std::string>>> bids;
    /// Asks to be updated
    std::optional<std::vector<std::vector<std::string>>> asks;

    bool operator==(const PartialBookDepthResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT PartialBookDepthResponse tag_invoke(
    boost::json::value_to_tag<PartialBookDepthResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const PartialBookDepthResponse& v);

} // namespace binance::spot::websocket_streams
