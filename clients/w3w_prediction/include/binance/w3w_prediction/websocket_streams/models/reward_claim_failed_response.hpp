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

struct RewardClaimFailedResponse {
    /// Unique ID of this push. Use it to remove duplicates.
    std::optional<std::string> push_id;
    /// Amount of the **first failed claim**. Rounded down to 2 decimals; shown as `<0.01` if
    /// smaller.
    std::optional<std::string> amount;
    /// Outcome name of the **first failed claim**, such as `Yes` or `No`; empty if unavailable.
    std::optional<std::string> outcome;

    bool operator==(const RewardClaimFailedResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT RewardClaimFailedResponse tag_invoke(
    boost::json::value_to_tag<RewardClaimFailedResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const RewardClaimFailedResponse& v);

} // namespace binance::w3w_prediction::websocket_streams
