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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct RecentTradesListResponseInner {
    /// id
    std::optional<std::int64_t> id;
    /// TradeId
    std::optional<std::int64_t> trade_id;
    /// Option trading pair
    std::optional<std::string> symbol;
    /// Completed trade price
    std::optional<std::string> price;
    /// Completed trade quantity
    std::optional<std::string> qty;
    /// Completed trade amount
    std::optional<std::string> quote_qty;
    /// Completed trade direction（-1 Sell，1 Buy）
    std::optional<std::int64_t> side;
    /// Time
    std::optional<std::int64_t> time;

    bool operator==(const RecentTradesListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT RecentTradesListResponseInner tag_invoke(
    boost::json::value_to_tag<RecentTradesListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const RecentTradesListResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
