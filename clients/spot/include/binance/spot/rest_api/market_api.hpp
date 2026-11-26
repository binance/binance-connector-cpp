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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/agg_trades_response_inner.hpp>
#include <binance/spot/rest_api/models/avg_price_response.hpp>
#include <binance/spot/rest_api/models/depth_response.hpp>
#include <binance/spot/rest_api/models/get_trades_response_inner.hpp>
#include <binance/spot/rest_api/models/historical_block_trades_response_inner.hpp>
#include <binance/spot/rest_api/models/klines_item_inner.hpp>
#include <binance/spot/rest_api/models/reference_price_calculation_response.hpp>
#include <binance/spot/rest_api/models/reference_price_response.hpp>
#include <binance/spot/rest_api/models/ticker24hr_response.hpp>
#include <binance/spot/rest_api/models/ticker_book_ticker_response.hpp>
#include <binance/spot/rest_api/models/ticker_price_response.hpp>
#include <binance/spot/rest_api/models/ticker_response.hpp>
#include <binance/spot/rest_api/models/ticker_trading_day_response.hpp>

namespace binance::spot::rest_api {

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

enum class TickerBookTickerSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(TickerBookTickerSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT TickerBookTickerSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<TickerBookTickerSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TickerBookTickerSymbolStatusEnum value);

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

struct AggTradesParams {
    common::Required<std::string> symbol;
    /// ID to get aggregate trades from INCLUSIVE.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Timestamp in ms to get aggregate trades from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get aggregate trades until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct AvgPriceParams {
    common::Required<std::string> symbol;
};

struct DepthParams {
    common::Required<std::string> symbol;
    /// If limit > 7500, only 7500 entries will be returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. A status mismatch returns error `-1220
    /// SYMBOL_DOES_NOT_MATCH_STATUS`.
    std::optional<DepthSymbolStatusEnum> symbol_status = std::nullopt;
};

struct GetTradesParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct HistoricalBlockTradesParams {
    common::Required<std::string> symbol;
    /// Block trade ID to fetch from
    common::Required<std::int64_t> from_id;
    /// Default: 500; Maximum: 1000
    std::optional<std::int64_t> limit = std::nullopt;
};

struct HistoricalTradesParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> limit = std::nullopt;
    /// TradeId to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
};

struct KlinesParams {
    common::Required<std::string> symbol;
    common::Required<KlinesIntervalEnum> interval;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct ReferencePriceParams {
    common::Required<std::string> symbol;
};

struct ReferencePriceCalculationParams {
    common::Required<std::string> symbol;
    /// Supported values: `TRADING`, `HALT`, `BREAK`, `CANCEL_ONLY`
    std::optional<ReferencePriceCalculationSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerParams {
    /// Either `symbol` or `symbols` must be provided
    std::optional<std::string> symbol = std::nullopt;
    /// Either `symbol` or `symbols` must be provided  Examples of accepted format for the `symbols`
    /// parameter: ["BTCUSDT","BNBUSDT"] or %5B%22BTCUSDT%22,%22BNBUSDT%22%5D  The maximum number of
    /// symbols allowed in a request is 100.
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Units cannot be combined (e.g. `1d2h` is not allowed).
    std::optional<TickerWindowSizeEnum> window_size = std::nullopt;
    std::optional<TickerTypeEnum> type = std::nullopt;
    std::optional<TickerSymbolStatusEnum> symbol_status = std::nullopt;
};

struct Ticker24hrParams {
    /// Either `symbol` or `symbols` must be provided
    std::optional<std::string> symbol = std::nullopt;
    /// Either `symbol` or `symbols` must be provided  Examples of accepted format for the `symbols`
    /// parameter: ["BTCUSDT","BNBUSDT"] or %5B%22BTCUSDT%22,%22BNBUSDT%22%5D  The maximum number of
    /// symbols allowed in a request is 100.
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    std::optional<Ticker24hrTypeEnum> type = std::nullopt;
    std::optional<Ticker24hrSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerBookTickerParams {
    /// Parameter symbol and symbols cannot be used in combination. If neither parameter is sent,
    /// `bookTickers` for all symbols will be returned in an array.
    std::optional<std::string> symbol = std::nullopt;
    /// Parameter symbol and symbols cannot be used in combination. If neither parameter is sent,
    /// `bookTickers` for all symbols will be returned in an array. Examples of accepted format for
    /// the symbols parameter: ["BTCUSDT","BNBUSDT"] or %5B%22BTCUSDT%22,%22BNBUSDT%22%5D
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response.
    std::optional<TickerBookTickerSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerPriceParams {
    /// Parameter symbol and symbols cannot be used in combination. If neither parameter is sent,
    /// prices for all symbols will be returned in an array.
    std::optional<std::string> symbol = std::nullopt;
    /// Parameter symbol and symbols cannot be used in combination. If neither parameter is sent,
    /// prices for all symbols will be returned in an array. Examples of accepted format for the
    /// symbols parameter: ["BTCUSDT","BNBUSDT"] or %5B%22BTCUSDT%22,%22BNBUSDT%22%5D
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple or all symbols,
    /// non-matching ones are simply excluded from the response.
    std::optional<TickerPriceSymbolStatusEnum> symbol_status = std::nullopt;
};

struct TickerTradingDayParams {
    /// Either `symbol` or `symbols` must be provided.
    std::optional<std::string> symbol = std::nullopt;
    /// Either `symbol` or `symbols` must be provided. Examples of accepted format for the `symbols`
    /// parameter: ["BTCUSDT","BNBUSDT"] or %5B%22BTCUSDT%22,%22BNBUSDT%22%5D. The maximum number of
    /// `symbols` allowed in a request is 100.
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    std::optional<TickerTradingDayTypeEnum> type = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. For a single symbol, a status mismatch
    /// returns error `-1220 SYMBOL_DOES_NOT_MATCH_STATUS`. For multiple symbols, non-matching ones
    /// are simply excluded from the response.
    std::optional<TickerTradingDaySymbolStatusEnum> symbol_status = std::nullopt;
};

struct UiKlinesParams {
    common::Required<std::string> symbol;
    common::Required<UiKlinesIntervalEnum> interval;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 0 (UTC)
    std::optional<std::string> time_zone = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

class BINANCE_SPOT_EXPORT MarketApi {
public:
    explicit MarketApi(std::shared_ptr<common::RestClient> client);

    /// Compressed/Aggregate trades list
    ///
    /// GET /api/v3/aggTrades.
    ///
    /// Get compressed, aggregate trades. Trades that fill at the time, from the same taker order,
    /// with the same price will have the quantity aggregated.
    ///
    /// Weight(IP): 4
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// - If fromId, startTime, and endTime are not sent, the most recent aggregate trades will be
    /// returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#agg-trades
    [[nodiscard]] common::RestApiResponse<std::vector<AggTradesResponseInner>>
    agg_trades(const AggTradesParams& params) const;

    /// Asynchronous `agg_trades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<AggTradesResponseInner>>)`.
    template <class CompletionToken>
    auto async_agg_trades(const AggTradesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AggTradesResponseInner>>(
            client_, agg_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Current average price
    ///
    /// GET /api/v3/avgPrice.
    ///
    /// Current average price for a symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#avg-price
    [[nodiscard]] common::RestApiResponse<AvgPriceResponse>
    avg_price(const AvgPriceParams& params) const;

    /// Asynchronous `avg_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AvgPriceResponse>)`.
    template <class CompletionToken>
    auto async_avg_price(const AvgPriceParams& params, CompletionToken&& token) const {
        return common::async_send<AvgPriceResponse>(client_, avg_price_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Order book
    ///
    /// GET /api/v3/depth.
    ///
    /// Order book
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#depth
    [[nodiscard]] common::RestApiResponse<DepthResponse> depth(const DepthParams& params) const;

    /// Asynchronous `depth()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DepthResponse>)`.
    template <class CompletionToken>
    auto async_depth(const DepthParams& params, CompletionToken&& token) const {
        return common::async_send<DepthResponse>(client_, depth_request(params),
                                                 std::forward<CompletionToken>(token));
    }

    /// Recent trades list
    ///
    /// GET /api/v3/trades.
    ///
    /// Get recent trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#get-trades
    [[nodiscard]] common::RestApiResponse<std::vector<GetTradesResponseInner>>
    get_trades(const GetTradesParams& params) const;

    /// Asynchronous `get_trades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<GetTradesResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_trades(const GetTradesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetTradesResponseInner>>(
            client_, get_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Historical Block Trades (MARKET_DATA)
    ///
    /// GET /api/v3/historicalBlockTrades.
    ///
    /// Get block trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#historical-block-trades
    [[nodiscard]] common::RestApiResponse<std::vector<HistoricalBlockTradesResponseInner>>
    historical_block_trades(const HistoricalBlockTradesParams& params) const;

    /// Asynchronous `historical_block_trades()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<HistoricalBlockTradesResponseInner>>)`.
    template <class CompletionToken>
    auto async_historical_block_trades(const HistoricalBlockTradesParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<HistoricalBlockTradesResponseInner>>(
            client_, historical_block_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Old trade lookup
    ///
    /// GET /api/v3/historicalTrades.
    ///
    /// Get older trades.
    ///
    /// Weight(IP): 25
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#historical-trades
    [[nodiscard]] common::RestApiResponse<std::vector<GetTradesResponseInner>>
    historical_trades(const HistoricalTradesParams& params) const;

    /// Asynchronous `historical_trades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<GetTradesResponseInner>>)`.
    template <class CompletionToken>
    auto async_historical_trades(const HistoricalTradesParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<std::vector<GetTradesResponseInner>>(
            client_, historical_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick data
    ///
    /// GET /api/v3/klines.
    ///
    /// Kline/candlestick bars for a symbol.
    /// Klines are uniquely identified by their open time.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#klines
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
    klines(const KlinesParams& params) const;

    /// Asynchronous `klines()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>)`.
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlinesItemInner>>>(
            client_, klines_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Reference Price
    ///
    /// GET /api/v3/referencePrice.
    ///
    /// Query the reference price for a symbol.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#reference-price
    [[nodiscard]] common::RestApiResponse<ReferencePriceResponse>
    reference_price(const ReferencePriceParams& params) const;

    /// Asynchronous `reference_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ReferencePriceResponse>)`.
    template <class CompletionToken>
    auto async_reference_price(const ReferencePriceParams& params, CompletionToken&& token) const {
        return common::async_send<ReferencePriceResponse>(client_, reference_price_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Query Reference Price Calculation
    ///
    /// GET /api/v3/referencePrice/calculation.
    ///
    /// Describes how reference price is calculated for a given symbol.
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#reference-price-calculation
    [[nodiscard]] common::RestApiResponse<ReferencePriceCalculationResponse>
    reference_price_calculation(const ReferencePriceCalculationParams& params) const;

    /// Asynchronous `reference_price_calculation()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ReferencePriceCalculationResponse>)`.
    template <class CompletionToken>
    auto async_reference_price_calculation(const ReferencePriceCalculationParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<ReferencePriceCalculationResponse>(
            client_, reference_price_calculation_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Rolling window price change statistics
    ///
    /// GET /api/v3/ticker.
    ///
    /// **Note:** This endpoint differs from `GET /api/v3/ticker/24hr`.
    ///
    /// The statistical time range of this endpoint can be up to 59999ms longer
    /// than the requested `windowSize`.
    ///
    /// `openTime` starts at the beginning of a minute, while the end time is
    /// the current time. Therefore, the actual interval can be up to 59999ms
    /// longer than the requested window.
    ///
    /// For example, if `closeTime` is 1641287867099 (January 04, 2022
    /// 09:17:47:099 UTC) and `windowSize` is `1d`, then `openTime` is
    /// 1641201420000 (January 3, 2022, 09:17:00 UTC).
    ///
    /// Weight: 4 for each requested symbol regardless of windowSize.
    ///
    /// The weight for this request will cap at 200 once the number of `symbols` in the request is
    /// more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker
    [[nodiscard]] common::RestApiResponse<TickerResponse>
    ticker(const TickerParams& params = {}) const;

    /// Asynchronous `ticker()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TickerResponse>)`.
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return common::async_send<TickerResponse>(client_, ticker_request(params),
                                                  std::forward<CompletionToken>(token));
    }

    /// 24hr ticker price change statistics
    ///
    /// GET /api/v3/ticker/24hr.
    ///
    /// 24 hour rolling window price change statistics. **Careful** when accessing this with no
    /// symbol.
    ///
    /// Weight:
    ///
    /// - Parameter | Symbols Provided | Weight
    /// - symbol | 1 | 2
    /// - symbol | symbol parameter is omitted | 80
    /// - symbols | 1-20 | 2
    /// - symbols | 21-100 | 40
    /// - symbols | 101 or more | 80
    /// - symbols | symbols parameter is omitted | 80
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker24hr
    [[nodiscard]] common::RestApiResponse<Ticker24hrResponse>
    ticker24hr(const Ticker24hrParams& params = {}) const;

    /// Asynchronous `ticker24hr()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<Ticker24hrResponse>)`.
    template <class CompletionToken>
    auto async_ticker24hr(const Ticker24hrParams& params, CompletionToken&& token) const {
        return common::async_send<Ticker24hrResponse>(client_, ticker24hr_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Symbol order book ticker
    ///
    /// GET /api/v3/ticker/bookTicker.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// Weight: |Parameter|Symbols Provided|Weight|
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
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-book-ticker
    [[nodiscard]] common::RestApiResponse<TickerBookTickerResponse>
    ticker_book_ticker(const TickerBookTickerParams& params = {}) const;

    /// Asynchronous `ticker_book_ticker()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TickerBookTickerResponse>)`.
    template <class CompletionToken>
    auto async_ticker_book_ticker(const TickerBookTickerParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<TickerBookTickerResponse>(
            client_, ticker_book_ticker_request(params), std::forward<CompletionToken>(token));
    }

    /// Symbol price ticker
    ///
    /// GET /api/v3/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: |Parameter|Symbols Provided|Weight|
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
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-price
    [[nodiscard]] common::RestApiResponse<TickerPriceResponse>
    ticker_price(const TickerPriceParams& params = {}) const;

    /// Asynchronous `ticker_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TickerPriceResponse>)`.
    template <class CompletionToken>
    auto async_ticker_price(const TickerPriceParams& params, CompletionToken&& token) const {
        return common::async_send<TickerPriceResponse>(client_, ticker_price_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Trading Day Ticker
    ///
    /// GET /api/v3/ticker/tradingDay.
    ///
    /// Price change statistics for a trading day.
    ///
    /// Weight: 4 for each requested symbol. The weight for this request will cap at 200 once the
    /// number of symbols in the request is more than 50.
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Database
    ///
    /// **Notes:**:
    ///   - Supported values for `timeZone`:
    ///     - Hours and minutes (e.g. `-1:00`, `05:45`)
    ///     - Only hours (e.g. `0`, `8`, `4`)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ticker-trading-day
    [[nodiscard]] common::RestApiResponse<TickerTradingDayResponse>
    ticker_trading_day(const TickerTradingDayParams& params = {}) const;

    /// Asynchronous `ticker_trading_day()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TickerTradingDayResponse>)`.
    template <class CompletionToken>
    auto async_ticker_trading_day(const TickerTradingDayParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<TickerTradingDayResponse>(
            client_, ticker_trading_day_request(params), std::forward<CompletionToken>(token));
    }

    /// UIKlines
    ///
    /// GET /api/v3/uiKlines.
    ///
    /// The request is similar to klines having the same parameters and
    /// response.
    ///
    /// `uiKlines` return modified kline data, optimized for presentation of
    /// candlestick charts.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/market#ui-klines
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>
    ui_klines(const UiKlinesParams& params) const;

    /// Asynchronous `ui_klines()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<KlinesItemInner>>>)`.
    template <class CompletionToken>
    auto async_ui_klines(const UiKlinesParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlinesItemInner>>>(
            client_, ui_klines_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest agg_trades_request(const AggTradesParams& params) const;
    [[nodiscard]] common::RestRequest avg_price_request(const AvgPriceParams& params) const;
    [[nodiscard]] common::RestRequest depth_request(const DepthParams& params) const;
    [[nodiscard]] common::RestRequest get_trades_request(const GetTradesParams& params) const;
    [[nodiscard]] common::RestRequest
    historical_block_trades_request(const HistoricalBlockTradesParams& params) const;
    [[nodiscard]] common::RestRequest
    historical_trades_request(const HistoricalTradesParams& params) const;
    [[nodiscard]] common::RestRequest klines_request(const KlinesParams& params) const;
    [[nodiscard]] common::RestRequest
    reference_price_request(const ReferencePriceParams& params) const;
    [[nodiscard]] common::RestRequest
    reference_price_calculation_request(const ReferencePriceCalculationParams& params) const;
    [[nodiscard]] common::RestRequest ticker_request(const TickerParams& params) const;
    [[nodiscard]] common::RestRequest ticker24hr_request(const Ticker24hrParams& params) const;
    [[nodiscard]] common::RestRequest
    ticker_book_ticker_request(const TickerBookTickerParams& params) const;
    [[nodiscard]] common::RestRequest ticker_price_request(const TickerPriceParams& params) const;
    [[nodiscard]] common::RestRequest
    ticker_trading_day_request(const TickerTradingDayParams& params) const;
    [[nodiscard]] common::RestRequest ui_klines_request(const UiKlinesParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::spot::rest_api
