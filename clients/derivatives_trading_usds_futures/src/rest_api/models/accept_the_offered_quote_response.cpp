//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/accept_the_offered_quote_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

AcceptTheOfferedQuoteResponse
tag_invoke(boost::json::value_to_tag<AcceptTheOfferedQuoteResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AcceptTheOfferedQuoteResponse");
    AcceptTheOfferedQuoteResponse out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "orderStatus", out.order_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AcceptTheOfferedQuoteResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "orderStatus", v.order_status);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
