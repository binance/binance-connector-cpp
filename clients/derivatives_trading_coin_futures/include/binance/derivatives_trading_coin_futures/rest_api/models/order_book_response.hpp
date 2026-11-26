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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct OrderBookResponse {
    /// Last update ID.
    std::optional<std::int64_t> last_update_id;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// Message output time
    std::optional<std::int64_t> e_uppercase;
    /// Transaction time
    std::optional<std::int64_t> t_uppercase;
    /// Bid orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> bids;
    /// Ask orders. Each entry is [price, quantity].
    std::optional<std::vector<std::vector<std::string>>> asks;

    bool operator==(const OrderBookResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT OrderBookResponse
tag_invoke(boost::json::value_to_tag<OrderBookResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, const OrderBookResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
