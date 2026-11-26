//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/account_information_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

AccountInformationResponse tag_invoke(boost::json::value_to_tag<AccountInformationResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountInformationResponse");
    AccountInformationResponse out;
    common::detail::json::read(obj, "uniMMR", out.uni_mmr);
    common::detail::json::read(obj, "accountEquity", out.account_equity);
    common::detail::json::read(obj, "actualEquity", out.actual_equity);
    common::detail::json::read(obj, "accountInitialMargin", out.account_initial_margin);
    common::detail::json::read(obj, "accountMaintMargin", out.account_maint_margin);
    common::detail::json::read(obj, "accountStatus", out.account_status);
    common::detail::json::read(obj, "virtualMaxWithdrawAmount", out.virtual_max_withdraw_amount);
    common::detail::json::read(obj, "totalAvailableBalance", out.total_available_balance);
    common::detail::json::read(obj, "totalMarginOpenLoss", out.total_margin_open_loss);
    common::detail::json::read(obj, "updateTime", out.update_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountInformationResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "uniMMR", v.uni_mmr);
    common::detail::json::write(obj, "accountEquity", v.account_equity);
    common::detail::json::write(obj, "actualEquity", v.actual_equity);
    common::detail::json::write(obj, "accountInitialMargin", v.account_initial_margin);
    common::detail::json::write(obj, "accountMaintMargin", v.account_maint_margin);
    common::detail::json::write(obj, "accountStatus", v.account_status);
    common::detail::json::write(obj, "virtualMaxWithdrawAmount", v.virtual_max_withdraw_amount);
    common::detail::json::write(obj, "totalAvailableBalance", v.total_available_balance);
    common::detail::json::write(obj, "totalMarginOpenLoss", v.total_margin_open_loss);
    common::detail::json::write(obj, "updateTime", v.update_time);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
