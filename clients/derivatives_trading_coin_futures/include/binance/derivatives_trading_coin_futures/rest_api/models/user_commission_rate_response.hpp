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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct UserCommissionRateResponse {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// 0.015%
    std::optional<std::string> maker_commission_rate;
    /// Taker commission rate.
    std::optional<std::string> taker_commission_rate;

    bool operator==(const UserCommissionRateResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT UserCommissionRateResponse tag_invoke(
    boost::json::value_to_tag<UserCommissionRateResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserCommissionRateResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
