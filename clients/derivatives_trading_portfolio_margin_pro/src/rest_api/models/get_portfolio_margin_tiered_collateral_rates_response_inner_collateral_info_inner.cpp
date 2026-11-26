//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_tiered_collateral_rates_response_inner_collateral_info_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetPortfolioMarginTieredCollateralRatesResponseInnerCollateralInfoInner
tag_invoke(boost::json::value_to_tag<
               GetPortfolioMarginTieredCollateralRatesResponseInnerCollateralInfoInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetPortfolioMarginTieredCollateralRatesResponseInnerCollateralInfoInner");
    GetPortfolioMarginTieredCollateralRatesResponseInnerCollateralInfoInner out;
    common::detail::json::read(obj, "tierFloor", out.tier_floor);
    common::detail::json::read(obj, "tierCap", out.tier_cap);
    common::detail::json::read(obj, "collateralRate", out.collateral_rate);
    common::detail::json::read(obj, "cum", out.cum);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioMarginTieredCollateralRatesResponseInnerCollateralInfoInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tierFloor", v.tier_floor);
    common::detail::json::write(obj, "tierCap", v.tier_cap);
    common::detail::json::write(obj, "collateralRate", v.collateral_rate);
    common::detail::json::write(obj, "cum", v.cum);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
