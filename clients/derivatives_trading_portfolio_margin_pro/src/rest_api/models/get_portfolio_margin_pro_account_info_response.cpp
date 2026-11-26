//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_account_info_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetPortfolioMarginProAccountInfoResponse
tag_invoke(boost::json::value_to_tag<GetPortfolioMarginProAccountInfoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPortfolioMarginProAccountInfoResponse");
    GetPortfolioMarginProAccountInfoResponse out;
    common::detail::json::read(obj, "uniMMR", out.uni_mmr);
    common::detail::json::read(obj, "accountEquity", out.account_equity);
    common::detail::json::read(obj, "actualEquity", out.actual_equity);
    common::detail::json::read(obj, "accountMaintMargin", out.account_maint_margin);
    common::detail::json::read(obj, "accountInitialMargin", out.account_initial_margin);
    common::detail::json::read(obj, "totalAvailableBalance", out.total_available_balance);
    common::detail::json::read(obj, "accountStatus", out.account_status);
    common::detail::json::read(obj, "accountType", out.account_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioMarginProAccountInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "uniMMR", v.uni_mmr);
    common::detail::json::write(obj, "accountEquity", v.account_equity);
    common::detail::json::write(obj, "actualEquity", v.actual_equity);
    common::detail::json::write(obj, "accountMaintMargin", v.account_maint_margin);
    common::detail::json::write(obj, "accountInitialMargin", v.account_initial_margin);
    common::detail::json::write(obj, "totalAvailableBalance", v.total_available_balance);
    common::detail::json::write(obj, "accountStatus", v.account_status);
    common::detail::json::write(obj, "accountType", v.account_type);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
