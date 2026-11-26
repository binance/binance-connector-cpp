//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/accept_quote_response.hpp>

namespace binance::convert::rest_api {

AcceptQuoteResponse tag_invoke(boost::json::value_to_tag<AcceptQuoteResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AcceptQuoteResponse");
    AcceptQuoteResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AcceptQuoteResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "orderStatus", v.order_status);
}

} // namespace binance::convert::rest_api
