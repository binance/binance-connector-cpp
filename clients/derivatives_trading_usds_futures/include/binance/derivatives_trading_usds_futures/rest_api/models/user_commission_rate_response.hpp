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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct UserCommissionRateResponse {
    std::optional<std::string> symbol;
    /// 0.02%
    std::optional<std::string> maker_commission_rate;
    /// 0.04%
    std::optional<std::string> taker_commission_rate;
    /// 0.005%
    std::optional<std::string> rpi_commission_rate;

    bool operator==(const UserCommissionRateResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT UserCommissionRateResponse tag_invoke(
    boost::json::value_to_tag<UserCommissionRateResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserCommissionRateResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
