//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_position_by_token_response_position.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetPositionByTokenResponse {
    std::optional<GetPositionByTokenResponsePosition> position;

    bool operator==(const GetPositionByTokenResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetPositionByTokenResponse tag_invoke(
    boost::json::value_to_tag<GetPositionByTokenResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetPositionByTokenResponse& v);

} // namespace binance::w3w_prediction::rest_api
