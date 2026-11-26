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

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_assets_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_contracts_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_rate_limits_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct ExchangeInformationResponse {
    /// Time zone used by the server
    std::optional<std::string> timezone;
    /// Current system time
    std::optional<std::int64_t> server_time;
    /// Option contract underlying asset info
    std::optional<std::vector<ExchangeInformationResponseOptionContractsInner>> option_contracts;
    /// Option asset info
    std::optional<std::vector<ExchangeInformationResponseOptionAssetsInner>> option_assets;
    /// Option trading pair info
    std::optional<std::vector<ExchangeInformationResponseOptionSymbolsInner>> option_symbols;
    /// rate Limits
    std::optional<std::vector<ExchangeInformationResponseRateLimitsInner>> rate_limits;

    bool operator==(const ExchangeInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT ExchangeInformationResponse tag_invoke(
    boost::json::value_to_tag<ExchangeInformationResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const ExchangeInformationResponse& v);

} // namespace binance::derivatives_trading_options::rest_api
