//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/classic_portfolio_margin_account_information_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

ClassicPortfolioMarginAccountInformationResponse
tag_invoke(boost::json::value_to_tag<ClassicPortfolioMarginAccountInformationResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ClassicPortfolioMarginAccountInformationResponse");
    ClassicPortfolioMarginAccountInformationResponse out;
    common::detail::json::read(obj, "maxWithdrawAmountUSD", out.max_withdraw_amount_usd);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "maxWithdrawAmount", out.max_withdraw_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ClassicPortfolioMarginAccountInformationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "maxWithdrawAmountUSD", v.max_withdraw_amount_usd);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "maxWithdrawAmount", v.max_withdraw_amount);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
