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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct PositionInformationResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// position amount
    std::optional<std::string> position_amt;
    /// Position entry price.
    std::optional<std::string> entry_price;
    /// break-even price
    std::optional<std::string> break_even_price;
    /// mark price
    std::optional<std::string> mark_price;
    /// Unrealized profit.
    std::optional<std::string> un_realized_profit;
    /// Liquidation price.
    std::optional<std::string> liquidation_price;
    /// Leverage value.
    std::optional<std::string> leverage;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// Margin type.
    std::optional<std::string> margin_type;
    /// Isolated margin amount.
    std::optional<std::string> isolated_margin;
    /// Whether auto-add margin is enabled.
    std::optional<std::string> is_auto_add_margin;
    /// Position side
    std::optional<std::string> position_side;
    /// update time
    std::optional<std::int64_t> update_time;

    bool operator==(const PositionInformationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<PositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionInformationResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
