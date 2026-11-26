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

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner_filters_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct ExchangeInformationResponseOptionSymbolsInner {
    /// expiry time
    std::optional<std::int64_t> expiry_date;
    /// filters
    std::optional<std::vector<ExchangeInformationResponseOptionSymbolsInnerFiltersInner>> filters;
    /// Trading pair name
    std::optional<std::string> symbol;
    /// Direction: CALL long, PUT short
    std::optional<std::string> side;
    /// Strike price
    std::optional<std::string> strike_price;
    /// Name of the underlying asset of the option contract
    std::optional<std::string> underlying;
    /// Contract unit, the quantity of the underlying asset represented by a single contract.
    std::optional<std::int64_t> unit;
    /// liquidation fee rate
    std::optional<std::string> liquidation_fee_rate;
    /// Minimum order quantity
    std::optional<std::string> min_qty;
    /// Maximum order quantity
    std::optional<std::string> max_qty;
    /// Initial Magin Ratio
    std::optional<std::string> initial_margin;
    /// Maintenance Margin Ratio
    std::optional<std::string> maintenance_margin;
    /// Min Initial Margin Ratio
    std::optional<std::string> min_initial_margin;
    /// Min Maintenance Margin Ratio
    std::optional<std::string> min_maintenance_margin;
    /// price precision
    std::optional<std::int64_t> price_scale;
    /// quantity precision
    std::optional<std::int64_t> quantity_scale;
    /// Quotation asset
    std::optional<std::string> quote_asset;
    /// Contract type
    std::optional<std::string> contract_type;
    /// Underlying type
    std::optional<std::string> underlying_type;
    /// Whether naked selling is allowed for this symbol
    std::optional<bool> naked_sell;
    /// Trading Status
    std::optional<std::string> status;

    bool operator==(const ExchangeInformationResponseOptionSymbolsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT ExchangeInformationResponseOptionSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseOptionSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseOptionSymbolsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
