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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

struct NewAlgoOrderResponseResult {
    std::optional<std::int64_t> algo_id;
    std::optional<std::string> client_algo_id;
    std::optional<std::string> algo_type;
    std::optional<std::string> order_type;
    std::optional<std::string> symbol;
    std::optional<std::string> side;
    std::optional<std::string> position_side;
    std::optional<std::string> time_in_force;
    std::optional<std::string> quantity;
    std::optional<std::string> algo_status;
    std::optional<std::string> trigger_price;
    std::optional<std::string> price;
    /// Reserved field, ignore.
    std::optional<std::string> iceberg_quantity;
    std::optional<std::string> self_trade_prevention_mode;
    std::optional<std::string> working_type;
    std::optional<std::string> price_match;
    std::optional<bool> close_position;
    std::optional<bool> price_protect;
    std::optional<bool> reduce_only;
    std::optional<std::int64_t> create_time;
    std::optional<std::int64_t> update_time;
    std::optional<std::int64_t> trigger_time;
    std::optional<std::int64_t> good_till_date;

    bool operator==(const NewAlgoOrderResponseResult& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewAlgoOrderResponseResult tag_invoke(
    boost::json::value_to_tag<NewAlgoOrderResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NewAlgoOrderResponseResult& v);

} // namespace binance::derivatives_trading_coin_futures::websocket_api
