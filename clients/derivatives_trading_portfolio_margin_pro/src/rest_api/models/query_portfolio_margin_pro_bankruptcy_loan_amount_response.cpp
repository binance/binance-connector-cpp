//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_bankruptcy_loan_amount_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

QueryPortfolioMarginProBankruptcyLoanAmountResponse
tag_invoke(boost::json::value_to_tag<QueryPortfolioMarginProBankruptcyLoanAmountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QueryPortfolioMarginProBankruptcyLoanAmountResponse");
    QueryPortfolioMarginProBankruptcyLoanAmountResponse out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryPortfolioMarginProBankruptcyLoanAmountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
