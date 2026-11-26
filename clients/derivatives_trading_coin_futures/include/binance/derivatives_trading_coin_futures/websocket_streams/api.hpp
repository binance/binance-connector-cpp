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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/aggregate_trade_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/all_book_tickers_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/all_market_liquidation_order_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/all_market_mini_tickers_stream_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/all_market_tickers_streams_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/continuous_contract_kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/contract_info_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/diff_book_depth_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/index_kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/index_price_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/individual_symbol_book_ticker_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/individual_symbol_mini_ticker_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/individual_symbol_ticker_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/mark_price_kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/mark_price_of_all_symbols_of_a_pair_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/mark_price_stream_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/market_liquidation_order_streams_response.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/partial_book_depth_streams_response.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

enum class ContinuousContractKlineCandlestickStreamsContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickStreamsContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
ContinuousContractKlineCandlestickStreamsContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsContractTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickStreamsContractTypeEnum value);

enum class ContinuousContractKlineCandlestickStreamsIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
ContinuousContractKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickStreamsIntervalEnum value);

enum class DiffBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(DiffBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT DiffBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<DiffBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           DiffBookDepthStreamsUpdateSpeedEnum value);

enum class IndexKlineCandlestickStreamsIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(IndexKlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<IndexKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           IndexKlineCandlestickStreamsIntervalEnum value);

enum class IndexPriceStreamUpdateSpeedEnum {
    UpdateSpeed1s,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(IndexPriceStreamUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexPriceStreamUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<IndexPriceStreamUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           IndexPriceStreamUpdateSpeedEnum value);

enum class KlineCandlestickStreamsIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(KlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT KlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           KlineCandlestickStreamsIntervalEnum value);

enum class MarkPriceKlineCandlestickStreamsIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(MarkPriceKlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceKlineCandlestickStreamsIntervalEnum value);

enum class MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum {
    UpdateSpeed1s,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum value);

enum class MarkPriceStreamUpdateSpeedEnum {
    UpdateSpeed1s,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(MarkPriceStreamUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceStreamUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceStreamUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceStreamUpdateSpeedEnum value);

enum class PartialBookDepthStreamsLevelsEnum {
    Levels5,
    Levels10,
    Levels20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PartialBookDepthStreamsLevelsEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PartialBookDepthStreamsLevelsEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsLevelsEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PartialBookDepthStreamsLevelsEnum value);

enum class PartialBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PartialBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PartialBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PartialBookDepthStreamsUpdateSpeedEnum value);

struct AggregateTradeStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllBookTickersStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllMarketLiquidationOrderStreamsParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllMarketMiniTickersStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct AllMarketTickersStreamsParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct ContinuousContractKlineCandlestickStreamsParams {
    /// The pair parameter
    common::Required<std::string> pair;
    /// The contractType parameter
    common::Required<ContinuousContractKlineCandlestickStreamsContractTypeEnum> contract_type;
    /// The interval parameter
    common::Required<ContinuousContractKlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct ContractInfoStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct DiffBookDepthStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<DiffBookDepthStreamsUpdateSpeedEnum> update_speed = std::nullopt;
};

struct IndexKlineCandlestickStreamsParams {
    /// The pair parameter
    common::Required<std::string> pair;
    /// The interval parameter
    common::Required<IndexKlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct IndexPriceStreamParams {
    /// The pair parameter
    common::Required<std::string> pair;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<IndexPriceStreamUpdateSpeedEnum> update_speed = std::nullopt;
};

struct IndividualSymbolBookTickerStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct IndividualSymbolMiniTickerStreamParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct IndividualSymbolTickerStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct KlineCandlestickStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// The interval parameter
    common::Required<KlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct MarkPriceKlineCandlestickStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// The interval parameter
    common::Required<MarkPriceKlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct MarkPriceOfAllSymbolsOfAPairParams {
    /// The pair parameter
    common::Required<std::string> pair;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<MarkPriceOfAllSymbolsOfAPairUpdateSpeedEnum> update_speed = std::nullopt;
};

struct MarkPriceStreamParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<MarkPriceStreamUpdateSpeedEnum> update_speed = std::nullopt;
};

struct MarketLiquidationOrderStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct PartialBookDepthStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// The levels parameter
    common::Required<PartialBookDepthStreamsLevelsEnum> levels;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<PartialBookDepthStreamsUpdateSpeedEnum> update_speed = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::WebsocketStreams> client);

    /// Aggregate Trade Streams
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// The Aggregate Trade Streams push market trade information that is aggregated for fills with
    /// same price and taking side every 100 milliseconds.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#aggregate-trade-streams
    [[nodiscard]] common::WebsocketStream<AggregateTradeStreamsResponse>
    aggregate_trade_streams(const AggregateTradeStreamsParams& params) const;

    /// All Book Tickers Stream
    ///
    /// `!bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for all symbols.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-book-tickers-stream
    [[nodiscard]] common::WebsocketStream<AllBookTickersStreamResponse>
    all_book_tickers_stream(const AllBookTickersStreamParams& params = {}) const;

    /// All Market Liquidation Order Streams
    ///
    /// `!forceOrder@arr`.
    ///
    /// The All Liquidation Order Snapshot Streams push force liquidation order information for all
    /// symbols in the market. For each symbol，only the latest one liquidation order within 1000ms
    /// will be pushed as the snapshot. If no liquidation happens in the interval of 1000ms, no
    /// stream will be pushed.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<AllMarketLiquidationOrderStreamsResponse>
    all_market_liquidation_order_streams(
        const AllMarketLiquidationOrderStreamsParams& params = {}) const;

    /// All Market Mini Tickers Stream
    ///
    /// `!miniTicker@arr`.
    ///
    /// 24hr rolling window mini-ticker statistics for all symbols. These are NOT the statistics of
    /// the UTC day, but a 24hr rolling window from requestTime to 24hrs before. Note that only
    /// tickers that have changed will be present in the array.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-mini-tickers-stream
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketMiniTickersStreamResponseInner>>
    all_market_mini_tickers_stream(const AllMarketMiniTickersStreamParams& params = {}) const;

    /// All Market Tickers Streams
    ///
    /// `!ticker@arr`.
    ///
    /// 24hr rolling window ticker statistics for all symbols. These are NOT the statistics of the
    /// UTC day, but a 24hr rolling window from requestTime to 24hrs before. Note that only tickers
    /// that have changed will be present in the array.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#all-market-tickers-streams
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
    all_market_tickers_streams(const AllMarketTickersStreamsParams& params = {}) const;

    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// `<pair>_<contractType>@continuousKline_<interval>`.
    ///
    /// Kline update every second
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#continuous-contract-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<ContinuousContractKlineCandlestickStreamsResponse>
    continuous_contract_kline_candlestick_streams(
        const ContinuousContractKlineCandlestickStreamsParams& params) const;

    /// Contract Info Stream
    ///
    /// `!contractInfo`.
    ///
    /// ContractInfo stream pushes when contract info updates(listing/settlement/contract bracket
    /// update). bks field only shows up when bracket gets updated.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#contract-info-stream
    [[nodiscard]] common::WebsocketStream<ContractInfoStreamResponse>
    contract_info_stream(const ContractInfoStreamParams& params = {}) const;

    /// Diff. Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 250 milliseconds, 500 milliseconds, or 100 milliseconds
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 250ms or 500ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const;

    /// Index Kline/Candlestick Streams
    ///
    /// `<pair>@indexPriceKline_<interval>`.
    ///
    /// Index Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to CM symbols on this
    /// stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#index-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<IndexKlineCandlestickStreamsResponse>
    index_kline_candlestick_streams(const IndexKlineCandlestickStreamsParams& params) const;

    /// Index Price Stream
    ///
    /// `<pair>@indexPrice@<updateSpeed>`.
    ///
    /// Index Price Stream
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#index-price-stream
    [[nodiscard]] common::WebsocketStream<IndexPriceStreamResponse>
    index_price_stream(const IndexPriceStreamParams& params) const;

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for a specified
    /// symbol.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: Real-time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const;

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics for a single symbol. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-mini-ticker-stream
    [[nodiscard]] common::WebsocketStream<IndividualSymbolMiniTickerStreamResponse>
    individual_symbol_mini_ticker_stream(
        const IndividualSymbolMiniTickerStreamParams& params) const;

    /// Individual Symbol Ticker Streams
    ///
    /// `<symbol>@ticker`.
    ///
    /// 24hr rolling window ticker statistics for a single symbol. These are NOT the statistics of
    /// the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#individual-symbol-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolTickerStreamsResponse>
    individual_symbol_ticker_streams(const IndividualSymbolTickerStreamsParams& params) const;

    /// Kline/Candlestick Streams
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current klines/candlestick every 250
    /// milliseconds (if existing).
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const;

    /// Mark Price Kline/Candlestick Streams
    ///
    /// `<symbol>@markPriceKline_<interval>`.
    ///
    /// Mark Price Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to CM symbols on this
    /// stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<MarkPriceKlineCandlestickStreamsResponse>
    mark_price_kline_candlestick_streams(
        const MarkPriceKlineCandlestickStreamsParams& params) const;

    /// Mark Price of All Symbols of a Pair
    ///
    /// `<pair>@markPrice@<updateSpeed>`.
    ///
    /// Mark Price of All Symbols of a Pair
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-of-all-symbols-of-apair
    [[nodiscard]] common::WebsocketStream<std::vector<MarkPriceOfAllSymbolsOfAPairResponseInner>>
    mark_price_of_all_symbols_of_a_pair(const MarkPriceOfAllSymbolsOfAPairParams& params) const;

    /// Mark Price Stream
    ///
    /// `<symbol>@markPrice@<updateSpeed>`.
    ///
    /// Mark price update stream
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3000ms OR 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#mark-price-stream
    [[nodiscard]] common::WebsocketStream<MarkPriceStreamResponse>
    mark_price_stream(const MarkPriceStreamParams& params) const;

    /// Market Liquidation Order Streams
    ///
    /// `<symbol>@forceOrder`.
    ///
    /// The Liquidation Order Snapshot Streams push force liquidation order information for specific
    /// symbol. For each symbol，only the latest one liquidation order within 1000ms will be pushed
    /// as the snapshot. If no liquidation happens in the interval of 1000ms, no stream will be
    /// pushed.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#market-liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<MarketLiquidationOrderStreamsResponse>
    market_liquidation_order_streams(const MarketLiquidationOrderStreamsParams& params) const;

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top levels bids and asks.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 250ms, 500ms or 100ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-streams/~#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
