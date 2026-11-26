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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/all_book_tickers_stream_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/diff_book_depth_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/individual_symbol_book_ticker_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/partial_book_depth_streams_response.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/rpi_diff_book_depth_streams_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

enum class DiffBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(DiffBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT DiffBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<DiffBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           DiffBookDepthStreamsUpdateSpeedEnum value);

enum class PartialBookDepthStreamsLevelsEnum {
    Levels5,
    Levels10,
    Levels20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PartialBookDepthStreamsLevelsEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PartialBookDepthStreamsLevelsEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsLevelsEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PartialBookDepthStreamsLevelsEnum value);

enum class PartialBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PartialBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PartialBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PartialBookDepthStreamsUpdateSpeedEnum value);

struct AllBookTickersStreamParams {
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

struct DiffBookDepthStreamsParams {
    /// Trading pair symbol.
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
    /// WebSocket stream update speed
    std::optional<DiffBookDepthStreamsUpdateSpeedEnum> update_speed = std::nullopt;
};

struct IndividualSymbolBookTickerStreamsParams {
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

struct RpiDiffBookDepthStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::string> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PublicApi {
public:
    explicit PublicApi(std::shared_ptr<common::WebsocketStreams> client);

    /// All Book Tickers Stream
    ///
    /// `!bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for all symbols.
    ///
    /// > **After CM migration**, this stream pushes the merged UM + CM universe (subscribable on
    /// both `fstream` and `dstream`); each payload is appended with a new `st` field (`1` = UM, `2`
    /// = CM) and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 5s
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#all-book-tickers-stream
    [[nodiscard]] common::WebsocketStream<AllBookTickersStreamResponse>
    all_book_tickers_stream(const AllBookTickersStreamParams& params = {}) const;

    /// Diff. Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 250 milliseconds, 500 milliseconds, 100 milliseconds (if
    /// existing).
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 250ms, 500ms, 100ms
    ///
    /// Response Notes:
    /// - Retail Price Improvement(RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const;

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
    /// Response Notes:
    /// Retail Price Improvement (RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const;

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<levels>@<updateSpeed>`.
    ///
    /// Top <levels> bids and asks
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 250ms or 500ms or 100ms
    ///
    /// Response Notes:
    /// Retail Price Improvement (RPI) orders are not visible and excluded in the response message.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const;

    /// RPI Diff. Book Depth Streams
    ///
    /// `<symbol>@rpiDepth@500ms`.
    ///
    /// Bids and asks including RPI orders, pushed every 500 milliseconds
    ///
    /// > **After CM migration**, the payload is appended with a new `st` field (`1` = UM, `2` = CM)
    /// and a new `ps` field (pair symbol).
    ///
    /// Update Speed: 500ms
    ///
    /// Response Notes:
    /// - RPI(Retail Price Improvement) orders are included and aggreated in the response message.
    /// When the quantity of a price level to be updated is equal to 0, it means either all
    /// quotations for this price have been filled/canceled, or the quantity of crossed RPI orders
    /// for this price are hidden
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/ws-streams/public#rpi-diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<RpiDiffBookDepthStreamsResponse>
    rpi_diff_book_depth_streams(const RpiDiffBookDepthStreamsParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
