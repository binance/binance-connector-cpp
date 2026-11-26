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

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/exchange_info_response_sors_inner.hpp>
#include <binance/spot/rest_api/models/exchange_info_response_symbols_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response_exchange_filters_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response_rate_limits_inner.hpp>

namespace binance::spot::rest_api {

struct ExchangeInfoResponse {
    std::optional<std::string> timezone;
    std::optional<std::int64_t> server_time;
    std::optional<std::vector<MyFiltersResponseRateLimitsInner>> rate_limits;
    /// Exchange filters are explained on the "Filters" page: All exchange filters are optional.
    std::optional<std::vector<MyFiltersResponseExchangeFiltersInner>> exchange_filters;
    std::optional<std::vector<ExchangeInfoResponseSymbolsInner>> symbols;
    /// Optional field. Present only when SOR is available.
    std::optional<std::vector<ExchangeInfoResponseSorsInner>> sors;

    bool operator==(const ExchangeInfoResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeInfoResponse
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeInfoResponse& v);

} // namespace binance::spot::rest_api
