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
#include <binance/simple_earn/rest_api/models/get_rwusd_rate_history_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

struct GetRwusdRateHistoryResponse {
    std::optional<std::vector<GetRwusdRateHistoryResponseRowsInner>> rows;
    std::optional<std::string> total;

    bool operator==(const GetRwusdRateHistoryResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetRwusdRateHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetRwusdRateHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetRwusdRateHistoryResponse& v);

} // namespace binance::simple_earn::rest_api
