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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionExpirationsResponseInner {
    /// Expiration date in `YYYY-MM-DD`, US Eastern (ET) calendar day. Can be passed as-is to Option
    /// Contracts.
    std::optional<std::string> expiration_date;
    /// OCC root symbol. Differs from `underlyingSymbol` for contracts adjusted by a corporate
    /// action (e.g. `GOOG1`).
    std::optional<std::string> root_symbol;

    bool operator==(const OptionExpirationsResponseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionExpirationsResponseInner
tag_invoke(boost::json::value_to_tag<OptionExpirationsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionExpirationsResponseInner& v);

} // namespace binance::stock_options::rest_api
