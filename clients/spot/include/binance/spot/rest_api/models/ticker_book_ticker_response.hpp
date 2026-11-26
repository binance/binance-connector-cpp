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
#include <binance/spot/rest_api/models/ticker_book_ticker_response1.hpp>
#include <binance/spot/rest_api/models/ticker_book_ticker_response2_inner.hpp>

namespace binance::spot::rest_api {

struct TickerBookTickerResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<TickerBookTickerResponse1, std::vector<TickerBookTickerResponse2Inner>,
                 boost::json::value>
        value;

    bool operator==(const TickerBookTickerResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT TickerBookTickerResponse tag_invoke(
    boost::json::value_to_tag<TickerBookTickerResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const TickerBookTickerResponse& v);

} // namespace binance::spot::rest_api
