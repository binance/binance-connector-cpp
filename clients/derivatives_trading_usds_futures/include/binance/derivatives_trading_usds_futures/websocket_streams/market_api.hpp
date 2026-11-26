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
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/aggregate_trade_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_market_liquidation_order_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_market_mini_tickers_stream_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_market_tickers_streams_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/asset_index_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/composite_index_symbol_information_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/continuous_contract_kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/contract_info_stream_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/individual_symbol_mini_ticker_stream_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/individual_symbol_ticker_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/liquidation_order_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/mark_price_stream_for_all_market_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/mark_price_stream_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/trading_session_stream_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

enum class ContinuousContractKlineCandlestickStreamsContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    TradifiPerpetual,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickStreamsContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
ContinuousContractKlineCandlestickStreamsContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsContractTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickStreamsContractTypeEnum value);

enum class ContinuousContractKlineCandlestickStreamsIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
ContinuousContractKlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickStreamsIntervalEnum value);

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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(KlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT KlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           KlineCandlestickStreamsIntervalEnum value);

enum class MarkPriceStreamUpdateSpeedEnum {
    UpdateSpeed1s,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(MarkPriceStreamUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceStreamUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceStreamUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceStreamUpdateSpeedEnum value);

enum class MarkPriceStreamForAllMarketUpdateSpeedEnum {
    UpdateSpeed1s,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(MarkPriceStreamForAllMarketUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceStreamForAllMarketUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<MarkPriceStreamForAllMarketUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceStreamForAllMarketUpdateSpeedEnum value);

struct AggregateTradeStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
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

struct AssetIndexParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct CompositeIndexSymbolInformationStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct ContinuousContractKlineCandlestickStreamsParams {
    common::Required<std::string> pair;
    common::Required<ContinuousContractKlineCandlestickStreamsContractTypeEnum> contract_type;
    common::Required<ContinuousContractKlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct ContractInfoStreamParams {
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

struct LiquidationOrderStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct MarkPriceStreamParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<MarkPriceStreamUpdateSpeedEnum> update_speed = std::nullopt;
};

struct MarkPriceStreamForAllMarketParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<MarkPriceStreamForAllMarketUpdateSpeedEnum> update_speed = std::nullopt;
};

struct TradingSessionStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarketApi {
public:
    explicit MarketApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Aggregate Trade Streams
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// The Aggregate Trade Streams push market trade information that is aggregated for fills with
    /// same price and taking side every 100 milliseconds. Only market trades will be aggregated,
    /// which means the insurance fund trades and ADL trades won't be aggregated.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM).
    ///
    /// Update Speed: 100ms
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are aggregated into field q and without special tags
    /// to be distinguished.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#aggregate-trade-streams
    [[nodiscard]] common::WebsocketStream<AggregateTradeStreamsResponse>
    aggregate_trade_streams(const AggregateTradeStreamsParams& params) const;

    /// All Market Liquidation Order Streams
    ///
    /// `!forceOrder@arr`.
    ///
    /// The All Liquidation Order Snapshot Streams push force liquidation order information for all
    /// symbols in the market. For each symbol，only the largest one liquidation order within 1000ms
    /// will be pushed as the snapshot. If no liquidation happens in the interval of 1000ms, no
    /// stream will be pushed.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-liquidation-order-streams
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
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-mini-tickers-stream
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
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#all-market-tickers-streams
    [[nodiscard]] common::WebsocketStream<std::vector<AllMarketTickersStreamsResponseInner>>
    all_market_tickers_streams(const AllMarketTickersStreamsParams& params = {}) const;

    /// Multi-Assets Mode Asset Index
    ///
    /// `!assetIndex@arr`.
    ///
    /// Asset index price. Subscribe with `!assetIndex@arr` for all assets, or
    /// `<assetSymbol>@assetIndex` for a specific asset.
    ///
    /// > **CM-UM Integration (Effective 2026-06-30):** Renamed from *Multi-Assets Mode Asset
    /// Index*. The stream `!assetIndex@arr` now additionally pushes COIN-M settlement-asset price
    /// index entries (e.g., `BTCUSD`, `ETHUSD`, `BNBUSD`). The on-the-wire stream key is unchanged;
    /// existing subscriptions continue to work.
    ///
    /// Update Speed: 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#asset-index
    [[nodiscard]] common::WebsocketStream<std::vector<AssetIndexResponseInner>>
    asset_index(const AssetIndexParams& params = {}) const;

    /// Composite Index Symbol Information Streams
    ///
    /// `<symbol>@compositeIndex`.
    ///
    /// Composite index information for index symbols pushed every second.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#composite-index-symbol-information-streams
    [[nodiscard]] common::WebsocketStream<CompositeIndexSymbolInformationStreamsResponse>
    composite_index_symbol_information_streams(
        const CompositeIndexSymbolInformationStreamsParams& params) const;

    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// `<pair>_<contractType>@continuousKline_<interval>`.
    ///
    /// Continuous Contract Kline/Candlestick Streams
    ///
    /// > **After CM migration**, both `fstream` and `dstream` may subscribe to either UM or CM
    /// symbols on this stream.
    ///
    /// Update Speed: 250ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#continuous-contract-kline-candlestick-streams
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#contract-info-stream
    [[nodiscard]] common::WebsocketStream<ContractInfoStreamResponse>
    contract_info_stream(const ContractInfoStreamParams& params = {}) const;

    /// Individual Symbol Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// 24hr rolling window mini-ticker statistics for a single symbol. These are NOT the statistics
    /// of the UTC day, but a 24hr rolling window from requestTime to 24hrs before.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 2s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#individual-symbol-mini-ticker-stream
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
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 2000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#individual-symbol-ticker-streams
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const;

    /// Liquidation Order Streams
    ///
    /// `<symbol>@forceOrder`.
    ///
    /// The Liquidation Order Snapshot Streams push force liquidation order information for specific
    /// symbol. For each symbol，only the largest one liquidation order within 1000ms will be pushed
    /// as the snapshot. If no liquidation happens in the interval of 1000ms, no stream will be
    /// pushed.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#liquidation-order-streams
    [[nodiscard]] common::WebsocketStream<LiquidationOrderStreamsResponse>
    liquidation_order_streams(const LiquidationOrderStreamsParams& params) const;

    /// Mark Price Stream
    ///
    /// `<symbol>@markPrice@<updateSpeed>`.
    ///
    /// Mark price and funding rate for a single symbol pushed every 3 seconds or every second.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#mark-price-stream
    [[nodiscard]] common::WebsocketStream<MarkPriceStreamResponse>
    mark_price_stream(const MarkPriceStreamParams& params) const;

    /// Mark Price Stream for All market
    ///
    /// `!markPrice@arr@<updateSpeed>`.
    ///
    /// Mark price and funding rate for all symbols pushed every 3 seconds or every second.
    ///
    /// **Note:**
    /// - TradFi symbols will be pushed through a seperate message.
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` =
    /// CM); both `fstream` and `dstream` may subscribe to either UM or CM symbols on this stream.
    ///
    /// Update Speed: 3s or 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#mark-price-stream-for-all-market
    [[nodiscard]] common::WebsocketStream<std::vector<MarkPriceStreamForAllMarketResponseInner>>
    mark_price_stream_for_all_market(const MarkPriceStreamForAllMarketParams& params = {}) const;

    /// Trading Session Stream
    ///
    /// `tradingSession`.
    ///
    /// Trading session information for the underlying assets of TradFi Perpetual contracts,
    /// covering the U.S. equity market, Korean equity market, Hong Kong equity market, China equity
    /// market, the commodity market, and the FX market, is updated every second. Trading session
    /// information for different underlying markets is pushed in separate messages.
    ///
    /// **Event type:**
    ///
    /// - `EquityUpdate`: Session types for the U.S. equity market include "PRE_MARKET", "REGULAR",
    /// "AFTER_MARKET", "OVERNIGHT", and "NO_TRADING".
    /// - `CommodityUpdate`: Session types for the commodity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `KR_EquityUpdate`: Session types for the Korean equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `HK_EquityUpdate`: Session types for the Hong Kong equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `CN_EquityUpdate`: Session types for the China equity market include "REGULAR" and
    /// "NO_TRADING".
    /// - `FXUpdate`: Session types for the FX market include "REGULAR" and "NO_TRADING".
    ///
    /// Update Speed: 1s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/market#trading-session-stream
    [[nodiscard]] common::WebsocketStream<TradingSessionStreamResponse>
    trading_session_stream(const TradingSessionStreamParams& params = {}) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
