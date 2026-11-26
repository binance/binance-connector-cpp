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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct RedeemLockedProductResponse {
    std::optional<std::int64_t> redeem_id;
    std::optional<bool> success;

    bool operator==(const RedeemLockedProductResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT RedeemLockedProductResponse tag_invoke(
    boost::json::value_to_tag<RedeemLockedProductResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const RedeemLockedProductResponse& v);

} // namespace binance::simple_earn::rest_api
