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
#include <binance/staking/rest_api/models/get_sol_redemption_history_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetSolRedemptionHistoryResponse {
    std::optional<std::vector<GetSolRedemptionHistoryResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetSolRedemptionHistoryResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetSolRedemptionHistoryResponse
tag_invoke(boost::json::value_to_tag<GetSolRedemptionHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetSolRedemptionHistoryResponse& v);

} // namespace binance::staking::rest_api
