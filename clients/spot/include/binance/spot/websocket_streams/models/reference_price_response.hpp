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

namespace binance::spot::websocket_streams {

struct ReferencePriceResponse {
    /// Event type
    std::optional<std::string> e;
    /// Symbol
    std::optional<std::string> s;
    /// Reference price (null if no reference price)
    std::optional<std::string> r;
    /// Engine timestamp when reference price was valid
    std::optional<std::int64_t> t;

    bool operator==(const ReferencePriceResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ReferencePriceResponse
tag_invoke(boost::json::value_to_tag<ReferencePriceResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ReferencePriceResponse& v);

} // namespace binance::spot::websocket_streams
