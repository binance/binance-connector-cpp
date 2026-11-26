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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetUmAccountDetailResponseAssetsInner {
    /// asset name
    std::optional<std::string> asset;
    /// wallet balance
    std::optional<std::string> cross_wallet_balance;
    /// unrealized profit
    std::optional<std::string> cross_un_pnl;
    /// maintenance margin required
    std::optional<std::string> maint_margin;
    /// total initial margin required with current mark price
    std::optional<std::string> initial_margin;
    /// initial margin required for positions with current mark price
    std::optional<std::string> position_initial_margin;
    /// initial margin required for open orders with current mark price
    std::optional<std::string> open_order_initial_margin;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const GetUmAccountDetailResponseAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUmAccountDetailResponseAssetsInner
tag_invoke(boost::json::value_to_tag<GetUmAccountDetailResponseAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetUmAccountDetailResponseAssetsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
