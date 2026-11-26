//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/check_collateral_repay_rate_response.hpp>

namespace binance::crypto_loan::rest_api {

CheckCollateralRepayRateResponse
tag_invoke(boost::json::value_to_tag<CheckCollateralRepayRateResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CheckCollateralRepayRateResponse");
    CheckCollateralRepayRateResponse out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "rate", out.rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CheckCollateralRepayRateResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "rate", v.rate);
}

} // namespace binance::crypto_loan::rest_api
