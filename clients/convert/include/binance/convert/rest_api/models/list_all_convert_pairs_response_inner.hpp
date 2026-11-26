//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/convert/export.hpp>

namespace binance::convert::rest_api {

struct ListAllConvertPairsResponseInner {
    std::optional<std::string> from_asset;
    std::optional<std::string> to_asset;
    std::optional<std::string> from_asset_min_amount;
    std::optional<std::string> from_asset_max_amount;
    std::optional<std::string> to_asset_min_amount;
    /// 9E+24 signals that this symbol has a very large upper limit close to infinity
    std::optional<std::string> to_asset_max_amount;

    bool operator==(const ListAllConvertPairsResponseInner& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT ListAllConvertPairsResponseInner
tag_invoke(boost::json::value_to_tag<ListAllConvertPairsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const ListAllConvertPairsResponseInner& v);

} // namespace binance::convert::rest_api
