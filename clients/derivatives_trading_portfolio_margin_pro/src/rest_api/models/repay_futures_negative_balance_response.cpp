//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/repay_futures_negative_balance_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

RepayFuturesNegativeBalanceResponse
tag_invoke(boost::json::value_to_tag<RepayFuturesNegativeBalanceResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "RepayFuturesNegativeBalanceResponse");
    RepayFuturesNegativeBalanceResponse out;
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const RepayFuturesNegativeBalanceResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
