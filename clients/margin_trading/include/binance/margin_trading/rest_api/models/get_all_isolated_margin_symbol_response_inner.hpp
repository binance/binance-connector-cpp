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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct GetAllIsolatedMarginSymbolResponseInner {
    /// base.
    std::optional<std::string> base;
    /// is Buy Allowed.
    std::optional<bool> is_buy_allowed;
    /// is Margin Trade.
    std::optional<bool> is_margin_trade;
    /// is Sell Allowed.
    std::optional<bool> is_sell_allowed;
    /// quote.
    std::optional<std::string> quote;
    /// symbol.
    std::optional<std::string> symbol;

    bool operator==(const GetAllIsolatedMarginSymbolResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetAllIsolatedMarginSymbolResponseInner
tag_invoke(boost::json::value_to_tag<GetAllIsolatedMarginSymbolResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetAllIsolatedMarginSymbolResponseInner& v);

} // namespace binance::margin_trading::rest_api
