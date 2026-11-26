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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct StartUserDataStreamResponse {
    /// listen Key
    std::optional<std::string> listen_key;
    /// Listen key expiration timestamp in milliseconds
    std::optional<std::int64_t> expiration;

    bool operator==(const StartUserDataStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT StartUserDataStreamResponse tag_invoke(
    boost::json::value_to_tag<StartUserDataStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const StartUserDataStreamResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
