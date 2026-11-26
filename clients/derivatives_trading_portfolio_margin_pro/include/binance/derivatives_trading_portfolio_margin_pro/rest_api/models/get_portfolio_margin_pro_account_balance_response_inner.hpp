//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct GetPortfolioMarginProAccountBalanceResponseInner {
    /// asset.
    std::optional<std::string> asset;
    /// total Wallet Balance.
    std::optional<std::string> total_wallet_balance;
    /// cross Margin Asset.
    std::optional<std::string> cross_margin_asset;
    /// cross Margin Borrowed.
    std::optional<std::string> cross_margin_borrowed;
    /// cross Margin Free.
    std::optional<std::string> cross_margin_free;
    /// cross Margin Interest.
    std::optional<std::string> cross_margin_interest;
    /// cross Margin Locked.
    std::optional<std::string> cross_margin_locked;
    /// um Wallet Balance.
    std::optional<std::string> um_wallet_balance;
    /// um Unrealized PNL.
    std::optional<std::string> um_unrealized_pnl;
    /// cm Wallet Balance.
    std::optional<std::string> cm_wallet_balance;
    /// cm Unrealized PNL.
    std::optional<std::string> cm_unrealized_pnl;
    /// update Time.
    std::optional<std::int64_t> update_time;
    /// negative Balance.
    std::optional<std::string> negative_balance;
    /// option Wallet Balance.
    std::optional<std::string> option_wallet_balance;
    /// option Equity.
    std::optional<std::string> option_equity;

    bool
    operator==(const GetPortfolioMarginProAccountBalanceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
GetPortfolioMarginProAccountBalanceResponseInner
tag_invoke(boost::json::value_to_tag<GetPortfolioMarginProAccountBalanceResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetPortfolioMarginProAccountBalanceResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
