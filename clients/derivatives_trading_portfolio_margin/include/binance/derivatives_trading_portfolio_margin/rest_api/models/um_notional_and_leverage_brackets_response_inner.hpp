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
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_notional_and_leverage_brackets_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct UmNotionalAndLeverageBracketsResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Notional Coef.
    std::optional<std::string> notional_coef;
    /// Brackets.
    std::optional<std::vector<UmNotionalAndLeverageBracketsResponseInnerBracketsInner>> brackets;

    bool operator==(const UmNotionalAndLeverageBracketsResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT UmNotionalAndLeverageBracketsResponseInner
tag_invoke(boost::json::value_to_tag<UmNotionalAndLeverageBracketsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UmNotionalAndLeverageBracketsResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
