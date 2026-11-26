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

namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams {

/// Pushed every 5 seconds with account asset status.
struct PmProAccountUpdate {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// uniMMR level
    std::optional<std::string> u;
    /// Account equity in USD
    std::optional<std::string> eq;
    /// Actual equity without collateral rate in USD
    std::optional<std::string> ae;
    /// Total initial margin in USD
    std::optional<std::string> im;
    /// Total maintenance margin in USD
    std::optional<std::string> mm;
    /// Total available balance in USD
    std::optional<std::string> avb;
    /// Virtual maxWithdraw amount in USD
    std::optional<std::string> vmw;

    bool operator==(const PmProAccountUpdate& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT PmProAccountUpdate
tag_invoke(boost::json::value_to_tag<PmProAccountUpdate> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PmProAccountUpdate& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::websocket_streams
