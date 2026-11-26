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

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct OrderOcoResponseOrderReportsInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> order_id;
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> client_order_id;
    std::optional<std::int64_t> transact_time;
    std::optional<std::string> price;
    std::optional<std::string> orig_qty;
    std::optional<std::string> executed_qty;
    std::optional<std::string> orig_quote_order_qty;
    std::optional<std::string> cummulative_quote_qty;
    std::optional<std::string> status;
    std::optional<std::string> time_in_force;
    std::optional<std::string> type;
    std::optional<std::string> side;
    std::optional<std::int64_t> working_time;
    std::optional<std::string> self_trade_prevention_mode;
    std::optional<std::string> stop_price;

    bool operator==(const OrderOcoResponseOrderReportsInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT OrderOcoResponseOrderReportsInner
tag_invoke(boost::json::value_to_tag<OrderOcoResponseOrderReportsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const OrderOcoResponseOrderReportsInner& v);

} // namespace binance::spot::rest_api
