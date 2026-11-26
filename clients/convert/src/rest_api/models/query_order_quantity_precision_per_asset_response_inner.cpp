//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/query_order_quantity_precision_per_asset_response_inner.hpp>

namespace binance::convert::rest_api {

QueryOrderQuantityPrecisionPerAssetResponseInner
tag_invoke(boost::json::value_to_tag<QueryOrderQuantityPrecisionPerAssetResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryOrderQuantityPrecisionPerAssetResponseInner");
    QueryOrderQuantityPrecisionPerAssetResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "fraction", out.fraction);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryOrderQuantityPrecisionPerAssetResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "fraction", v.fraction);
}

} // namespace binance::convert::rest_api
