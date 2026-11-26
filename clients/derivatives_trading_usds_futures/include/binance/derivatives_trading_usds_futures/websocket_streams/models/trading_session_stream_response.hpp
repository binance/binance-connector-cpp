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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

struct TradingSessionStreamResponse {
    /// Event type, can also be CommodityUpdate, KR_EquityUpdate, HK_EquityUpdate, CN_EquityUpdate
    /// or FXUpdate
    std::optional<std::string> e;
    /// Event time
    std::optional<std::int64_t> e_uppercase;
    /// Session start time
    std::optional<std::int64_t> t;
    /// Session end time
    std::optional<std::int64_t> t_uppercase;
    /// Session type
    std::optional<std::string> s_uppercase;

    bool operator==(const TradingSessionStreamResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TradingSessionStreamResponse tag_invoke(
    boost::json::value_to_tag<TradingSessionStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const TradingSessionStreamResponse& v);

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
