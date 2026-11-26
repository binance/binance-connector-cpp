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

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/notional_bracket_for_pair_response_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct NotionalBracketForSymbolResponseInner {
    /// Trading symbol
    std::optional<std::string> symbol;
    /// user symbol bracket multiplier, only appears when user's symbol bracket is adjusted
    std::optional<common::Decimal> notional_coef;
    /// Leverage bracket details.
    std::optional<std::vector<NotionalBracketForPairResponseInnerBracketsInner>> brackets;

    bool operator==(const NotionalBracketForSymbolResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NotionalBracketForSymbolResponseInner
tag_invoke(boost::json::value_to_tag<NotionalBracketForSymbolResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NotionalBracketForSymbolResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
