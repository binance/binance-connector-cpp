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

struct QueryOptionOrderHistoryResponseInner {
    /// order Id
    std::optional<std::int64_t> order_id;
    /// symbol
    std::optional<std::string> symbol;
    /// price
    std::optional<std::string> price;
    /// quantity
    std::optional<std::string> quantity;
    /// executed Qty
    std::optional<std::string> executed_qty;
    /// side
    std::optional<std::string> side;
    /// type
    std::optional<std::string> type;
    /// time In Force
    std::optional<std::string> time_in_force;
    /// reduce Only
    std::optional<bool> reduce_only;
    /// create Time
    std::optional<std::int64_t> create_time;
    /// update Time
    std::optional<std::int64_t> update_time;
    /// status
    std::optional<std::string> status;
    /// avg Price
    std::optional<std::string> avg_price;
    /// client Order Id
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

    bool operator==(const QueryOptionOrderHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT QueryOptionOrderHistoryResponseInner
tag_invoke(boost::json::value_to_tag<QueryOptionOrderHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryOptionOrderHistoryResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
