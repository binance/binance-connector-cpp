//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_pro_bankruptcy_loan_repay_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

PortfolioMarginProBankruptcyLoanRepayResponse
tag_invoke(boost::json::value_to_tag<PortfolioMarginProBankruptcyLoanRepayResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PortfolioMarginProBankruptcyLoanRepayResponse");
    PortfolioMarginProBankruptcyLoanRepayResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PortfolioMarginProBankruptcyLoanRepayResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
