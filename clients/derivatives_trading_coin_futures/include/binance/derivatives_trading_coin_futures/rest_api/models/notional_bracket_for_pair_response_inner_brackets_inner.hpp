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
#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct NotionalBracketForPairResponseInnerBracketsInner {
    /// bracket level
    std::optional<std::int64_t> bracket;
    /// the maximum leverage
    std::optional<std::int64_t> initial_leverage;
    /// upper edge of base asset quantity
    std::optional<std::int64_t> qty_cap;
    /// lower edge of base asset quantity
    std::optional<std::int64_t> qtyl_floor;
    /// Maintenance margin ratio.
    std::optional<common::Decimal> maint_margin_ratio;
    /// Cumulative value.
    std::optional<common::Decimal> cum;

    bool
    operator==(const NotionalBracketForPairResponseInnerBracketsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NotionalBracketForPairResponseInnerBracketsInner
tag_invoke(boost::json::value_to_tag<NotionalBracketForPairResponseInnerBracketsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NotionalBracketForPairResponseInnerBracketsInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
