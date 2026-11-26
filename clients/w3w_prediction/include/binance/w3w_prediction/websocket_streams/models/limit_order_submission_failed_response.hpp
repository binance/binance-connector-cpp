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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::websocket_streams {

struct LimitOrderSubmissionFailedResponse {
    /// Unique ID of this push. Use it to remove duplicates.
    std::optional<std::string> push_id;
    /// Market title, cut to 12 characters with `..` added when longer; empty if unavailable.
    std::optional<std::string> topic;

    bool operator==(const LimitOrderSubmissionFailedResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT LimitOrderSubmissionFailedResponse
tag_invoke(boost::json::value_to_tag<LimitOrderSubmissionFailedResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const LimitOrderSubmissionFailedResponse& v);

} // namespace binance::w3w_prediction::websocket_streams
