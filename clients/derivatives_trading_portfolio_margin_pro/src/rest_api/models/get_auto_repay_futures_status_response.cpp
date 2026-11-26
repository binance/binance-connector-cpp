//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_auto_repay_futures_status_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetAutoRepayFuturesStatusResponse
tag_invoke(boost::json::value_to_tag<GetAutoRepayFuturesStatusResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetAutoRepayFuturesStatusResponse");
    GetAutoRepayFuturesStatusResponse out;
    common::detail::json::read(obj, "autoRepay", out.auto_repay);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetAutoRepayFuturesStatusResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "autoRepay", v.auto_repay);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
