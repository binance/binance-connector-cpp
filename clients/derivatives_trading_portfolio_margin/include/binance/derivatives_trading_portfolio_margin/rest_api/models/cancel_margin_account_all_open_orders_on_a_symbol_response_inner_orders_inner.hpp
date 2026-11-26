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

struct CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner {
    /// Trade symbol, if existing.
    std::optional<std::string> symbol;
    /// Normal orderID after trigger if appliable, only have when the strategy is triggered
    std::optional<std::int64_t> order_id;
    /// Client Order ID.
    std::optional<std::string> client_order_id;

    bool
    operator==(const CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner& /*other*/)
        const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT
CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner
tag_invoke(boost::json::value_to_tag<
               CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CancelMarginAccountAllOpenOrdersOnASymbolResponseInnerOrdersInner& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
