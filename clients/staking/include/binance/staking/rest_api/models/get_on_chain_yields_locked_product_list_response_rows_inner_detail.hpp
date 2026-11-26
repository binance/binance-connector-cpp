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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/staking/export.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedProductListResponseRowsInnerDetail {
    /// Lock up asset
    std::optional<std::string> asset;
    /// Earn Asset
    std::optional<std::string> reward_asset;
    /// Lock period(days)
    std::optional<std::int64_t> duration;
    /// Project supports renewal (auto-subscribe when maturity)
    std::optional<bool> renewable;
    std::optional<bool> is_sold_out;
    /// 0.039 stands for 3.9%
    std::optional<std::string> apr;
    /// PREHEATING,PURCHASING
    std::optional<std::string> status;
    std::optional<std::int64_t> subscription_start_time;
    /// Whether redemption to simple earn flexible is supported.
    std::optional<bool> can_redeem_to_flex;

    bool operator==(
        const GetOnChainYieldsLockedProductListResponseRowsInnerDetail& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedProductListResponseRowsInnerDetail tag_invoke(
    boost::json::value_to_tag<GetOnChainYieldsLockedProductListResponseRowsInnerDetail> /*tag*/,
    const boost::json::value& jv);
BINANCE_STAKING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOnChainYieldsLockedProductListResponseRowsInnerDetail& v);

} // namespace binance::staking::rest_api
