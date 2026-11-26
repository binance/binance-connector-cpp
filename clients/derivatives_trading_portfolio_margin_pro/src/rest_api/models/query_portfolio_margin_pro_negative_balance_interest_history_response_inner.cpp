//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_negative_balance_interest_history_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner");
    QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "interestAccruedTime", out.interest_accrued_time);
    common::detail::json::read(obj, "interestRate", out.interest_rate);
    common::detail::json::read(obj, "principal", out.principal);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "interestAccruedTime", v.interest_accrued_time);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "principal", v.principal);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
