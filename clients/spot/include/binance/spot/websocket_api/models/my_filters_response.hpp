//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/exchange_filters.hpp>
#include <binance/spot/websocket_api/models/max_asset_filter.hpp>
#include <binance/spot/websocket_api/models/rate_limits.hpp>
#include <binance/spot/websocket_api/models/symbol_filters.hpp>

namespace binance::spot::websocket_api {

struct MyFiltersResponse {
    std::optional<std::vector<ExchangeFilters>> exchange_filters;
    std::optional<std::vector<SymbolFilters>> symbol_filters;
    std::optional<std::vector<MaxAssetFilter>> asset_filters;
    std::optional<std::vector<RateLimits>> rate_limits;

    bool operator==(const MyFiltersResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyFiltersResponse
tag_invoke(boost::json::value_to_tag<MyFiltersResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyFiltersResponse& v);

} // namespace binance::spot::websocket_api
