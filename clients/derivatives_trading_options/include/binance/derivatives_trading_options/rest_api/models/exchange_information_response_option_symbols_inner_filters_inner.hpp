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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct ExchangeInformationResponseOptionSymbolsInnerFiltersInner {
    /// filter Type
    std::optional<std::string> filter_type;
    /// min Price
    std::optional<std::string> min_price;
    /// max Price
    std::optional<std::string> max_price;
    /// tick Size
    std::optional<std::string> tick_size;
    /// Minimum order quantity
    std::optional<std::string> min_qty;
    /// Maximum order quantity
    std::optional<std::string> max_qty;
    /// step Size
    std::optional<std::string> step_size;

    bool operator==(
        const ExchangeInformationResponseOptionSymbolsInnerFiltersInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT ExchangeInformationResponseOptionSymbolsInnerFiltersInner
tag_invoke(
    boost::json::value_to_tag<ExchangeInformationResponseOptionSymbolsInnerFiltersInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseOptionSymbolsInnerFiltersInner& v);

} // namespace binance::derivatives_trading_options::rest_api
