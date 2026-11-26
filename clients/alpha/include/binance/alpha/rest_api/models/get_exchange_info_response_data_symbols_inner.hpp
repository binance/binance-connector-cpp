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

#include <binance/alpha/export.hpp>
#include <binance/alpha/rest_api/models/get_exchange_info_response_data_symbols_inner_filters_inner.hpp>

namespace binance::alpha::rest_api {

struct GetExchangeInfoResponseDataSymbolsInner {
    /// Trading symbol.
    std::optional<std::string> symbol;
    /// Trading status.
    std::optional<std::string> status;
    /// Base asset symbol.
    std::optional<std::string> base_asset;
    /// Quote asset symbol.
    std::optional<std::string> quote_asset;
    /// Allowed precision for price.
    std::optional<std::int64_t> price_precision;
    /// Allowed precision for quantity.
    std::optional<std::int64_t> quantity_precision;
    /// Base asset precision.
    std::optional<std::int64_t> base_asset_precision;
    /// Quote asset precision.
    std::optional<std::int64_t> quote_precision;
    /// Trading filters and constraints.
    std::optional<std::vector<GetExchangeInfoResponseDataSymbolsInnerFiltersInner>> filters;
    /// Supported order types for this symbol.
    std::optional<std::vector<std::string>> order_types;

    bool operator==(const GetExchangeInfoResponseDataSymbolsInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT GetExchangeInfoResponseDataSymbolsInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const GetExchangeInfoResponseDataSymbolsInner& v);

} // namespace binance::alpha::rest_api
