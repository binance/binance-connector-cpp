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
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/account_api.hpp>
#include <binance/stocks/rest_api/market_data_api.hpp>
#include <binance/stocks/rest_api/models.hpp>
#include <binance/stocks/rest_api/tokenized_api.hpp>
#include <binance/stocks/rest_api/trade_api.hpp>
#include <binance/stocks/rest_api/user_data_streams_api.hpp>

namespace binance::stocks::rest_api {

/// Stocks REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_STOCKS_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Stocks REST API).
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

    // AccountApi

    /// Sign US Equity Disclaimer (TRADE)
    ///
    /// POST /sapi/v1/equity/account/disclaimer.
    ///
    /// Records the user's acknowledgement and acceptance of the US equity disclaimer. This must be
    /// completed before the account can access certain US equity trading features. The acceptance
    /// is tied to the account associated with the API key.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/account#sign-us-equity-disclaimer
    [[nodiscard]] common::RestApiResponse<SignUsEquityDisclaimerResponse>
    sign_us_equity_disclaimer(const SignUsEquityDisclaimerParams& params = {}) const {
        return account_api_.sign_us_equity_disclaimer(params);
    }
    /// Asynchronous `sign_us_equity_disclaimer()`.
    template <class CompletionToken>
    auto async_sign_us_equity_disclaimer(const SignUsEquityDisclaimerParams& params,
                                         CompletionToken&& token) const {
        return account_api_.async_sign_us_equity_disclaimer(params,
                                                            std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Exchange Info (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/exchangeInfo.
    ///
    /// Returns current exchange trading rules and the list of tradable US-equity symbols.
    /// MARKET_DATA endpoint — requires an API key (`X-MBX-APIKEY`) but no signature. Response is
    /// served from a server-side cache.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#exchange-info
    [[nodiscard]] common::RestApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const {
        return market_data_api_.exchange_info(params);
    }
    /// Asynchronous `exchange_info()`.
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return market_data_api_.async_exchange_info(params, std::forward<CompletionToken>(token));
    }

    /// Latest Quote (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/quote.
    ///
    /// Returns the latest best bid / best ask for a single US-equity ticker. The returned value is
    /// at most ~5 seconds stale. Returns an **empty response body** (not the literal `null`) when
    /// no quote is available for the supplied ticker (e.g. the ticker is unknown, halted, or
    /// de-listed).
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#latest-quote
    [[nodiscard]] common::RestApiResponse<LatestQuoteResponse>
    latest_quote(const LatestQuoteParams& params) const {
        return market_data_api_.latest_quote(params);
    }
    /// Asynchronous `latest_quote()`.
    template <class CompletionToken>
    auto async_latest_quote(const LatestQuoteParams& params, CompletionToken&& token) const {
        return market_data_api_.async_latest_quote(params, std::forward<CompletionToken>(token));
    }

    /// Tokenized Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/tokenized-assets.
    ///
    /// Returns the list of all tokenized assets currently available for mint / redeem, together
    /// with each asset's underlying equity symbol and conversion multiplier. MARKET_DATA endpoint —
    /// requires an API key (`X-MBX-APIKEY`) but no signature. Response is served from a server-side
    /// cache.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#tokenized-assets
    [[nodiscard]] common::RestApiResponse<std::vector<TokenizedAssetsResponseInner>>
    tokenized_assets() const {
        return market_data_api_.tokenized_assets();
    }
    /// Asynchronous `tokenized_assets()`.
    template <class CompletionToken> auto async_tokenized_assets(CompletionToken&& token) const {
        return market_data_api_.async_tokenized_assets(std::forward<CompletionToken>(token));
    }

    // TokenizedApi

    /// Bstocks Corporate Action Records (USER_DATA)
    ///
    /// GET /sapi/v1/bstocks/corp-action.
    ///
    /// Query the asset balance changes caused by corporate actions (for example stock splits and
    /// cash dividends) on the caller's account. Cursor-style pagination — supply the `nextTime` and
    /// `nextId` from the previous page's response as `lastTime` and `lastId` to fetch the next
    /// page. Records are returned in descending order of modification time. This endpoint is
    /// equivalent to `/sapi/v1/equity/corp-action`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#bstocks-corporate-action-records
    [[nodiscard]] common::RestApiResponse<BstocksCorporateActionRecordsResponse>
    bstocks_corporate_action_records(const BstocksCorporateActionRecordsParams& params) const {
        return tokenized_api_.bstocks_corporate_action_records(params);
    }
    /// Asynchronous `bstocks_corporate_action_records()`.
    template <class CompletionToken>
    auto async_bstocks_corporate_action_records(const BstocksCorporateActionRecordsParams& params,
                                                CompletionToken&& token) const {
        return tokenized_api_.async_bstocks_corporate_action_records(
            params, std::forward<CompletionToken>(token));
    }

    /// Corporate Action Records (USER_DATA)
    ///
    /// GET /sapi/v1/equity/corp-action.
    ///
    /// Query the asset balance changes caused by corporate actions (for example stock splits and
    /// cash dividends) on the caller's account. Cursor-style pagination — supply the `nextTime` and
    /// `nextId` from the previous page's response as `lastTime` and `lastId` to fetch the next
    /// page. Records are returned in descending order of modification time. This endpoint is
    /// equivalent to `/sapi/v1/bstocks/corp-action`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#corporate-action-records
    [[nodiscard]] common::RestApiResponse<CorporateActionRecordsResponse>
    corporate_action_records(const CorporateActionRecordsParams& params) const {
        return tokenized_api_.corporate_action_records(params);
    }
    /// Asynchronous `corporate_action_records()`.
    template <class CompletionToken>
    auto async_corporate_action_records(const CorporateActionRecordsParams& params,
                                        CompletionToken&& token) const {
        return tokenized_api_.async_corporate_action_records(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Tokenized Convert History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/tokenized/history.
    ///
    /// Paged history of mint / redeem conversions for the caller. Cursor-style pagination — supply
    /// the `nextLastId` from the previous page's response to fetch the next page.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-convert-history
    [[nodiscard]] common::RestApiResponse<TokenizedConvertHistoryResponse>
    tokenized_convert_history(const TokenizedConvertHistoryParams& params = {}) const {
        return tokenized_api_.tokenized_convert_history(params);
    }
    /// Asynchronous `tokenized_convert_history()`.
    template <class CompletionToken>
    auto async_tokenized_convert_history(const TokenizedConvertHistoryParams& params,
                                         CompletionToken&& token) const {
        return tokenized_api_.async_tokenized_convert_history(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Tokenized Convert Status (USER_DATA)
    ///
    /// GET /sapi/v1/equity/tokenized/convert-status.
    ///
    /// Query the current status of a single mint / redeem request by its `issuerRequestId`. Returns
    /// an empty object when no record matches (caller's ID scope only).
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-convert-status
    [[nodiscard]] common::RestApiResponse<TokenizedConvertStatusResponse>
    tokenized_convert_status(const TokenizedConvertStatusParams& params) const {
        return tokenized_api_.tokenized_convert_status(params);
    }
    /// Asynchronous `tokenized_convert_status()`.
    template <class CompletionToken>
    auto async_tokenized_convert_status(const TokenizedConvertStatusParams& params,
                                        CompletionToken&& token) const {
        return tokenized_api_.async_tokenized_convert_status(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Tokenized Mint (TRADE)
    ///
    /// POST /sapi/v1/equity/tokenized/mint.
    ///
    /// Mint a tokenized asset from an underlying equity holding. The caller's underlying equity
    /// (e.g. `AAPL`) is burned (or locked), and the corresponding tokenized asset (e.g. `AAPLB`) is
    /// credited. The tokenized asset is resolved server-side from `underlyingAsset`; callers only
    /// provide the underlying ticker and quantity. Mint is asynchronous: the endpoint returns an
    /// `issuerRequestId` immediately with a transient status; poll `/tokenized/convert-status` to
    /// observe the terminal state, or inspect `/tokenized/history` for the full record. Rate limit:
    /// 50 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-mint
    [[nodiscard]] common::RestApiResponse<TokenizedMintResponse>
    tokenized_mint(const TokenizedMintParams& params) const {
        return tokenized_api_.tokenized_mint(params);
    }
    /// Asynchronous `tokenized_mint()`.
    template <class CompletionToken>
    auto async_tokenized_mint(const TokenizedMintParams& params, CompletionToken&& token) const {
        return tokenized_api_.async_tokenized_mint(params, std::forward<CompletionToken>(token));
    }

    /// Tokenized Redeem (TRADE)
    ///
    /// POST /sapi/v1/equity/tokenized/redeem.
    ///
    /// Redeem a tokenized asset back into the underlying equity. The caller's tokenized asset (e.g.
    /// `AAPLB`) is burned, and the corresponding underlying equity (e.g. `AAPL`) is released. The
    /// underlying asset is resolved server-side from `tokenizedAsset`; callers only provide the
    /// tokenized asset and quantity. Redeem is asynchronous: the endpoint returns an
    /// `issuerRequestId` immediately with a transient status; poll `/tokenized/convert-status` to
    /// observe the terminal state, or inspect `/tokenized/history` for the full record. Rate limit:
    /// 200 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-redeem
    [[nodiscard]] common::RestApiResponse<TokenizedRedeemResponse>
    tokenized_redeem(const TokenizedRedeemParams& params) const {
        return tokenized_api_.tokenized_redeem(params);
    }
    /// Asynchronous `tokenized_redeem()`.
    template <class CompletionToken>
    auto async_tokenized_redeem(const TokenizedRedeemParams& params,
                                CompletionToken&& token) const {
        return tokenized_api_.async_tokenized_redeem(params, std::forward<CompletionToken>(token));
    }

    // TradeApi

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
    cancel_all_equity_orders(const CancelAllEquityOrdersParams& params = {}) const {
        return trade_api_.cancel_all_equity_orders(params);
    }
    /// Asynchronous `cancel_all_equity_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_equity_orders(const CancelAllEquityOrdersParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_cancel_all_equity_orders(params,
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
    cancel_equity_order(const CancelEquityOrderParams& params) const {
        return trade_api_.cancel_equity_order(params);
    }
    /// Asynchronous `cancel_equity_order()`.
    template <class CompletionToken>
    auto async_cancel_equity_order(const CancelEquityOrderParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_cancel_equity_order(params, std::forward<CompletionToken>(token));
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
    current_open_orders(const CurrentOpenOrdersParams& params = {}) const {
        return trade_api_.current_open_orders(params);
    }
    /// Asynchronous `current_open_orders()`.
    template <class CompletionToken>
    auto async_current_open_orders(const CurrentOpenOrdersParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_current_open_orders(params, std::forward<CompletionToken>(token));
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
    equity_order_detail(const EquityOrderDetailParams& params = {}) const {
        return trade_api_.equity_order_detail(params);
    }
    /// Asynchronous `equity_order_detail()`.
    template <class CompletionToken>
    auto async_equity_order_detail(const EquityOrderDetailParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_equity_order_detail(params, std::forward<CompletionToken>(token));
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
    equity_order_history(const EquityOrderHistoryParams& params) const {
        return trade_api_.equity_order_history(params);
    }
    /// Asynchronous `equity_order_history()`.
    template <class CompletionToken>
    auto async_equity_order_history(const EquityOrderHistoryParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_equity_order_history(params, std::forward<CompletionToken>(token));
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
    equity_trade_history(const EquityTradeHistoryParams& params) const {
        return trade_api_.equity_trade_history(params);
    }
    /// Asynchronous `equity_trade_history()`.
    template <class CompletionToken>
    auto async_equity_trade_history(const EquityTradeHistoryParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_equity_trade_history(params, std::forward<CompletionToken>(token));
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
    place_equity_order(const PlaceEquityOrderParams& params) const {
        return trade_api_.place_equity_order(params);
    }
    /// Asynchronous `place_equity_order()`.
    template <class CompletionToken>
    auto async_place_equity_order(const PlaceEquityOrderParams& params,
                                  CompletionToken&& token) const {
        return trade_api_.async_place_equity_order(params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Create / Renew Listen Key (USER_STREAM)
    ///
    /// POST /sapi/v1/equity/listenKey.
    ///
    /// Create a new stock user-data-stream `listenKey`, or renew an existing one. Calling this
    /// endpoint for the same user with an active `listenKey` extends its validity; if there is no
    /// active key, a new one is issued. Use the returned `listenKey` to subscribe to the stock user
    /// data stream.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/user-data-streams#create-renew-listen-key
    [[nodiscard]] common::RestApiResponse<CreateRenewListenKeyResponse>
    create_renew_listen_key(const CreateRenewListenKeyParams& params = {}) const {
        return user_data_streams_api_.create_renew_listen_key(params);
    }
    /// Asynchronous `create_renew_listen_key()`.
    template <class CompletionToken>
    auto async_create_renew_listen_key(const CreateRenewListenKeyParams& params,
                                       CompletionToken&& token) const {
        return user_data_streams_api_.async_create_renew_listen_key(
            params, std::forward<CompletionToken>(token));
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
    AccountApi account_api_;
    MarketDataApi market_data_api_;
    TokenizedApi tokenized_api_;
    TradeApi trade_api_;
    UserDataStreamsApi user_data_streams_api_;
};

} // namespace binance::stocks::rest_api
