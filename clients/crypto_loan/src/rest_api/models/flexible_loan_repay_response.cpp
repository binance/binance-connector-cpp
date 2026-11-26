//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_repay_response.hpp>

namespace binance::crypto_loan::rest_api {

FlexibleLoanRepayResponse tag_invoke(boost::json::value_to_tag<FlexibleLoanRepayResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FlexibleLoanRepayResponse");
    FlexibleLoanRepayResponse out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "remainingDebt", out.remaining_debt);
    common::detail::json::read(obj, "remainingCollateral", out.remaining_collateral);
    common::detail::json::read(obj, "fullRepayment", out.full_repayment);
    common::detail::json::read(obj, "currentLTV", out.current_ltv);
    common::detail::json::read(obj, "repayStatus", out.repay_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FlexibleLoanRepayResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "remainingDebt", v.remaining_debt);
    common::detail::json::write(obj, "remainingCollateral", v.remaining_collateral);
    common::detail::json::write(obj, "fullRepayment", v.full_repayment);
    common::detail::json::write(obj, "currentLTV", v.current_ltv);
    common::detail::json::write(obj, "repayStatus", v.repay_status);
}

} // namespace binance::crypto_loan::rest_api
