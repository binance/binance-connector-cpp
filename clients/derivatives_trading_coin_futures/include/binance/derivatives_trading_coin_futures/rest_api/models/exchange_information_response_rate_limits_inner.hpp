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

struct ExchangeInformationResponseRateLimitsInner {
    /// Rate limit interval.
    std::optional<std::string> interval;
    /// Rate limit interval multiplier.
    std::optional<std::int64_t> interval_num;
    /// Maximum allowed orders for this rule.
    std::optional<std::int64_t> limit;
    /// Rate limit type.
    std::optional<std::string> rate_limit_type;

    bool operator==(const ExchangeInformationResponseRateLimitsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ExchangeInformationResponseRateLimitsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseRateLimitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseRateLimitsInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
