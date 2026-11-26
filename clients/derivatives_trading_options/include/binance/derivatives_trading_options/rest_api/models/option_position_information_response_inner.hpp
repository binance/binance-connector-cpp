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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct OptionPositionInformationResponseInner {
    /// Average entry price
    std::optional<std::string> entry_price;
    /// Option trading pair
    std::optional<std::string> symbol;
    /// Position direction
    std::optional<std::string> side;
    /// Number of positions (positive numbers represent long positions, negative number represent
    /// short positions)
    std::optional<std::string> quantity;
    /// Current market value
    std::optional<std::string> mark_value;
    /// Unrealized profit/loss
    std::optional<std::string> unrealized_pnl;
    /// Mark price
    std::optional<std::string> mark_price;
    /// Strike price
    std::optional<std::string> strike_price;
    /// Exercise time
    std::optional<std::int64_t> expiry_date;
    /// price Scale
    std::optional<std::int64_t> price_scale;
    /// quantity Scale
    std::optional<std::int64_t> quantity_scale;
    /// option type
    std::optional<std::string> option_side;
    /// quote asset
    std::optional<std::string> quote_asset;
    /// last update time
    std::optional<std::int64_t> time;
    /// buy order qty
    std::optional<std::string> bid_quantity;
    /// sell order qty
    std::optional<std::string> ask_quantity;

    bool operator==(const OptionPositionInformationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OptionPositionInformationResponseInner
tag_invoke(boost::json::value_to_tag<OptionPositionInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const OptionPositionInformationResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
