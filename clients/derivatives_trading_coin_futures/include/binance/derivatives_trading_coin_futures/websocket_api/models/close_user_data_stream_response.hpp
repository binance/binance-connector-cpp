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

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/close_user_data_stream_response_rate_limits_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

struct CloseUserDataStreamResponse {
    /// positionId
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    /// Indicates that combined is set to true.
    std::optional<boost::json::value> result;
    /// Rate limit definitions.
    std::optional<std::vector<CloseUserDataStreamResponseRateLimitsInner>> rate_limits;

    bool operator==(const CloseUserDataStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT CloseUserDataStreamResponse tag_invoke(
    boost::json::value_to_tag<CloseUserDataStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CloseUserDataStreamResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
