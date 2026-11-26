//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_collateral_assets_data_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanCollateralAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanCollateralAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanCollateralAssetsDataResponseRowsInner");
    GetFlexibleLoanCollateralAssetsDataResponseRowsInner out;
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "initialLTV", out.initial_ltv);
    common::detail::json::read(obj, "marginCallLTV", out.margin_call_ltv);
    common::detail::json::read(obj, "liquidationLTV", out.liquidation_ltv);
    common::detail::json::read(obj, "maxLimit", out.max_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanCollateralAssetsDataResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "initialLTV", v.initial_ltv);
    common::detail::json::write(obj, "marginCallLTV", v.margin_call_ltv);
    common::detail::json::write(obj, "liquidationLTV", v.liquidation_ltv);
    common::detail::json::write(obj, "maxLimit", v.max_limit);
}

} // namespace binance::crypto_loan::rest_api
