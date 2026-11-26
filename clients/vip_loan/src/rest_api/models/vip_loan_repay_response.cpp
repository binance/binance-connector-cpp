//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_repay_response.hpp>

namespace binance::vip_loan::rest_api {

VipLoanRepayResponse tag_invoke(boost::json::value_to_tag<VipLoanRepayResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "VipLoanRepayResponse");
    VipLoanRepayResponse out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "repayAmount", out.repay_amount);
    common::detail::json::read(obj, "remainingPrincipal", out.remaining_principal);
    common::detail::json::read(obj, "remainingInterest", out.remaining_interest);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "currentLTV", out.current_ltv);
    common::detail::json::read(obj, "repayStatus", out.repay_status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VipLoanRepayResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "repayAmount", v.repay_amount);
    common::detail::json::write(obj, "remainingPrincipal", v.remaining_principal);
    common::detail::json::write(obj, "remainingInterest", v.remaining_interest);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "currentLTV", v.current_ltv);
    common::detail::json::write(obj, "repayStatus", v.repay_status);
}

} // namespace binance::vip_loan::rest_api
