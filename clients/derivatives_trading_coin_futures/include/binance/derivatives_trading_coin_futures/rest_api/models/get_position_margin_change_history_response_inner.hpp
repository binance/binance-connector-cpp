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

struct GetPositionMarginChangeHistoryResponseInner {
    /// Amount.
    std::optional<std::string> amount;
    /// asset name
    std::optional<std::string> asset;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Time
    std::optional<std::int64_t> time;
    /// Order type.
    std::optional<std::int64_t> type;
    /// Position side
    std::optional<std::string> position_side;

    bool operator==(const GetPositionMarginChangeHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetPositionMarginChangeHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetPositionMarginChangeHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetPositionMarginChangeHistoryResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
