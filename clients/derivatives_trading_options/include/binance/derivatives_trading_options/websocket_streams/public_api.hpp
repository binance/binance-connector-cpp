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

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/diff_book_depth_streams_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/hour24_ticker_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/individual_symbol_book_ticker_streams_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/partial_book_depth_streams_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/trade_streams_response.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

enum class DiffBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(DiffBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT DiffBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<DiffBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           DiffBookDepthStreamsUpdateSpeedEnum value);

enum class PartialBookDepthStreamsLevelEnum {
    Level5,
    Level10,
    Level20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PartialBookDepthStreamsLevelEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PartialBookDepthStreamsLevelEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsLevelEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           PartialBookDepthStreamsLevelEnum value);

enum class PartialBookDepthStreamsUpdateSpeedEnum {
    UpdateSpeed100ms,
    UpdateSpeed500ms,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(PartialBookDepthStreamsUpdateSpeedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PartialBookDepthStreamsUpdateSpeedEnum
tag_invoke(boost::json::value_to_tag<PartialBookDepthStreamsUpdateSpeedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PartialBookDepthStreamsUpdateSpeedEnum value);

struct DiffBookDepthStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// WebSocket stream update speed
    common::Required<DiffBookDepthStreamsUpdateSpeedEnum> update_speed;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct Hour24TickerParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
    /// The expiration date parameter
    std::optional<std::string> expiration_date = std::nullopt;
};

struct IndividualSymbolBookTickerStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct PartialBookDepthStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// The level parameter
    common::Required<PartialBookDepthStreamsLevelEnum> level;
    /// WebSocket stream update speed
    common::Required<PartialBookDepthStreamsUpdateSpeedEnum> update_speed;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct TradeStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT PublicApi {
public:
    explicit PublicApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Diff Book Depth Streams
    ///
    /// `<symbol>@depth@<updateSpeed>`.
    ///
    /// Bids and asks, pushed every 500 milliseconds, 100 milliseconds (if existing)
    ///
    /// Update Speed: 100ms or 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#diff-book-depth-streams
    [[nodiscard]] common::WebsocketStream<DiffBookDepthStreamsResponse>
    diff_book_depth_streams(const DiffBookDepthStreamsParams& params) const;

    /// 24-hour TICKER
    ///
    /// `<symbol>@optionTicker<expirationDate>`.
    ///
    /// 24hr ticker info for all symbols. Only symbols whose ticker info changed will be sent.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#hour24-ticker
    [[nodiscard]] common::WebsocketStream<Hour24TickerResponse>
    hour24_ticker(const Hour24TickerParams& params) const;

    /// Individual Symbol Book Ticker Streams
    ///
    /// `<symbol>@bookTicker`.
    ///
    /// Pushes any update to the best bid or ask's price or quantity in real-time for a specified
    /// symbol.
    ///
    /// Update Speed: Real-Time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#individual-symbol-book-ticker-streams
    [[nodiscard]] common::WebsocketStream<IndividualSymbolBookTickerStreamsResponse>
    individual_symbol_book_ticker_streams(
        const IndividualSymbolBookTickerStreamsParams& params) const;

    /// Partial Book Depth Streams
    ///
    /// `<symbol>@depth<level>@<updateSpeed>`.
    ///
    /// Top <levels> bids and asks. Valid <levels> are 5, 10, 20.
    ///
    /// Update Speed: 100ms or 500ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#partial-book-depth-streams
    [[nodiscard]] common::WebsocketStream<PartialBookDepthStreamsResponse>
    partial_book_depth_streams(const PartialBookDepthStreamsParams& params) const;

    /// Trade Streams
    ///
    /// `<symbol>@optionTrade`.
    ///
    /// The Trade Streams push raw trade information for specific symbol or underlying asset.
    /// E.g.btcusdt@optionTrade
    ///
    /// Update Speed: 50ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/public#trade-streams
    [[nodiscard]] common::WebsocketStream<TradeStreamsResponse>
    trade_streams(const TradeStreamsParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::derivatives_trading_options::websocket_streams
