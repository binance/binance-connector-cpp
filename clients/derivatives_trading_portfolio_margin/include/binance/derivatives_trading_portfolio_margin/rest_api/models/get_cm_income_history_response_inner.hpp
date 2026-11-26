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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetCmIncomeHistoryResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Income type.
    std::optional<std::string> income_type;
    /// Income amount.
    std::optional<std::string> income;
    /// Income asset.
    std::optional<std::string> asset;
    /// Extra information.
    std::optional<std::string> info;
    /// Event time.
    std::optional<std::int64_t> time;
    /// Transaction ID.
    std::optional<std::string> tran_id;
    /// Trade ID, if existing.
    std::optional<std::string> trade_id;

    bool operator==(const GetCmIncomeHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetCmIncomeHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetCmIncomeHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCmIncomeHistoryResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
