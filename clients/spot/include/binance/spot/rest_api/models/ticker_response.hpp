//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/ticker_response1.hpp>
#include <binance/spot/rest_api/models/ticker_response2_inner.hpp>

namespace binance::spot::rest_api {

struct TickerResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<TickerResponse1, std::vector<TickerResponse2Inner>, boost::json::value> value;

    bool operator==(const TickerResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerResponse tag_invoke(boost::json::value_to_tag<TickerResponse> /*tag*/,
                                              const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerResponse& v);

} // namespace binance::spot::rest_api
