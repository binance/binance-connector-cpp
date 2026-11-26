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

#include <binance/algo/export.hpp>

namespace binance::algo::rest_api {

struct QuerySubOrdersFutureAlgoResponseSubOrdersInner {
    /// Algo order ID
    std::optional<std::int64_t> algo_id;
    /// Sub-order ID
    std::optional<std::int64_t> order_id;
    /// Sub-order status
    std::optional<std::string> order_status;
    /// Executed quantity
    std::optional<std::string> executed_qty;
    /// Executed amount
    std::optional<std::string> executed_amt;
    /// Fee amount
    std::optional<std::string> fee_amt;
    /// Fee asset
    std::optional<std::string> fee_asset;
    /// Order creation time
    std::optional<std::int64_t> book_time;
    /// Average execution price
    std::optional<std::string> avg_price;
    /// Trading side
    std::optional<std::string> side;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Sub-order execution sequence ID
    std::optional<std::int64_t> sub_id;
    /// Time in force
    std::optional<std::string> time_in_force;
    /// Original order quantity
    std::optional<std::string> orig_qty;

    bool
    operator==(const QuerySubOrdersFutureAlgoResponseSubOrdersInner& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT QuerySubOrdersFutureAlgoResponseSubOrdersInner
tag_invoke(boost::json::value_to_tag<QuerySubOrdersFutureAlgoResponseSubOrdersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const QuerySubOrdersFutureAlgoResponseSubOrdersInner& v);

} // namespace binance::algo::rest_api
