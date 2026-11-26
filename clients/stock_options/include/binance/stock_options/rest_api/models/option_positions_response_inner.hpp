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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionPositionsResponseInner {
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Position side: `LONG` / `SHORT`.
    std::optional<std::string> side;
    /// Contracts available to close, signed (negative for short positions).
    std::optional<std::string> free;
    /// Contracts reserved by open orders or submitted exercises, signed (negative for short
    /// positions).
    std::optional<std::string> locked;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Premium multiplier. Order cost = price × quantity × multiplier.
    std::optional<std::string> multiplier;

    bool operator==(const OptionPositionsResponseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionPositionsResponseInner tag_invoke(
    boost::json::value_to_tag<OptionPositionsResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionPositionsResponseInner& v);

} // namespace binance::stock_options::rest_api
