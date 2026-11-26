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

#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rate_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetWbethRateHistoryResponse {
    std::optional<std::vector<GetWbethRateHistoryResponseRowsInner>> rows;
    std::optional<std::string> total;

    bool operator==(const GetWbethRateHistoryResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetWbethRateHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetWbethRateHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetWbethRateHistoryResponse& v);

} // namespace binance::staking::rest_api
