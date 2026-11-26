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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>
#include <binance/alpha/rest_api/models/aggregated_trades_response.hpp>
#include <binance/alpha/rest_api/models/full_depth_response.hpp>
#include <binance/alpha/rest_api/models/get_exchange_info_response.hpp>
#include <binance/alpha/rest_api/models/klines_response.hpp>
#include <binance/alpha/rest_api/models/ticker_response.hpp>
#include <binance/alpha/rest_api/models/token_list_response.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>

namespace binance::alpha::rest_api {

enum class FullDepthLimitEnum {
    Limit5,
    Limit10,
    Limit20,
    Limit50,
    Limit100,
    Limit500,
    Limit1000,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view to_string(FullDepthLimitEnum value) noexcept;
BINANCE_ALPHA_EXPORT FullDepthLimitEnum
tag_invoke(boost::json::value_to_tag<FullDepthLimitEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     FullDepthLimitEnum value);

enum class KlinesIntervalEnum {
    Interval1s,
    Interval15s,
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

[[nodiscard]] BINANCE_ALPHA_EXPORT std::string_view to_string(KlinesIntervalEnum value) noexcept;
BINANCE_ALPHA_EXPORT KlinesIntervalEnum
tag_invoke(boost::json::value_to_tag<KlinesIntervalEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     KlinesIntervalEnum value);

struct AggregatedTradesParams {
    /// Trading pair symbol, e.g. ALPHA_118USDC (use token ID from Token List).
    common::Required<std::string> symbol;
    /// Starting aggregate trade ID to fetch from.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Start timestamp in milliseconds.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End timestamp in milliseconds.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct FullDepthParams {
    /// Trading pair symbol, e.g. ALPHA_175USDT (use token ID from Token List).
    common::Required<std::string> symbol;
    /// Number of price levels to return. Valid values: 5, 10, 20, 50, 100, 500, 1000.
    std::optional<FullDepthLimitEnum> limit = std::nullopt;
};

struct KlinesParams {
    /// Trading pair symbol, e.g. ALPHA_175USDT (use token ID from Token List).
    common::Required<std::string> symbol;
    /// Kline interval.
    common::Required<KlinesIntervalEnum> interval;
    /// Number of klines to return.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Start timestamp in milliseconds.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End timestamp in milliseconds.
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct TickerParams {
    /// Trading pair symbol, e.g. ALPHA_175USDT (use token ID from Token List).
    common::Required<std::string> symbol;
};

class BINANCE_ALPHA_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Aggregated Trades
    ///
    /// GET /bapi/defi/v1/public/alpha-trade/agg-trades.
    ///
    /// Retrieves compressed, aggregated historical trades for a specific symbol. Useful for recent
    /// trade history.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#aggregated-trades
    [[nodiscard]] common::RestApiResponse<AggregatedTradesResponse>
    aggregated_trades(const AggregatedTradesParams& params) const;

    /// Asynchronous `aggregated_trades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AggregatedTradesResponse>)`.
    template <class CompletionToken>
    auto async_aggregated_trades(const AggregatedTradesParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<AggregatedTradesResponse>(
            client_, aggregated_trades_request(params), std::forward<CompletionToken>(token));
    }

    /// Full Depth
    ///
    /// GET /bapi/defi/v1/public/alpha-trade/fullDepth.
    ///
    /// Fetches the full order book depth (UI & API orders) for a symbol, including bid and ask
    /// orders with their prices and quantities.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#full-depth
    [[nodiscard]] common::RestApiResponse<FullDepthResponse>
    full_depth(const FullDepthParams& params) const;

    /// Asynchronous `full_depth()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FullDepthResponse>)`.
    template <class CompletionToken>
    auto async_full_depth(const FullDepthParams& params, CompletionToken&& token) const {
        return common::async_send<FullDepthResponse>(client_, full_depth_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Get Exchange Info
    ///
    /// GET /bapi/defi/v1/public/alpha-trade/get-exchange-info.
    ///
    /// Fetches general exchange information, such as supported symbols, rate limits, and server
    /// time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#get-exchange-info
    [[nodiscard]] common::RestApiResponse<GetExchangeInfoResponse> get_exchange_info() const;

    /// Asynchronous `get_exchange_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetExchangeInfoResponse>)`.
    template <class CompletionToken> auto async_get_exchange_info(CompletionToken&& token) const {
        return common::async_send<GetExchangeInfoResponse>(client_, get_exchange_info_request(),
                                                           std::forward<CompletionToken>(token));
    }

    /// Klines
    ///
    /// GET /bapi/defi/v1/public/alpha-trade/klines.
    ///
    /// Fetches Kline/candlestick bars for a symbol, which include open/high/low/close prices and
    /// volume over intervals. Useful for charting and analysis.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#klines
    [[nodiscard]] common::RestApiResponse<KlinesResponse> klines(const KlinesParams& params) const;

    /// Asynchronous `klines()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<KlinesResponse>)`.
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return common::async_send<KlinesResponse>(client_, klines_request(params),
                                                  std::forward<CompletionToken>(token));
    }

    /// Ticker
    ///
    /// GET /bapi/defi/v1/public/alpha-trade/ticker.
    ///
    /// Gets the 24-hour rolling window price change statistics for a symbol, including volume and
    /// price changes.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#ticker
    [[nodiscard]] common::RestApiResponse<TickerResponse> ticker(const TickerParams& params) const;

    /// Asynchronous `ticker()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TickerResponse>)`.
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return common::async_send<TickerResponse>(client_, ticker_request(params),
                                                  std::forward<CompletionToken>(token));
    }

    /// Token List
    ///
    /// GET /bapi/defi/v1/public/wallet-direct/buw/wallet/cex/alpha/all/token/list.
    ///
    /// Retrieves a list of all available ALPHA tokens, including their IDs and symbols. Use this to
    /// find the token ID for constructing symbols in other endpoints.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-alpha-trading/api/rest-api/market-data#token-list
    [[nodiscard]] common::RestApiResponse<TokenListResponse> token_list() const;

    /// Asynchronous `token_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TokenListResponse>)`.
    template <class CompletionToken> auto async_token_list(CompletionToken&& token) const {
        return common::async_send<TokenListResponse>(client_, token_list_request(),
                                                     std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    aggregated_trades_request(const AggregatedTradesParams& params) const;
    [[nodiscard]] common::RestRequest full_depth_request(const FullDepthParams& params) const;
    [[nodiscard]] common::RestRequest get_exchange_info_request() const;
    [[nodiscard]] common::RestRequest klines_request(const KlinesParams& params) const;
    [[nodiscard]] common::RestRequest ticker_request(const TickerParams& params) const;
    [[nodiscard]] common::RestRequest token_list_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::alpha::rest_api
