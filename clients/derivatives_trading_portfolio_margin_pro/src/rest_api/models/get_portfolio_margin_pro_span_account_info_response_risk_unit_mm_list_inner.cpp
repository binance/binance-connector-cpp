//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_span_account_info_response_risk_unit_mm_list_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner
tag_invoke(boost::json::value_to_tag<
               GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner");
    GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "uniMaintainUsd", out.uni_maintain_usd);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "uniMaintainUsd", v.uni_maintain_usd);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
