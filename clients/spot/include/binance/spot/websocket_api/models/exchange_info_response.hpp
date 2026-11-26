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
#include <binance/spot/websocket_api/models/exchange_filters.hpp>
#include <binance/spot/websocket_api/models/exchange_info_response_sors_inner.hpp>
#include <binance/spot/websocket_api/models/exchange_info_response_symbols_inner.hpp>
#include <binance/spot/websocket_api/models/rate_limits.hpp>

namespace binance::spot::websocket_api {

struct ExchangeInfoResponse {
    std::optional<std::string> timezone;
    std::optional<std::int64_t> server_time;
    /// Global rate limits. See "Rate limits" section.
    std::optional<std::vector<RateLimits>> rate_limits;
    /// Exchange filters are explained on the "Filters" page: All exchange filters are optional.
    std::optional<std::vector<ExchangeFilters>> exchange_filters;
    std::optional<std::vector<ExchangeInfoResponseSymbolsInner>> symbols;
    /// Optional field. Present only when SOR is available.
    std::optional<std::vector<ExchangeInfoResponseSorsInner>> sors;

    bool operator==(const ExchangeInfoResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeInfoResponse
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeInfoResponse& v);

} // namespace binance::spot::websocket_api
