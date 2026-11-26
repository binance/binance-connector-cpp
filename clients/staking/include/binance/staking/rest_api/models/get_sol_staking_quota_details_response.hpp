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

struct GetSolStakingQuotaDetailsResponse {
    std::optional<std::string> left_staking_personal_quota;
    std::optional<std::string> left_redemption_personal_quota;
    std::optional<std::string> min_stake_amount;
    std::optional<std::string> min_redeem_amount;
    std::optional<std::int64_t> redeem_period;
    std::optional<bool> stakeable;
    std::optional<bool> redeemable;
    std::optional<bool> sold_out;
    std::optional<std::string> commission_fee;
    std::optional<std::int64_t> next_epoch_time;
    std::optional<bool> calculating;

    bool operator==(const GetSolStakingQuotaDetailsResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetSolStakingQuotaDetailsResponse
tag_invoke(boost::json::value_to_tag<GetSolStakingQuotaDetailsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetSolStakingQuotaDetailsResponse& v);

} // namespace binance::staking::rest_api
