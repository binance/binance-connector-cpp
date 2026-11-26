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
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetSoftStakingProductListResponse {
    std::optional<bool> status;
    std::optional<std::string> total_rewards_usdt;
    std::optional<std::vector<GetSoftStakingProductListResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetSoftStakingProductListResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetSoftStakingProductListResponse
tag_invoke(boost::json::value_to_tag<GetSoftStakingProductListResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetSoftStakingProductListResponse& v);

} // namespace binance::staking::rest_api
