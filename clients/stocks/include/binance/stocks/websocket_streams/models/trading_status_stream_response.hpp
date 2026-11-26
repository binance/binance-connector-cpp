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

struct TradingStatusStreamResponse {
    /// Event type, always `"tradingStatus"`.
    std::optional<std::string> e;
    /// Symbol (UPPERCASE ticker), e.g. `"AAPL"`.
    std::optional<std::string> symbol;
    /// Internal asset code `EQ_{symbol}`; reference only.
    std::optional<std::string> asset_code;
    /// Trading status.
    std::optional<std::string> status;
    /// Reason code.
    std::optional<std::string> msg;
    /// Status-effective time (epoch milliseconds UTC). May be in the future.
    std::optional<std::int64_t> time;
    /// Tape designation: `C` = CTA (NYSE / AMEX), `N` = UTP (Nasdaq).
    std::optional<std::string> z;
    /// Tradability after the status change: `BUY_SELL` / `BUY` / `SELL` / `NONE`.
    std::optional<std::string> tradability;

    bool operator==(const TradingStatusStreamResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TradingStatusStreamResponse tag_invoke(
    boost::json::value_to_tag<TradingStatusStreamResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TradingStatusStreamResponse& v);

} // namespace binance::stocks::websocket_streams
