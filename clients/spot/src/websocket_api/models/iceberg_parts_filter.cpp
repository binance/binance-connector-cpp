//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/iceberg_parts_filter.hpp>

namespace binance::spot::websocket_api {

IcebergPartsFilter tag_invoke(boost::json::value_to_tag<IcebergPartsFilter> /*tag*/,
                              const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "IcebergPartsFilter");
    IcebergPartsFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "limit", out.limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const IcebergPartsFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "limit", v.limit);
}

} // namespace binance::spot::websocket_api
