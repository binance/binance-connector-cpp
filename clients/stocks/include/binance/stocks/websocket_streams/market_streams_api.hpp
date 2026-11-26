//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/stocks/export.hpp>
#include <binance/stocks/websocket_streams/models/calendar_stream_response.hpp>
#include <binance/stocks/websocket_streams/models/kline_stream_response.hpp>
#include <binance/stocks/websocket_streams/models/price_stream_response.hpp>
#include <binance/stocks/websocket_streams/models/quote_stream_response.hpp>
#include <binance/stocks/websocket_streams/models/tradability_stream_response.hpp>
#include <binance/stocks/websocket_streams/models/trading_status_stream_response.hpp>

namespace binance::stocks::websocket_streams {

struct CalendarStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct KlineStreamParams {
    /// US-equity ticker (UPPERCASE), e.g. `AAPL`.
    common::Required<std::string> symbol;
    /// Kline interval — `5m` / `1h` / `1d` / `1w` / `1M`.
    common::Required<std::string> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct PriceStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct QuoteStreamParams {
    /// US-equity ticker (UPPERCASE), e.g. `AAPL`.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct TradabilityStreamParams {
    /// US-equity ticker (UPPERCASE), e.g. `AAPL`.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct TradingStatusStreamParams {
    /// US-equity ticker (UPPERCASE), e.g. `AAPL`.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_STOCKS_EXPORT MarketStreamsApi {
public:
    explicit MarketStreamsApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Calendar Stream
    ///
    /// `calendar`.
    ///
    /// Single-stream broadcast of market-phase transitions. One message per transition; no periodic
    /// heartbeat payload. Server polls every 5 seconds. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#calendar-stream
    [[nodiscard]] common::WebsocketStream<CalendarStreamResponse>
    calendar_stream(const CalendarStreamParams& params = {}) const;

    /// Kline Stream
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// Per-symbol candlestick updates. One stream per (symbol, interval) combination. Supported
    /// intervals: 5m, 1h, 1d, 1w, 1M. Also reachable via the SUBSCRIBE/UNSUBSCRIBE RPC — see
    /// Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#kline-stream
    [[nodiscard]] common::WebsocketStream<KlineStreamResponse>
    kline_stream(const KlineStreamParams& params) const;

    /// Price Stream
    ///
    /// `price`.
    ///
    /// Push-all price snapshot, polled every 3 seconds. One message carries the latest price for
    /// every active US-equity symbol. Also reachable via the SUBSCRIBE/UNSUBSCRIBE RPC — see
    /// Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#price-stream
    [[nodiscard]] common::WebsocketStream<PriceStreamResponse>
    price_stream(const PriceStreamParams& params = {}) const;

    /// Quote Stream
    ///
    /// `<symbol>@quote`.
    ///
    /// Per-symbol real-time best-bid / best-ask. Each symbol has its own stream. Per-symbol
    /// throttle: at most one push per symbol every 200 ms. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#quote-stream
    [[nodiscard]] common::WebsocketStream<QuoteStreamResponse>
    quote_stream(const QuoteStreamParams& params) const;

    /// Tradability Stream
    ///
    /// `<symbol>@tradability`.
    ///
    /// Per-symbol push whenever the tradable direction of a symbol changes. Pushed only when the
    /// value actually changes (new value ≠ old value). Also reachable via the SUBSCRIBE/UNSUBSCRIBE
    /// RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#tradability-stream
    [[nodiscard]] common::WebsocketStream<TradabilityStreamResponse>
    tradability_stream(const TradabilityStreamParams& params) const;

    /// Trading Status Stream
    ///
    /// `<symbol>@tradingStatus`.
    ///
    /// Per-symbol trading-status transitions (halts, resumes, SSR, LULD pauses, etc.). Events that
    /// do not match a known status/reason rule are not pushed. Also reachable via the
    /// SUBSCRIBE/UNSUBSCRIBE RPC — see Subscribing via RPC.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/ws-streams/market-streams#trading-status-stream
    [[nodiscard]] common::WebsocketStream<TradingStatusStreamResponse>
    trading_status_stream(const TradingStatusStreamParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::stocks::websocket_streams
