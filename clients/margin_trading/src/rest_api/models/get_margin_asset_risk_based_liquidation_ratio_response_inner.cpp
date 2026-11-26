//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_margin_asset_risk_based_liquidation_ratio_response_inner.hpp>

namespace binance::margin_trading::rest_api {

GetMarginAssetRiskBasedLiquidationRatioResponseInner
tag_invoke(boost::json::value_to_tag<GetMarginAssetRiskBasedLiquidationRatioResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetMarginAssetRiskBasedLiquidationRatioResponseInner");
    GetMarginAssetRiskBasedLiquidationRatioResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "riskBasedLiquidationRatio", out.risk_based_liquidation_ratio);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetMarginAssetRiskBasedLiquidationRatioResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "riskBasedLiquidationRatio", v.risk_based_liquidation_ratio);
}

} // namespace binance::margin_trading::rest_api
