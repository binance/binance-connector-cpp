//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/max_asset_filter.hpp>

namespace binance::spot::rest_api {

struct MyFiltersResponseAssetFiltersInner {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<MaxAssetFilter, boost::json::value> value;

    bool operator==(const MyFiltersResponseAssetFiltersInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyFiltersResponseAssetFiltersInner
tag_invoke(boost::json::value_to_tag<MyFiltersResponseAssetFiltersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyFiltersResponseAssetFiltersInner& v);

} // namespace binance::spot::rest_api
