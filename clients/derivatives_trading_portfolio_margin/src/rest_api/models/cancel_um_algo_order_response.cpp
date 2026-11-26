//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cancel_um_algo_order_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

CancelUmAlgoOrderResponse tag_invoke(boost::json::value_to_tag<CancelUmAlgoOrderResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CancelUmAlgoOrderResponse");
    CancelUmAlgoOrderResponse out;
    common::detail::json::read(obj, "complete", out.complete);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CancelUmAlgoOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "complete", v.complete);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
