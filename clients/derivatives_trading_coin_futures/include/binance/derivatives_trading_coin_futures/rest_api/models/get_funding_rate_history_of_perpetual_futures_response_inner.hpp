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

struct GetFundingRateHistoryOfPerpetualFuturesResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Funding time.
    std::optional<std::int64_t> funding_time;
    /// Funding rate.
    std::optional<std::string> funding_rate;

    bool operator==(const GetFundingRateHistoryOfPerpetualFuturesResponseInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetFundingRateHistoryOfPerpetualFuturesResponseInner
tag_invoke(boost::json::value_to_tag<GetFundingRateHistoryOfPerpetualFuturesResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFundingRateHistoryOfPerpetualFuturesResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
