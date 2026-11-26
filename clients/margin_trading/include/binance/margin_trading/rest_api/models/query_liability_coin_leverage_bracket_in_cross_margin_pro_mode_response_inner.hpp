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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_response_inner_brackets_inner.hpp>

namespace binance::margin_trading::rest_api {

struct QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner {
    /// asset Names list.
    std::optional<std::vector<std::string>> asset_names;
    /// rank.
    std::optional<std::int64_t> rank;
    /// brackets list.
    std::optional<std::vector<
        QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInnerBracketsInner>>
        brackets;

    bool
    operator==(const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner& /*other*/)
        const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner
tag_invoke(boost::json::value_to_tag<
               QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner& v);

} // namespace binance::margin_trading::rest_api
