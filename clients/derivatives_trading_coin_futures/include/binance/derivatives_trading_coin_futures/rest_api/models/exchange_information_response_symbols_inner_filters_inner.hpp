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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ExchangeInformationResponseSymbolsInnerFiltersInner {
    /// Filter type.
    std::optional<std::string> filter_type;
    /// Maximum price.
    std::optional<std::string> max_price;
    /// Minimum price.
    std::optional<std::string> min_price;
    /// Tick size.
    std::optional<std::string> tick_size;
    /// maximum quantity of base asset
    std::optional<std::string> max_qty;
    /// Minimum quantity.
    std::optional<std::string> min_qty;
    /// Step size.
    std::optional<std::string> step_size;
    /// Maximum allowed orders for this rule.
    std::optional<std::int64_t> limit;
    /// Upper multiplier bound.
    std::optional<std::string> multiplier_up;
    /// Lower multiplier bound.
    std::optional<std::string> multiplier_down;
    /// Multiplier decimal precision.
    std::optional<std::string> multiplier_decimal;

    bool operator==(const ExchangeInformationResponseSymbolsInnerFiltersInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ExchangeInformationResponseSymbolsInnerFiltersInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseSymbolsInnerFiltersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseSymbolsInnerFiltersInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
