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

struct GetCmAccountDetailResponseAssetsInner {
    /// asset name
    std::optional<std::string> asset;
    /// total wallet balance
    std::optional<std::string> cross_wallet_balance;
    /// unrealized profit or loss
    std::optional<std::string> cross_un_pnl;
    /// maintenance margin
    std::optional<std::string> maint_margin;
    /// total intial margin required with the latest mark price
    std::optional<std::string> initial_margin;
    /// positions margin required with the latest mark price
    std::optional<std::string> position_initial_margin;
    /// open orders intial margin required with the latest mark price
    std::optional<std::string> open_order_initial_margin;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const GetCmAccountDetailResponseAssetsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetCmAccountDetailResponseAssetsInner
tag_invoke(boost::json::value_to_tag<GetCmAccountDetailResponseAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCmAccountDetailResponseAssetsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
