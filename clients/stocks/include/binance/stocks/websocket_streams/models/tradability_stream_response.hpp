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

struct TradabilityStreamResponse {
    /// Event type, always `"tradability"`.
    std::optional<std::string> e;
    /// Symbol (UPPERCASE ticker).
    std::optional<std::string> symbol;
    /// Internal asset code `EQ_{symbol}`; reference only. May be null for symbols not yet in the
    /// symbol dictionary. `std::nullopt` when the field is absent; holds `std::nullopt` when it is
    /// `null`.
    std::optional<std::optional<std::string>> asset_code;
    /// The new tradability value. `OFFMARKET` and `DELISTING` are protected states — trading-status
    /// events will not transition a symbol out of them.
    std::optional<std::string> tradability;
    /// Push time (epoch milliseconds UTC).
    std::optional<std::int64_t> t;

    bool operator==(const TradabilityStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TradabilityStreamResponse tag_invoke(
    boost::json::value_to_tag<TradabilityStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TradabilityStreamResponse& v);

} // namespace binance::stocks::websocket_streams
