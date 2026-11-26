//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_accrued_interest_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetVIPLoanAccruedInterestResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanAccruedInterestResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetVIPLoanAccruedInterestResponseRowsInner");
    GetVIPLoanAccruedInterestResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "principalAmount", out.principal_amount);
    common::detail::json::read(obj, "interestAmount", out.interest_amount);
    common::detail::json::read(obj, "annualInterestRate", out.annual_interest_rate);
    common::detail::json::read(obj, "accrualTime", out.accrual_time);
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetVIPLoanAccruedInterestResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "principalAmount", v.principal_amount);
    common::detail::json::write(obj, "interestAmount", v.interest_amount);
    common::detail::json::write(obj, "annualInterestRate", v.annual_interest_rate);
    common::detail::json::write(obj, "accrualTime", v.accrual_time);
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::vip_loan::rest_api
