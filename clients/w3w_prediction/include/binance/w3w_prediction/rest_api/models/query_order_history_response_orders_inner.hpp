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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryOrderHistoryResponseOrdersInner {
    std::optional<std::string> order_id;
    std::optional<std::string> vendor_order_id;
    std::optional<std::string> vendor;
    std::optional<std::int64_t> market_topic_id;
    std::optional<std::string> slug;
    std::optional<std::string> market_topic_title;
    std::optional<std::int64_t> market_id;
    std::optional<std::string> market_title;
    std::optional<std::string> outcome;
    std::optional<std::int64_t> outcome_index;
    std::optional<std::string> status;
    std::optional<std::string> side;
    std::optional<std::string> order_type;
    std::optional<std::int64_t> create_time;
    std::optional<std::int64_t> modify_time;
    std::optional<std::int64_t> terminal_time;
    std::optional<std::string> maker_usdt_amount;
    std::optional<std::string> maker_share_qty;
    std::optional<std::string> filled_usdt_amount;
    std::optional<std::string> filled_share_qty;
    std::optional<std::string> fill_percentage;
    std::optional<std::string> price;
    std::optional<std::string> market_provider_fee;
    std::optional<std::string> network_fee;

    bool operator==(const QueryOrderHistoryResponseOrdersInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryOrderHistoryResponseOrdersInner
tag_invoke(boost::json::value_to_tag<QueryOrderHistoryResponseOrdersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryOrderHistoryResponseOrdersInner& v);

} // namespace binance::w3w_prediction::rest_api
