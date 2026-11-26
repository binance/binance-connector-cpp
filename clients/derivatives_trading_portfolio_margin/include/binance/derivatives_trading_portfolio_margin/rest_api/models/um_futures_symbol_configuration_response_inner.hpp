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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct UmFuturesSymbolConfigurationResponseInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Margin Type.
    std::optional<std::string> margin_type;
    /// Is Auto Add Margin.
    std::optional<std::string> is_auto_add_margin;
    /// current initial leverage
    std::optional<std::int64_t> leverage;
    /// Max Notional Value.
    std::optional<std::string> max_notional_value;

    bool operator==(const UmFuturesSymbolConfigurationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT UmFuturesSymbolConfigurationResponseInner
tag_invoke(boost::json::value_to_tag<UmFuturesSymbolConfigurationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UmFuturesSymbolConfigurationResponseInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
