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

#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rate_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

struct GetBfusdRateHistoryResponse {
    std::optional<std::vector<GetBfusdRateHistoryResponseRowsInner>> rows;
    std::optional<std::string> total;

    bool operator==(const GetBfusdRateHistoryResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetBfusdRateHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetBfusdRateHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetBfusdRateHistoryResponse& v);

} // namespace binance::simple_earn::rest_api
