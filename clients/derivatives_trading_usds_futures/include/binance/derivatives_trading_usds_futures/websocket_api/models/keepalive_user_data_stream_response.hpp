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
#include <binance/derivatives_trading_usds_futures/websocket_api/models/keepalive_user_data_stream_response_result.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/models/symbol_order_book_ticker_response1_rate_limits_inner.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct KeepaliveUserDataStreamResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<KeepaliveUserDataStreamResponseResult> result;
    std::optional<std::vector<SymbolOrderBookTickerResponse1RateLimitsInner>> rate_limits;

    bool operator==(const KeepaliveUserDataStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT KeepaliveUserDataStreamResponse
tag_invoke(boost::json::value_to_tag<KeepaliveUserDataStreamResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const KeepaliveUserDataStreamResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
