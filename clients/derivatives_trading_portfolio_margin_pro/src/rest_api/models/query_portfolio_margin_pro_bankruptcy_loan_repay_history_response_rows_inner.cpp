//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_bankruptcy_loan_repay_history_response_rows_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<
               QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner");
    QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "repayTime", out.repay_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "repayTime", v.repay_time);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
