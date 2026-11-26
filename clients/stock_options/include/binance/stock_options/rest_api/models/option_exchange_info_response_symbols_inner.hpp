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

struct OptionExchangeInfoResponseSymbolsInner {
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// OCC root symbol. Differs from `underlyingSymbol` for contracts adjusted by a corporate
    /// action (e.g. `GOOG1`).
    std::optional<std::string> root_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Contract trading status: `OPEN_CLOSE` / `CLOSE_ONLY` / `NONE`. Omitted when the status of a
    /// contract is temporarily unavailable. See Common Definition.
    std::optional<std::string> status;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Premium multiplier. Order cost = price × quantity × multiplier. `100` for standard
    /// contracts.
    std::optional<std::string> multiplier;
    /// Shares delivered per contract. Equals `multiplier` for standard contracts; may differ after
    /// a corporate action.
    std::optional<std::int64_t> contract_size;
    /// Minimum price increment.
    std::optional<std::string> tick_size;
    /// Quantity increment (contracts).
    std::optional<std::string> step_size;
    /// Minimum order quantity (contracts).
    std::optional<std::string> min_qty;
    /// Maximum order quantity (contracts).
    std::optional<std::string> max_qty;
    /// Minimum order notional (`price` × `quantity` × `multiplier`), excluding fees.
    std::optional<std::string> min_notional;
    /// Maximum order notional (`price` × `quantity` × `multiplier`), excluding fees.
    std::optional<std::string> max_notional;
    /// Whether options on this underlying close 15 minutes later: `true` means 16:15 ET, otherwise
    /// 16:00 ET (both move earlier accordingly on early-close days).
    std::optional<bool> options_late_close;
    /// Penny Program indicator. Omitted when unknown.
    std::optional<bool> penny_program;
    /// What one contract delivers on exercise / assignment.
    std::optional<std::vector<OptionExchangeInfoResponseSymbolsInnerDeliverablesInner>>
        deliverables;

    bool operator==(const OptionExchangeInfoResponseSymbolsInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<OptionExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionExchangeInfoResponseSymbolsInner& v);

} // namespace binance::stock_options::rest_api
