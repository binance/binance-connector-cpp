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

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_events_response_events_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetOtcBlocktradeEventsResponse {
    std::optional<std::string> cursor;
    std::optional<std::vector<GetOtcBlocktradeEventsResponseEventsInner>> events;

    bool operator==(const GetOtcBlocktradeEventsResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetOtcBlocktradeEventsResponse
tag_invoke(boost::json::value_to_tag<GetOtcBlocktradeEventsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetOtcBlocktradeEventsResponse& v);

} // namespace binance::w3w_prediction::rest_api
