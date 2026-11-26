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

struct WrapBethResponse {
    std::optional<bool> success;
    std::optional<std::string> wbeth_amount;
    std::optional<std::string> exchange_rate;

    bool operator==(const WrapBethResponse& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT WrapBethResponse
tag_invoke(boost::json::value_to_tag<WrapBethResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const WrapBethResponse& v);

} // namespace binance::staking::rest_api
