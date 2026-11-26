//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/cross_margin_collateral_ratio_response_inner_collaterals_inner.hpp>

namespace binance::margin_trading::rest_api {

CrossMarginCollateralRatioResponseInnerCollateralsInner tag_invoke(
    boost::json::value_to_tag<CrossMarginCollateralRatioResponseInnerCollateralsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "CrossMarginCollateralRatioResponseInnerCollateralsInner");
    CrossMarginCollateralRatioResponseInnerCollateralsInner out;
    common::detail::json::read(obj, "minUsdValue", out.min_usd_value);
    common::detail::json::read(obj, "maxUsdValue", out.max_usd_value);
    common::detail::json::read(obj, "discountRate", out.discount_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CrossMarginCollateralRatioResponseInnerCollateralsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "minUsdValue", v.min_usd_value);
    common::detail::json::write(obj, "maxUsdValue", v.max_usd_value);
    common::detail::json::write(obj, "discountRate", v.discount_rate);
}

} // namespace binance::margin_trading::rest_api
