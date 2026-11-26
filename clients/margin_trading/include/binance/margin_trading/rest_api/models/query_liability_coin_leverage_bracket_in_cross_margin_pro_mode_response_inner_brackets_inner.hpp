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
#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner {
    /// leverage.
    std::optional<std::int64_t> leverage;
    /// max Debt.
    std::optional<common::Decimal> max_debt;
    /// maintenance Margin Rate.
    std::optional<common::Decimal> maintenance_margin_rate;
    /// initial Margin Rate.
    std::optional<common::Decimal> initial_margin_rate;
    /// fast Num.
    std::optional<common::Decimal> fast_num;

    bool operator==(
        const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner& /*other*/)
        const = default;
};

BINANCE_MARGIN_TRADING_EXPORT
QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner tag_invoke(
    boost::json::value_to_tag<
        QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner& v);

} // namespace binance::margin_trading::rest_api
