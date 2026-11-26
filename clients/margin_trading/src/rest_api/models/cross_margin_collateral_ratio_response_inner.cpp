//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/cross_margin_collateral_ratio_response_inner.hpp>

namespace binance::margin_trading::rest_api {

CrossMarginCollateralRatioResponseInner
tag_invoke(boost::json::value_to_tag<CrossMarginCollateralRatioResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CrossMarginCollateralRatioResponseInner");
    CrossMarginCollateralRatioResponseInner out;
    common::detail::json::read(obj, "collaterals", out.collaterals);
    common::detail::json::read(obj, "assetNames", out.asset_names);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CrossMarginCollateralRatioResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "collaterals", v.collaterals);
    common::detail::json::write(obj, "assetNames", v.asset_names);
}

} // namespace binance::margin_trading::rest_api
