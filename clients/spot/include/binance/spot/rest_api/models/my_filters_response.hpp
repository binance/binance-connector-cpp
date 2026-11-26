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
#include <binance/spot/rest_api/models/my_filters_response_asset_filters_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response_exchange_filters_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response_rate_limits_inner.hpp>
#include <binance/spot/rest_api/models/my_filters_response_symbol_filters_inner.hpp>

namespace binance::spot::rest_api {

struct MyFiltersResponse {
    std::optional<std::vector<MyFiltersResponseExchangeFiltersInner>> exchange_filters;
    std::optional<std::vector<MyFiltersResponseSymbolFiltersInner>> symbol_filters;
    std::optional<std::vector<MyFiltersResponseAssetFiltersInner>> asset_filters;
    std::optional<std::vector<MyFiltersResponseRateLimitsInner>> rate_limits;

    bool operator==(const MyFiltersResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyFiltersResponse
tag_invoke(boost::json::value_to_tag<MyFiltersResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyFiltersResponse& v);

} // namespace binance::spot::rest_api
