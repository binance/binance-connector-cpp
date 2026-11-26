//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/ticker24hr_price_change_statistics_response1.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/ticker24hr_price_change_statistics_response2_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct Ticker24hrPriceChangeStatisticsResponse {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<Ticker24hrPriceChangeStatisticsResponse1,
                 std::vector<Ticker24hrPriceChangeStatisticsResponse2Inner>, boost::json::value>
        value;

    bool operator==(const Ticker24hrPriceChangeStatisticsResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT Ticker24hrPriceChangeStatisticsResponse
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const Ticker24hrPriceChangeStatisticsResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
