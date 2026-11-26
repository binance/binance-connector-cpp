//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/get_order_detail_response_data.hpp>

namespace binance::fiat::rest_api {

GetOrderDetailResponseData tag_invoke(boost::json::value_to_tag<GetOrderDetailResponseData> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetOrderDetailResponseData");
    GetOrderDetailResponseData out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "fee", out.fee);
    common::detail::json::read(obj, "fiatCurrency", out.fiat_currency);
    common::detail::json::read(obj, "errorCode", out.error_code);
    common::detail::json::read(obj, "errorMessage", out.error_message);
    common::detail::json::read(obj, "ext", out.ext);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOrderDetailResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "orderStatus", v.order_status);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "fee", v.fee);
    common::detail::json::write(obj, "fiatCurrency", v.fiat_currency);
    common::detail::json::write(obj, "errorCode", v.error_code);
    common::detail::json::write(obj, "errorMessage", v.error_message);
    common::detail::json::write(obj, "ext", v.ext);
}

} // namespace binance::fiat::rest_api
