//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/transfer_ldusdt_rwusd_for_portfolio_margin_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

TransferLdusdtRwusdForPortfolioMarginResponse
tag_invoke(boost::json::value_to_tag<TransferLdusdtRwusdForPortfolioMarginResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TransferLdusdtRwusdForPortfolioMarginResponse");
    TransferLdusdtRwusdForPortfolioMarginResponse out;
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TransferLdusdtRwusdForPortfolioMarginResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
