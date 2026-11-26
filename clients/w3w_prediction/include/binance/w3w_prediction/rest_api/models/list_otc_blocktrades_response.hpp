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
#include <binance/w3w_prediction/rest_api/models/list_otc_blocktrades_response_blocktrades_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct ListOtcBlocktradesResponse {
    std::optional<std::string> cursor;
    std::optional<std::vector<ListOtcBlocktradesResponseBlocktradesInner>> blocktrades;

    bool operator==(const ListOtcBlocktradesResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListOtcBlocktradesResponse tag_invoke(
    boost::json::value_to_tag<ListOtcBlocktradesResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const ListOtcBlocktradesResponse& v);

} // namespace binance::w3w_prediction::rest_api
