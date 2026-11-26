//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetSolStakingHistoryResponse {
    std::optional<std::vector<GetSolStakingHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetSolStakingHistoryResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetSolStakingHistoryResponse tag_invoke(
    boost::json::value_to_tag<GetSolStakingHistoryResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetSolStakingHistoryResponse& v);

} // namespace binance::staking::rest_api
