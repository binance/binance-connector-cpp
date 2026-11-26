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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_streams.hpp>
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/index_price_streams_response_inner.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/kline_candlestick_streams_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/new_symbol_info_response.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/open_interest_response_inner.hpp>
#include <binance/derivatives_trading_options/websocket_streams/models/option_mark_price_response_inner.hpp>

namespace binance::derivatives_trading_options::websocket_streams {

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
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(KlineCandlestickStreamsIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT KlineCandlestickStreamsIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickStreamsIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           KlineCandlestickStreamsIntervalEnum value);

struct IndexPriceStreamsParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct KlineCandlestickStreamsParams {
    /// The symbol parameter
    common::Required<std::string> symbol;
    /// The interval parameter
    common::Required<KlineCandlestickStreamsIntervalEnum> interval;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct NewSymbolInfoParams {
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct OpenInterestParams {
    /// The underlying parameter
    common::Required<std::string> underlying;
    /// The expirationDate parameter
    common::Required<std::string> expiration_date;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

struct OptionMarkPriceParams {
    /// The underlying parameter
    common::Required<std::string> underlying;
    /// Unique WebSocket request ID.
    std::optional<std::int64_t> id = std::nullopt;
};

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT MarketApi {
public:
    explicit MarketApi(std::shared_ptr<common::WebsocketStreams> client);

    /// Index Price Streams
    ///
    /// `!index@arr`.
    ///
    /// Underlying(e.g ETHUSDT) index stream.
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#index-price-streams
    [[nodiscard]] common::WebsocketStream<std::vector<IndexPriceStreamsResponseInner>>
    index_price_streams(const IndexPriceStreamsParams& params = {}) const;

    /// Kline/Candlestick Streams
    ///
    /// `<symbol>@kline_<interval>`.
    ///
    /// The Kline/Candlestick Stream push updates to the current klines/candlestick every 1000
    /// milliseconds (if existing).
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#kline-candlestick-streams
    [[nodiscard]] common::WebsocketStream<KlineCandlestickStreamsResponse>
    kline_candlestick_streams(const KlineCandlestickStreamsParams& params) const;

    /// New Symbol Info
    ///
    /// `!optionSymbol`.
    ///
    /// New symbol listing stream.
    ///
    /// Update Speed: 50ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#new-symbol-info
    [[nodiscard]] common::WebsocketStream<NewSymbolInfoResponse>
    new_symbol_info(const NewSymbolInfoParams& params = {}) const;

    /// Open Interest
    ///
    /// `<underlying>@optionOpenInterest@<expirationDate>`.
    ///
    /// Option open interest for specific underlying asset on specific expiration date.
    /// E.g.ethusdt@optionOpenInterest@221125
    ///
    /// Update Speed: 60s
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#open-interest
    [[nodiscard]] common::WebsocketStream<std::vector<OpenInterestResponseInner>>
    open_interest(const OpenInterestParams& params) const;

    /// Option Mark Price
    ///
    /// `<underlying>@optionMarkPrice`.
    ///
    /// The mark price for all option symbols on specific underlying asset.
    /// E.g.btcusdt@optionMarkPrice
    ///
    /// Update Speed: 1000ms
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/ws-streams/market#option-mark-price
    [[nodiscard]] common::WebsocketStream<std::vector<OptionMarkPriceResponseInner>>
    option_mark_price(const OptionMarkPriceParams& params) const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::derivatives_trading_options::websocket_streams
