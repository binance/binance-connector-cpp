//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_ltv_adjustment_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner");
    GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "direction", out.direction);
    common::detail::json::read(obj, "collateralAmount", out.collateral_amount);
    common::detail::json::read(obj, "preLTV", out.pre_ltv);
    common::detail::json::read(obj, "afterLTV", out.after_ltv);
    common::detail::json::read(obj, "adjustTime", out.adjust_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanLtvAdjustmentHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "direction", v.direction);
    common::detail::json::write(obj, "collateralAmount", v.collateral_amount);
    common::detail::json::write(obj, "preLTV", v.pre_ltv);
    common::detail::json::write(obj, "afterLTV", v.after_ltv);
    common::detail::json::write(obj, "adjustTime", v.adjust_time);
}

} // namespace binance::crypto_loan::rest_api
