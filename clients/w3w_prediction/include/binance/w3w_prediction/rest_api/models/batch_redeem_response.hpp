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
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response_results_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct BatchRedeemResponse {
    std::optional<std::string> batch_id;
    std::optional<std::vector<BatchRedeemResponseResultsInner>> results;

    bool operator==(const BatchRedeemResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT BatchRedeemResponse
tag_invoke(boost::json::value_to_tag<BatchRedeemResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, const BatchRedeemResponse& v);

} // namespace binance::w3w_prediction::rest_api
