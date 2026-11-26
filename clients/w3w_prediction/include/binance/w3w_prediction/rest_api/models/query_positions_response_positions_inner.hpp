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

struct QueryPositionsResponsePositionsInner {
    std::optional<std::int64_t> position_id;
    std::optional<std::string> vendor;
    std::optional<std::string> chain_id;
    std::optional<std::string> token_id;
    std::optional<std::string> collateral_symbol;
    std::optional<std::string> topic_type;
    std::optional<std::int64_t> market_topic_id;
    std::optional<std::int64_t> market_id;
    std::optional<std::string> market_topic_title;
    std::optional<std::string> market_title;
    std::optional<std::string> outcome_name;
    std::optional<std::int64_t> outcome_index;
    std::optional<std::string> shares;
    std::optional<std::string> avg_price;
    std::optional<std::string> total_cost;
    std::optional<std::string> value;
    std::optional<std::string> current_price;
    std::optional<std::string> to_win;
    std::optional<std::string> position_status;
    std::optional<bool> can_claim;
    std::optional<std::int64_t> end_date;
    std::optional<std::string> unrealized_pnl;
    std::optional<std::string> unrealized_pnl_percent;
    std::optional<std::string> realized_pnl;
    std::optional<std::string> pnl;
    std::optional<std::int64_t> created_time;
    std::optional<std::int64_t> updated_time;

    bool operator==(const QueryPositionsResponsePositionsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPositionsResponsePositionsInner
tag_invoke(boost::json::value_to_tag<QueryPositionsResponsePositionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPositionsResponsePositionsInner& v);

} // namespace binance::w3w_prediction::rest_api
