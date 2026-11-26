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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct ExchangeInformationResponseSymbolsInnerFiltersInner {
    /// Filter Type.
    std::optional<std::string> filter_type;
    /// Max Price.
    std::optional<std::string> max_price;
    /// Min Price.
    std::optional<std::string> min_price;
    /// Tick Size.
    std::optional<std::string> tick_size;
    /// Max Qty.
    std::optional<std::string> max_qty;
    /// Min Qty.
    std::optional<std::string> min_qty;
    /// Step Size.
    std::optional<std::string> step_size;
    /// Limit.
    std::optional<std::int64_t> limit;
    std::optional<std::string> notional;
    /// Multiplier Up.
    std::optional<std::string> multiplier_up;
    /// Multiplier Down.
    std::optional<std::string> multiplier_down;
    std::optional<std::string> multiplier_decimal;

    bool operator==(const ExchangeInformationResponseSymbolsInnerFiltersInner& /*other*/) const =
        default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ExchangeInformationResponseSymbolsInnerFiltersInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseSymbolsInnerFiltersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseSymbolsInnerFiltersInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
