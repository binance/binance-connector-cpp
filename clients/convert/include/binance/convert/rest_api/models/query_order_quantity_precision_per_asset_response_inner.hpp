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

#include <binance/convert/export.hpp>

namespace binance::convert::rest_api {

struct QueryOrderQuantityPrecisionPerAssetResponseInner {
    std::optional<std::string> asset;
    std::optional<std::int64_t> fraction;

    bool
    operator==(const QueryOrderQuantityPrecisionPerAssetResponseInner& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT QueryOrderQuantityPrecisionPerAssetResponseInner
tag_invoke(boost::json::value_to_tag<QueryOrderQuantityPrecisionPerAssetResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const QueryOrderQuantityPrecisionPerAssetResponseInner& v);

} // namespace binance::convert::rest_api
