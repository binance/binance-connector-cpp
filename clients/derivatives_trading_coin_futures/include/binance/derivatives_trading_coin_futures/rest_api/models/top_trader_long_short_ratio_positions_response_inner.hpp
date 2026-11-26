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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct TopTraderLongShortRatioPositionsResponseInner {
    /// Pair
    std::optional<std::string> pair;
    /// Long/short ratio.
    std::optional<std::string> long_short_ratio;
    /// 64.42%
    std::optional<std::string> long_position;
    /// 44.04%
    std::optional<std::string> short_position;
    /// End time of the period, in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const TopTraderLongShortRatioPositionsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TopTraderLongShortRatioPositionsResponseInner
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TopTraderLongShortRatioPositionsResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
