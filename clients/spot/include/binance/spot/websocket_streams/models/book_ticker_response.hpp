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

struct BookTickerResponse {
    /// Order book updateId
    std::optional<std::int64_t> u;
    /// Symbol
    std::optional<std::string> s;
    /// Best bid price
    std::optional<std::string> b;
    /// Best bid qty
    std::optional<std::string> b_uppercase;
    /// Best ask price
    std::optional<std::string> a;
    /// Best ask qty
    std::optional<std::string> a_uppercase;

    bool operator==(const BookTickerResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT BookTickerResponse
tag_invoke(boost::json::value_to_tag<BookTickerResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const BookTickerResponse& v);

} // namespace binance::spot::websocket_streams
