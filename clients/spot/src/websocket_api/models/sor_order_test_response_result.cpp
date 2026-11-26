//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/sor_order_test_response_result.hpp>

namespace binance::spot::websocket_api {

SorOrderTestResponseResult tag_invoke(boost::json::value_to_tag<SorOrderTestResponseResult> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SorOrderTestResponseResult");
    SorOrderTestResponseResult out;
    common::detail::json::read(obj, "standardCommissionForOrder",
                               out.standard_commission_for_order);
    common::detail::json::read(obj, "taxCommissionForOrder", out.tax_commission_for_order);
    common::detail::json::read(obj, "discount", out.discount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SorOrderTestResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "standardCommissionForOrder", v.standard_commission_for_order);
    common::detail::json::write(obj, "taxCommissionForOrder", v.tax_commission_for_order);
    common::detail::json::write(obj, "discount", v.discount);
}

} // namespace binance::spot::websocket_api
