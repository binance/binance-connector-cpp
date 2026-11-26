//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_repayment_history_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetVIPLoanRepaymentHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanRepaymentHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetVIPLoanRepaymentHistoryResponseRowsInner");
    GetVIPLoanRepaymentHistoryResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "repayAmount", out.repay_amount);
    common::detail::json::read(obj, "repayPrincipal", out.repay_principal);
    common::detail::json::read(obj, "repayInterest", out.repay_interest);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "repayStatus", out.repay_status);
    common::detail::json::read(obj, "loanDate", out.loan_date);
    common::detail::json::read(obj, "repayTime", out.repay_time);
    common::detail::json::read(obj, "orderId", out.order_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetVIPLoanRepaymentHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "repayAmount", v.repay_amount);
    common::detail::json::write(obj, "repayPrincipal", v.repay_principal);
    common::detail::json::write(obj, "repayInterest", v.repay_interest);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "repayStatus", v.repay_status);
    common::detail::json::write(obj, "loanDate", v.loan_date);
    common::detail::json::write(obj, "repayTime", v.repay_time);
    common::detail::json::write(obj, "orderId", v.order_id);
}

} // namespace binance::vip_loan::rest_api
