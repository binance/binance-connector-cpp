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
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/cancel_all_equity_orders_response.hpp>
#include <binance/stocks/rest_api/models/cancel_equity_order_response.hpp>
#include <binance/stocks/rest_api/models/current_open_orders_response_inner.hpp>
#include <binance/stocks/rest_api/models/equity_order_detail_response.hpp>
#include <binance/stocks/rest_api/models/equity_order_history_response.hpp>
#include <binance/stocks/rest_api/models/equity_trade_history_response.hpp>
#include <binance/stocks/rest_api/models/place_equity_order_response.hpp>

namespace binance::stocks::rest_api {

enum class EquityOrderHistoryOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(EquityOrderHistoryOrderTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT EquityOrderHistoryOrderTypeEnum
tag_invoke(boost::json::value_to_tag<EquityOrderHistoryOrderTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      EquityOrderHistoryOrderTypeEnum value);

enum class EquityOrderHistorySideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(EquityOrderHistorySideEnum value) noexcept;
BINANCE_STOCKS_EXPORT EquityOrderHistorySideEnum tag_invoke(
    boost::json::value_to_tag<EquityOrderHistorySideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      EquityOrderHistorySideEnum value);

enum class EquityTradeHistorySideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(EquityTradeHistorySideEnum value) noexcept;
BINANCE_STOCKS_EXPORT EquityTradeHistorySideEnum tag_invoke(
    boost::json::value_to_tag<EquityTradeHistorySideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      EquityTradeHistorySideEnum value);

enum class PlaceEquityOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderSideEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderSideEnum tag_invoke(
    boost::json::value_to_tag<PlaceEquityOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderSideEnum value);

enum class PlaceEquityOrderOrderTypeEnum {
    Market,
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderOrderTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderOrderTypeEnum tag_invoke(
    boost::json::value_to_tag<PlaceEquityOrderOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderOrderTypeEnum value);

enum class PlaceEquityOrderTimeInForceEnum {
    Day,
    Gtc,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderTimeInForceEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderTimeInForceEnum value);

enum class PlaceEquityOrderTradingSessionEnum {
    Rth,
    Extended,
    TradingSession24H,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderTradingSessionEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderTradingSessionEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTradingSessionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderTradingSessionEnum value);

enum class PlaceEquityOrderWalletTypeEnum {
    Card,
    Main,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderWalletTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderWalletTypeEnum value);

enum class PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum {
    Main,
    Card,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum value);

struct CancelAllEquityOrdersParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelEquityOrderParams {
    /// Equity order id returned by `/order/place` or a query endpoint.
    common::Required<std::string> order_id;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CurrentOpenOrdersParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EquityOrderDetailParams {
    /// Equity order id. Either `orderId` or `clientOrderId` must be provided.
    std::optional<std::string> order_id = std::nullopt;
    /// Client-supplied order id. Either `orderId` or `clientOrderId` must be provided.
    std::optional<std::string> client_order_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EquityOrderHistoryParams {
    /// Start time (ms epoch).
    common::Required<std::int64_t> start_time;
    /// End time (ms epoch).
    common::Required<std::int64_t> end_time;
    /// US-equity ticker filter, e.g. `NVDA`.
    std::optional<std::string> symbol = std::nullopt;
    /// Order type filter: `MARKET` / `LIMIT`.
    std::optional<EquityOrderHistoryOrderTypeEnum> order_type = std::nullopt;
    /// Side filter: `BUY` / `SELL`.
    std::optional<EquityOrderHistorySideEnum> side = std::nullopt;
    /// Comma-separated status filter. Allowed values: `FILLED`, `PARTIALLY_FILLED`, `CANCELED`,
    /// `EXPIRED`, `REJECTED`.
    std::optional<std::string> order_status = std::nullopt;
    /// Page number, 1-based. Default `1`.
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EquityTradeHistoryParams {
    /// Start time (ms epoch).
    common::Required<std::int64_t> start_time;
    /// End time (ms epoch).
    common::Required<std::int64_t> end_time;
    /// US-equity ticker filter, e.g. `NVDA`.
    std::optional<std::string> symbol = std::nullopt;
    /// Side filter: `BUY` / `SELL`.
    std::optional<EquityTradeHistorySideEnum> side = std::nullopt;
    /// Narrow the result to executions of a single order.
    std::optional<std::string> order_id = std::nullopt;
    /// Page number, 1-based. Default `1`.
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PlaceEquityOrderParams {
    /// US stock ticker, e.g. `AAPL`, `TSLA`. Must be a tradable US-equity symbol — verify via
    /// `/sapi/v1/equity/market/exchangeInfo`. Tokenization enablement (verifiable via
    /// `/sapi/v1/equity/market/tokenized-assets`) is *not* required; non-tokenized symbols are
    /// accepted and settle as traditional underlying-equity trades. The `tokenize` parameter only
    /// takes effect on tokenization-enabled symbols and is silently ignored otherwise.
    common::Required<std::string> symbol;
    /// `BUY` / `SELL`.
    common::Required<PlaceEquityOrderSideEnum> side;
    /// `MARKET` / `LIMIT`.
    common::Required<PlaceEquityOrderOrderTypeEnum> order_type;
    /// Quote asset. Defaults to `USDC`; must be within the server's allowed set.
    std::optional<std::string> quote_asset = std::nullopt;
    /// **Required** for `LIMIT`; **forbidden** for `MARKET`. Maximum 2 decimal places.
    std::optional<std::string> price = std::nullopt;
    /// **Required** for `LIMIT` (both sides) and `SELL MARKET`; **forbidden** for `BUY MARKET`.
    std::optional<std::string> quantity = std::nullopt;
    /// **Required** for `BUY MARKET`; **forbidden** for `LIMIT` and `SELL MARKET`.
    std::optional<std::string> notional = std::nullopt;
    /// `DAY` (default) / `GTC`. `GTC` is only supported for `LIMIT` orders; a fractional-share
    /// `GTC` order must be paired with `tradingSession = EXTENDED` or `24H`.
    std::optional<PlaceEquityOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// `RTH` / `EXTENDED` / `24H`. **Required** for `LIMIT`; **forbidden** for `MARKET`.
    std::optional<PlaceEquityOrderTradingSessionEnum> trading_session = std::nullopt;
    /// Payment wallet for `BUY` orders: `CARD` (default) / `MAIN`. `SELL` orders always settle to
    /// `CARD`.
    std::optional<PlaceEquityOrderWalletTypeEnum> wallet_type = std::nullopt;
    /// Client-supplied order id. Format `^[a-zA-Z0-9-_]{32,36}$`. Auto-generated when omitted.
    std::optional<std::string> client_order_id = std::nullopt;
    /// Whether to tokenize the purchased stock asset upon settlement. Default `true`. Only takes
    /// effect when the symbol is tokenization-enabled (check via `/market/tokenized-assets`);
    /// silently ignored for non-tokenized symbols, which always settle as traditional
    /// underlying-equity trades.
    std::optional<bool> tokenize = std::nullopt;
    /// Wallet that receives the tokenized asset minted after the order fills. `MAIN` = Spot wallet,
    /// `CARD` = Funding wallet. Default `CARD`. Only applies when `side` = `BUY` and `tokenize` =
    /// `true`; ignored for `SELL` or `tokenize` = `false`. If `MAIN` is sent while Spot wallet
    /// settlement is not enabled, the request is rejected as an illegal parameter.
    std::optional<PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum>
        tokenized_asset_settle_wallet_type = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCKS_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Cancel All Equity Orders (TRADE)
    ///
    /// POST /sapi/v1/equity/order/cancel-all.
    ///
    /// Cancel all open orders for the caller. No request body is required — the scope is all of the
    /// caller's open orders. The downstream service handles idempotency; to inspect per-order
    /// outcomes, query `/order/history` after the call.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#cancel-all-equity-orders
    [[nodiscard]] common::RestApiResponse<CancelAllEquityOrdersResponse>
    cancel_all_equity_orders(const CancelAllEquityOrdersParams& params = {}) const;

    /// Asynchronous `cancel_all_equity_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllEquityOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_equity_orders(const CancelAllEquityOrdersParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<CancelAllEquityOrdersResponse>(
            client_, cancel_all_equity_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Equity Order (TRADE)
    ///
    /// POST /sapi/v1/equity/order/cancel.
    ///
    /// Cancel a single open order by its `orderId`.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#cancel-equity-order
    [[nodiscard]] common::RestApiResponse<CancelEquityOrderResponse>
    cancel_equity_order(const CancelEquityOrderParams& params) const;

    /// Asynchronous `cancel_equity_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelEquityOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_equity_order(const CancelEquityOrderParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<CancelEquityOrderResponse>(
            client_, cancel_equity_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Current Open Orders (USER_DATA)
    ///
    /// GET /sapi/v1/equity/order/open-orders.
    ///
    /// Query all unfinished (open) orders for the caller. No business parameters are needed — user
    /// identity is derived from the signature.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#current-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentOpenOrdersResponseInner>>
    current_open_orders(const CurrentOpenOrdersParams& params = {}) const;

    /// Asynchronous `current_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CurrentOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_current_open_orders(const CurrentOpenOrdersParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<CurrentOpenOrdersResponseInner>>(
            client_, current_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Equity Order Detail (USER_DATA)
    ///
    /// GET /sapi/v1/equity/order/detail.
    ///
    /// Returns a single order along with its trade execution list. Callers can only read their own
    /// orders — the user identity is derived from the signed request.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#equity-order-detail
    [[nodiscard]] common::RestApiResponse<EquityOrderDetailResponse>
    equity_order_detail(const EquityOrderDetailParams& params = {}) const;

    /// Asynchronous `equity_order_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EquityOrderDetailResponse>)`.
    template <class CompletionToken>
    auto async_equity_order_detail(const EquityOrderDetailParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<EquityOrderDetailResponse>(
            client_, equity_order_detail_request(params), std::forward<CompletionToken>(token));
    }

    /// Equity Order History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/order/history.
    ///
    /// Paged order history for the caller. Filters by symbol, order type, side, status, and time
    /// range.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#equity-order-history
    [[nodiscard]] common::RestApiResponse<EquityOrderHistoryResponse>
    equity_order_history(const EquityOrderHistoryParams& params) const;

    /// Asynchronous `equity_order_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EquityOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_equity_order_history(const EquityOrderHistoryParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<EquityOrderHistoryResponse>(
            client_, equity_order_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Equity Trade History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/trade/history.
    ///
    /// Paged equity trade (per-fill) history for the caller. Each row is one execution, not one
    /// order — a partially filled order produces multiple rows. Filters by symbol, side, specific
    /// `orderId`, and time range.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#equity-trade-history
    [[nodiscard]] common::RestApiResponse<EquityTradeHistoryResponse>
    equity_trade_history(const EquityTradeHistoryParams& params) const;

    /// Asynchronous `equity_trade_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<EquityTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_equity_trade_history(const EquityTradeHistoryParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<EquityTradeHistoryResponse>(
            client_, equity_trade_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Place Equity Order (TRADE)
    ///
    /// POST /sapi/v1/equity/order/place.
    ///
    /// Place a new equity order. Supports all combinations of `LIMIT` /
    /// `MARKET` × `BUY` / `SELL`. For `LIMIT BUY` orders the commission fee is
    /// automatically computed and reserved by the server at placement time —
    /// callers submit `price` and `quantity` only, no `fee` field is required.
    ///
    /// **Field combination matrix**
    ///
    /// | Side | OrderType | Required | Forbidden |
    /// | ---- | --------- | -------- | --------- |
    /// | BUY | LIMIT | `price`, `quantity`, `tradingSession` | `notional` |
    /// | BUY | MARKET | `notional` | `price`, `quantity`, `tradingSession` |
    /// | SELL | LIMIT | `price`, `quantity`, `tradingSession` | `notional` |
    /// | SELL | MARKET | `quantity` | `price`, `notional`, `tradingSession` |
    ///
    /// **Fractional shares**: when `quantity` has a decimal component, or an
    /// order is placed by `notional`, it is treated as a fractional-share
    /// order. A fractional-share `GTC` order must be paired with
    /// `tradingSession = EXTENDED` or `24H`.
    ///
    /// Rate limit: 200 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/trade#place-equity-order
    [[nodiscard]] common::RestApiResponse<PlaceEquityOrderResponse>
    place_equity_order(const PlaceEquityOrderParams& params) const;

    /// Asynchronous `place_equity_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<PlaceEquityOrderResponse>)`.
    template <class CompletionToken>
    auto async_place_equity_order(const PlaceEquityOrderParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<PlaceEquityOrderResponse>(
            client_, place_equity_order_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    cancel_all_equity_orders_request(const CancelAllEquityOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_equity_order_request(const CancelEquityOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    current_open_orders_request(const CurrentOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    equity_order_detail_request(const EquityOrderDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    equity_order_history_request(const EquityOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    equity_trade_history_request(const EquityTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    place_equity_order_request(const PlaceEquityOrderParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stocks::rest_api
