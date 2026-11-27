//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/cancel_algo_order_response.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

CancelAlgoOrderResponse tag_invoke(boost::json::value_to_tag<CancelAlgoOrderResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelAlgoOrderResponse");
    CancelAlgoOrderResponse out;
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "clientAlgoId", out.client_algo_id);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelAlgoOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "clientAlgoId", v.client_algo_id);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
