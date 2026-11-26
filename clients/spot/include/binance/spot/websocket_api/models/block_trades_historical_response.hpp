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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/block_trades_historical_response_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/block_trades_historical_response_result_inner.hpp>

namespace binance::spot::websocket_api {

struct BlockTradesHistoricalResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<BlockTradesHistoricalResponseResultInner>> result;
    std::optional<std::vector<BlockTradesHistoricalResponseRateLimitsInner>> rate_limits;

    bool operator==(const BlockTradesHistoricalResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT BlockTradesHistoricalResponse tag_invoke(
    boost::json::value_to_tag<BlockTradesHistoricalResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const BlockTradesHistoricalResponse& v);

} // namespace binance::spot::websocket_api
