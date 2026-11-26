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
#include <utility>
#include <variant>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/avg_price_response_result.hpp>
#include <binance/spot/websocket_api/models/block_trades_historical_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/depth_response_result.hpp>
#include <binance/spot/websocket_api/models/klines_response_result_inner_inner.hpp>
#include <binance/spot/websocket_api/models/reference_price_calculation_response_result.hpp>
#include <binance/spot/websocket_api/models/reference_price_response_result.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response1_result.hpp>
#include <binance/spot/websocket_api/models/ticker24hr_response2_result_inner.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response1_result.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response2_result_inner.hpp>
#include <binance/spot/websocket_api/models/ticker_price_response1_result.hpp>
#include <binance/spot/websocket_api/models/ticker_price_response2_result_inner.hpp>
#include <binance/spot/websocket_api/models/ticker_response1_result.hpp>
#include <binance/spot/websocket_api/models/ticker_response2_result_inner.hpp>
#include <binance/spot/websocket_api/models/ticker_trading_day_response1_result.hpp>
#include <binance/spot/websocket_api/models/ticker_trading_day_response2_result_inner.hpp>
#include <binance/spot/websocket_api/models/trades_aggregate_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/trades_historical_response_result_inner.hpp>
#include <binance/spot/websocket_api/models/trades_recent_response_result_inner.hpp>

namespace binance::spot::websocket_api {

enum class DepthSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(DepthSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT DepthSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<DepthSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    DepthSymbolStatusEnum value);

enum class KlinesIntervalEnum {
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

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(KlinesIntervalEnum value) noexcept;
BINANCE_SPOT_EXPORT KlinesIntervalEnum
tag_invoke(boost::json::value_to_tag<KlinesIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    KlinesIntervalEnum value);

enum class ReferencePriceCalculationSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(ReferencePriceCalculationSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT ReferencePriceCalculationSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<ReferencePriceCalculationSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    ReferencePriceCalculationSymbolStatusEnum value);

enum class TickerTypeEnum {
    Full,
    Mini,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(TickerTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerTypeEnum tag_invoke(boost::json::value_to_tag<TickerTypeEnum> /*tag*/,
                                              const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerTypeEnum value);

enum class TickerWindowSizeEnum {
    WindowSize1m,
    WindowSize2m,
    WindowSize3m,
    WindowSize4m,
    WindowSize5m,
    WindowSize6m,
    WindowSize7m,
    WindowSize8m,
    WindowSize9m,
    WindowSize10m,
    WindowSize11m,
    WindowSize12m,
    WindowSize13m,
    WindowSize14m,
    WindowSize15m,
    WindowSize16m,
    WindowSize17m,
    WindowSize18m,
    WindowSize19m,
    WindowSize20m,
    WindowSize21m,
    WindowSize22m,
    WindowSize23m,
    WindowSize24m,
    WindowSize25m,
    WindowSize26m,
    WindowSize27m,
    WindowSize28m,
    WindowSize29m,
    WindowSize30m,
    WindowSize31m,
    WindowSize32m,
    WindowSize33m,
    WindowSize34m,
    WindowSize35m,
    WindowSize36m,
    WindowSize37m,
    WindowSize38m,
    WindowSize39m,
    WindowSize40m,
    WindowSize41m,
    WindowSize42m,
    WindowSize43m,
    WindowSize44m,
    WindowSize45m,
    WindowSize46m,
    WindowSize47m,
    WindowSize48m,
    WindowSize49m,
    WindowSize50m,
    WindowSize51m,
    WindowSize52m,
    WindowSize53m,
    WindowSize54m,
    WindowSize55m,
    WindowSize56m,
    WindowSize57m,
    WindowSize58m,
    WindowSize59m,
    WindowSize1h,
    WindowSize2h,
    WindowSize3h,
    WindowSize4h,
    WindowSize5h,
    WindowSize6h,
    WindowSize7h,
    WindowSize8h,
    WindowSize9h,
    WindowSize10h,
    WindowSize11h,
    WindowSize12h,
    WindowSize13h,
    WindowSize14h,
    WindowSize15h,
    WindowSize16h,
    WindowSize17h,
    WindowSize18h,
    WindowSize19h,
    WindowSize20h,
    WindowSize21h,
    WindowSize22h,
    WindowSize23h,
    WindowSize1d,
    WindowSize2d,
    WindowSize3d,
    WindowSize4d,
    WindowSize5d,
    WindowSize6d,
    WindowSize7d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(TickerWindowSizeEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerWindowSizeEnum
tag_invoke(boost::json::value_to_tag<TickerWindowSizeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerWindowSizeEnum value);

enum class TickerSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(TickerSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerSymbolStatusEnum value);

enum class Ticker24hrTypeEnum {
    Full,
    Mini,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(Ticker24hrTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT Ticker24hrTypeEnum
tag_invoke(boost::json::value_to_tag<Ticker24hrTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    Ticker24hrTypeEnum value);

enum class Ticker24hrSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(Ticker24hrSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT Ticker24hrSymbolStatusEnum tag_invoke(
    boost::json::value_to_tag<Ticker24hrSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    Ticker24hrSymbolStatusEnum value);

enum class TickerBookSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(TickerBookSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerBookSymbolStatusEnum tag_invoke(
    boost::json::value_to_tag<TickerBookSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerBookSymbolStatusEnum value);

enum class TickerPriceSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(TickerPriceSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerPriceSymbolStatusEnum tag_invoke(
    boost::json::value_to_tag<TickerPriceSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerPriceSymbolStatusEnum value);

enum class TickerTradingDayTypeEnum {
    Full,
    Mini,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(TickerTradingDayTypeEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerTradingDayTypeEnum tag_invoke(
    boost::json::value_to_tag<TickerTradingDayTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerTradingDayTypeEnum value);

enum class TickerTradingDaySymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(TickerTradingDaySymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerTradingDaySymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerTradingDaySymbolStatusEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerTradingDaySymbolStatusEnum value);

enum class UiKlinesIntervalEnum {
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

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view to_string(UiKlinesIntervalEnum value) noexcept;
BINANCE_SPOT_EXPORT UiKlinesIntervalEnum
tag_invoke(boost::json::value_to_tag<UiKlinesIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    UiKlinesIntervalEnum value);

struct AvgPriceParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct BlockTradesHistoricalParams {
    common::Required<std::string> symbol;
    /// Block trade ID to fetch from
    common::Required<std::int64_t> from_id;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
};

struct DepthParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// If limit > 7500, only 7500 entries will be returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. A status mismatch returns error `-1220
    /// SYMBOL_DOES_NOT_MATCH_STATUS`.
    std::optional<DepthSymbolStatusEnum> symbol_status = std::nullopt;
};

struct KlinesParams {
    common::Required<std::string> symbol;
    common::Required<KlinesIntervalEnum> interval;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct ReferencePriceParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct ReferencePriceCalculationParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<ReferencePriceCalculationSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Query ticker of a single symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Query ticker for multiple symbols
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Ticker type. Supported values: FULL (default) or MINI
    std::optional<TickerTypeEnum> type = std::nullopt;
    /// Defaults to 1d if no parameter provided.
    std::optional<TickerWindowSizeEnum> window_size = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<TickerSymbolStatusEnum> symbol_status = std::nullopt;
};

struct Ticker24hrParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Ticker type. Supported values: FULL (default) or MINI
    std::optional<Ticker24hrTypeEnum> type = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<Ticker24hrSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerBookParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Query ticker for a single symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Query ticker for multiple symbols
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<TickerBookSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerPriceParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Query price for a single symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Query price for multiple symbols
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<TickerPriceSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerTradingDayParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    /// Ticker type. Supported values: FULL (default) or MINI
    std::optional<TickerTradingDayTypeEnum> type = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<TickerTradingDaySymbolStatusEnum> symbol_status = std::nullopt;
};

struct TradesAggregateParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Aggregate trade ID to begin at
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Timestamp in ms to get aggregate trades from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get aggregate trades until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct TradesHistoricalParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Trade ID to begin at
    std::optional<std::int64_t> from_id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct TradesRecentParams {
    common::Required<std::string> symbol;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct UiKlinesParams {
    common::Required<std::string> symbol;
    common::Required<UiKlinesIntervalEnum> interval;
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

class BINANCE_SPOT_EXPORT MarketApi {
public:
    explicit MarketApi(std::shared_ptr<common::WebsocketApi> client);

    /// Current average price
    ///
    /// `avgPrice`.
    ///
    /// Get current average price for a symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#avg-price
    [[nodiscard]] common::WebsocketApiResponse<AvgPriceResponseResult>
    avg_price(const AvgPriceParams& params) const;

    /// Asynchronous `avg_price()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<AvgPriceResponseResult>)`.
    template <class CompletionToken>
    auto async_avg_price(const AvgPriceParams& params, CompletionToken&& token) const {
        return common::async_send<AvgPriceResponseResult>(
            client_, "avgPrice", avg_price_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Historical Block Trades
    ///
    /// `blockTrades.historical`.
    ///
    /// Get block trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#block-trades-historical
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<BlockTradesHistoricalResponseResultInner>>
    block_trades_historical(const BlockTradesHistoricalParams& params) const;

    /// Asynchronous `block_trades_historical()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<BlockTradesHistoricalResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_block_trades_historical(const BlockTradesHistoricalParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<BlockTradesHistoricalResponseResultInner>>(
            client_, "blockTrades.historical", block_trades_historical_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Order book
    ///
    /// `depth`.
    ///
    /// Get current order book.
    ///
    /// Note that this request returns limited market depth.
    ///
    /// If you need to continuously monitor order book updates, please consider using WebSocket
    /// Streams:
    ///   * `<symbol>@depth<levels>`
    ///   * `<symbol>@depth`
    ///
    /// You can use `depth` request together with `<symbol>@depth` streams to maintain a local order
    /// book.
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// |Limit|Request Weight
    /// ------|-------
    /// 1-100|  5
    /// 101-500| 25
    /// 501-1000| 50
    /// 1001-5000| 250
    /// 5001-7500| 500
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#depth
    [[nodiscard]] common::WebsocketApiResponse<DepthResponseResult>
    depth(const DepthParams& params) const;

    /// Asynchronous `depth()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<DepthResponseResult>)`.
    template <class CompletionToken>
    auto async_depth(const DepthParams& params, CompletionToken&& token) const {
        return common::async_send<DepthResponseResult>(client_, "depth", depth_payload(params),
                                                       make_options(false, false, false, false),
                                                       std::forward<CompletionToken>(token));
    }

    /// Klines
    ///
    /// `klines`.
    ///
    /// Get klines (candlestick bars).
    ///
    /// Klines are uniquely identified by their open & close time.
    ///
    /// If you need access to real-time kline updates, please consider using WebSocket Streams:
    ///   * `<symbol>@kline_<interval>`
    ///
    /// If you need historical kline data, please consider using data.binance.vision.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Supported kline intervals (case-sensitive):
    ///
    /// Interval  | `interval` value
    /// --------- | ----------------
    /// seconds   | `1s`
    /// minutes   | `1m`, `3m`, `5m`, `15m`, `30m`
    /// hours     | `1h`, `2h`, `4h`, `6h`, `8h`, `12h`
    /// days      | `1d`, `3d`
    /// weeks     | `1w`
    /// months    | `1M`
    ///
    /// **Notes:**
    ///
    /// * If `startTime` and `endTime` are not sent, the most recent klines are returned.
    /// * Supported values for `timeZone`:
    ///   * Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   * Only hours (e.g. `0`, `8`, `4`)
    ///   * Accepted range is strictly [-12:00 to +14:00] inclusive
    /// * If `timeZone` provided, kline intervals are interpreted in that timezone instead of UTC.
    /// * Note that `startTime` and `endTime` are always interpreted in UTC, regardless of
    /// `timeZone`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#klines
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<std::vector<KlinesResponseResultInnerInner>>>
    klines(const KlinesParams& params) const;

    /// Asynchronous `klines()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<std::vector<KlinesResponseResultInnerInner>>>)`.
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlinesResponseResultInnerInner>>>(
            client_, "klines", klines_payload(params), make_options(false, false, false, false),
            std::forward<CompletionToken>(token));
    }

    /// Query Reference Price
    ///
    /// `referencePrice`.
    ///
    /// Query Reference Price
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// If the symbol has never had a reference price set, the request is rejected with:
    ///
    /// ```json
    /// {
    ///     "code": -2043,
    ///     "msg": "This symbol doesn't have a reference price."
    /// }
    /// ```
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#reference-price
    [[nodiscard]] common::WebsocketApiResponse<ReferencePriceResponseResult>
    reference_price(const ReferencePriceParams& params) const;

    /// Asynchronous `reference_price()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<ReferencePriceResponseResult>)`.
    template <class CompletionToken>
    auto async_reference_price(const ReferencePriceParams& params, CompletionToken&& token) const {
        return common::async_send<ReferencePriceResponseResult>(
            client_, "referencePrice", reference_price_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Reference Price Calculation
    ///
    /// `referencePrice.calculation`.
    ///
    /// Query Reference Price Calculation
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#reference-price-calculation
    [[nodiscard]] common::WebsocketApiResponse<ReferencePriceCalculationResponseResult>
    reference_price_calculation(const ReferencePriceCalculationParams& params) const;

    /// Asynchronous `reference_price_calculation()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<ReferencePriceCalculationResponseResult>)`.
    template <class CompletionToken>
    auto async_reference_price_calculation(const ReferencePriceCalculationParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<ReferencePriceCalculationResponseResult>(
            client_, "referencePrice.calculation", reference_price_calculation_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Rolling window price change statistics
    ///
    /// `ticker`.
    ///
    /// Get rolling window price change statistics with a custom window.
    ///
    /// This request is similar to `ticker.24hr` but statistics are computed on demand using the
    /// arbitrary window you specify.
    ///
    /// **Note:** Window size precision is limited to 1 minute.
    /// While the `closeTime` is the current time of the request, `openTime` always start on a
    /// minute boundary. As such, the effective window might be up to 59999 ms wider than the
    /// requested `windowSize`.
    ///
    /// **Window computation example**
    ///
    /// For example, a request for `"windowSize": "7d"` might result in the following window:
    ///
    /// ```json
    /// {
    ///     "openTime": 1659580020000,
    ///     "closeTime": 1660184865291
    /// }
    /// ```
    ///
    /// Time of the request – `closeTime` – is 1660184865291 (August 11, 2022 02:27:45.291).
    /// Requested window size should put the `openTime` 7 days before that – August 4, 02:27:45.291
    /// – but due to limited precision it ends up a bit earlier: 1659580020000 (August 4, 2022
    /// 02:27:00), exactly at the start of a minute.
    ///
    /// If you need to continuously monitor trading statistics, please consider using WebSocket
    /// Streams:
    ///   * `<symbol>@ticker_<window_size>` or `!ticker_<window-size>@arr`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// | Symbols | Weight |
    /// |:-------:|:------:|
    /// |    1–50 | 4 per symbol |
    /// |  51–100 |    200 |
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Supported window sizes:
    ///
    /// Unit    | `windowSize` value
    /// ------- | ------------------
    /// minutes | `1m`, `2m` ... `59m`
    /// hours   | `1h`, `2h` ... `23h`
    /// days    | `1d`, `2d` ... `7d`
    ///
    /// Notes:
    ///
    /// * Either `symbol` or `symbols` must be specified.
    ///
    /// * Maximum number of symbols in one request: 200.
    ///
    /// * Window size units cannot be combined.
    ///   E.g., `1d 2h` is not supported.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        TickerResponse1Result, std::vector<TickerResponse2ResultInner>, boost::json::value>>
    ticker(const TickerParams& params = {}) const;

    /// Asynchronous `ticker()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<std::variant<TickerResponse1Result,
    /// std::vector<TickerResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return common::async_send<std::variant<
            TickerResponse1Result, std::vector<TickerResponse2ResultInner>, boost::json::value>>(
            client_, "ticker", ticker_payload(params), make_options(false, false, false, false),
            std::forward<CompletionToken>(token));
    }

    /// 24hr ticker price change statistics
    ///
    /// `ticker.24hr`.
    ///
    /// Get 24-hour rolling window price change statistics.
    ///
    /// If you need to continuously monitor trading statistics, please consider using WebSocket
    /// Streams:
    ///
    /// * `<symbol>@ticker` or `!ticker@arr`
    ///
    /// * `<symbol>@miniTicker` or `!miniTicker@arr`
    ///
    /// If you need different window sizes,
    ///
    /// use the `ticker` request.
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 80|
    /// |symbols| 1-20 |2|
    /// | | 21-100 |40|
    /// | | 101+ |80|
    /// | |omitted| 80|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker24hr
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        Ticker24hrResponse1Result, std::vector<Ticker24hrResponse2ResultInner>, boost::json::value>>
    ticker24hr(const Ticker24hrParams& params = {}) const;

    /// Asynchronous `ticker24hr()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<Ticker24hrResponse1Result,
    /// std::vector<Ticker24hrResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_ticker24hr(const Ticker24hrParams& params, CompletionToken&& token) const {
        return common::async_send<
            std::variant<Ticker24hrResponse1Result, std::vector<Ticker24hrResponse2ResultInner>,
                         boost::json::value>>(client_, "ticker.24hr", ticker24hr_payload(params),
                                              make_options(false, false, false, false),
                                              std::forward<CompletionToken>(token));
    }

    /// Symbol order book ticker
    ///
    /// `ticker.book`.
    ///
    /// Get the current best price and quantity on the order book.
    ///
    /// If you need access to real-time order book ticker updates, please
    /// consider using WebSocket Streams:
    ///
    /// * `<symbol>@bookTicker`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 4|
    /// |symbols| Any |4|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-book
    [[nodiscard]] common::WebsocketApiResponse<std::variant<
        TickerBookResponse1Result, std::vector<TickerBookResponse2ResultInner>, boost::json::value>>
    ticker_book(const TickerBookParams& params = {}) const;

    /// Asynchronous `ticker_book()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<TickerBookResponse1Result,
    /// std::vector<TickerBookResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_ticker_book(const TickerBookParams& params, CompletionToken&& token) const {
        return common::async_send<
            std::variant<TickerBookResponse1Result, std::vector<TickerBookResponse2ResultInner>,
                         boost::json::value>>(client_, "ticker.book", ticker_book_payload(params),
                                              make_options(false, false, false, false),
                                              std::forward<CompletionToken>(token));
    }

    /// Symbol price ticker
    ///
    /// `ticker.price`.
    ///
    /// Get the latest market price for a symbol.
    ///
    /// If you need access to real-time price updates, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@aggTrade`
    ///
    /// * `<symbol>@trade`
    ///
    /// Weight: Adjusted based on the number of requested symbols:
    ///
    /// |Parameter|Symbols Provided|Weight|
    /// |---|---|---|
    /// |symbol| 1 |2|
    /// | |omitted| 4|
    /// |symbols| Any |4|
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// Notes:
    ///
    /// * `symbol` and `symbols` cannot be used together.
    ///
    /// * If no symbol is specified, returns information about all symbols currently trading on the
    /// exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-price
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<TickerPriceResponse1Result, std::vector<TickerPriceResponse2ResultInner>,
                     boost::json::value>>
    ticker_price(const TickerPriceParams& params = {}) const;

    /// Asynchronous `ticker_price()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<TickerPriceResponse1Result,
    /// std::vector<TickerPriceResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_ticker_price(const TickerPriceParams& params, CompletionToken&& token) const {
        return common::async_send<
            std::variant<TickerPriceResponse1Result, std::vector<TickerPriceResponse2ResultInner>,
                         boost::json::value>>(client_, "ticker.price", ticker_price_payload(params),
                                              make_options(false, false, false, false),
                                              std::forward<CompletionToken>(token));
    }

    /// Trading Day Ticker
    ///
    /// `ticker.tradingDay`.
    ///
    /// Price change statistics for a trading day.
    ///
    /// Weight: 4 for each requested symbol regardless of windowSize. The weight for this request
    /// will cap at 200 once the number of symbols in the request is more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// **Notes:**
    ///
    /// * Supported values for `timeZone`:
    ///   * Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   * Only hours (e.g. `0`, `8`, `4`)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ticker-trading-day
    [[nodiscard]] common::WebsocketApiResponse<
        std::variant<TickerTradingDayResponse1Result,
                     std::vector<TickerTradingDayResponse2ResultInner>, boost::json::value>>
    ticker_trading_day(const TickerTradingDayParams& params = {}) const;

    /// Asynchronous `ticker_trading_day()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::variant<TickerTradingDayResponse1Result,
    /// std::vector<TickerTradingDayResponse2ResultInner>, boost::json::value>>)`.
    template <class CompletionToken>
    auto async_ticker_trading_day(const TickerTradingDayParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<
            std::variant<TickerTradingDayResponse1Result,
                         std::vector<TickerTradingDayResponse2ResultInner>, boost::json::value>>(
            client_, "ticker.tradingDay", ticker_trading_day_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Aggregate trades
    ///
    /// `trades.aggregate`.
    ///
    /// Get aggregate trades.
    ///
    /// An *aggregate trade* (aggtrade) represents one or more individual
    /// trades.
    ///
    /// Trades that fill at the same time, from the same taker order, with the
    /// same price –
    ///
    /// those trades are collected into an aggregate trade with total quantity
    /// of the individual trades.
    ///
    /// If you need access to real-time trading activity, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@aggTrade`
    ///
    /// If you need historical aggregate trade data, please consider using data.binance.vision.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If `fromId` is specified, return aggtrades with aggregate trade ID >= `fromId`. Use
    /// `fromId` and `limit` to page through all aggtrades.
    /// - If `startTime` and/or `endTime` are specified, aggtrades are filtered by execution time
    /// (`T`). `fromId` cannot be used together with `startTime` and `endTime`.
    /// - If no condition is specified, the most recent aggregate trades are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-aggregate
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesAggregateResponseResultInner>>
    trades_aggregate(const TradesAggregateParams& params) const;

    /// Asynchronous `trades_aggregate()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<TradesAggregateResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_trades_aggregate(const TradesAggregateParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<TradesAggregateResponseResultInner>>(
            client_, "trades.aggregate", trades_aggregate_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Historical trades
    ///
    /// `trades.historical`.
    ///
    /// Get historical trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// Notes:
    ///
    /// * If `fromId` is not specified, the most recent trades are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-historical
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesHistoricalResponseResultInner>>
    trades_historical(const TradesHistoricalParams& params) const;

    /// Asynchronous `trades_historical()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<TradesHistoricalResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_trades_historical(const TradesHistoricalParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<std::vector<TradesHistoricalResponseResultInner>>(
            client_, "trades.historical", trades_historical_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Recent trades
    ///
    /// `trades.recent`.
    ///
    /// Get recent trades.
    ///
    /// If you need access to real-time trading activity, please consider using
    /// WebSocket Streams:
    ///
    /// * `<symbol>@trade`
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#trades-recent
    [[nodiscard]] common::WebsocketApiResponse<std::vector<TradesRecentResponseResultInner>>
    trades_recent(const TradesRecentParams& params) const;

    /// Asynchronous `trades_recent()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<TradesRecentResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_trades_recent(const TradesRecentParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<TradesRecentResponseResultInner>>(
            client_, "trades.recent", trades_recent_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// UI Klines
    ///
    /// `uiKlines`.
    ///
    /// Get klines (candlestick bars) optimized for presentation.
    ///
    /// This request is similar to `klines`, having the same parameters and response. `uiKlines`
    /// return modified kline data, optimized for presentation of candlestick charts.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If `startTime` and `endTime` are not sent, the most recent klines are returned.
    /// - Supported values for `timeZone`:
    ///   - Hours and minutes (e.g. `-1:00`, `05:45`)
    ///   - Only hours (e.g. `0`, `8`, `4`)
    ///   - Accepted range is strictly [-12:00 to +14:00] inclusive
    /// - If `timeZone` provided, kline intervals are interpreted in that timezone instead of UTC.
    /// - Note that `startTime` and `endTime` are always interpreted in UTC, regardless of
    /// `timeZone`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/market#ui-klines
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<std::vector<KlinesResponseResultInnerInner>>>
    ui_klines(const UiKlinesParams& params) const;

    /// Asynchronous `ui_klines()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<std::vector<KlinesResponseResultInnerInner>>>)`.
    template <class CompletionToken>
    auto async_ui_klines(const UiKlinesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlinesResponseResultInnerInner>>>(
            client_, "uiKlines", ui_klines_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params avg_price_payload(const AvgPriceParams& params);
    [[nodiscard]] static common::Params
    block_trades_historical_payload(const BlockTradesHistoricalParams& params);
    [[nodiscard]] static common::Params depth_payload(const DepthParams& params);
    [[nodiscard]] static common::Params klines_payload(const KlinesParams& params);
    [[nodiscard]] static common::Params reference_price_payload(const ReferencePriceParams& params);
    [[nodiscard]] static common::Params
    reference_price_calculation_payload(const ReferencePriceCalculationParams& params);
    [[nodiscard]] static common::Params ticker_payload(const TickerParams& params);
    [[nodiscard]] static common::Params ticker24hr_payload(const Ticker24hrParams& params);
    [[nodiscard]] static common::Params ticker_book_payload(const TickerBookParams& params);
    [[nodiscard]] static common::Params ticker_price_payload(const TickerPriceParams& params);
    [[nodiscard]] static common::Params
    ticker_trading_day_payload(const TickerTradingDayParams& params);
    [[nodiscard]] static common::Params
    trades_aggregate_payload(const TradesAggregateParams& params);
    [[nodiscard]] static common::Params
    trades_historical_payload(const TradesHistoricalParams& params);
    [[nodiscard]] static common::Params trades_recent_payload(const TradesRecentParams& params);
    [[nodiscard]] static common::Params ui_klines_payload(const UiKlinesParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::spot::websocket_api
