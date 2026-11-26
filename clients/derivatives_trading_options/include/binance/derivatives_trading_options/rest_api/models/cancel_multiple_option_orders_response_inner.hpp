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

struct CancelMultipleOptionOrdersResponseInner {
    /// System order number
    std::optional<std::int64_t> order_id;
    /// Option trading pair
    std::optional<std::string> symbol;
    /// Order Price
    std::optional<std::string> price;
    /// Order Quantity
    std::optional<std::string> quantity;
    /// Number of completed quantity
    std::optional<std::string> executed_qty;
    /// fee
    std::optional<std::string> fee;
    /// Buy/sell direction
    std::optional<std::string> side;
    /// Order type
    std::optional<std::string> type;
    /// Time in force method
    std::optional<std::string> time_in_force;
    /// Order is reduce only Y/N
    std::optional<bool> reduce_only;
    /// Order Time
    std::optional<std::int64_t> create_time;
    /// Update time
    std::optional<std::int64_t> update_time;
    /// Order status
    std::optional<std::string> status;
    /// Average price of completed trade
    std::optional<std::string> avg_price;
    /// Client order ID
    std::optional<std::string> client_order_id;
    /// price Scale
    std::optional<std::int64_t> price_scale;
    /// quantity Scale
    std::optional<std::int64_t> quantity_scale;
    /// option Side
    std::optional<std::string> option_side;
    /// quote Asset
    std::optional<std::string> quote_asset;
    /// mmp
    std::optional<bool> mmp;
    std::optional<std::string> source;
    /// self trading prevention mode
    std::optional<std::string> self_trade_prevention_mode;

    bool operator==(const CancelMultipleOptionOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT CancelMultipleOptionOrdersResponseInner
tag_invoke(boost::json::value_to_tag<CancelMultipleOptionOrdersResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CancelMultipleOptionOrdersResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
