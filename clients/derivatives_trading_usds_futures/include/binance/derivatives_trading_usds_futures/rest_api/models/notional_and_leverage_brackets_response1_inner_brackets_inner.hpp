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

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct NotionalAndLeverageBracketsResponse1InnerBracketsInner {
    /// Notional bracket
    std::optional<std::int64_t> bracket;
    /// Max initial leverage for this bracket
    std::optional<std::int64_t> initial_leverage;
    /// Cap notional of this bracket
    std::optional<std::int64_t> notional_cap;
    /// Notional threshold of this bracket
    std::optional<std::int64_t> notional_floor;
    /// Maintenance ratio for this bracket
    std::optional<common::Decimal> maint_margin_ratio;
    /// Auxiliary number for quick calculation
    std::optional<common::Decimal> cum;

    bool operator==(const NotionalAndLeverageBracketsResponse1InnerBracketsInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
NotionalAndLeverageBracketsResponse1InnerBracketsInner tag_invoke(
    boost::json::value_to_tag<NotionalAndLeverageBracketsResponse1InnerBracketsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NotionalAndLeverageBracketsResponse1InnerBracketsInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
