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

namespace binance::derivatives_trading_usds_futures::websocket_api {

struct PositionInformationV2ResponseResultInner {
    std::optional<std::string> symbol;
    /// Position Side
    std::optional<std::string> position_side;
    std::optional<std::string> position_amt;
    std::optional<std::string> entry_price;
    std::optional<std::string> break_even_price;
    std::optional<std::string> mark_price;
    /// Unrealized Profit
    std::optional<std::string> un_realized_profit;
    std::optional<std::string> liquidation_price;
    std::optional<std::string> isolated_margin;
    std::optional<std::string> notional;
    std::optional<std::string> margin_asset;
    std::optional<std::string> isolated_wallet;
    /// Initial Margin
    std::optional<std::string> initial_margin;
    /// Maintainance Margin
    std::optional<std::string> maint_margin;
    /// Position Initial Margin
    std::optional<std::string> position_initial_margin;
    /// Open Order Initial Margin
    std::optional<std::string> open_order_initial_margin;
    std::optional<std::int64_t> adl;
    std::optional<std::string> bid_notional;
    std::optional<std::string> ask_notional;
    /// Update Time
    std::optional<std::int64_t> update_time;

    bool operator==(const PositionInformationV2ResponseResultInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PositionInformationV2ResponseResultInner
tag_invoke(boost::json::value_to_tag<PositionInformationV2ResponseResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionInformationV2ResponseResultInner& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
