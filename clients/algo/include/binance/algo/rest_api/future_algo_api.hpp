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

#include <binance/algo/export.hpp>
#include <binance/algo/rest_api/models/cancel_algo_order_future_algo_response.hpp>
#include <binance/algo/rest_api/models/query_current_algo_open_orders_future_algo_response.hpp>
#include <binance/algo/rest_api/models/query_historical_algo_orders_future_algo_response.hpp>
#include <binance/algo/rest_api/models/query_sub_orders_future_algo_response.hpp>
#include <binance/algo/rest_api/models/time_weighted_average_price_future_algo_response.hpp>
#include <binance/algo/rest_api/models/volume_participation_future_algo_response.hpp>
#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>

namespace binance::algo::rest_api {

enum class QueryHistoricalAlgoOrdersFutureAlgoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(QueryHistoricalAlgoOrdersFutureAlgoSideEnum value) noexcept;
BINANCE_ALGO_EXPORT QueryHistoricalAlgoOrdersFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    QueryHistoricalAlgoOrdersFutureAlgoSideEnum value);

enum class TimeWeightedAveragePriceFutureAlgoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(TimeWeightedAveragePriceFutureAlgoSideEnum value) noexcept;
BINANCE_ALGO_EXPORT TimeWeightedAveragePriceFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TimeWeightedAveragePriceFutureAlgoSideEnum value);

enum class TimeWeightedAveragePriceFutureAlgoPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(TimeWeightedAveragePriceFutureAlgoPositionSideEnum value) noexcept;
BINANCE_ALGO_EXPORT TimeWeightedAveragePriceFutureAlgoPositionSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceFutureAlgoPositionSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TimeWeightedAveragePriceFutureAlgoPositionSideEnum value);

enum class VolumeParticipationFutureAlgoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(VolumeParticipationFutureAlgoSideEnum value) noexcept;
BINANCE_ALGO_EXPORT VolumeParticipationFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    VolumeParticipationFutureAlgoSideEnum value);

enum class VolumeParticipationFutureAlgoUrgencyEnum {
    Low,
    Medium,
    High,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(VolumeParticipationFutureAlgoUrgencyEnum value) noexcept;
BINANCE_ALGO_EXPORT VolumeParticipationFutureAlgoUrgencyEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoUrgencyEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    VolumeParticipationFutureAlgoUrgencyEnum value);

enum class VolumeParticipationFutureAlgoPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(VolumeParticipationFutureAlgoPositionSideEnum value) noexcept;
BINANCE_ALGO_EXPORT VolumeParticipationFutureAlgoPositionSideEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoPositionSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    VolumeParticipationFutureAlgoPositionSideEnum value);

struct CancelAlgoOrderFutureAlgoParams {
    /// eg. 14511
    std::optional<std::int64_t> algo_id = std::nullopt;
    /// eg. "65ce1630101a480b85915d7e11fd5078"
    std::optional<std::string> client_algo_id = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentAlgoOpenOrdersFutureAlgoParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryHistoricalAlgoOrdersFutureAlgoParams {
    /// Trading symbol eg. BTCUSDT
    std::optional<std::string> symbol = std::nullopt;
    /// BUY or SELL
    std::optional<QueryHistoricalAlgoOrdersFutureAlgoSideEnum> side = std::nullopt;
    /// in milliseconds  eg.1641522717552
    std::optional<std::int64_t> start_time = std::nullopt;
    /// in milliseconds  eg.1641522526562
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Page number
    std::optional<std::int64_t> page = std::nullopt;
    /// Records per page
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubOrdersFutureAlgoParams {
    /// eg. 14511
    common::Required<std::int64_t> algo_id;
    /// Page number
    std::optional<std::int64_t> page = std::nullopt;
    /// Records per page
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TimeWeightedAveragePriceFutureAlgoParams {
    /// Trading symbol eg. BTCUSDT
    common::Required<std::string> symbol;
    /// Trading side ( BUY or SELL )
    common::Required<TimeWeightedAveragePriceFutureAlgoSideEnum> side;
    /// Quantity of base asset; The notional (`quantity` * `mark price(base asset)`) must be more
    /// than the equivalent of 1,000 USDT, and the maximum notional varies by symbol: up to
    /// 50,000,000 USDT for BTCUSDT perpetual, up to 25,000,000 USDT for ETHUSDT perpetual, and up
    /// to 5,000,000 USDT for other symbols
    common::Required<common::Decimal> quantity;
    /// Duration for TWAP orders in seconds
    common::Required<std::int64_t> duration;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<TimeWeightedAveragePriceFutureAlgoPositionSideEnum> position_side = std::nullopt;
    /// A unique id among Algo orders (length should be 32 characters)， If it is not sent, we will
    /// give default value
    std::optional<std::string> client_algo_id = std::nullopt;
    /// "true" or "false". Default "false"; Cannot be sent in Hedge Mode; Cannot be sent when you
    /// open a position
    std::optional<bool> reduce_only = std::nullopt;
    /// Limit price of the order; If it is not sent, will place order by market price by default
    std::optional<common::Decimal> limit_price = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct VolumeParticipationFutureAlgoParams {
    /// Trading symbol eg. BTCUSDT
    common::Required<std::string> symbol;
    /// Trading side ( BUY or SELL )
    common::Required<VolumeParticipationFutureAlgoSideEnum> side;
    /// Quantity of base asset; The notional (`quantity` * `mark price(base asset)`) must be more
    /// than the equivalent of 10,000 USDT, and the maximum notional varies by symbol: up to
    /// 50,000,000 USDT for BTCUSDT perpetual, up to 25,000,000 USDT for ETHUSDT perpetual, and up
    /// to 5,000,000 USDT for other symbols
    common::Required<common::Decimal> quantity;
    /// Represent the relative speed of the current execution; ENUM: LOW, MEDIUM, HIGH
    common::Required<VolumeParticipationFutureAlgoUrgencyEnum> urgency;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<VolumeParticipationFutureAlgoPositionSideEnum> position_side = std::nullopt;
    /// A unique id among Algo orders (length should be 32 characters)， If it is not sent, we will
    /// give default value
    std::optional<std::string> client_algo_id = std::nullopt;
    /// "true" or "false". Default "false"; Cannot be sent in Hedge Mode; Cannot be sent when you
    /// open a position
    std::optional<bool> reduce_only = std::nullopt;
    /// Limit price of the order; If it is not sent, will place order by market price by default
    std::optional<common::Decimal> limit_price = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_ALGO_EXPORT FutureAlgoApi {
public:
    explicit FutureAlgoApi(std::shared_ptr<common::RestClient> client);

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
    cancel_algo_order_future_algo(const CancelAlgoOrderFutureAlgoParams& params = {}) const;

    /// Asynchronous `cancel_algo_order_future_algo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAlgoOrderFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_cancel_algo_order_future_algo(const CancelAlgoOrderFutureAlgoParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<CancelAlgoOrderFutureAlgoResponse>(
            client_, cancel_algo_order_future_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params = {}) const;

    /// Asynchronous `query_current_algo_open_orders_future_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryCurrentAlgoOpenOrdersFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_current_algo_open_orders_future_algo(
        const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<QueryCurrentAlgoOpenOrdersFutureAlgoResponse>(
            client_, query_current_algo_open_orders_future_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryHistoricalAlgoOrdersFutureAlgoParams& params = {}) const;

    /// Asynchronous `query_historical_algo_orders_future_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryHistoricalAlgoOrdersFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_historical_algo_orders_future_algo(
        const QueryHistoricalAlgoOrdersFutureAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<QueryHistoricalAlgoOrdersFutureAlgoResponse>(
            client_, query_historical_algo_orders_future_algo_request(params),
            std::forward<CompletionToken>(token));
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
    query_sub_orders_future_algo(const QuerySubOrdersFutureAlgoParams& params) const;

    /// Asynchronous `query_sub_orders_future_algo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySubOrdersFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_orders_future_algo(const QuerySubOrdersFutureAlgoParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<QuerySubOrdersFutureAlgoResponse>(
            client_, query_sub_orders_future_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const TimeWeightedAveragePriceFutureAlgoParams& params) const;

    /// Asynchronous `time_weighted_average_price_future_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<TimeWeightedAveragePriceFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_time_weighted_average_price_future_algo(
        const TimeWeightedAveragePriceFutureAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<TimeWeightedAveragePriceFutureAlgoResponse>(
            client_, time_weighted_average_price_future_algo_request(params),
            std::forward<CompletionToken>(token));
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
    volume_participation_future_algo(const VolumeParticipationFutureAlgoParams& params) const;

    /// Asynchronous `volume_participation_future_algo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VolumeParticipationFutureAlgoResponse>)`.
    template <class CompletionToken>
    auto async_volume_participation_future_algo(const VolumeParticipationFutureAlgoParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<VolumeParticipationFutureAlgoResponse>(
            client_, volume_participation_future_algo_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    cancel_algo_order_future_algo_request(const CancelAlgoOrderFutureAlgoParams& params) const;
    [[nodiscard]] common::RestRequest query_current_algo_open_orders_future_algo_request(
        const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params) const;
    [[nodiscard]] common::RestRequest query_historical_algo_orders_future_algo_request(
        const QueryHistoricalAlgoOrdersFutureAlgoParams& params) const;
    [[nodiscard]] common::RestRequest
    query_sub_orders_future_algo_request(const QuerySubOrdersFutureAlgoParams& params) const;
    [[nodiscard]] common::RestRequest time_weighted_average_price_future_algo_request(
        const TimeWeightedAveragePriceFutureAlgoParams& params) const;
    [[nodiscard]] common::RestRequest volume_participation_future_algo_request(
        const VolumeParticipationFutureAlgoParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::algo::rest_api
