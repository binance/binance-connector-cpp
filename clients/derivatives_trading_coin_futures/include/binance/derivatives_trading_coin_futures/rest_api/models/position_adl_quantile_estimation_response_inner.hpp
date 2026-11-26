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
#include <binance/derivatives_trading_coin_futures/rest_api/models/position_adl_quantile_estimation_response_inner_adl_quantile.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct PositionAdlQuantileEstimationResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    std::optional<PositionAdlQuantileEstimationResponseInnerAdlQuantile> adl_quantile;

    bool operator==(const PositionAdlQuantileEstimationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PositionAdlQuantileEstimationResponseInner
tag_invoke(boost::json::value_to_tag<PositionAdlQuantileEstimationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const PositionAdlQuantileEstimationResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
