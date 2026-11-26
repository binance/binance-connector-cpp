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
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_record_response_rows_inner.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedSubscriptionRecordResponse {
    std::optional<std::vector<GetOnChainYieldsLockedSubscriptionRecordResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool
    operator==(const GetOnChainYieldsLockedSubscriptionRecordResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedSubscriptionRecordResponse
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedSubscriptionRecordResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetOnChainYieldsLockedSubscriptionRecordResponse& v);

} // namespace binance::staking::rest_api
