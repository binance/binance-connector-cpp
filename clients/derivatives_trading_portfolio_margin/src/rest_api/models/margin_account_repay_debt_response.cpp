//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_account_repay_debt_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

MarginAccountRepayDebtResponse
tag_invoke(boost::json::value_to_tag<MarginAccountRepayDebtResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarginAccountRepayDebtResponse");
    MarginAccountRepayDebtResponse out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "specifyRepayAssets", out.specify_repay_assets);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MarginAccountRepayDebtResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "specifyRepayAssets", v.specify_repay_assets);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
