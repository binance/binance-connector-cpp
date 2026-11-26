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

namespace binance::stocks::websocket_streams {

struct PriceStreamResponseRatesInner {
    /// Symbol (UPPERCASE ticker), e.g. `"AAPL"`.
    std::optional<std::string> s;
    /// Internal asset code, `EQ_{symbol}`. Reference only; do not use as a trading identifier.
    std::optional<std::string> ac;
    /// Latest price, trailing-zero stripped.
    std::optional<std::string> p;
    /// Price time (epoch milliseconds UTC); may be null.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> t;
    /// Previous trading day's close price; absent when unknown.
    std::optional<std::string> pc;
    /// Today's close price; absent before After-Hours.
    std::optional<std::string> tc;
    /// Final close price of the most recent completed RTH trading day. Rolls forward only once the
    /// next trading day enters Post-Market and the 1-minute kline for the minute before that day's
    /// RTH close is available; while unavailable, the previous `lrc`/`prc` pair is retained.
    std::optional<std::string> lrc;
    /// Final close price of the trading day before the `lrc` trading day. `null` when the symbol
    /// has only one completed RTH trading day (e.g. a new IPO). `std::nullopt` when the field is
    /// absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> prc;
    /// Per-symbol market phase: `C` Closed, `ON` Overnight, `PRE` Pre-Market, `O` Market Open,
    /// `POST` Post-Market.
    std::optional<std::string> mp;

    bool operator==(const PriceStreamResponseRatesInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT PriceStreamResponseRatesInner tag_invoke(
    boost::json::value_to_tag<PriceStreamResponseRatesInner> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const PriceStreamResponseRatesInner& v);

} // namespace binance::stocks::websocket_streams
