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

struct GetFundingRateInfoResponseInner {
    std::optional<std::string> symbol;
    std::optional<std::string> adjusted_funding_rate_cap;
    std::optional<std::string> adjusted_funding_rate_floor;
    std::optional<std::int64_t> funding_interval_hours;
    /// ingore
    std::optional<bool> disclaimer;

    bool operator==(const GetFundingRateInfoResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetFundingRateInfoResponseInner
tag_invoke(boost::json::value_to_tag<GetFundingRateInfoResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFundingRateInfoResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
