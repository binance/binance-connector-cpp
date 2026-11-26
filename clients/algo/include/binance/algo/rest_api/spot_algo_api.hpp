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
#include <binance/algo/rest_api/models/cancel_algo_order_spot_algo_response.hpp>
#include <binance/algo/rest_api/models/query_current_algo_open_orders_spot_algo_response.hpp>
#include <binance/algo/rest_api/models/query_historical_algo_orders_spot_algo_response.hpp>
#include <binance/algo/rest_api/models/query_sub_orders_spot_algo_response.hpp>
#include <binance/algo/rest_api/models/time_weighted_average_price_spot_algo_response.hpp>
#include <binance/algo/rest_api/models/volume_participation_response.hpp>
#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>

namespace binance::algo::rest_api {

enum class QueryHistoricalAlgoOrdersSpotAlgoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(QueryHistoricalAlgoOrdersSpotAlgoSideEnum value) noexcept;
BINANCE_ALGO_EXPORT QueryHistoricalAlgoOrdersSpotAlgoSideEnum
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersSpotAlgoSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    QueryHistoricalAlgoOrdersSpotAlgoSideEnum value);

enum class TimeWeightedAveragePriceSpotAlgoSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(TimeWeightedAveragePriceSpotAlgoSideEnum value) noexcept;
BINANCE_ALGO_EXPORT TimeWeightedAveragePriceSpotAlgoSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceSpotAlgoSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    TimeWeightedAveragePriceSpotAlgoSideEnum value);

enum class VolumeParticipationSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(VolumeParticipationSideEnum value) noexcept;
BINANCE_ALGO_EXPORT VolumeParticipationSideEnum tag_invoke(
    boost::json::value_to_tag<VolumeParticipationSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    VolumeParticipationSideEnum value);

enum class VolumeParticipationUrgencyEnum {
    Low,
    Medium,
    High,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_ALGO_EXPORT std::string_view
to_string(VolumeParticipationUrgencyEnum value) noexcept;
BINANCE_ALGO_EXPORT VolumeParticipationUrgencyEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationUrgencyEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALGO_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    VolumeParticipationUrgencyEnum value);

struct CancelAlgoOrderSpotAlgoParams {
    std::optional<std::int64_t> algo_id = std::nullopt;
    std::optional<std::string> client_algo_id = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentAlgoOpenOrdersSpotAlgoParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryHistoricalAlgoOrdersSpotAlgoParams {
    /// Trading symbol
    std::optional<std::string> symbol = std::nullopt;
    std::optional<QueryHistoricalAlgoOrdersSpotAlgoSideEnum> side = std::nullopt;
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

struct QuerySubOrdersSpotAlgoParams {
    /// eg. 14511
    common::Required<std::int64_t> algo_id;
    /// Page number
    std::optional<std::int64_t> page = std::nullopt;
    /// Records per page
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TimeWeightedAveragePriceSpotAlgoParams {
    /// Trading symbol eg. BTCUSDT
    common::Required<std::string> symbol;
    /// Trading side ( BUY or SELL )
    common::Required<TimeWeightedAveragePriceSpotAlgoSideEnum> side;
    /// Quantity of base asset; Maximum notional per order is 200k, 2mm or 10mm, depending on
    /// symbol. Please reduce your size if you order is above the maximum notional per order.
    common::Required<common::Decimal> quantity;
    /// Duration for TWAP orders in seconds
    common::Required<std::int64_t> duration;
    /// A unique id among Algo orders (length should be 32 characters)， If it is not sent, we will
    /// give default value
    std::optional<std::string> client_algo_id = std::nullopt;
    /// Limit price of the order; If it is not sent, will place order by market price by default
    std::optional<common::Decimal> limit_price = std::nullopt;
};

struct VolumeParticipationParams {
    /// Trading symbol eg. BTCUSDT
    common::Required<std::string> symbol;
    /// Trading side ( BUY or SELL )
    common::Required<VolumeParticipationSideEnum> side;
    /// Total order quantity in base asset; The notional must be at least the equivalent of 1,000
    /// USDT, and the maximum notional per order is 200k, 2mm or 10mm, depending on symbol. Please
    /// reduce your size if your order is above the maximum notional per order.
    common::Required<common::Decimal> quantity;
    /// Represent the relative speed of the current execution; ENUM: LOW, MEDIUM, HIGH
    common::Required<VolumeParticipationUrgencyEnum> urgency;
    /// A unique id among Algo orders (length should be 32 characters). If it is not sent, we will
    /// give default value. Must be unique across all open Algo orders.
    std::optional<std::string> client_algo_id = std::nullopt;
    /// Max allowed duration in seconds (minimum 300, maximum 86400). If it is not sent, 86400 is
    /// used and the order runs until fully filled or cancelled.
    std::optional<std::int64_t> vp_time_limit = std::nullopt;
    /// Cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_ALGO_EXPORT SpotAlgoApi {
public:
    explicit SpotAlgoApi(std::shared_ptr<common::RestClient> client);

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
    cancel_algo_order_spot_algo(const CancelAlgoOrderSpotAlgoParams& params = {}) const;

    /// Asynchronous `cancel_algo_order_spot_algo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAlgoOrderSpotAlgoResponse>)`.
    template <class CompletionToken>
    auto async_cancel_algo_order_spot_algo(const CancelAlgoOrderSpotAlgoParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<CancelAlgoOrderSpotAlgoResponse>(
            client_, cancel_algo_order_spot_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params = {}) const;

    /// Asynchronous `query_current_algo_open_orders_spot_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryCurrentAlgoOpenOrdersSpotAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_current_algo_open_orders_spot_algo(
        const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<QueryCurrentAlgoOpenOrdersSpotAlgoResponse>(
            client_, query_current_algo_open_orders_spot_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const QueryHistoricalAlgoOrdersSpotAlgoParams& params = {}) const;

    /// Asynchronous `query_historical_algo_orders_spot_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryHistoricalAlgoOrdersSpotAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_historical_algo_orders_spot_algo(
        const QueryHistoricalAlgoOrdersSpotAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<QueryHistoricalAlgoOrdersSpotAlgoResponse>(
            client_, query_historical_algo_orders_spot_algo_request(params),
            std::forward<CompletionToken>(token));
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
    query_sub_orders_spot_algo(const QuerySubOrdersSpotAlgoParams& params) const;

    /// Asynchronous `query_sub_orders_spot_algo()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySubOrdersSpotAlgoResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_orders_spot_algo(const QuerySubOrdersSpotAlgoParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<QuerySubOrdersSpotAlgoResponse>(
            client_, query_sub_orders_spot_algo_request(params),
            std::forward<CompletionToken>(token));
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
        const TimeWeightedAveragePriceSpotAlgoParams& params) const;

    /// Asynchronous `time_weighted_average_price_spot_algo()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<TimeWeightedAveragePriceSpotAlgoResponse>)`.
    template <class CompletionToken>
    auto async_time_weighted_average_price_spot_algo(
        const TimeWeightedAveragePriceSpotAlgoParams& params, CompletionToken&& token) const {
        return common::async_send<TimeWeightedAveragePriceSpotAlgoResponse>(
            client_, time_weighted_average_price_spot_algo_request(params),
            std::forward<CompletionToken>(token));
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
    volume_participation(const VolumeParticipationParams& params) const;

    /// Asynchronous `volume_participation()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VolumeParticipationResponse>)`.
    template <class CompletionToken>
    auto async_volume_participation(const VolumeParticipationParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<VolumeParticipationResponse>(
            client_, volume_participation_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    cancel_algo_order_spot_algo_request(const CancelAlgoOrderSpotAlgoParams& params) const;
    [[nodiscard]] common::RestRequest query_current_algo_open_orders_spot_algo_request(
        const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params) const;
    [[nodiscard]] common::RestRequest query_historical_algo_orders_spot_algo_request(
        const QueryHistoricalAlgoOrdersSpotAlgoParams& params) const;
    [[nodiscard]] common::RestRequest
    query_sub_orders_spot_algo_request(const QuerySubOrdersSpotAlgoParams& params) const;
    [[nodiscard]] common::RestRequest time_weighted_average_price_spot_algo_request(
        const TimeWeightedAveragePriceSpotAlgoParams& params) const;
    [[nodiscard]] common::RestRequest
    volume_participation_request(const VolumeParticipationParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::algo::rest_api
