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

struct UsersForceOrdersResponseInner {
    std::optional<std::int64_t> order_id;
    std::optional<std::string> symbol;
    /// Pair.
    std::optional<std::string> pair;
    std::optional<std::string> status;
    std::optional<std::string> client_order_id;
    std::optional<std::string> price;
    std::optional<std::string> avg_price;
    std::optional<std::string> orig_qty;
    std::optional<std::string> executed_qty;
    std::optional<std::string> cum_quote;
    /// Cum Base.
    std::optional<std::string> cum_base;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    std::optional<bool> reduce_only;
    std::optional<bool> close_position;
    std::optional<std::string> side;
    std::optional<std::string> position_side;
    std::optional<std::string> stop_price;
    std::optional<std::string> working_type;
    std::optional<std::string> orig_type;
    std::optional<std::int64_t> time;
    std::optional<std::int64_t> update_time;

    bool operator==(const UsersForceOrdersResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT UsersForceOrdersResponseInner tag_invoke(
    boost::json::value_to_tag<UsersForceOrdersResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UsersForceOrdersResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
