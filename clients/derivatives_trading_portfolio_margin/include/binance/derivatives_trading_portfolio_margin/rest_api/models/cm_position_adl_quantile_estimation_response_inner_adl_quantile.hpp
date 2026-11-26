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
struct CmPositionAdlQuantileEstimationResponseInnerAdlQuantile {
    /// adl quantile for "LONG" position in hedge mode
    std::optional<std::int64_t> r_long;
    /// adl qauntile for "SHORT" position in hedge mode
    std::optional<std::int64_t> r_short;
    /// only a sign, ignore the value
    std::optional<std::int64_t> hedge;
    /// adl qunatile for position in one-way mode
    std::optional<std::int64_t> both;

    bool operator==(
        const CmPositionAdlQuantileEstimationResponseInnerAdlQuantile& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
CmPositionAdlQuantileEstimationResponseInnerAdlQuantile tag_invoke(
    boost::json::value_to_tag<CmPositionAdlQuantileEstimationResponseInnerAdlQuantile> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CmPositionAdlQuantileEstimationResponseInnerAdlQuantile& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
