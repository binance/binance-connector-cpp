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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response_symbols_inner_filters_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct ExchangeInformationResponseSymbolsInner {
    /// Trading filters and constraints.
    std::optional<std::vector<ExchangeInformationResponseSymbolsInnerFiltersInner>> filters;
    /// Supported order types.
    std::optional<std::vector<std::string>> order_types;
    /// Time in force
    std::optional<std::vector<std::string>> time_in_force;
    /// liquidation fee rate
    std::optional<std::string> liquidation_fee;
    /// the max price difference rate( from mark price) a market order can make
    std::optional<std::string> market_take_bound;
    /// Trading symbol
    std::optional<std::string> symbol;
    /// Pair
    std::optional<std::string> pair;
    /// Contract type.
    std::optional<std::string> contract_type;
    /// Delivery timestamp.
    std::optional<std::int64_t> delivery_date;
    /// Onboard timestamp.
    std::optional<std::int64_t> onboard_date;
    /// Contract status.
    std::optional<std::string> contract_status;
    /// Contract size.
    std::optional<std::int64_t> contract_size;
    /// Quote asset symbol.
    std::optional<std::string> quote_asset;
    /// Base asset symbol.
    std::optional<std::string> base_asset;
    /// Margin asset.
    std::optional<std::string> margin_asset;
    /// please do not use it as tickSize
    std::optional<std::int64_t> price_precision;
    /// please do not use it as stepSize
    std::optional<std::int64_t> quantity_precision;
    /// Base asset precision.
    std::optional<std::int64_t> base_asset_precision;
    /// Quote asset precision.
    std::optional<std::int64_t> quote_precision;
    /// ignore
    std::optional<std::int64_t> equal_qty_precision;
    /// threshold for algo order with "priceProtect"
    std::optional<std::string> trigger_protect;
    /// ignore
    std::optional<std::string> maint_margin_percent;
    /// ignore
    std::optional<std::string> required_margin_percent;
    /// Underlying asset type.
    std::optional<std::string> underlying_type;
    /// Underlying asset sub-type.
    std::optional<std::vector<std::string>> underlying_sub_type;

    bool operator==(const ExchangeInformationResponseSymbolsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ExchangeInformationResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseSymbolsInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
