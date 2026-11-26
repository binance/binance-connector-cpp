//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>
#include <binance/alpha/websocket_streams/models/aggregate_trade_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/all_book_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/all_mini_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/all_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/all_tokens24h_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/book_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/contract_kline_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/full_depth_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/kline_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/mini_ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/partial_depth_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/ticker_stream_response.hpp>
#include <binance/alpha/websocket_streams/models/trade_stream_response.hpp>
#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>

namespace binance::alpha::websocket_streams {

enum class ContractKlineStreamIntervalEnum {
    Interval1s,
    Interval1m,
    Interval5m,
    Interval15m,
    Interval1h,
    Interval4h,
    Interval1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view
to_string(ContractKlineStreamIntervalEnum value) noexcept;
BINANCE_ALPHA_EXPORT ContractKlineStreamIntervalEnum
tag_invoke(boost::json::value_to_tag<ContractKlineStreamIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     ContractKlineStreamIntervalEnum value);

enum class FullDepthStreamIntervalEnum {
    Interval0ms,
    Interval100ms,
    Interval500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view
to_string(FullDepthStreamIntervalEnum value) noexcept;
BINANCE_ALPHA_EXPORT FullDepthStreamIntervalEnum tag_invoke(
    boost::json::value_to_tag<FullDepthStreamIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     FullDepthStreamIntervalEnum value);

enum class KlineStreamIntervalEnum {
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

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view
to_string(KlineStreamIntervalEnum value) noexcept;
BINANCE_ALPHA_EXPORT KlineStreamIntervalEnum tag_invoke(
    boost::json::value_to_tag<KlineStreamIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     KlineStreamIntervalEnum value);

enum class PartialDepthStreamLevelsEnum {
    Levels5,
    Levels10,
    Levels20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view
to_string(PartialDepthStreamLevelsEnum value) noexcept;
BINANCE_ALPHA_EXPORT PartialDepthStreamLevelsEnum tag_invoke(
    boost::json::value_to_tag<PartialDepthStreamLevelsEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     PartialDepthStreamLevelsEnum value);

enum class PartialDepthStreamIntervalEnum {
    Interval0ms,
    Interval100ms,
    Interval500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view
to_string(PartialDepthStreamIntervalEnum value) noexcept;
BINANCE_ALPHA_EXPORT PartialDepthStreamIntervalEnum
tag_invoke(boost::json::value_to_tag<PartialDepthStreamIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     PartialDepthStreamIntervalEnum value);

struct AggregateTradeStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct AllBookTickerStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct AllMiniTickerStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct AllTickerStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct AllTokens24hTickerStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct BookTickerStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct ContractKlineStreamParams {
    /// Contract address.
    common::Required<std::string> contract_address;
    /// Chain ID.
    common::Required<std::string> chain_id;
    /// Kline interval.
    common::Required<ContractKlineStreamIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct FullDepthStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Update interval.
    common::Required<FullDepthStreamIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct KlineStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Kline interval.
    common::Required<KlineStreamIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct MiniTickerStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct PartialDepthStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Depth levels.
    common::Required<PartialDepthStreamLevelsEnum> levels;
    /// Update interval.
    common::Required<PartialDepthStreamIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct TickerStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct TradeStreamParams {
    /// Symbol to subscribe, in lowercase stream format.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_ALPHA_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::WebsocketStreams> client);

    /// Aggregate Trade Stream
    ///
    /// `<symbol>@aggTrade`.
    ///
    /// Pushes aggregate trade updates for a symbol.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#aggregate-trade-stream
    [[nodiscard]] common::WebsocketStream<AggregateTradeStreamResponse>
    aggregate_trade_stream(const AggregateTradeStreamParams& params) const;

    /// All Book Ticker Stream
    ///
    /// `!bookTicker`.
    ///
    /// Pushes best bid/ask updates for all symbols.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#all-book-ticker-stream
    [[nodiscard]] common::WebsocketStream<AllBookTickerStreamResponse>
    all_book_ticker_stream(const AllBookTickerStreamParams& params = {}) const;

    /// All Mini Ticker Stream
    ///
    /// `!miniTicker@arr`.
    ///
    /// Pushes mini ticker statistics for all symbols.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#all-mini-ticker-stream
    [[nodiscard]] common::WebsocketStream<AllMiniTickerStreamResponse>
    all_mini_ticker_stream(const AllMiniTickerStreamParams& params = {}) const;

    /// All Ticker Stream
    ///
    /// `!ticker@arr`.
    ///
    /// Pushes full ticker statistics for all symbols.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#all-ticker-stream
    [[nodiscard]] common::WebsocketStream<AllTickerStreamResponse>
    all_ticker_stream(const AllTickerStreamParams& params = {}) const;

    /// All Tokens 24h Ticker Stream
    ///
    /// `came@allTokens@ticker24`.
    ///
    /// Pushes 24h ticker-like metrics for all tokens.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#all-tokens24h-ticker-stream
    [[nodiscard]] common::WebsocketStream<AllTokens24hTickerStreamResponse>
    all_tokens24h_ticker_stream(const AllTokens24hTickerStreamParams& params = {}) const;

    /// Book Ticker Stream
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes best bid/ask updates for a symbol.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#book-ticker-stream
    [[nodiscard]] common::WebsocketStream<BookTickerStreamResponse>
    book_ticker_stream(const BookTickerStreamParams& params) const;

    /// Contract Kline Stream
    ///
    /// `came@<contractAddress>@<chainId>@kline_<interval>`.
    ///
    /// Pushes kline updates by contractAddress@chainId.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#contract-kline-stream
    [[nodiscard]] common::WebsocketStream<ContractKlineStreamResponse>
    contract_kline_stream(const ContractKlineStreamParams& params) const;

    /// Full Depth Stream
    ///
    /// `<symbol>@fulldepth@<interval>`.
    ///
    /// Returns all available depth, including UI and API orders.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#full-depth-stream
    [[nodiscard]] common::WebsocketStream<FullDepthStreamResponse>
    full_depth_stream(const FullDepthStreamParams& params) const;

    /// Kline Stream
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// Pushes kline updates for a symbol.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#kline-stream
    [[nodiscard]] common::WebsocketStream<KlineStreamResponse>
    kline_stream(const KlineStreamParams& params) const;

    /// Mini Ticker Stream
    ///
    /// `<symbol>@miniTicker`.
    ///
    /// Pushes 24h rolling mini ticker statistics.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#mini-ticker-stream
    [[nodiscard]] common::WebsocketStream<MiniTickerStreamResponse>
    mini_ticker_stream(const MiniTickerStreamParams& params) const;

    /// Partial Depth Stream
    ///
    /// `<symbol>@depth<levels>@<interval>`.
    ///
    /// Pushes partial depth updates (UI orders only).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#partial-depth-stream
    [[nodiscard]] common::WebsocketStream<PartialDepthStreamResponse>
    partial_depth_stream(const PartialDepthStreamParams& params) const;

    /// Ticker Stream
    ///
    /// `<symbol>@ticker`.
    ///
    /// Pushes full 24h rolling ticker statistics.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#ticker-stream
    [[nodiscard]] common::WebsocketStream<TickerStreamResponse>
    ticker_stream(const TickerStreamParams& params) const;

    /// Trade Stream
    ///
    /// `<symbol>@trade`.
    ///
    /// Pushes raw trade updates for a symbol.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/ws-streams/~#trade-stream
    [[nodiscard]] common::WebsocketStream<TradeStreamResponse>
    trade_stream(const TradeStreamParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::alpha::websocket_streams
