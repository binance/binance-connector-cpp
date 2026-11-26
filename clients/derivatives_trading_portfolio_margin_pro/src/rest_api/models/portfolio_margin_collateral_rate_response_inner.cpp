//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_collateral_rate_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

PortfolioMarginCollateralRateResponseInner
tag_invoke(boost::json::value_to_tag<PortfolioMarginCollateralRateResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "PortfolioMarginCollateralRateResponseInner");
    PortfolioMarginCollateralRateResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "collateralRate", out.collateral_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const PortfolioMarginCollateralRateResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "collateralRate", v.collateral_rate);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
