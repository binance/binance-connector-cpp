//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_repayment_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanRepaymentHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanRepaymentHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanRepaymentHistoryResponseRowsInner");
    GetFlexibleLoanRepaymentHistoryResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "repayAmount", out.repay_amount);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "collateralReturn", out.collateral_return);
    common::detail::json::read(obj, "repayStatus", out.repay_status);
    common::detail::json::read(obj, "repayTime", out.repay_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanRepaymentHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "repayAmount", v.repay_amount);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "collateralReturn", v.collateral_return);
    common::detail::json::write(obj, "repayStatus", v.repay_status);
    common::detail::json::write(obj, "repayTime", v.repay_time);
}

} // namespace binance::crypto_loan::rest_api
