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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetDownloadIdForCmFuturesOrderHistoryResponse {
    /// Average time taken for data download in the past 30 days
    std::optional<std::int64_t> avg_cost_timestamp_of_last30d;
    /// Download ID.
    std::optional<std::string> download_id;

    bool operator==(const GetDownloadIdForCmFuturesOrderHistoryResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetDownloadIdForCmFuturesOrderHistoryResponse
tag_invoke(boost::json::value_to_tag<GetDownloadIdForCmFuturesOrderHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDownloadIdForCmFuturesOrderHistoryResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
