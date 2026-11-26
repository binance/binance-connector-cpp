//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryPositionsResponseSummary {
    std::optional<std::string> total_value;
    std::optional<std::string> position_value;
    std::optional<std::string> wallet_balance;
    std::optional<std::string> total_claimable_amount;
    std::optional<std::string> today_realized_pnl;
    std::optional<std::string> today_realized_pnl_percent;
    std::optional<std::string> today_total_cost;

    bool operator==(const QueryPositionsResponseSummary& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPositionsResponseSummary tag_invoke(
    boost::json::value_to_tag<QueryPositionsResponseSummary> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPositionsResponseSummary& v);

} // namespace binance::w3w_prediction::rest_api
