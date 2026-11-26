//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_borrow_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanBorrowHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanBorrowHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanBorrowHistoryResponseRowsInner");
    GetFlexibleLoanBorrowHistoryResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "initialLoanAmount", out.initial_loan_amount);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "initialCollateralAmount", out.initial_collateral_amount);
    common::detail::json::read(obj, "borrowTime", out.borrow_time);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanBorrowHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "initialLoanAmount", v.initial_loan_amount);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "initialCollateralAmount", v.initial_collateral_amount);
    common::detail::json::write(obj, "borrowTime", v.borrow_time);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::crypto_loan::rest_api
