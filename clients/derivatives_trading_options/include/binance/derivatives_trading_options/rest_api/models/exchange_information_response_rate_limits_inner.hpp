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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct ExchangeInformationResponseRateLimitsInner {
    /// rate Limit Type
    std::optional<std::string> rate_limit_type;
    /// interval
    std::optional<std::string> interval;
    /// interval Num
    std::optional<std::int64_t> interval_num;
    /// limit
    std::optional<std::int64_t> limit;

    bool operator==(const ExchangeInformationResponseRateLimitsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT ExchangeInformationResponseRateLimitsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseRateLimitsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseRateLimitsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
