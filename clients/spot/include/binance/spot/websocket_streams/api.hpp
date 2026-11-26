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
#include <string_view>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_streams/models/agg_trade_response.hpp>
#include <binance/spot/websocket_streams/models/all_market_rolling_window_ticker_response_inner.hpp>
#include <binance/spot/websocket_streams/models/all_mini_ticker_response_inner.hpp>
#include <binance/spot/websocket_streams/models/avg_price_response.hpp>
#include <binance/spot/websocket_streams/models/block_trade_response.hpp>
#include <binance/spot/websocket_streams/models/book_ticker_response.hpp>
#include <binance/spot/websocket_streams/models/diff_book_depth_response.hpp>
#include <binance/spot/websocket_streams/models/kline_offset_response.hpp>
#include <binance/spot/websocket_streams/models/kline_response.hpp>
#include <binance/spot/websocket_streams/models/mini_ticker_response.hpp>
#include <binance/spot/websocket_streams/models/partial_book_depth_response.hpp>
#include <binance/spot/websocket_streams/models/reference_price_response.hpp>
#include <binance/spot/websocket_streams/models/rolling_window_ticker_response.hpp>
#include <binance/spot/websocket_streams/models/ticker_response.hpp>
#include <binance/spot/websocket_streams/models/trade_response.hpp>

namespace binance::spot::websocket_streams {

enum class AllMarketRollingWindowTickerWindowSizeEnum {
    WindowSize1h,
    WindowSize4h,
    WindowSize1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(AllMarketRollingWindowTickerWindowSizeEnum value) noexcept;
BINANCE_SPOT_EXPORT AllMarketRollingWindowTickerWindowSizeEnum
tag_invoke(boost::json::value_to_tag<AllMarketRollingWindowTickerWindowSizeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    AllMarketRollingWindowTickerWindowSizeEnum value);

enum class DiffBookDepthUpdateSpeedEnum {
    UpdateSpeed100ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(DiffBookDepthUpdateSpeedEnum value) noexcept;
BINANCE_SPOT_EXPORT DiffBookDepthUpdateSpeedEnum tag_invoke(
    boost::json::value_to_tag<DiffBookDepthUpdateSpeedEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    DiffBookDepthUpdateSpeedEnum value);

enum class KlineIntervalEnum {
    Interval1s,
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(KlineIntervalEnum value) noexcept;
BINANCE_SPOT_EXPORT KlineIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    KlineIntervalEnum value);

enum class KlineOffsetIntervalEnum {
    Interval1s,
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(KlineOffsetIntervalEnum value) noexcept;
BINANCE_SPOT_EXPORT KlineOffsetIntervalEnum tag_invoke(
    boost::json::value_to_tag<KlineOffsetIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    KlineOffsetIntervalEnum value);

enum class PartialBookDepthLevelsEnum {
    Levels5,
    Levels10,
    Levels20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(PartialBookDepthLevelsEnum value) noexcept;
BINANCE_SPOT_EXPORT PartialBookDepthLevelsEnum tag_invoke(
    boost::json::value_to_tag<PartialBookDepthLevelsEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    PartialBookDepthLevelsEnum value);

enum class PartialBookDepthUpdateSpeedEnum {
    UpdateSpeed100ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(PartialBookDepthUpdateSpeedEnum value) noexcept;
BINANCE_SPOT_EXPORT PartialBookDepthUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    PartialBookDepthUpdateSpeedEnum value);

enum class RollingWindowTickerWindowSizeEnum {
    WindowSize1h,
    WindowSize4h,
    WindowSize1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(RollingWindowTickerWindowSizeEnum value) noexcept;
BINANCE_SPOT_EXPORT RollingWindowTickerWindowSizeEnum
tag_invoke(boost::json::value_to_tag<RollingWindowTickerWindowSizeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    RollingWindowTickerWindowSizeEnum value);

struct AggTradeParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllMarketRollingWindowTickerParams {
    common::Required<AllMarketRollingWindowTickerWindowSizeEnum> window_size;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllMiniTickerParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AvgPriceParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct BlockTradeParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct BookTickerParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct DiffBookDepthParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// Optional stream update speed suffix
    std::optional<DiffBookDepthUpdateSpeedEnum> update_speed = std::nullopt;
};

struct KlineParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    common::Required<KlineIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct KlineOffsetParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    common::Required<KlineOffsetIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct MiniTickerParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct PartialBookDepthParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    common::Required<PartialBookDepthLevelsEnum> levels;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// Optional stream update speed suffix
    std::optional<PartialBookDepthUpdateSpeedEnum> update_speed = std::nullopt;
};

struct ReferencePriceParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct RollingWindowTickerParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    common::Required<RollingWindowTickerWindowSizeEnum> window_size;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct TickerParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct TradeParams {
    /// Symbol to query
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_SPOT_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::WebsocketStreams> client);

    /// Aggregate Trade Streams
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// The Aggregate Trade Streams push trade information that is aggregated
    /// for a single taker order.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#agg-trade
    [[nodiscard]] common::WebsocketStream<AggTradeResponse>
    agg_trade(const AggTradeParams& params) const;

    /// All Market Rolling Window Statistics Streams
    ///
    /// `!ticker_<windowSize>@arr`.
    ///
    /// Rolling window ticker statistics for all market symbols, computed over
    /// multiple windows.
    ///
    /// Note that only tickers that have changed will be present in the array.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#all-market-rolling-window-ticker
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketRollingWindowTickerResponseInner>>
    all_market_rolling_window_ticker(const AllMarketRollingWindowTickerParams& params) const;

    /// All Market Mini Tickers Stream
    ///
    /// `!miniTicker@arr`.
    ///
    /// 24hr rolling window mini-ticker statistics for all symbols that changed
    /// in an array. These are NOT the statistics of the UTC day, but a 24hr
    /// rolling window for the previous 24hrs. Note that only tickers that have
    /// changed will be present in the array.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#all-mini-ticker
    [[nodiscard]] common::WebsocketStream<std::vector<AllMiniTickerResponseInner>>
    all_mini_ticker(const AllMiniTickerParams& params = {}) const;

    /// Average Price
    ///
    /// `<symbol>@avgPrice`.
    ///
    /// Average price streams push changes in the average price over a fixed time interval.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#avg-price
    [[nodiscard]] common::WebsocketStream<AvgPriceResponse>
    avg_price(const AvgPriceParams& params) const;

    /// Block Trade Streams
    ///
    /// `<symbol>@blockTrade`.
    ///
    /// Block Trade Streams push block trade information in real-time.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#block-trade
    [[nodiscard]] common::WebsocketStream<BlockTradeResponse>
    block_trade(const BlockTradeParams& params) const;

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in
    /// real-time for a specified symbol.
    ///
    /// Multiple `<symbol>@bookTicker` streams can be subscribed to over one
    /// connection.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#book-ticker
    [[nodiscard]] common::WebsocketStream<BookTickerResponse>
    book_ticker(const BookTickerParams& params) const;

    /// Diff. Depth Stream
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Order book price and quantity depth updates used to locally manage an order book.
    ///
    /// Update Speed: 1000ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#diff-book-depth
    [[nodiscard]] common::WebsocketStream<DiffBookDepthResponse>
    diff_book_depth(const DiffBookDepthParams& params) const;

    /// Kline/Candlestick Streams for UTC
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current
    /// klines/candlestick every second in `UTC+0` timezone
    ///
    /// Update Speed: 1000ms for `1s`, 2000ms for the other intervals
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#kline
    [[nodiscard]] common::WebsocketStream<KlineResponse> kline(const KlineParams& params) const;

    /// Kline/Candlestick Streams with timezone offset
    ///
    /// `<symbol>@kline_<interval>@+08:00`.
    ///
    /// The Kline/Candlestick Stream push updates to the current
    /// klines/candlestick every second in `UTC+8` timezone
    ///
    /// **Kline/Candlestick chart intervals:**
    ///
    /// Supported intervals: See Kline/Candlestick chart intervals
    ///
    /// **UTC+8 timezone offset:**
    ///
    /// - Kline intervals open and close in the `UTC+8` timezone. For example the `1d` klines will
    /// open at the beginning of the `UTC+8` day, and close at the end of the `UTC+8` day.
    /// - Note that `E` (event time), `t` (start time) and `T` (close time) in the payload are Unix
    /// timestamps, which are always interpreted in UTC.
    ///
    /// Update Speed: 1000ms for `1s`, 2000ms for the other intervals
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#kline-offset
    [[nodiscard]] common::WebsocketStream<KlineOffsetResponse>
    kline_offset(const KlineOffsetParams& params) const;

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window for the previous 24hrs.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#mini-ticker
    [[nodiscard]] common::WebsocketStream<MiniTickerResponse>
    mini_ticker(const MiniTickerParams& params) const;

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top **\<levels\>** bids and asks, pushed every second. Valid **\<levels\>** are 5, 10,
    /// or 20.
    ///
    /// Update Speed: 1000ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#partial-book-depth
    [[nodiscard]] common::WebsocketStream<PartialBookDepthResponse>
    partial_book_depth(const PartialBookDepthParams& params) const;

    /// Reference Price Streams
    ///
    /// `<symbol>@referencePrice`.
    ///
    /// Reference price stream for a symbol.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#reference-price
    [[nodiscard]] common::WebsocketStream<ReferencePriceResponse>
    reference_price(const ReferencePriceParams& params) const;

    /// Individual Symbol Rolling Window Statistics Streams
    ///
    /// `<symbol>@ticker_<windowSize>`.
    ///
    /// Rolling window ticker statistics for a single symbol, computed over
    /// multiple windows.
    ///
    /// **Note:** This stream is different from the `<symbol>@ticker` stream. The open time `"O"`
    /// always starts on a minute, while the closing time `"C"` is the current time of the update.
    /// As such, the effective window might be up to 59999ms wider than `<windowSize>`.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#rolling-window-ticker
    [[nodiscard]] common::WebsocketStream<RollingWindowTickerResponse>
    rolling_window_ticker(const RollingWindowTickerParams& params) const;

    /// Individual Symbol Ticker Streams
    ///
    /// `<symbol>@ticker`.
    ///
    /// 24hr rolling window ticker statistics for a single symbol. These are NOT
    /// the statistics of the UTC day, but a 24hr rolling window for the
    /// previous 24hrs.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#ticker
    [[nodiscard]] common::WebsocketStream<TickerResponse> ticker(const TickerParams& params) const;

    /// Trade Streams
    ///
    /// `<symbol>@trade`.
    ///
    /// The Trade Streams push raw trade information; each trade has a unique
    /// buyer and seller.
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-streams/~#trade
    [[nodiscard]] common::WebsocketStream<TradeResponse> trade(const TradeParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::spot::websocket_streams
