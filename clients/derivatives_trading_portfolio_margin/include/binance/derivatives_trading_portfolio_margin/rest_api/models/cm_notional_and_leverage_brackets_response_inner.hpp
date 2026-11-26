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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_notional_and_leverage_brackets_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct CmNotionalAndLeverageBracketsResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Brackets.
    std::optional<std::vector<CmNotionalAndLeverageBracketsResponseInnerBracketsInner>> brackets;

    bool operator==(const CmNotionalAndLeverageBracketsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT CmNotionalAndLeverageBracketsResponseInner
tag_invoke(boost::json::value_to_tag<CmNotionalAndLeverageBracketsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CmNotionalAndLeverageBracketsResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
