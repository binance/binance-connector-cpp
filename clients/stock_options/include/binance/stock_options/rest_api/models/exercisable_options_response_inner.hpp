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

#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_exchange_info_response_symbols_inner_deliverables_inner.hpp>

namespace binance::stock_options::rest_api {

struct ExercisableOptionsResponseInner {
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// OCC root symbol. Differs from `underlyingSymbol` for contracts adjusted by a corporate
    /// action (e.g. `GOOG1`).
    std::optional<std::string> root_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Premium multiplier. Order cost = price × quantity × multiplier.
    std::optional<std::string> multiplier;
    /// Total contracts held.
    std::optional<std::string> position_qty;
    /// Contracts available to exercise; the upper limit for Submit Option Exercise.
    std::optional<std::string> available_qty;
    /// What one contract delivers on exercise / assignment.
    std::optional<std::vector<OptionExchangeInfoResponseSymbolsInnerDeliverablesInner>>
        deliverables;

    bool operator==(const ExercisableOptionsResponseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT ExercisableOptionsResponseInner
tag_invoke(boost::json::value_to_tag<ExercisableOptionsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const ExercisableOptionsResponseInner& v);

} // namespace binance::stock_options::rest_api
