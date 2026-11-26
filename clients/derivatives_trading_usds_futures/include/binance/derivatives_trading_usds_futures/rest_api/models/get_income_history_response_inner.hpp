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

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetIncomeHistoryResponseInner {
    /// trade symbol, if existing
    std::optional<std::string> symbol;
    /// income type
    std::optional<std::string> income_type;
    /// income amount
    std::optional<std::string> income;
    /// income asset
    std::optional<std::string> asset;
    /// extra information
    std::optional<std::string> info;
    /// Time.
    std::optional<std::int64_t> time;
    /// transaction id
    std::optional<std::int64_t> tran_id;
    /// trade id, if existing
    std::optional<std::string> trade_id;

    bool operator==(const GetIncomeHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetIncomeHistoryResponseInner tag_invoke(
    boost::json::value_to_tag<GetIncomeHistoryResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetIncomeHistoryResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
