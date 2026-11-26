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
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/check_server_time_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/historical_exercise_records_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/index_price_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/open_interest_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_mark_price_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/order_book_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/recent_block_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/recent_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/ticker24hr_price_change_statistics_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class KlineCandlestickDataIntervalEnum {
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(KlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT KlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           KlineCandlestickDataIntervalEnum value);

struct HistoricalExerciseRecordsParams {
    /// Underlying asset.
    std::optional<std::string> underlying = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned
    std::optional<std::int64_t> limit = std::nullopt;
};

struct IndexPriceParams {
    /// Underlying asset.
    common::Required<std::string> underlying;
};

struct KlineCandlestickDataParams {
    /// Option trading pair
    common::Required<std::string> symbol;
    /// Time interval
    common::Required<KlineCandlestickDataIntervalEnum> interval;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned
    std::optional<std::int64_t> limit = std::nullopt;
};

struct OpenInterestParams {
    /// Underlying asset.
    common::Required<std::string> underlying_asset;
    /// expiration date
    common::Required<std::string> expiration;
};

struct OptionMarkPriceParams {
    /// Option trading pair
    std::optional<std::string> symbol = std::nullopt;
};

struct OrderBookParams {
    /// Option trading pair
    common::Required<std::string> symbol;
    /// Default:100 Max:1000.Optional value:[10, 20, 50, 100, 500, 1000]
    std::optional<std::int64_t> limit = std::nullopt;
};

struct RecentBlockTradesListParams {
    /// Option trading pair
    std::optional<std::string> symbol = std::nullopt;
    /// Number of records
    std::optional<std::int64_t> limit = std::nullopt;
};

struct RecentTradesListParams {
    /// Option trading pair
    common::Required<std::string> symbol;
    /// Number of result sets returned
    std::optional<std::int64_t> limit = std::nullopt;
};

struct Ticker24hrPriceChangeStatisticsParams {
    /// Option trading pair
    std::optional<std::string> symbol = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Check Server Time
    ///
    /// GET /eapi/v1/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#check-server-time
    [[nodiscard]] common::RestApiResponse<CheckServerTimeResponse> check_server_time() const;

    /// Asynchronous `check_server_time()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckServerTimeResponse>)`.
    template <class CompletionToken> auto async_check_server_time(CompletionToken&& token) const {
        return common::async_send<CheckServerTimeResponse>(client_, check_server_time_request(),
                                                           std::forward<CompletionToken>(token));
    }

    /// Exchange Information
    ///
    /// GET /eapi/v1/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#exchange-information
    [[nodiscard]] common::RestApiResponse<ExchangeInformationResponse> exchange_information() const;

    /// Asynchronous `exchange_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExchangeInformationResponse>)`.
    template <class CompletionToken>
    auto async_exchange_information(CompletionToken&& token) const {
        return common::async_send<ExchangeInformationResponse>(
            client_, exchange_information_request(), std::forward<CompletionToken>(token));
    }

    /// Historical Exercise Records
    ///
    /// GET /eapi/v1/exerciseHistory.
    ///
    /// Get historical exercise records.
    ///
    /// * REALISTIC_VALUE_STRICKEN -> Exercised
    /// * EXTRINSIC_VALUE_EXPIRED -> Expired OTM
    ///
    /// Weight(IP): 3
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#historical-exercise-records
    [[nodiscard]] common::RestApiResponse<std::vector<HistoricalExerciseRecordsResponseInner>>
    historical_exercise_records(const HistoricalExerciseRecordsParams& params = {}) const;

    /// Asynchronous `historical_exercise_records()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<HistoricalExerciseRecordsResponseInner>>)`.
    template <class CompletionToken>
    auto async_historical_exercise_records(const HistoricalExerciseRecordsParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<HistoricalExerciseRecordsResponseInner>>(
            client_, historical_exercise_records_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Index Price
    ///
    /// GET /eapi/v1/index.
    ///
    /// Get spot index price for option underlying.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#index-price
    [[nodiscard]] common::RestApiResponse<IndexPriceResponse>
    index_price(const IndexPriceParams& params) const;

    /// Asynchronous `index_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<IndexPriceResponse>)`.
    template <class CompletionToken>
    auto async_index_price(const IndexPriceParams& params, CompletionToken&& token) const {
        return common::async_send<IndexPriceResponse>(client_, index_price_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick Data
    ///
    /// GET /eapi/v1/klines.
    ///
    /// Kline/candlestick bars for an option symbol. Klines are uniquely identified by their open
    /// time.
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent klines are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>
    kline_candlestick_data(const KlineCandlestickDataParams& params) const;

    /// Asynchronous `kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_kline_candlestick_data(const KlineCandlestickDataParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlineCandlestickDataItemInner>>>(
            client_, kline_candlestick_data_request(params), std::forward<CompletionToken>(token));
    }

    /// Open Interest
    ///
    /// GET /eapi/v1/openInterest.
    ///
    /// Get open interest for specific underlying asset on specific expiration date.
    ///
    /// Weight(IP): 0
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#open-interest
    [[nodiscard]] common::RestApiResponse<std::vector<OpenInterestResponseInner>>
    open_interest(const OpenInterestParams& params) const;

    /// Asynchronous `open_interest()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<OpenInterestResponseInner>>)`.
    template <class CompletionToken>
    auto async_open_interest(const OpenInterestParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<OpenInterestResponseInner>>(
            client_, open_interest_request(params), std::forward<CompletionToken>(token));
    }

    /// Option Mark Price
    ///
    /// GET /eapi/v1/mark.
    ///
    /// Option mark price and greek info.
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#option-mark-price
    [[nodiscard]] common::RestApiResponse<std::vector<OptionMarkPriceResponseInner>>
    option_mark_price(const OptionMarkPriceParams& params = {}) const;

    /// Asynchronous `option_mark_price()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OptionMarkPriceResponseInner>>)`.
    template <class CompletionToken>
    auto async_option_mark_price(const OptionMarkPriceParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<std::vector<OptionMarkPriceResponseInner>>(
            client_, option_mark_price_request(params), std::forward<CompletionToken>(token));
    }

    /// Order Book
    ///
    /// GET /eapi/v1/depth.
    ///
    /// Check orderbook depth on specific symbol
    ///
    /// Weight: limit         | weight
    /// ------------  | ------------
    /// 5, 10, 20, 50 | 1
    /// 100           | 5
    /// 500           | 10
    /// 1000          | 20
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#order-book
    [[nodiscard]] common::RestApiResponse<OrderBookResponse>
    order_book(const OrderBookParams& params) const;

    /// Asynchronous `order_book()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderBookResponse>)`.
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return common::async_send<OrderBookResponse>(client_, order_book_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Recent Block Trades List
    ///
    /// GET /eapi/v1/blockTrades.
    ///
    /// Get recent block trades
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#recent-block-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<RecentBlockTradesListResponseInner>>
    recent_block_trades_list(const RecentBlockTradesListParams& params = {}) const;

    /// Asynchronous `recent_block_trades_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<RecentBlockTradesListResponseInner>>)`.
    template <class CompletionToken>
    auto async_recent_block_trades_list(const RecentBlockTradesListParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<RecentBlockTradesListResponseInner>>(
            client_, recent_block_trades_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Recent Trades List
    ///
    /// GET /eapi/v1/trades.
    ///
    /// Get recent market trades
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#recent-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<RecentTradesListResponseInner>>
    recent_trades_list(const RecentTradesListParams& params) const;

    /// Asynchronous `recent_trades_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<RecentTradesListResponseInner>>)`.
    template <class CompletionToken>
    auto async_recent_trades_list(const RecentTradesListParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<RecentTradesListResponseInner>>(
            client_, recent_trades_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Test Connectivity
    ///
    /// GET /eapi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const;

    /// Asynchronous `test_connectivity()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, test_connectivity_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// 24hr Ticker Price Change Statistics
    ///
    /// GET /eapi/v1/ticker.
    ///
    /// 24 hour rolling window price change statistics.
    ///
    /// Weight: 1 for a single symbol; 40 when the symbol parameter is omitted
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-data#ticker24hr-price-change-statistics
    [[nodiscard]] common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>
    ticker24hr_price_change_statistics(
        const Ticker24hrPriceChangeStatisticsParams& params = {}) const;

    /// Asynchronous `ticker24hr_price_change_statistics()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_ticker24hr_price_change_statistics(const Ticker24hrPriceChangeStatisticsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>(
            client_, ticker24hr_price_change_statistics_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest check_server_time_request() const;
    [[nodiscard]] common::RestRequest exchange_information_request() const;
    [[nodiscard]] common::RestRequest
    historical_exercise_records_request(const HistoricalExerciseRecordsParams& params) const;
    [[nodiscard]] common::RestRequest index_price_request(const IndexPriceParams& params) const;
    [[nodiscard]] common::RestRequest
    kline_candlestick_data_request(const KlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest open_interest_request(const OpenInterestParams& params) const;
    [[nodiscard]] common::RestRequest
    option_mark_price_request(const OptionMarkPriceParams& params) const;
    [[nodiscard]] common::RestRequest order_book_request(const OrderBookParams& params) const;
    [[nodiscard]] common::RestRequest
    recent_block_trades_list_request(const RecentBlockTradesListParams& params) const;
    [[nodiscard]] common::RestRequest
    recent_trades_list_request(const RecentTradesListParams& params) const;
    [[nodiscard]] common::RestRequest test_connectivity_request() const;
    [[nodiscard]] common::RestRequest ticker24hr_price_change_statistics_request(
        const Ticker24hrPriceChangeStatisticsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_options::rest_api
