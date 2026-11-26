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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct ExchangeInfoResponseSymbolsInner {
    /// US-equity ticker, e.g. `AAPL`.
    std::optional<std::string> symbol;
    /// Trading direction allowed — one of `BUY_SELL` / `BUY` / `SELL` / `NONE`.
    std::optional<std::string> tradability;
    /// Last time the `tradability` value was updated (ms epoch).
    std::optional<std::int64_t> tradability_update_time;
    /// Whether the symbol supports overnight trading.
    std::optional<bool> overnight_supported;
    /// Whether fractional shares are supported during the regular session.
    std::optional<bool> fractionable;
    /// Whether fractional shares are supported during extended hours.
    std::optional<bool> fractionable_eh;
    /// Whether extended-session trading is enabled.
    std::optional<bool> extended_session;
    /// Maximum number of open orders a user may have for this symbol.
    std::optional<std::int64_t> max_num_orders;
    /// Lot size — minimum increment for `quantity`.
    std::optional<std::string> step_size;
    /// Upper price multiplier limit relative to reference.
    std::optional<std::string> multiplier_up;
    /// Lower price multiplier limit relative to reference.
    std::optional<std::string> multiplier_down;
    /// Minimum allowed `quantity`.
    std::optional<std::string> min_qty;
    /// Maximum allowed `quantity`.
    std::optional<std::string> max_qty;
    /// Minimum order notional (USD).
    std::optional<std::string> min_notional;
    /// Maximum order notional (USD).
    std::optional<std::string> max_notional;
    /// Listing timestamp (ms epoch).
    std::optional<std::int64_t> listing_time;
    /// Scheduled delisting timestamp (ms epoch); `null` if not scheduled for delisting.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> delisting_time;

    bool operator==(const ExchangeInfoResponseSymbolsInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT ExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const ExchangeInfoResponseSymbolsInner& v);

} // namespace binance::stocks::rest_api
