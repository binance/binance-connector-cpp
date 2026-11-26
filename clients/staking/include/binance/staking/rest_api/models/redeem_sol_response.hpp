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

struct RedeemSolResponse {
    std::optional<bool> success;
    std::optional<std::string> sol_amount;
    std::optional<std::int64_t> redeem_id;
    std::optional<std::string> exchange_rate;
    std::optional<std::int64_t> arrival_time;

    bool operator==(const RedeemSolResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT RedeemSolResponse
tag_invoke(boost::json::value_to_tag<RedeemSolResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const RedeemSolResponse& v);

} // namespace binance::staking::rest_api
