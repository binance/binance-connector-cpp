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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response_rate_limits_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response_symbols_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ExchangeInformationResponse {
    /// Exchange filters.
    std::optional<std::vector<std::string>> exchange_filters;
    /// Rate limit definitions.
    std::optional<std::vector<ExchangeInformationResponseRateLimitsInner>> rate_limits;
    /// Ignore please. If you want to check current server time, please check via "GET
    /// /dapi/v1/time"
    std::optional<std::int64_t> server_time;
    /// Supported trading symbols.
    std::optional<std::vector<ExchangeInformationResponseSymbolsInner>> symbols;
    /// Timezone of market data.
    std::optional<std::string> timezone;

    bool operator==(const ExchangeInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ExchangeInformationResponse tag_invoke(
    boost::json::value_to_tag<ExchangeInformationResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
