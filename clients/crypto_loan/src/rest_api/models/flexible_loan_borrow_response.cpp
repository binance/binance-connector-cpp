//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_borrow_response.hpp>

namespace binance::crypto_loan::rest_api {

FlexibleLoanBorrowResponse tag_invoke(boost::json::value_to_tag<FlexibleLoanBorrowResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FlexibleLoanBorrowResponse");
    FlexibleLoanBorrowResponse out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "loanAmount", out.loan_amount);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "collateralAmount", out.collateral_amount);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FlexibleLoanBorrowResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "loanAmount", v.loan_amount);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "collateralAmount", v.collateral_amount);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::crypto_loan::rest_api
