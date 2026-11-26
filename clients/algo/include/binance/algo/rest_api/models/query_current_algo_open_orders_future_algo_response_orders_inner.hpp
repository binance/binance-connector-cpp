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

struct QueryCurrentAlgoOpenOrdersFutureAlgoResponseOrdersInner {
    /// Algo order ID
    std::optional<std::int64_t> algo_id;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Trading side
    std::optional<std::string> side;
    /// Position side
    std::optional<std::string> position_side;
    /// Total order quantity
    std::optional<std::string> total_qty;
    /// Executed quantity
    std::optional<std::string> executed_qty;
    /// Executed amount
    std::optional<std::string> executed_amt;
    /// Average execution price
    std::optional<std::string> avg_price;
    /// Client-defined algo order ID
    std::optional<std::string> client_algo_id;
    /// Order creation time
    std::optional<std::int64_t> book_time;
    /// End time
    std::optional<std::int64_t> end_time;
    /// Algo order status
    std::optional<std::string> algo_status;
    /// Algo order type
    std::optional<std::string> algo_type;
    /// Execution urgency
    std::optional<std::string> urgency;

    bool operator==(
        const QueryCurrentAlgoOpenOrdersFutureAlgoResponseOrdersInner& /*other*/) const = default;
};

BINANCE_ALGO_EXPORT QueryCurrentAlgoOpenOrdersFutureAlgoResponseOrdersInner tag_invoke(
    boost::json::value_to_tag<QueryCurrentAlgoOpenOrdersFutureAlgoResponseOrdersInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_ALGO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryCurrentAlgoOpenOrdersFutureAlgoResponseOrdersInner& v);

} // namespace binance::algo::rest_api
