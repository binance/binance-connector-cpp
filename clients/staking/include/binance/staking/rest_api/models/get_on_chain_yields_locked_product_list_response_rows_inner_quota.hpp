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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedProductListResponseRowsInnerQuota {
    /// Total Personal quota
    std::optional<std::string> total_personal_quota;
    /// Minimum amount per order
    std::optional<std::string> minimum;

    bool operator==(
        const GetOnChainYieldsLockedProductListResponseRowsInnerQuota& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedProductListResponseRowsInnerQuota tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedProductListResponseRowsInnerQuota> /*tag*/,
    const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedProductListResponseRowsInnerQuota& v);

} // namespace binance::staking::rest_api
