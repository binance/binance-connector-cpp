//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/cancel_all_algo_open_orders_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

CancelAllAlgoOpenOrdersResponse
tag_invoke(boost::json::value_to_tag<CancelAllAlgoOpenOrdersResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelAllAlgoOpenOrdersResponse");
    CancelAllAlgoOpenOrdersResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelAllAlgoOpenOrdersResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
