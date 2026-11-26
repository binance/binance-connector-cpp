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
#include <binance/w3w_prediction/rest_api/models/preview_otc_blocktrade_response_order_data.hpp>

namespace binance::w3w_prediction::rest_api {

struct PreviewOtcBlocktradeResponse {
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> order_id;
    std::optional<std::string> status;
    std::optional<PreviewOtcBlocktradeResponseOrderData> order_data;

    bool operator==(const PreviewOtcBlocktradeResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT PreviewOtcBlocktradeResponse tag_invoke(
    boost::json::value_to_tag<PreviewOtcBlocktradeResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const PreviewOtcBlocktradeResponse& v);

} // namespace binance::w3w_prediction::rest_api
