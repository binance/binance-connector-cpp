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

/// Candlestick payload.
struct KlineStreamResponseK {
    /// Open time (epoch milliseconds).
    std::optional<std::int64_t> t;
    /// Close time (epoch milliseconds). For fixed intervals: `openTime + duration − 1ms`. For `1M`:
    /// last day of month at 23:59:59.999 UTC.
    std::optional<std::int64_t> ct;
    /// Symbol (UPPERCASE ticker).
    std::optional<std::string> s;
    /// Interval — `"5m"` / `"1h"` / `"1d"` / `"1w"` / `"1M"`.
    std::optional<std::string> i;
    /// Open price.
    std::optional<std::string> o;
    /// Close price (latest print within the interval).
    std::optional<std::string> c;
    /// High price.
    std::optional<std::string> h;
    /// Low price.
    std::optional<std::string> l;
    /// Volume (shares), default `"0"`.
    std::optional<std::string> v;
    /// Trade count; absent when upstream did not populate.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> n;
    /// Candle is closed — `true` once the interval has ended.
    std::optional<bool> x;
    /// VWAP (volume-weighted average price); absent when upstream did not populate.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> vw;

    bool operator==(const KlineStreamResponseK& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT KlineStreamResponseK
tag_invoke(boost::json::value_to_tag<KlineStreamResponseK> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const KlineStreamResponseK& v);

} // namespace binance::stocks::websocket_streams
