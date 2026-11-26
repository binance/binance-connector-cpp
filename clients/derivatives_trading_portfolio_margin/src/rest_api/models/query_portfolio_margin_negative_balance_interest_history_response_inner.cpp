//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_portfolio_margin_negative_balance_interest_history_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner");
    QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "interest", out.interest);
    common::detail::json::read(obj, "interestAccuredTime", out.interest_accured_time);
    common::detail::json::read(obj, "interestRate", out.interest_rate);
    common::detail::json::read(obj, "principal", out.principal);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "interest", v.interest);
    common::detail::json::write(obj, "interestAccuredTime", v.interest_accured_time);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "principal", v.principal);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
