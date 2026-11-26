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

struct QueryOrderResponseResult {
    std::optional<std::string> avg_price;
    std::optional<std::string> client_order_id;
    std::optional<std::string> cum_quote;
    std::optional<std::string> executed_qty;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> orig_qty;
    std::optional<std::string> orig_type;
    std::optional<std::string> price;
    std::optional<bool> reduce_only;
    std::optional<std::string> side;
    std::optional<std::string> position_side;
    std::optional<std::string> status;
    /// please ignore when order type is TRAILING_STOP_MARKET
    std::optional<std::string> stop_price;
    /// if Close-All
    std::optional<bool> close_position;
    std::optional<std::string> symbol;
    /// order time
    std::optional<std::int64_t> time;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    /// activation price, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> activate_price;
    /// callback rate, only return with TRAILING_STOP_MARKET order
    std::optional<std::string> price_rate;
    /// update time
    std::optional<std::int64_t> update_time;
    std::optional<std::string> working_type;
    /// if conditional order trigger is protected
    std::optional<bool> price_protect;
    std::optional<std::string> price_match;
    /// Self-trade prevention mode
    std::optional<std::string> self_trade_prevention_mode;
    /// Order good till date timestamp
    std::optional<std::int64_t> good_till_date;

    bool operator==(const QueryOrderResponseResult& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT QueryOrderResponseResult tag_invoke(
    boost::json::value_to_tag<QueryOrderResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const QueryOrderResponseResult& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_api
