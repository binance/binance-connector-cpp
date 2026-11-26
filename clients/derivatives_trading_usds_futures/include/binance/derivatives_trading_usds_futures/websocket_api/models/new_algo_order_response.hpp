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

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/cancel_order_response_rate_limits_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/new_algo_order_response_result.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct NewAlgoOrderResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<NewAlgoOrderResponseResult> result;
    std::optional<std::vector<CancelOrderResponseRateLimitsInner>> rate_limits;

    bool operator==(const NewAlgoOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NewAlgoOrderResponse
tag_invoke(boost::json::value_to_tag<NewAlgoOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const NewAlgoOrderResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
