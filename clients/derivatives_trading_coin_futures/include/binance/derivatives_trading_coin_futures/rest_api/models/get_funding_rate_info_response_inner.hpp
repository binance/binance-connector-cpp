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

struct GetFundingRateInfoResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Adjusted funding rate cap.
    std::optional<std::string> adjusted_funding_rate_cap;
    /// Adjusted funding rate floor.
    std::optional<std::string> adjusted_funding_rate_floor;
    /// Funding interval in hours.
    std::optional<std::int64_t> funding_interval_hours;
    /// Disclaimer text.
    std::optional<bool> disclaimer;

    bool operator==(const GetFundingRateInfoResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetFundingRateInfoResponseInner
tag_invoke(boost::json::value_to_tag<GetFundingRateInfoResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFundingRateInfoResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
