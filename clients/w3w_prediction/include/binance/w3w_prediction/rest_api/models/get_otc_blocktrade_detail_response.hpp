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
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_detail_response_order_data.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetOtcBlocktradeDetailResponse {
    std::optional<std::string> order_id;
    std::optional<std::string> status;
    std::optional<GetOtcBlocktradeDetailResponseOrderData> order_data;

    bool operator==(const GetOtcBlocktradeDetailResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetOtcBlocktradeDetailResponse
tag_invoke(boost::json::value_to_tag<GetOtcBlocktradeDetailResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetOtcBlocktradeDetailResponse& v);

} // namespace binance::w3w_prediction::rest_api
