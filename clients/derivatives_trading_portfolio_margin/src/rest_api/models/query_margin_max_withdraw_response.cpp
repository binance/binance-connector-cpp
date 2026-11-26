//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_max_withdraw_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryMarginMaxWithdrawResponse
tag_invoke(boost::json::value_to_tag<QueryMarginMaxWithdrawResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMarginMaxWithdrawResponse");
    QueryMarginMaxWithdrawResponse out;
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMarginMaxWithdrawResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
