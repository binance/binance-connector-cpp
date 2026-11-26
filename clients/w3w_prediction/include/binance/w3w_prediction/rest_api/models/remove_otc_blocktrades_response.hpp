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

namespace binance::w3w_prediction::rest_api {

struct RemoveOtcBlocktradesResponse {
    std::optional<std::vector<std::string>> removed;
    std::optional<std::vector<std::string>> noop;

    bool operator==(const RemoveOtcBlocktradesResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT RemoveOtcBlocktradesResponse tag_invoke(
    boost::json::value_to_tag<RemoveOtcBlocktradesResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const RemoveOtcBlocktradesResponse& v);

} // namespace binance::w3w_prediction::rest_api
