//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_account_balance_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

GetPortfolioMarginProAccountBalanceResponseInner
tag_invoke(boost::json::value_to_tag<GetPortfolioMarginProAccountBalanceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPortfolioMarginProAccountBalanceResponseInner");
    GetPortfolioMarginProAccountBalanceResponseInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "totalWalletBalance", out.total_wallet_balance);
    common::detail::json::read(obj, "crossMarginAsset", out.cross_margin_asset);
    common::detail::json::read(obj, "crossMarginBorrowed", out.cross_margin_borrowed);
    common::detail::json::read(obj, "crossMarginFree", out.cross_margin_free);
    common::detail::json::read(obj, "crossMarginInterest", out.cross_margin_interest);
    common::detail::json::read(obj, "crossMarginLocked", out.cross_margin_locked);
    common::detail::json::read(obj, "umWalletBalance", out.um_wallet_balance);
    common::detail::json::read(obj, "umUnrealizedPNL", out.um_unrealized_pnl);
    common::detail::json::read(obj, "cmWalletBalance", out.cm_wallet_balance);
    common::detail::json::read(obj, "cmUnrealizedPNL", out.cm_unrealized_pnl);
    common::detail::json::read(obj, "updateTime", out.update_time);
    common::detail::json::read(obj, "negativeBalance", out.negative_balance);
    common::detail::json::read(obj, "optionWalletBalance", out.option_wallet_balance);
    common::detail::json::read(obj, "optionEquity", out.option_equity);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPortfolioMarginProAccountBalanceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "totalWalletBalance", v.total_wallet_balance);
    common::detail::json::write(obj, "crossMarginAsset", v.cross_margin_asset);
    common::detail::json::write(obj, "crossMarginBorrowed", v.cross_margin_borrowed);
    common::detail::json::write(obj, "crossMarginFree", v.cross_margin_free);
    common::detail::json::write(obj, "crossMarginInterest", v.cross_margin_interest);
    common::detail::json::write(obj, "crossMarginLocked", v.cross_margin_locked);
    common::detail::json::write(obj, "umWalletBalance", v.um_wallet_balance);
    common::detail::json::write(obj, "umUnrealizedPNL", v.um_unrealized_pnl);
    common::detail::json::write(obj, "cmWalletBalance", v.cm_wallet_balance);
    common::detail::json::write(obj, "cmUnrealizedPNL", v.cm_unrealized_pnl);
    common::detail::json::write(obj, "updateTime", v.update_time);
    common::detail::json::write(obj, "negativeBalance", v.negative_balance);
    common::detail::json::write(obj, "optionWalletBalance", v.option_wallet_balance);
    common::detail::json::write(obj, "optionEquity", v.option_equity);
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
