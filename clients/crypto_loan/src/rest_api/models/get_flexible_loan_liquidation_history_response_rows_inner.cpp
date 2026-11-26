//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_liquidation_history_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanLiquidationHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanLiquidationHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanLiquidationHistoryResponseRowsInner");
    GetFlexibleLoanLiquidationHistoryResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "liquidationDebt", out.liquidation_debt);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "liquidationCollateralAmount",
                               out.liquidation_collateral_amount);
    common::detail::json::read(obj, "returnCollateralAmount", out.return_collateral_amount);
    common::detail::json::read(obj, "liquidationFee", out.liquidation_fee);
    common::detail::json::read(obj, "liquidationStartingPrice", out.liquidation_starting_price);
    common::detail::json::read(obj, "liquidationStartingTime", out.liquidation_starting_time);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanLiquidationHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "liquidationDebt", v.liquidation_debt);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "liquidationCollateralAmount",
                                v.liquidation_collateral_amount);
    common::detail::json::write(obj, "returnCollateralAmount", v.return_collateral_amount);
    common::detail::json::write(obj, "liquidationFee", v.liquidation_fee);
    common::detail::json::write(obj, "liquidationStartingPrice", v.liquidation_starting_price);
    common::detail::json::write(obj, "liquidationStartingTime", v.liquidation_starting_time);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::crypto_loan::rest_api
