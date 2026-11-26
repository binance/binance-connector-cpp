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

struct GetIncomeHistoryResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// income type
    std::optional<std::string> income_type;
    /// income amount
    std::optional<std::string> income;
    /// asset name
    std::optional<std::string> asset;
    /// extra information
    std::optional<std::string> info;
    /// Time
    std::optional<std::int64_t> time;
    /// transaction id
    std::optional<std::string> tran_id;
    /// Trade ID.
    std::optional<std::string> trade_id;

    bool operator==(const GetIncomeHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT GetIncomeHistoryResponseInner tag_invoke(
    boost::json::value_to_tag<GetIncomeHistoryResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetIncomeHistoryResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
