//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_pro_tiered_collateral_rate_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

PortfolioMarginProTieredCollateralRateResponseInner
tag_invoke(boost::json::value_to_tag<PortfolioMarginProTieredCollateralRateResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PortfolioMarginProTieredCollateralRateResponseInner");
    PortfolioMarginProTieredCollateralRateResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "collateralInfo", out.collateral_info);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PortfolioMarginProTieredCollateralRateResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "collateralInfo", v.collateral_info);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
