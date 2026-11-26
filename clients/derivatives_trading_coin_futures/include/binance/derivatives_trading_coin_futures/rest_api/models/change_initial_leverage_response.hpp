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

struct ChangeInitialLeverageResponse {
    /// Leverage value.
    std::optional<std::int64_t> leverage;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// Trading symbol
    std::optional<std::string> symbol;

    bool operator==(const ChangeInitialLeverageResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ChangeInitialLeverageResponse tag_invoke(
    boost::json::value_to_tag<ChangeInitialLeverageResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ChangeInitialLeverageResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
