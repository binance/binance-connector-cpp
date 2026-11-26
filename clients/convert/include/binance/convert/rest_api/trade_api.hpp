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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/convert/export.hpp>
#include <binance/convert/rest_api/models/accept_quote_response.hpp>
#include <binance/convert/rest_api/models/cancel_limit_order_response.hpp>
#include <binance/convert/rest_api/models/get_convert_trade_history_response.hpp>
#include <binance/convert/rest_api/models/order_status_response.hpp>
#include <binance/convert/rest_api/models/place_limit_order_response.hpp>
#include <binance/convert/rest_api/models/query_limit_open_orders_response.hpp>
#include <binance/convert/rest_api/models/send_quote_request_response.hpp>

namespace binance::convert::rest_api {

enum class PlaceLimitOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CONVERT_EXPORT std::string_view
to_string(PlaceLimitOrderSideEnum value) noexcept;
BINANCE_CONVERT_EXPORT PlaceLimitOrderSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceLimitOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       PlaceLimitOrderSideEnum value);

enum class PlaceLimitOrderExpiredTypeEnum {
    ExpiredType1D,
    ExpiredType3D,
    ExpiredType7D,
    ExpiredType30D,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CONVERT_EXPORT std::string_view
to_string(PlaceLimitOrderExpiredTypeEnum value) noexcept;
BINANCE_CONVERT_EXPORT PlaceLimitOrderExpiredTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceLimitOrderExpiredTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       PlaceLimitOrderExpiredTypeEnum value);

enum class PlaceLimitOrderWalletTypeEnum {
    Spot,
    Funding,
    Earn,
    SpotFunding,
    FundingEarn,
    SpotFundingEarn,
    SpotEarn,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CONVERT_EXPORT std::string_view
to_string(PlaceLimitOrderWalletTypeEnum value) noexcept;
BINANCE_CONVERT_EXPORT PlaceLimitOrderWalletTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceLimitOrderWalletTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       PlaceLimitOrderWalletTypeEnum value);

enum class SendQuoteRequestWalletTypeEnum {
    Spot,
    Funding,
    Earn,
    SpotFunding,
    FundingEarn,
    SpotFundingEarn,
    SpotEarn,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CONVERT_EXPORT std::string_view
to_string(SendQuoteRequestWalletTypeEnum value) noexcept;
BINANCE_CONVERT_EXPORT SendQuoteRequestWalletTypeEnum
tag_invoke(boost::json::value_to_tag<SendQuoteRequestWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       SendQuoteRequestWalletTypeEnum value);

enum class SendQuoteRequestValidTimeEnum {
    ValidTime10s,
    ValidTime30s,
    ValidTime1m,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_CONVERT_EXPORT std::string_view
to_string(SendQuoteRequestValidTimeEnum value) noexcept;
BINANCE_CONVERT_EXPORT SendQuoteRequestValidTimeEnum tag_invoke(
    boost::json::value_to_tag<SendQuoteRequestValidTimeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       SendQuoteRequestValidTimeEnum value);

struct AcceptQuoteParams {
    common::Required<std::string> quote_id;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelLimitOrderParams {
    /// The orderId from `placeOrder` api
    common::Required<std::int64_t> order_id;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetConvertTradeHistoryParams {
    common::Required<std::int64_t> start_time;
    common::Required<std::int64_t> end_time;
    /// Number of records to return
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OrderStatusParams {
    /// Either orderId or quoteId is required
    std::optional<std::string> order_id = std::nullopt;
    /// Either orderId or quoteId is required
    std::optional<std::string> quote_id = std::nullopt;
};

struct PlaceLimitOrderParams {
    /// base asset (use the response `fromIsBase` from `GET /sapi/v1/convert/exchangeInfo` api to
    /// check which one is baseAsset )
    common::Required<std::string> base_asset;
    /// quote asset
    common::Required<std::string> quote_asset;
    /// Symbol limit price (from baseAsset to quoteAsset)
    common::Required<common::Decimal> limit_price;
    /// `BUY` or `SELL`
    common::Required<PlaceLimitOrderSideEnum> side;
    /// Order expiry duration. 1_D, 3_D, 7_D, 30_D (D means day)
    common::Required<PlaceLimitOrderExpiredTypeEnum> expired_type;
    /// Base asset amount. (One of `baseAmount` or `quoteAmount` is required)
    std::optional<common::Decimal> base_amount = std::nullopt;
    /// Quote asset amount. (One of `baseAmount` or `quoteAmount` is required)
    std::optional<common::Decimal> quote_amount = std::nullopt;
    /// Wallet to use for payment. Supported values: `SPOT`, `FUNDING`, `EARN`. Combined wallets
    /// also supported: `SPOT_FUNDING`, `FUNDING_EARN`, `SPOT_FUNDING_EARN`, `SPOT_EARN`. Default is
    /// `SPOT`.
    std::optional<PlaceLimitOrderWalletTypeEnum> wallet_type = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryLimitOpenOrdersParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SendQuoteRequestParams {
    common::Required<std::string> from_asset;
    common::Required<std::string> to_asset;
    /// When specified, it is the amount you will be debited after the conversion
    std::optional<common::Decimal> from_amount = std::nullopt;
    /// When specified, it is the amount you will be credited after the conversion
    std::optional<common::Decimal> to_amount = std::nullopt;
    /// Wallet to use for payment. Supported values: `SPOT`, `FUNDING`, `EARN`. Combined wallets
    /// also supported: `SPOT_FUNDING`, `FUNDING_EARN`, `SPOT_FUNDING_EARN`, `SPOT_EARN`. Default is
    /// `SPOT`.
    std::optional<SendQuoteRequestWalletTypeEnum> wallet_type = std::nullopt;
    /// Quote valid duration. Supported values: 10s, 30s, 1m. Default is 10s.
    std::optional<SendQuoteRequestValidTimeEnum> valid_time = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_CONVERT_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

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
    accept_quote(const AcceptQuoteParams& params) const;

    /// Asynchronous `accept_quote()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AcceptQuoteResponse>)`.
    template <class CompletionToken>
    auto async_accept_quote(const AcceptQuoteParams& params, CompletionToken&& token) const {
        return common::async_send<AcceptQuoteResponse>(client_, accept_quote_request(params),
                                                       std::forward<CompletionToken>(token));
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
    cancel_limit_order(const CancelLimitOrderParams& params) const;

    /// Asynchronous `cancel_limit_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelLimitOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_limit_order(const CancelLimitOrderParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<CancelLimitOrderResponse>(
            client_, cancel_limit_order_request(params), std::forward<CompletionToken>(token));
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
    get_convert_trade_history(const GetConvertTradeHistoryParams& params) const;

    /// Asynchronous `get_convert_trade_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetConvertTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_convert_trade_history(const GetConvertTradeHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetConvertTradeHistoryResponse>(
            client_, get_convert_trade_history_request(params),
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
    order_status(const OrderStatusParams& params = {}) const;

    /// Asynchronous `order_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderStatusResponse>)`.
    template <class CompletionToken>
    auto async_order_status(const OrderStatusParams& params, CompletionToken&& token) const {
        return common::async_send<OrderStatusResponse>(client_, order_status_request(params),
                                                       std::forward<CompletionToken>(token));
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
    place_limit_order(const PlaceLimitOrderParams& params) const;

    /// Asynchronous `place_limit_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<PlaceLimitOrderResponse>)`.
    template <class CompletionToken>
    auto async_place_limit_order(const PlaceLimitOrderParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<PlaceLimitOrderResponse>(
            client_, place_limit_order_request(params), std::forward<CompletionToken>(token));
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
    query_limit_open_orders(const QueryLimitOpenOrdersParams& params = {}) const;

    /// Asynchronous `query_limit_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryLimitOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_query_limit_open_orders(const QueryLimitOpenOrdersParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<QueryLimitOpenOrdersResponse>(
            client_, query_limit_open_orders_request(params), std::forward<CompletionToken>(token));
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
    send_quote_request(const SendQuoteRequestParams& params) const;

    /// Asynchronous `send_quote_request()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SendQuoteRequestResponse>)`.
    template <class CompletionToken>
    auto async_send_quote_request(const SendQuoteRequestParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<SendQuoteRequestResponse>(
            client_, send_quote_request_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest accept_quote_request(const AcceptQuoteParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_limit_order_request(const CancelLimitOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    get_convert_trade_history_request(const GetConvertTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest order_status_request(const OrderStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    place_limit_order_request(const PlaceLimitOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_limit_open_orders_request(const QueryLimitOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    send_quote_request_request(const SendQuoteRequestParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::convert::rest_api
