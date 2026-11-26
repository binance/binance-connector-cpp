//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/check_vip_loan_collateral_account_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

CheckVIPLoanCollateralAccountResponseRowsInner
tag_invoke(boost::json::value_to_tag<CheckVIPLoanCollateralAccountResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CheckVIPLoanCollateralAccountResponseRowsInner");
    CheckVIPLoanCollateralAccountResponseRowsInner out;
    common::detail::json::read(obj, "collateralAccountId", out.collateral_account_id);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CheckVIPLoanCollateralAccountResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "collateralAccountId", v.collateral_account_id);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
}

} // namespace binance::vip_loan::rest_api
