//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_auto_repay_futures_status_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

ChangeAutoRepayFuturesStatusResponse
tag_invoke(boost::json::value_to_tag<ChangeAutoRepayFuturesStatusResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ChangeAutoRepayFuturesStatusResponse");
    ChangeAutoRepayFuturesStatusResponse out;
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ChangeAutoRepayFuturesStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
