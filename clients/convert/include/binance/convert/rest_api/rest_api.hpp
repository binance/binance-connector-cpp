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

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/convert/export.hpp>
#include <binance/convert/rest_api/market_data_api.hpp>
#include <binance/convert/rest_api/models.hpp>
#include <binance/convert/rest_api/trade_api.hpp>

namespace binance::convert::rest_api {

/// Convert REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_CONVERT_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Convert REST API).
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

    /// List All Convert Pairs
    ///
    /// GET /sapi/v1/convert/exchangeInfo.
    ///
    /// Query for all convertible token pairs and the tokens’ respective
    /// upper/lower limits
    ///
    /// Weight(IP): 3000
    ///
    /// Notes:
    /// - User needs to supply either or both input parameters.
    /// - If only one of `fromAsset` and `toAsset` is provided, only partial token pairs are
    /// returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/market-data#list-all-convert-pairs
    [[nodiscard]] common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>
    list_all_convert_pairs(const ListAllConvertPairsParams& params = {}) const {
        return market_data_api_.list_all_convert_pairs(params);
    }
    /// Asynchronous `list_all_convert_pairs()`.
    template <class CompletionToken>
    auto async_list_all_convert_pairs(const ListAllConvertPairsParams& params,
                                      CompletionToken&& token) const {
        return market_data_api_.async_list_all_convert_pairs(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Query order quantity precision per asset (USER_DATA)
    ///
    /// GET /sapi/v1/convert/assetInfo.
    ///
    /// Query for supported asset’s precision information
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/market-data#query-order-quantity-precision-per-asset
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>
    query_order_quantity_precision_per_asset(
        const QueryOrderQuantityPrecisionPerAssetParams& params = {}) const {
        return market_data_api_.query_order_quantity_precision_per_asset(params);
    }
    /// Asynchronous `query_order_quantity_precision_per_asset()`.
    template <class CompletionToken>
    auto async_query_order_quantity_precision_per_asset(
        const QueryOrderQuantityPrecisionPerAssetParams& params, CompletionToken&& token) const {
        return market_data_api_.async_query_order_quantity_precision_per_asset(
            params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Accept Quote (TRADE)
    ///
    /// POST /sapi/v1/convert/acceptQuote.
    ///
    /// Accept the offered quote by quote ID.
    ///
    /// Weight(UID): 500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#accept-quote
    [[nodiscard]] common::RestApiResponse<AcceptQuoteResponse>
    accept_quote(const AcceptQuoteParams& params) const {
        return trade_api_.accept_quote(params);
    }
    /// Asynchronous `accept_quote()`.
    template <class CompletionToken>
    auto async_accept_quote(const AcceptQuoteParams& params, CompletionToken&& token) const {
        return trade_api_.async_accept_quote(params, std::forward<CompletionToken>(token));
    }

    /// Cancel limit order (TRADE)
    ///
    /// POST /sapi/v1/convert/limit/cancelOrder.
    ///
    /// Enable users to cancel a limit order
    ///
    /// Weight(UID): 200
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#cancel-limit-order
    [[nodiscard]] common::RestApiResponse<CancelLimitOrderResponse>
    cancel_limit_order(const CancelLimitOrderParams& params) const {
        return trade_api_.cancel_limit_order(params);
    }
    /// Asynchronous `cancel_limit_order()`.
    template <class CompletionToken>
    auto async_cancel_limit_order(const CancelLimitOrderParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_cancel_limit_order(params, std::forward<CompletionToken>(token));
    }

    /// Get Convert Trade History (USER_DATA)
    ///
    /// GET /sapi/v1/convert/tradeFlow.
    ///
    /// Get Convert Trade History
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The max interval between `startTime` and `endTime` is 30 days.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#get-convert-trade-history
    [[nodiscard]] common::RestApiResponse<GetConvertTradeHistoryResponse>
    get_convert_trade_history(const GetConvertTradeHistoryParams& params) const {
        return trade_api_.get_convert_trade_history(params);
    }
    /// Asynchronous `get_convert_trade_history()`.
    template <class CompletionToken>
    auto async_get_convert_trade_history(const GetConvertTradeHistoryParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_get_convert_trade_history(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Order status (USER_DATA)
    ///
    /// GET /sapi/v1/convert/orderStatus.
    ///
    /// Query order status by order ID.
    ///
    /// Weight(UID): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#order-status
    [[nodiscard]] common::RestApiResponse<OrderStatusResponse>
    order_status(const OrderStatusParams& params = {}) const {
        return trade_api_.order_status(params);
    }
    /// Asynchronous `order_status()`.
    template <class CompletionToken>
    auto async_order_status(const OrderStatusParams& params, CompletionToken&& token) const {
        return trade_api_.async_order_status(params, std::forward<CompletionToken>(token));
    }

    /// Place limit order (TRADE)
    ///
    /// POST /sapi/v1/convert/limit/placeOrder.
    ///
    /// Enable users to place a limit order
    ///
    /// Weight(UID): 500
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `baseAsset` and `quoteAsset` can be determined via the `exchangeInfo` endpoint.
    /// - Limit price is defined from `baseAsset` to `quoteAsset`.
    /// - Exactly one of `baseAmount` or `quoteAmount` should be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#place-limit-order
    [[nodiscard]] common::RestApiResponse<PlaceLimitOrderResponse>
    place_limit_order(const PlaceLimitOrderParams& params) const {
        return trade_api_.place_limit_order(params);
    }
    /// Asynchronous `place_limit_order()`.
    template <class CompletionToken>
    auto async_place_limit_order(const PlaceLimitOrderParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_place_limit_order(params, std::forward<CompletionToken>(token));
    }

    /// Query limit open orders (USER_DATA)
    ///
    /// GET /sapi/v1/convert/limit/queryOpenOrders.
    ///
    /// Query current open limit orders
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#query-limit-open-orders
    [[nodiscard]] common::RestApiResponse<QueryLimitOpenOrdersResponse>
    query_limit_open_orders(const QueryLimitOpenOrdersParams& params = {}) const {
        return trade_api_.query_limit_open_orders(params);
    }
    /// Asynchronous `query_limit_open_orders()`.
    template <class CompletionToken>
    auto async_query_limit_open_orders(const QueryLimitOpenOrdersParams& params,
                                       CompletionToken&& token) const {
        return trade_api_.async_query_limit_open_orders(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Send Quote Request (TRADE)
    ///
    /// POST /sapi/v1/convert/getQuote.
    ///
    /// Request a quote for the requested token pairs
    ///
    /// Weight(UID): 200
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `fromAmount` or `toAmount` should be sent.
    /// - `quoteId` is returned only if you have enough funds to convert.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/trade#send-quote-request
    [[nodiscard]] common::RestApiResponse<SendQuoteRequestResponse>
    send_quote_request(const SendQuoteRequestParams& params) const {
        return trade_api_.send_quote_request(params);
    }
    /// Asynchronous `send_quote_request()`.
    template <class CompletionToken>
    auto async_send_quote_request(const SendQuoteRequestParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_send_quote_request(params, std::forward<CompletionToken>(token));
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
    TradeApi trade_api_;
};

} // namespace binance::convert::rest_api
