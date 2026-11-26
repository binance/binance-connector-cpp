//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/exchange_max_num_iceberg_orders_filter.hpp>

namespace binance::spot::websocket_api {

ExchangeMaxNumIcebergOrdersFilter
tag_invoke(boost::json::value_to_tag<ExchangeMaxNumIcebergOrdersFilter> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ExchangeMaxNumIcebergOrdersFilter");
    ExchangeMaxNumIcebergOrdersFilter out;
    common::detail::json::read(obj, "filterType", out.filter_type);
    common::detail::json::read(obj, "maxNumIcebergOrders", out.max_num_iceberg_orders);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ExchangeMaxNumIcebergOrdersFilter& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "filterType", v.filter_type);
    common::detail::json::write(obj, "maxNumIcebergOrders", v.max_num_iceberg_orders);
}

} // namespace binance::spot::websocket_api
