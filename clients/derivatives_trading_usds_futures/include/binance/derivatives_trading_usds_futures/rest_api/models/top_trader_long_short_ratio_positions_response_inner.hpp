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

struct TopTraderLongShortRatioPositionsResponseInner {
    std::optional<std::string> symbol;
    /// long/short position ratio of top traders
    std::optional<std::string> long_short_ratio;
    /// long positions ratio of top traders
    std::optional<std::string> long_account;
    /// short positions ratio of top traders
    std::optional<std::string> short_account;
    /// End time of the period, in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const TopTraderLongShortRatioPositionsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TopTraderLongShortRatioPositionsResponseInner
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TopTraderLongShortRatioPositionsResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
