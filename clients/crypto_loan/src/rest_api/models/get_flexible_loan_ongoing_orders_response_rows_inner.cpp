//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_ongoing_orders_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanOngoingOrdersResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanOngoingOrdersResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanOngoingOrdersResponseRowsInner");
    GetFlexibleLoanOngoingOrdersResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "totalDebt", out.total_debt);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "collateralAmount", out.collateral_amount);
    common::detail::json::read(obj, "currentLTV", out.current_ltv);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanOngoingOrdersResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "totalDebt", v.total_debt);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "collateralAmount", v.collateral_amount);
    common::detail::json::write(obj, "currentLTV", v.current_ltv);
}

} // namespace binance::crypto_loan::rest_api
