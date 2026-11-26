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

namespace binance::derivatives_trading_portfolio_margin::websocket_streams {

struct RiskLevelChange {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// uniMMR level
    std::optional<std::string> u;
    /// Risk level: MARGIN_CALL, REDUCE_ONLY, FORCE_LIQUIDATION
    std::optional<std::string> s;
    /// Account equity in USD value
    std::optional<std::string> eq;
    /// Actual equity without collateral rate in USD value
    std::optional<std::string> ae;
    /// Total maintenance margin in USD value
    std::optional<std::string> m;

    bool operator==(const RiskLevelChange& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT RiskLevelChange
tag_invoke(boost::json::value_to_tag<RiskLevelChange> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const RiskLevelChange& v);

} // namespace binance::derivatives_trading_portfolio_margin::websocket_streams
