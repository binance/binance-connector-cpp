//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_ongoing_orders_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetVIPLoanOngoingOrdersResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetVIPLoanOngoingOrdersResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetVIPLoanOngoingOrdersResponseRowsInner");
    GetVIPLoanOngoingOrdersResponseRowsInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "totalDebt", out.total_debt);
    common::detail::json::read(obj, "loanRate", out.loan_rate);
    common::detail::json::read(obj, "residualInterest", out.residual_interest);
    common::detail::json::read(obj, "collateralAccountId", out.collateral_account_id);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "totalCollateralValueAfterHaircut",
                               out.total_collateral_value_after_haircut);
    common::detail::json::read(obj, "lockedCollateralValue", out.locked_collateral_value);
    common::detail::json::read(obj, "currentLTV", out.current_ltv);
    common::detail::json::read(obj, "expirationTime", out.expiration_time);
    common::detail::json::read(obj, "loanDate", out.loan_date);
    common::detail::json::read(obj, "loanTerm", out.loan_term);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetVIPLoanOngoingOrdersResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "totalDebt", v.total_debt);
    common::detail::json::write(obj, "loanRate", v.loan_rate);
    common::detail::json::write(obj, "residualInterest", v.residual_interest);
    common::detail::json::write(obj, "collateralAccountId", v.collateral_account_id);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "totalCollateralValueAfterHaircut",
                                v.total_collateral_value_after_haircut);
    common::detail::json::write(obj, "lockedCollateralValue", v.locked_collateral_value);
    common::detail::json::write(obj, "currentLTV", v.current_ltv);
    common::detail::json::write(obj, "expirationTime", v.expiration_time);
    common::detail::json::write(obj, "loanDate", v.loan_date);
    common::detail::json::write(obj, "loanTerm", v.loan_term);
}

} // namespace binance::vip_loan::rest_api
