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

/// positions of all symbols in the market are returned
struct AccountInformationV2ResponsePositionsInner {
    /// Symbol.
    std::optional<std::string> symbol;
    /// Initial margin requirement.
    std::optional<std::string> initial_margin;
    /// Maintenance margin requirement.
    std::optional<std::string> maint_margin;
    /// Unrealized profit.
    std::optional<std::string> unrealized_profit;
    /// Initial margin required for positions.
    std::optional<std::string> position_initial_margin;
    /// Initial margin required for open orders.
    std::optional<std::string> open_order_initial_margin;
    /// Current initial leverage.
    std::optional<std::string> leverage;
    /// Whether the position uses isolated margin mode.
    std::optional<bool> isolated;
    /// Average entry price.
    std::optional<std::string> entry_price;
    /// Maximum available notional under current leverage.
    std::optional<std::string> max_notional;
    /// Bid notional (ignore).
    std::optional<std::string> bid_notional;
    /// Ask notional (ignore).
    std::optional<std::string> ask_notional;
    /// Position side.
    std::optional<std::string> position_side;
    /// Position quantity.
    std::optional<std::string> position_amt;
    /// Last update time in milliseconds.
    std::optional<std::int64_t> update_time;

    bool operator==(const AccountInformationV2ResponsePositionsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountInformationV2ResponsePositionsInner
tag_invoke(boost::json::value_to_tag<AccountInformationV2ResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountInformationV2ResponsePositionsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
