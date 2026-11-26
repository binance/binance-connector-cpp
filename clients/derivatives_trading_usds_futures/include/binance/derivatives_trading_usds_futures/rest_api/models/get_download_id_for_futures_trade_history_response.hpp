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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetDownloadIdForFuturesTradeHistoryResponse {
    /// Average time taken for data download in the past 30 days
    std::optional<std::int64_t> avg_cost_timestamp_of_last30d;
    /// Download Id.
    std::optional<std::string> download_id;

    bool operator==(const GetDownloadIdForFuturesTradeHistoryResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetDownloadIdForFuturesTradeHistoryResponse
tag_invoke(boost::json::value_to_tag<GetDownloadIdForFuturesTradeHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDownloadIdForFuturesTradeHistoryResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
