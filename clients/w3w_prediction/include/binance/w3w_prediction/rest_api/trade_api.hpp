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
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_cancel_info_list_parameter_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quote_response.hpp>
#include <binance/w3w_prediction/rest_api/models/place_order_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_active_orders_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_history_response.hpp>

namespace binance::w3w_prediction::rest_api {

enum class GetQuoteSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(GetQuoteSideEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT GetQuoteSideEnum
tag_invoke(boost::json::value_to_tag<GetQuoteSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, GetQuoteSideEnum value);

enum class GetQuoteOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(GetQuoteOrderTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT GetQuoteOrderTypeEnum
tag_invoke(boost::json::value_to_tag<GetQuoteOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, GetQuoteOrderTypeEnum value);

enum class GetQuoteFundingSourceEnum {
    Mpc,
    Cex,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(GetQuoteFundingSourceEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT GetQuoteFundingSourceEnum tag_invoke(
    boost::json::value_to_tag<GetQuoteFundingSourceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              GetQuoteFundingSourceEnum value);

enum class PlaceOrderAccountTypeEnum {
    Spot,
    Funding,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(PlaceOrderAccountTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT PlaceOrderAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceOrderAccountTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              PlaceOrderAccountTypeEnum value);

enum class PlaceOrderOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(PlaceOrderOrderTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT PlaceOrderOrderTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceOrderOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              PlaceOrderOrderTypeEnum value);

enum class PlaceOrderFundingSourceEnum {
    Mpc,
    Cex,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(PlaceOrderFundingSourceEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT PlaceOrderFundingSourceEnum tag_invoke(
    boost::json::value_to_tag<PlaceOrderFundingSourceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              PlaceOrderFundingSourceEnum value);

enum class QueryActiveOrdersTradeSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(QueryActiveOrdersTradeSideEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT QueryActiveOrdersTradeSideEnum
tag_invoke(boost::json::value_to_tag<QueryActiveOrdersTradeSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryActiveOrdersTradeSideEnum value);

enum class QueryOrderHistoryOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(QueryOrderHistoryOrderTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT QueryOrderHistoryOrderTypeEnum
tag_invoke(boost::json::value_to_tag<QueryOrderHistoryOrderTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryOrderHistoryOrderTypeEnum value);

struct BatchCancelOrdersParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Wallet ID
    common::Required<std::string> wallet_id;
    /// List of orders to cancel (index `i` starts from 0)
    std::optional<std::vector<BatchCancelOrdersCancelInfoListParameterInner>> cancel_info_list =
        std::nullopt;
};

struct GetQuoteParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Prediction outcome token ID
    common::Required<std::string> token_id;
    /// Trade direction. Enum: `BUY`, `SELL`
    common::Required<GetQuoteSideEnum> side;
    /// Input amount in wei (18 decimals). Must be > 0. The minimum is set by the server and may
    /// change, see the response notes. Example: `1000000000000000000` = 1 USDT
    common::Required<std::string> amount_in;
    /// Order type. Enum: `MARKET`, `LIMIT`
    common::Required<GetQuoteOrderTypeEnum> order_type;
    /// Slippage tolerance in basis points. Range 1–10000
    common::Required<std::int64_t> slippage_bps;
    /// Limit price. Required when `orderType=LIMIT`. Must be > 0. A price that is not on the price
    /// tick of the market (see `decimalPrecision` in Get Market Detail) is truncated down instead
    /// of being rejected, unless the result is 0
    std::optional<std::string> price_limit = std::nullopt;
    /// Chain ID. Default `56` (BSC)
    std::optional<std::string> chain_id = std::nullopt;
    /// Fee rate in basis points. Default `200`, range 1–10000
    std::optional<std::int64_t> fee_rate_bps = std::nullopt;
    /// Funding source. Enum: `MPC`, `CEX`. Default `MPC`
    std::optional<GetQuoteFundingSourceEnum> funding_source = std::nullopt;
    /// Auto-transfer amount before order (wei). Must be > 0 if provided
    std::optional<std::string> fund_transfer_amount = std::nullopt;
};

struct PlaceOrderParams {
    /// User's prediction wallet address. Must be a valid address owned by the calling UID — a
    /// well-formed address not owned by the UID and a malformed (non-address) value both return the
    /// same generic `-3026`. An empty string instead returns `-1102` naming the field.
    common::Required<std::string> wallet_address;
    /// Wallet ID
    common::Required<std::string> wallet_id;
    /// Quote ID obtained from `Get Quote`
    common::Required<std::string> quote_id;
    /// Must match `orderType`: `FOK` for `MARKET`, `GTC` for `LIMIT`
    common::Required<std::string> time_in_force;
    /// Payment account type. Enum: `SPOT`, `FUNDING`. This only determines the settlement/reference
    /// account — it does not control which balance is debited. See `fundingSource` below for that.
    common::Required<PlaceOrderAccountTypeEnum> account_type;
    /// Order type. Enum: `MARKET`, `LIMIT` only. Do not combine with `timeInForce` (e.g.
    /// `LIMIT_GTC` is not a valid value) — set `timeInForce` separately per the Validation Rules
    /// table below.
    common::Required<PlaceOrderOrderTypeEnum> order_type;
    /// Slippage tolerance in basis points. Range 1–10000
    common::Required<std::int64_t> slippage_bps;
    /// Limit price. Required when `orderType=LIMIT`, must be > 0. Omitting it when
    /// `orderType=LIMIT` returns a generic `-3026` (no field name in the message).
    std::optional<std::string> price_limit = std::nullopt;
    /// Funding source. Enum: `MPC`, `CEX`. Default `MPC`. This determines which balance is actually
    /// debited, independent of `accountType`.
    std::optional<PlaceOrderFundingSourceEnum> funding_source = std::nullopt;
    /// Auto-transfer amount before order (wei). Must be > 0 if provided
    std::optional<std::string> fund_transfer_amount = std::nullopt;
};

struct QueryActiveOrdersParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Filter by trade side. Enum: `BUY`, `SELL`
    std::optional<QueryActiveOrdersTradeSideEnum> trade_side = std::nullopt;
    /// Filter by level-1 category
    std::optional<std::string> l1_category = std::nullopt;
    /// Filter by market ID
    std::optional<std::int64_t> market_id = std::nullopt;
    /// Pagination offset. Default `0`
    std::optional<std::int64_t> offset = std::nullopt;
    /// Page size. Default `20`, range 1–100
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOrderHistoryParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Filter by level-1 category
    std::optional<std::string> l1_category = std::nullopt;
    /// Filter by order type. Enum: `MARKET`, `LIMIT`
    std::optional<QueryOrderHistoryOrderTypeEnum> order_type = std::nullopt;
    /// Filter by order status
    std::optional<std::string> status = std::nullopt;
    /// Start date. Format: `yyyy-MM-dd`. Must be ≤ `endDate`
    std::optional<std::string> start_date = std::nullopt;
    /// End date. Format: `yyyy-MM-dd`. Must be ≥ `startDate`
    std::optional<std::string> end_date = std::nullopt;
    /// Pagination offset. Default `0`
    std::optional<std::int64_t> offset = std::nullopt;
    /// Page size. Default `20`, range 1–100
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_W3W_PREDICTION_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Batch Cancel Orders (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/trade/batch-cancel.
    ///
    /// Cancel one or more active prediction orders in a single request. Requires SAS authorization.
    ///
    /// **Known Issue — Bracket Encoding Incompatibility:**
    /// This endpoint uses indexed bracket notation (`cancelInfoList[0].orderId`). Binance SAPI
    /// signature verification runs over the **raw, unencoded** canonical string. However,
    /// mainstream HTTP libraries (Python `requests`, Java `HttpURLConnection`/`URI`, Go `net/url`,
    /// Node.js `url`) automatically percent-encode `[` → `%5B` and `]` → `%5D`, producing a
    /// signature mismatch with error `-1022 Signature for this request is not valid`. Postman is
    /// unaffected because it does not encode keys.
    ///
    /// **Workarounds** (use low-level HTTP APIs that do not normalize URLs):
    /// - **Python:** use `http.client` (stdlib) and hand-build the body string.
    /// - **Java:** use `HttpURLConnection` and write the raw body bytes directly.
    /// - **Go:** use `strings.NewReader` with a hand-built body instead of `url.Values.Encode()`.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Use dot notation for nested list fields: `cancelInfoList[0].orderId`,
    /// `cancelInfoList[1].orderId`, etc.
    /// - `vendor` does not need to be supplied. The server automatically sets the correct vendor
    /// (`predict_fun`) for every item in the batch.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/trade#batch-cancel-orders
    [[nodiscard]] common::RestApiResponse<BatchCancelOrdersResponse>
    batch_cancel_orders(const BatchCancelOrdersParams& params) const;

    /// Asynchronous `batch_cancel_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<BatchCancelOrdersResponse>)`.
    template <class CompletionToken>
    auto async_batch_cancel_orders(const BatchCancelOrdersParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<BatchCancelOrdersResponse>(
            client_, batch_cancel_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Quote (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/trade/get-quote.
    ///
    /// Get a price quote for a prediction order. The returned `quoteId` must be used in the
    /// subsequent Place Order request.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Response Notes:
    /// - `feeAmount` is a string because it is denominated in wei (18 decimals) and may exceed
    /// JavaScript's safe integer range. `feeDiscountBps` is also a string to allow fractional
    /// basis-point values in the future. `feeRateBps` and `slippageBps` are integers and will never
    /// exceed safe integer bounds.
    /// - **Minimum order amount:** The minimum order amount is set by the server and the upstream
    /// market rules and may change, so no fixed value is documented. `BUY` orders are checked by
    /// amount (`amountIn`) and `SELL` orders by share quantity, for both `MARKET` and `LIMIT`
    /// orders. If the `amountIn` of a `BUY` order is below the minimum, the server returns `-9000`
    /// with the message `Your order amount is too small`. A successful quote does not guarantee
    /// that the order is accepted or filled, so check the error message and the final order status.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/trade#get-quote
    [[nodiscard]] common::RestApiResponse<GetQuoteResponse>
    get_quote(const GetQuoteParams& params) const;

    /// Asynchronous `get_quote()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetQuoteResponse>)`.
    template <class CompletionToken>
    auto async_get_quote(const GetQuoteParams& params, CompletionToken&& token) const {
        return common::async_send<GetQuoteResponse>(client_, get_quote_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Place Order (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/trade/place-order-bundle.
    ///
    /// Place a prediction order using a previously obtained quote. Requires SAS authorization.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Validation rules:
    ///
    ///   | orderType | timeInForce   | priceLimit            |
    ///   | --------- | ------------- | --------------------- |
    ///   | `MARKET`  | Must be `FOK` | Not required          |
    ///   | `LIMIT`   | Must be `GTC` | Required, must be > 0 |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/trade#place-order
    [[nodiscard]] common::RestApiResponse<PlaceOrderResponse>
    place_order(const PlaceOrderParams& params) const;

    /// Asynchronous `place_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<PlaceOrderResponse>)`.
    template <class CompletionToken>
    auto async_place_order(const PlaceOrderParams& params, CompletionToken&& token) const {
        return common::async_send<PlaceOrderResponse>(client_, place_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Query Active Orders (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/order/list.
    ///
    /// Get active (open) prediction orders for the authenticated user.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/trade#query-active-orders
    [[nodiscard]] common::RestApiResponse<QueryActiveOrdersResponse>
    query_active_orders(const QueryActiveOrdersParams& params) const;

    /// Asynchronous `query_active_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryActiveOrdersResponse>)`.
    template <class CompletionToken>
    auto async_query_active_orders(const QueryActiveOrdersParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<QueryActiveOrdersResponse>(
            client_, query_active_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Order History (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/order/history.
    ///
    /// Get historical prediction orders (all statuses) for the authenticated user, with optional
    /// filters.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/trade#query-order-history
    [[nodiscard]] common::RestApiResponse<QueryOrderHistoryResponse>
    query_order_history(const QueryOrderHistoryParams& params) const;

    /// Asynchronous `query_order_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_order_history(const QueryOrderHistoryParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<QueryOrderHistoryResponse>(
            client_, query_order_history_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    batch_cancel_orders_request(const BatchCancelOrdersParams& params) const;
    [[nodiscard]] common::RestRequest get_quote_request(const GetQuoteParams& params) const;
    [[nodiscard]] common::RestRequest place_order_request(const PlaceOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_active_orders_request(const QueryActiveOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_order_history_request(const QueryOrderHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
