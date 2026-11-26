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

struct PositionInformationV3ResponseInner {
    /// symbol
    std::optional<std::string> symbol;
    /// position side
    std::optional<std::string> position_side;
    /// position amount, positive for long, negative for short
    std::optional<std::string> position_amt;
    /// entry price
    std::optional<std::string> entry_price;
    /// break-even price
    std::optional<std::string> break_even_price;
    /// current mark price
    std::optional<std::string> mark_price;
    /// unrealized profit
    std::optional<std::string> un_realized_profit;
    /// liquidation price
    std::optional<std::string> liquidation_price;
    /// isolated margin
    std::optional<std::string> isolated_margin;
    /// notional value of position
    std::optional<std::string> notional;
    /// margin asset
    std::optional<std::string> margin_asset;
    /// isolated wallet (if isolated position)
    std::optional<std::string> isolated_wallet;
    /// initial margin required with current mark price
    std::optional<std::string> initial_margin;
    /// maintenance margin required
    std::optional<std::string> maint_margin;
    /// initial margin required for positions with current mark price
    std::optional<std::string> position_initial_margin;
    /// initial margin required for open orders with current mark price
    std::optional<std::string> open_order_initial_margin;
    /// auto-deleverage ranking
    std::optional<std::int64_t> adl;
    /// ignore
    std::optional<std::string> bid_notional;
    /// ignore
    std::optional<std::string> ask_notional;
    /// update time
    std::optional<std::int64_t> update_time;

    bool operator==(const PositionInformationV3ResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PositionInformationV3ResponseInner
tag_invoke(boost::json::value_to_tag<PositionInformationV3ResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionInformationV3ResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
