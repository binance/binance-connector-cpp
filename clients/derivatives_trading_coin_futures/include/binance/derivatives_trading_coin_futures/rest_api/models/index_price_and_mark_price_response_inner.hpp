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

namespace binance::derivatives_trading_coin_futures::rest_api {

struct IndexPriceAndMarkPriceResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// mark price
    std::optional<std::string> mark_price;
    /// index price
    std::optional<std::string> index_price;
    /// Estimated Settle Price, only useful in the last hour before the settlement starts.
    std::optional<std::string> estimated_settle_price;
    /// the lasted funding rate, for perpetual contract symbols only. For delivery symbols, "" will
    /// be shown.
    std::optional<std::string> last_funding_rate;
    /// the base asset interest rate, for perpetual contract symbols only. For delivery symbols, ""
    /// will be shown.
    std::optional<std::string> interest_rate;
    /// For perpetual contract symbols only. For delivery symbols, 0 will be shown
    std::optional<std::int64_t> next_funding_time;
    /// Time
    std::optional<std::int64_t> time;

    bool operator==(const IndexPriceAndMarkPriceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexPriceAndMarkPriceResponseInner
tag_invoke(boost::json::value_to_tag<IndexPriceAndMarkPriceResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const IndexPriceAndMarkPriceResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
