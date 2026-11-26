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

#include <binance/algo/export.hpp>
#include <binance/algo/rest_api/future_algo_api.hpp>
#include <binance/algo/rest_api/models.hpp>
#include <binance/algo/rest_api/spot_algo_api.hpp>
#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>

namespace binance::algo::rest_api {

/// Algo REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_ALGO_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Algo REST API).
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

    // FutureAlgoApi

    /// Cancel Futures Algo Order (TRADE)
    ///
    /// DELETE /sapi/v1/algo/futures/order.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    /// - You need to enable `Futures Trading Permission` for the API key that requests this
    /// endpoint.
    /// - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#cancel-algo-order-future-algo
    [[nodiscard]] common::RestApiResponse<CancelAlgoOrderFutureAlgoResponse>
    cancel_algo_order_future_algo(const CancelAlgoOrderFutureAlgoParams& params = {}) const {
        return future_algo_api_.cancel_algo_order_future_algo(params);
    }
    /// Asynchronous `cancel_algo_order_future_algo()`.
    template <class CompletionToken>
    auto async_cancel_algo_order_future_algo(const CancelAlgoOrderFutureAlgoParams& params,
                                             CompletionToken&& token) const {
        return future_algo_api_.async_cancel_algo_order_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Current Futures Algo Open Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/futures/openOrders.
    ///
    /// Query Current Algo Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable `Futures Trading Permission` for the API key that requests this
    /// endpoint.
    /// - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#query-current-algo-open-orders-future-algo
    [[nodiscard]] common::RestApiResponse<QueryCurrentAlgoOpenOrdersFutureAlgoResponse>
    query_current_algo_open_orders_future_algo(
        const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params = {}) const {
        return future_algo_api_.query_current_algo_open_orders_future_algo(params);
    }
    /// Asynchronous `query_current_algo_open_orders_future_algo()`.
    template <class CompletionToken>
    auto async_query_current_algo_open_orders_future_algo(
        const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params, CompletionToken&& token) const {
        return future_algo_api_.async_query_current_algo_open_orders_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Historical Futures Algo Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/futures/historicalOrders.
    ///
    /// Query Historical Algo Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable `Futures Trading Permission` for the API key that requests this
    /// endpoint.
    /// - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#query-historical-algo-orders-future-algo
    [[nodiscard]] common::RestApiResponse<QueryHistoricalAlgoOrdersFutureAlgoResponse>
    query_historical_algo_orders_future_algo(
        const QueryHistoricalAlgoOrdersFutureAlgoParams& params = {}) const {
        return future_algo_api_.query_historical_algo_orders_future_algo(params);
    }
    /// Asynchronous `query_historical_algo_orders_future_algo()`.
    template <class CompletionToken>
    auto async_query_historical_algo_orders_future_algo(
        const QueryHistoricalAlgoOrdersFutureAlgoParams& params, CompletionToken&& token) const {
        return future_algo_api_.async_query_historical_algo_orders_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Futures Sub Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/futures/subOrders.
    ///
    /// Get respective sub orders for a specified algoId
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable `Futures Trading Permission` for the API key that requests this
    /// endpoint.
    /// - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#query-sub-orders-future-algo
    [[nodiscard]] common::RestApiResponse<QuerySubOrdersFutureAlgoResponse>
    query_sub_orders_future_algo(const QuerySubOrdersFutureAlgoParams& params) const {
        return future_algo_api_.query_sub_orders_future_algo(params);
    }
    /// Asynchronous `query_sub_orders_future_algo()`.
    template <class CompletionToken>
    auto async_query_sub_orders_future_algo(const QuerySubOrdersFutureAlgoParams& params,
                                            CompletionToken&& token) const {
        return future_algo_api_.async_query_sub_orders_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Time-Weighted Futures Average Price (Twap) New Order (TRADE)
    ///
    /// POST /sapi/v1/algo/futures/newOrderTwap.
    ///
    /// Send in a Twap new order. Only support on USDⓈ-M Contracts.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Other info:
    ///   - Total Algo open orders max allowed: `30` orders.
    ///   - Leverage and position mode follow your futures account settings.
    ///   - Receiving `"success": true` does not guarantee execution; query order endpoints for
    ///   final status.
    ///   - If balance/position constraints fail, response may still return success but order status
    ///   becomes `expired`.
    ///   - `quantity * 60 / duration` must be greater than `minQty`.
    ///   - `duration` cannot be less than 5 minutes or greater than 24 hours.
    ///   - For delivery contracts, TWAP end time should be one hour earlier than symbol delivery
    ///   time.
    ///   - You need to enable the corresponding permission for the API key requesting this
    ///   endpoint:
    ///     - `Futures Trading Permission` — for Classic Trading Account mode
    ///     - `Portfolio Margin Trading Permission` — for Portfolio Margin Account mode
    ///   - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#time-weighted-average-price-future-algo
    [[nodiscard]] common::RestApiResponse<TimeWeightedAveragePriceFutureAlgoResponse>
    time_weighted_average_price_future_algo(
        const TimeWeightedAveragePriceFutureAlgoParams& params) const {
        return future_algo_api_.time_weighted_average_price_future_algo(params);
    }
    /// Asynchronous `time_weighted_average_price_future_algo()`.
    template <class CompletionToken>
    auto async_time_weighted_average_price_future_algo(
        const TimeWeightedAveragePriceFutureAlgoParams& params, CompletionToken&& token) const {
        return future_algo_api_.async_time_weighted_average_price_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Volume Participation (VP) New Order (TRADE)
    ///
    /// POST /sapi/v1/algo/futures/newOrderVp.
    ///
    /// Send in a VP new order. Only support on USDⓈ-M Contracts.
    ///
    /// Weight(UID): 300
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Other info:
    ///   - Total Algo open orders max allowed: `10` orders.
    ///   - Leverage and position mode follow your futures account settings.
    ///   - Receiving `"success": true` does not guarantee execution; query order endpoints for
    ///   final status.
    ///   - If balance/position constraints fail, response may still return success but order status
    ///   becomes `expired`.
    ///   - You need to enable the corresponding permission for the API key requesting this
    ///   endpoint:
    ///     - `Futures Trading Permission` — for Classic Trading Account mode
    ///     - `Portfolio Margin Trading Permission` — for Portfolio Margin Account mode
    ///   - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/future-algo#volume-participation-future-algo
    [[nodiscard]] common::RestApiResponse<VolumeParticipationFutureAlgoResponse>
    volume_participation_future_algo(const VolumeParticipationFutureAlgoParams& params) const {
        return future_algo_api_.volume_participation_future_algo(params);
    }
    /// Asynchronous `volume_participation_future_algo()`.
    template <class CompletionToken>
    auto async_volume_participation_future_algo(const VolumeParticipationFutureAlgoParams& params,
                                                CompletionToken&& token) const {
        return future_algo_api_.async_volume_participation_future_algo(
            params, std::forward<CompletionToken>(token));
    }

    // SpotAlgoApi

    /// Cancel Spot Algo Order (TRADE)
    ///
    /// DELETE /sapi/v1/algo/spot/order.
    ///
    /// Cancel an open TWAP or VP algo order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#cancel-algo-order-spot-algo
    [[nodiscard]] common::RestApiResponse<CancelAlgoOrderSpotAlgoResponse>
    cancel_algo_order_spot_algo(const CancelAlgoOrderSpotAlgoParams& params = {}) const {
        return spot_algo_api_.cancel_algo_order_spot_algo(params);
    }
    /// Asynchronous `cancel_algo_order_spot_algo()`.
    template <class CompletionToken>
    auto async_cancel_algo_order_spot_algo(const CancelAlgoOrderSpotAlgoParams& params,
                                           CompletionToken&& token) const {
        return spot_algo_api_.async_cancel_algo_order_spot_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Current Spot Algo Open Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/spot/openOrders.
    ///
    /// Get all open Spot TWAP and VP algo orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#query-current-algo-open-orders-spot-algo
    [[nodiscard]] common::RestApiResponse<QueryCurrentAlgoOpenOrdersSpotAlgoResponse>
    query_current_algo_open_orders_spot_algo(
        const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params = {}) const {
        return spot_algo_api_.query_current_algo_open_orders_spot_algo(params);
    }
    /// Asynchronous `query_current_algo_open_orders_spot_algo()`.
    template <class CompletionToken>
    auto async_query_current_algo_open_orders_spot_algo(
        const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params, CompletionToken&& token) const {
        return spot_algo_api_.async_query_current_algo_open_orders_spot_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Historical Spot Algo Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/spot/historicalOrders.
    ///
    /// Get all historical Spot TWAP and VP algo orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#query-historical-algo-orders-spot-algo
    [[nodiscard]] common::RestApiResponse<QueryHistoricalAlgoOrdersSpotAlgoResponse>
    query_historical_algo_orders_spot_algo(
        const QueryHistoricalAlgoOrdersSpotAlgoParams& params = {}) const {
        return spot_algo_api_.query_historical_algo_orders_spot_algo(params);
    }
    /// Asynchronous `query_historical_algo_orders_spot_algo()`.
    template <class CompletionToken>
    auto async_query_historical_algo_orders_spot_algo(
        const QueryHistoricalAlgoOrdersSpotAlgoParams& params, CompletionToken&& token) const {
        return spot_algo_api_.async_query_historical_algo_orders_spot_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Spot Sub Orders (USER_DATA)
    ///
    /// GET /sapi/v1/algo/spot/subOrders.
    ///
    /// Get respective sub orders for a specified algoId
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#query-sub-orders-spot-algo
    [[nodiscard]] common::RestApiResponse<QuerySubOrdersSpotAlgoResponse>
    query_sub_orders_spot_algo(const QuerySubOrdersSpotAlgoParams& params) const {
        return spot_algo_api_.query_sub_orders_spot_algo(params);
    }
    /// Asynchronous `query_sub_orders_spot_algo()`.
    template <class CompletionToken>
    auto async_query_sub_orders_spot_algo(const QuerySubOrdersSpotAlgoParams& params,
                                          CompletionToken&& token) const {
        return spot_algo_api_.async_query_sub_orders_spot_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Time-Weighted Spot Average Price(Twap) New Order (TRADE)
    ///
    /// POST /sapi/v1/algo/spot/newOrderTwap.
    ///
    /// Place a new spot TWAP order with Algo service.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Total Algo open orders max allowed: `20` orders.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#time-weighted-average-price-spot-algo
    [[nodiscard]] common::RestApiResponse<TimeWeightedAveragePriceSpotAlgoResponse>
    time_weighted_average_price_spot_algo(
        const TimeWeightedAveragePriceSpotAlgoParams& params) const {
        return spot_algo_api_.time_weighted_average_price_spot_algo(params);
    }
    /// Asynchronous `time_weighted_average_price_spot_algo()`.
    template <class CompletionToken>
    auto async_time_weighted_average_price_spot_algo(
        const TimeWeightedAveragePriceSpotAlgoParams& params, CompletionToken&& token) const {
        return spot_algo_api_.async_time_weighted_average_price_spot_algo(
            params, std::forward<CompletionToken>(token));
    }

    /// Volume Participation (VP) New Order (TRADE)
    ///
    /// POST /sapi/v1/algo/spot/newOrderVp.
    ///
    /// Place a new spot VP (Volume Participation) order with Algo service. A VP order automatically
    /// slices the total quantity over time, targeting a percentage of the market volume.
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - VP orders do not accept `price` or `timeInForce`; pricing is determined algorithmically
    /// based on market volume.
    /// - `urgency` controls the participation rate: LOW = passive, MEDIUM = neutral, HIGH =
    /// aggressive.
    /// - Receiving `"success": true` does not guarantee execution; use the query order endpoints
    /// (`GET /sapi/v1/algo/spot/openOrders` or `GET /sapi/v1/algo/spot/historicalOrders`) to check
    /// the final status.
    /// - You need to enable the `Spot Trading` permission for the API key requesting this endpoint.
    /// - Base URL: `https://api.binance.com`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-algo-trading/api/rest-api/spot-algo#volume-participation
    [[nodiscard]] common::RestApiResponse<VolumeParticipationResponse>
    volume_participation(const VolumeParticipationParams& params) const {
        return spot_algo_api_.volume_participation(params);
    }
    /// Asynchronous `volume_participation()`.
    template <class CompletionToken>
    auto async_volume_participation(const VolumeParticipationParams& params,
                                    CompletionToken&& token) const {
        return spot_algo_api_.async_volume_participation(params,
                                                         std::forward<CompletionToken>(token));
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
    FutureAlgoApi future_algo_api_;
    SpotAlgoApi spot_algo_api_;
};

} // namespace binance::algo::rest_api
