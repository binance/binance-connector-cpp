//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/equity_order_detail_response_trades_inner.hpp>

namespace binance::stocks::rest_api {

EquityOrderDetailResponseTradesInner
tag_invoke(boost::json::value_to_tag<EquityOrderDetailResponseTradesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "EquityOrderDetailResponseTradesInner");
    EquityOrderDetailResponseTradesInner out;
    common::detail::json::read(obj, "executionId", out.execution_id);
    common::detail::json::read(obj, "executionAt", out.execution_at);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "qty", out.qty);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const EquityOrderDetailResponseTradesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "executionId", v.execution_id);
    common::detail::json::write(obj, "executionAt", v.execution_at);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "qty", v.qty);
}

} // namespace binance::stocks::rest_api
