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
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetBnsolRateHistoryResponse {
    std::optional<std::vector<GetBnsolRateHistoryResponseRowsInner>> rows;
    std::optional<std::string> total;

    bool operator==(const GetBnsolRateHistoryResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetBnsolRateHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetBnsolRateHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetBnsolRateHistoryResponse& v);

} // namespace binance::staking::rest_api
