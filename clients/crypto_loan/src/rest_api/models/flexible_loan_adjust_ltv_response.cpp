//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/flexible_loan_adjust_ltv_response.hpp>

namespace binance::crypto_loan::rest_api {

FlexibleLoanAdjustLtvResponse
tag_invoke(boost::json::value_to_tag<FlexibleLoanAdjustLtvResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FlexibleLoanAdjustLtvResponse");
    FlexibleLoanAdjustLtvResponse out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "direction", out.direction);
    common::detail::json::read(obj, "adjustmentAmount", out.adjustment_amount);
    common::detail::json::read(obj, "currentLTV", out.current_ltv);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FlexibleLoanAdjustLtvResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "direction", v.direction);
    common::detail::json::write(obj, "adjustmentAmount", v.adjustment_amount);
    common::detail::json::write(obj, "currentLTV", v.current_ltv);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::crypto_loan::rest_api
