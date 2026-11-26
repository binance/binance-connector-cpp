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
#include <binance/derivatives_trading_coin_futures/websocket_api/models/cancel_order_response_rate_limits_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/modify_order_response_result.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

struct ModifyOrderResponse {
    /// positionId
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<ModifyOrderResponseResult> result;
    /// Rate limit definitions.
    std::optional<std::vector<CancelOrderResponseRateLimitsInner>> rate_limits;

    bool operator==(const ModifyOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyOrderResponse
tag_invoke(boost::json::value_to_tag<ModifyOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const ModifyOrderResponse& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
