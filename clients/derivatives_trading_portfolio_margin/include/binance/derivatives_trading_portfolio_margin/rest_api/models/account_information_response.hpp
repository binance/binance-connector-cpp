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

struct AccountInformationResponse {
    /// Portfolio margin account maintenance margin rate
    std::optional<std::string> uni_mmr;
    /// Account equity, in USD value
    std::optional<std::string> account_equity;
    /// Account equity without collateral rate, in USD value
    std::optional<std::string> actual_equity;
    /// Account Initial Margin.
    std::optional<std::string> account_initial_margin;
    /// Portfolio margin account maintenance margin, unit：USD
    std::optional<std::string> account_maint_margin;
    /// Portfolio margin account status:"NORMAL", "MARGIN_CALL", "SUPPLY_MARGIN", "REDUCE_ONLY",
    /// "ACTIVE_LIQUIDATION", "FORCE_LIQUIDATION", "BANKRUPTED"
    std::optional<std::string> account_status;
    /// Portfolio margin maximum amount for transfer out in USD
    std::optional<std::string> virtual_max_withdraw_amount;
    /// Total Available Balance.
    std::optional<std::string> total_available_balance;
    /// in USD margin open order
    std::optional<std::string> total_margin_open_loss;
    /// last update time
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountInformationResponse tag_invoke(
    boost::json::value_to_tag<AccountInformationResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
