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
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_redemption_record_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedRedemptionRecordResponse {
    std::optional<std::vector<GetOnChainYieldsLockedRedemptionRecordResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool
    operator==(const GetOnChainYieldsLockedRedemptionRecordResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedRedemptionRecordResponse
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedRedemptionRecordResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetOnChainYieldsLockedRedemptionRecordResponse& v);

} // namespace binance::staking::rest_api
