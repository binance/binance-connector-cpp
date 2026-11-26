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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

/// positions of all symbols user had position/ open orders are returned
struct AccountInformationV3ResponsePositionsInner {
    /// Symbol.
    std::optional<std::string> symbol;
    /// Position side.
    std::optional<std::string> position_side;
    /// Position quantity.
    std::optional<std::string> position_amt;
    /// Unrealized profit.
    std::optional<std::string> unrealized_profit;
    /// Isolated margin.
    std::optional<std::string> isolated_margin;
    /// Position notional value.
    std::optional<std::string> notional;
    /// Isolated wallet balance.
    std::optional<std::string> isolated_wallet;
    /// Initial margin requirement.
    std::optional<std::string> initial_margin;
    /// Maintenance margin requirement.
    std::optional<std::string> maint_margin;
    /// Last update time in milliseconds.
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationV3ResponsePositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV3ResponsePositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV3ResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV3ResponsePositionsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
