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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

/// Adl Quantile.
struct UmPositionAdlQuantileEstimationResponseInnerAdlQuantile {
    /// adl quantile for "LONG" position in hedge mode
    std::optional<std::int64_t> r_long;
    /// adl quantile for "SHORT" position in hedge mode
    std::optional<std::int64_t> r_short;
    /// adl quantile for position in one-way mode
    std::optional<std::int64_t> both;

    bool operator==(
        const UmPositionAdlQuantileEstimationResponseInnerAdlQuantile& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
UmPositionAdlQuantileEstimationResponseInnerAdlQuantile tag_invoke(
    boost::json::value_to_tag<UmPositionAdlQuantileEstimationResponseInnerAdlQuantile> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UmPositionAdlQuantileEstimationResponseInnerAdlQuantile& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
