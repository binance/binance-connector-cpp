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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

/// ADL quantile information.
struct PositionAdlQuantileEstimationResponseInnerAdlQuantile {
    /// adl quantile for "LONG" position in hedge mode
    std::optional<std::int64_t> r_long;
    /// adl qauntile for "SHORT" position in hedge mode
    std::optional<std::int64_t> r_short;
    /// Hedge mode ADL quantile.
    std::optional<std::int64_t> hedge;
    /// One-way mode ADL quantile.
    std::optional<std::int64_t> both;

    bool operator==(const PositionAdlQuantileEstimationResponseInnerAdlQuantile& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
PositionAdlQuantileEstimationResponseInnerAdlQuantile
tag_invoke(boost::json::value_to_tag<PositionAdlQuantileEstimationResponseInnerAdlQuantile> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionAdlQuantileEstimationResponseInnerAdlQuantile& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
