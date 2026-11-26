//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <binance/alpha/export.hpp>
#include <binance/alpha/rest_api/market_data_api.hpp>
#include <binance/alpha/rest_api/models.hpp>
#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>

namespace binance::alpha::rest_api {

/// Alpha REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_ALPHA_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Alpha REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // MarketDataApi

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
    aggregated_trades(const AggregatedTradesParams& params) const {
        return market_data_api_.aggregated_trades(params);
    }
    /// Asynchronous `aggregated_trades()`.
    template <class CompletionToken>
    auto async_aggregated_trades(const AggregatedTradesParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_aggregated_trades(params,
                                                        std::forward<CompletionToken>(token));
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
    full_depth(const FullDepthParams& params) const {
        return market_data_api_.full_depth(params);
    }
    /// Asynchronous `full_depth()`.
    template <class CompletionToken>
    auto async_full_depth(const FullDepthParams& params, CompletionToken&& token) const {
        return market_data_api_.async_full_depth(params, std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<GetExchangeInfoResponse> get_exchange_info() const {
        return market_data_api_.get_exchange_info();
    }
    /// Asynchronous `get_exchange_info()`.
    template <class CompletionToken> auto async_get_exchange_info(CompletionToken&& token) const {
        return market_data_api_.async_get_exchange_info(std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<KlinesResponse> klines(const KlinesParams& params) const {
        return market_data_api_.klines(params);
    }
    /// Asynchronous `klines()`.
    template <class CompletionToken>
    auto async_klines(const KlinesParams& params, CompletionToken&& token) const {
        return market_data_api_.async_klines(params, std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<TickerResponse> ticker(const TickerParams& params) const {
        return market_data_api_.ticker(params);
    }
    /// Asynchronous `ticker()`.
    template <class CompletionToken>
    auto async_ticker(const TickerParams& params, CompletionToken&& token) const {
        return market_data_api_.async_ticker(params, std::forward<CompletionToken>(token));
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
    [[nodiscard]] common::RestApiResponse<TokenListResponse> token_list() const {
        return market_data_api_.token_list();
    }
    /// Asynchronous `token_list()`.
    template <class CompletionToken> auto async_token_list(CompletionToken&& token) const {
        return market_data_api_.async_token_list(std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    MarketDataApi market_data_api_;
};

} // namespace binance::alpha::rest_api
