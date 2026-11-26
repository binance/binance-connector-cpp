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
#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct CmNotionalAndLeverageBracketsResponseInnerBracketsInner {
    /// bracket level
    std::optional<std::int64_t> bracket;
    /// the maximum leverage
    std::optional<std::int64_t> initial_leverage;
    /// upper edge of base asset quantity
    std::optional<std::int64_t> qty_cap;
    /// lower edge of base asset quantity
    std::optional<std::int64_t> qty_floor;
    /// maintenance margin rate
    std::optional<common::Decimal> maint_margin_ratio;
    /// Auxiliary number for quick calculation
    std::optional<common::Decimal> cum;

    bool operator==(
        const CmNotionalAndLeverageBracketsResponseInnerBracketsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
CmNotionalAndLeverageBracketsResponseInnerBracketsInner tag_invoke(
    boost::json::value_to_tag<CmNotionalAndLeverageBracketsResponseInnerBracketsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CmNotionalAndLeverageBracketsResponseInnerBracketsInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
