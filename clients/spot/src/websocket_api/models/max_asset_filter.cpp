//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/max_asset_filter.hpp>

namespace binance::spot::websocket_api {

MaxAssetFilter tag_invoke(boost::json::value_to_tag<MaxAssetFilter> /*tag*/,
                          const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MaxAssetFilter");
    MaxAssetFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "qtyExponent", out.qty_exponent);
    common::detail::json::read(obj, "limit", out.limit);
    common::detail::json::read(obj, "asset", out.asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MaxAssetFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "qtyExponent", v.qty_exponent);
    common::detail::json::write(obj, "limit", v.limit);
    common::detail::json::write(obj, "asset", v.asset);
}

} // namespace binance::spot::websocket_api
