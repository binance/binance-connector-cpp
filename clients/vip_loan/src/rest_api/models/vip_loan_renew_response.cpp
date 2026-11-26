//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_renew_response.hpp>

namespace binance::vip_loan::rest_api {

VipLoanRenewResponse tag_invoke(boost::json::value_to_tag<VipLoanRenewResponse> /*tag*/,
                                const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "VipLoanRenewResponse");
    VipLoanRenewResponse out;
    common::detail::json::read(obj, "loanAccountId", out.loan_account_id);
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "loanAmount", out.loan_amount);
    common::detail::json::read(obj, "collateralAccountId", out.collateral_account_id);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "loanTerm", out.loan_term);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VipLoanRenewResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanAccountId", v.loan_account_id);
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "loanAmount", v.loan_amount);
    common::detail::json::write(obj, "collateralAccountId", v.collateral_account_id);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "loanTerm", v.loan_term);
}

} // namespace binance::vip_loan::rest_api
