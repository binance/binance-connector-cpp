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
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/notional_and_leverage_brackets_response1_inner_brackets_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct NotionalAndLeverageBracketsResponse1Inner {
    std::optional<std::string> symbol;
    /// user symbol bracket multiplier, only appears when user's symbol bracket is adjusted
    std::optional<common::Decimal> notional_coef;
    std::optional<std::vector<NotionalAndLeverageBracketsResponse1InnerBracketsInner>> brackets;

    bool operator==(const NotionalAndLeverageBracketsResponse1Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT NotionalAndLeverageBracketsResponse1Inner
tag_invoke(boost::json::value_to_tag<NotionalAndLeverageBracketsResponse1Inner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const NotionalAndLeverageBracketsResponse1Inner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
