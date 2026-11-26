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
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/market_data_api.hpp>
#include <binance/w3w_prediction/rest_api/models.hpp>
#include <binance/w3w_prediction/rest_api/otc_api.hpp>
#include <binance/w3w_prediction/rest_api/position_api.hpp>
#include <binance/w3w_prediction/rest_api/redeem_api.hpp>
#include <binance/w3w_prediction/rest_api/trade_api.hpp>
#include <binance/w3w_prediction/rest_api/transfer_api.hpp>
#include <binance/w3w_prediction/rest_api/wallet_api.hpp>

namespace binance::w3w_prediction::rest_api {

/// W3WPrediction REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_W3W_PREDICTION_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (W3w Prediction REST API).
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

    /// Get Market Detail
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/market/detail.
    ///
    /// Get full details for a specific prediction market topic, including variant data and
    /// timeline.
    ///
    /// Weight(IP): 1
    ///
    /// Response Notes:
    /// - `status` is a case-sensitive string. `REGISTERED`: registered and not yet resolved, this
    /// value alone does not guarantee that trading is available. `RESOLVED`: the outcome has been
    /// determined, it does not mean that the user has already claimed the payout. `PAUSED`: trading
    /// is temporarily suspended and may resume. `CLOSED`: closed for display, for example the end
    /// time has passed or the market was removed, it does not guarantee that trading is closed.
    /// - `markets[].tradingStatus` shows whether new orders may be attempted. `OPEN`: new orders
    /// may be attempted, this is the only value that allows new orders. `MATCHING_NOT_ENABLED`:
    /// order matching is not enabled. `CANCEL_ONLY`: only cancellation is allowed. `CLOSED`:
    /// trading has stopped. Use `markets[].tradingStatus`, not `status`, to decide whether to place
    /// an order, because a market whose `status` is `CLOSED` can still have `tradingStatus` `OPEN`.
    /// A topic can contain several markets and an order is placed on one market, so only the
    /// `tradingStatus` of that market matters. A successful quote does not guarantee that an order
    /// is accepted or filled.
    /// - `outcomes[].winner` is returned only after the market is resolved. There is no separate
    /// cancelled, invalid or refunded status. A resolved market can pay more than one outcome, in
    /// that case several outcomes have `winner` set to `true` and `price` is the settled value per
    /// share, for example `0.5` for each of two outcomes.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#get-market-detail
    [[nodiscard]] common::RestApiResponse<GetMarketDetailResponse>
    get_market_detail(const GetMarketDetailParams& params) const {
        return market_data_api_.get_market_detail(params);
    }
    /// Asynchronous `get_market_detail()`.
    template <class CompletionToken>
    auto async_get_market_detail(const GetMarketDetailParams& params,
                                 CompletionToken&& token) const {
        return market_data_api_.async_get_market_detail(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// List Prediction Categories
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/category/list.
    ///
    /// Get all available prediction market categories (L1 and L2).
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#list-prediction-categories
    [[nodiscard]] common::RestApiResponse<ListPredictionCategoriesResponse>
    list_prediction_categories() const {
        return market_data_api_.list_prediction_categories();
    }
    /// Asynchronous `list_prediction_categories()`.
    template <class CompletionToken>
    auto async_list_prediction_categories(CompletionToken&& token) const {
        return market_data_api_.async_list_prediction_categories(
            std::forward<CompletionToken>(token));
    }

    /// List Prediction Markets
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/market/list.
    ///
    /// Get a paginated list of prediction market topics, with optional category and sort filters.
    ///
    /// Weight(IP): 1
    ///
    /// Response Notes:
    /// - For the values of `status` and `markets[].tradingStatus`, see Get Market Detail.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#list-prediction-markets
    [[nodiscard]] common::RestApiResponse<ListPredictionMarketsResponse>
    list_prediction_markets(const ListPredictionMarketsParams& params = {}) const {
        return market_data_api_.list_prediction_markets(params);
    }
    /// Asynchronous `list_prediction_markets()`.
    template <class CompletionToken>
    auto async_list_prediction_markets(const ListPredictionMarketsParams& params,
                                       CompletionToken&& token) const {
        return market_data_api_.async_list_prediction_markets(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Market Search
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/market/search.
    ///
    /// Semantic search for prediction market topics by keyword.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#market-search
    [[nodiscard]] common::RestApiResponse<std::vector<MarketSearchResponseInner>>
    market_search(const MarketSearchParams& params) const {
        return market_data_api_.market_search(params);
    }
    /// Asynchronous `market_search()`.
    template <class CompletionToken>
    auto async_market_search(const MarketSearchParams& params, CompletionToken&& token) const {
        return market_data_api_.async_market_search(params, std::forward<CompletionToken>(token));
    }

    /// Query Last Trade Price
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/order-book/last-trade-price.
    ///
    /// Get the most recent trade price for a prediction market.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#query-last-trade-price
    [[nodiscard]] common::RestApiResponse<QueryLastTradePriceResponse>
    query_last_trade_price(const QueryLastTradePriceParams& params) const {
        return market_data_api_.query_last_trade_price(params);
    }
    /// Asynchronous `query_last_trade_price()`.
    template <class CompletionToken>
    auto async_query_last_trade_price(const QueryLastTradePriceParams& params,
                                      CompletionToken&& token) const {
        return market_data_api_.async_query_last_trade_price(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Query Order Book
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/order-book.
    ///
    /// Get the current order book (bids and asks) for a specific prediction market outcome token.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/market-data#query-order-book
    [[nodiscard]] common::RestApiResponse<QueryOrderBookResponse>
    query_order_book(const QueryOrderBookParams& params) const {
        return market_data_api_.query_order_book(params);
    }
    /// Asynchronous `query_order_book()`.
    template <class CompletionToken>
    auto async_query_order_book(const QueryOrderBookParams& params, CompletionToken&& token) const {
        return market_data_api_.async_query_order_book(params,
                                                       std::forward<CompletionToken>(token));
    }

    // OtcApi

    /// Create OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/create.
    ///
    /// Create an OTC blocktrade as the maker (BID to buy outcome shares with USDT, or ASK to sell
    /// outcome shares for USDT). The maker wallet is resolved server-side by `userId`; signing is
    /// done server-side via SAS `typedDataSign`. Returns `orderId` and a one-time `secretToken` to
    /// share out-of-band with the intended taker.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - Side & Amount Rules:
    ///
    ///   | side   | makerAmount   | takerAmount   |
    ///   | ------ | ------------- | ------------- |
    ///   | `BUY`  | USDT (wei)    | shares (wei)  |
    ///   | `SELL` | shares (wei)  | USDT (wei)    |
    /// - "Note on `side` encoding: this request uses a string enum (`BUY`/`SELL`). Responses from
    /// Get Blocktrade Detail / Preview / List return `side` as an integer and also include a
    /// `quoteType` string — both encode the same concept."
    ///
    ///   | Request `side` | Response `side` (Integer) | Response `quoteType` |
    ///   | --------------- | -------------------------- | ---------------------- |
    ///   | `BUY`           | `0`                         | `"Bid"`                |
    ///   | `SELL`          | `1`                         | `"Ask"`                |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#create-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<CreateOtcBlocktradeResponse>
    create_otc_blocktrade(const CreateOtcBlocktradeParams& params) const {
        return otc_api_.create_otc_blocktrade(params);
    }
    /// Asynchronous `create_otc_blocktrade()`.
    template <class CompletionToken>
    auto async_create_otc_blocktrade(const CreateOtcBlocktradeParams& params,
                                     CompletionToken&& token) const {
        return otc_api_.async_create_otc_blocktrade(params, std::forward<CompletionToken>(token));
    }

    /// Fulfil OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/fulfil.
    ///
    /// Fulfil an open maker blocktrade as the taker, using the `secretToken` the maker shared
    /// out-of-band. All-or-nothing fill (no partial fill); the taker order is the server-derived
    /// symmetric inverse of the maker order.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#fulfil-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<FulfilOtcBlocktradeResponse>
    fulfil_otc_blocktrade(const FulfilOtcBlocktradeParams& params) const {
        return otc_api_.fulfil_otc_blocktrade(params);
    }
    /// Asynchronous `fulfil_otc_blocktrade()`.
    template <class CompletionToken>
    auto async_fulfil_otc_blocktrade(const FulfilOtcBlocktradeParams& params,
                                     CompletionToken&& token) const {
        return otc_api_.async_fulfil_otc_blocktrade(params, std::forward<CompletionToken>(token));
    }

    /// Get OTC Blocktrade Detail (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/detail.
    ///
    /// Query the maker's own blocktrade by `orderId`. Returns full order data including status and
    /// `secretToken`.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-blocktrade-detail
    [[nodiscard]] common::RestApiResponse<GetOtcBlocktradeDetailResponse>
    get_otc_blocktrade_detail(const GetOtcBlocktradeDetailParams& params) const {
        return otc_api_.get_otc_blocktrade_detail(params);
    }
    /// Asynchronous `get_otc_blocktrade_detail()`.
    template <class CompletionToken>
    auto async_get_otc_blocktrade_detail(const GetOtcBlocktradeDetailParams& params,
                                         CompletionToken&& token) const {
        return otc_api_.async_get_otc_blocktrade_detail(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get OTC Blocktrade Events (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/events.
    ///
    /// Paginated feed of blocktrade lifecycle and settlement events (CREATE, FULFIL, MATCH_SUBMIT,
    /// MATCH_SUCCESS, EXPIRE, FAILED, etc.).
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-blocktrade-events
    [[nodiscard]] common::RestApiResponse<GetOtcBlocktradeEventsResponse>
    get_otc_blocktrade_events(const GetOtcBlocktradeEventsParams& params = {}) const {
        return otc_api_.get_otc_blocktrade_events(params);
    }
    /// Asynchronous `get_otc_blocktrade_events()`.
    template <class CompletionToken>
    auto async_get_otc_blocktrade_events(const GetOtcBlocktradeEventsParams& params,
                                         CompletionToken&& token) const {
        return otc_api_.async_get_otc_blocktrade_events(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// Get OTC Reserved Balances (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/reserved-balances.
    ///
    /// Query PredictFun reserved balances for the caller's bound wallet — these are funds locked by
    /// the caller's open OTC blocktrade orders (maker BID locks USDT, maker ASK locks shares). Not
    /// tied to a specific blocktrade id; the path nesting under `otc/blocktrade` reflects the cause
    /// of the lock, not a per-order query. Returns one entry per requested asset, aligned with the
    /// request order. Pass `{type:"USDT"}` for reserved USDT, or `{type:"SHARE", tokenId:"..."}`
    /// for a specific outcome token's reserved shares.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - AssetQuery:
    ///
    ///   | Name    | Type   | Mandatory | Description |
    ///   | ------- | ------ | --------- | ----------- |
    ///   | type    | STRING | YES       | Asset type. Enum: `USDT`, `SHARE` |
    ///   | tokenId | STRING | NO        | Outcome token id (present for `SHARE` entries only) |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-reserved-balances
    [[nodiscard]] common::RestApiResponse<GetOtcReservedBalancesResponse>
    get_otc_reserved_balances(const GetOtcReservedBalancesParams& params) const {
        return otc_api_.get_otc_reserved_balances(params);
    }
    /// Asynchronous `get_otc_reserved_balances()`.
    template <class CompletionToken>
    auto async_get_otc_reserved_balances(const GetOtcReservedBalancesParams& params,
                                         CompletionToken&& token) const {
        return otc_api_.async_get_otc_reserved_balances(params,
                                                        std::forward<CompletionToken>(token));
    }

    /// List OTC Blocktrades (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/list.
    ///
    /// List the maker's own blocktrades with optional status filter and cursor pagination.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#list-otc-blocktrades
    [[nodiscard]] common::RestApiResponse<ListOtcBlocktradesResponse>
    list_otc_blocktrades(const ListOtcBlocktradesParams& params = {}) const {
        return otc_api_.list_otc_blocktrades(params);
    }
    /// Asynchronous `list_otc_blocktrades()`.
    template <class CompletionToken>
    auto async_list_otc_blocktrades(const ListOtcBlocktradesParams& params,
                                    CompletionToken&& token) const {
        return otc_api_.async_list_otc_blocktrades(params, std::forward<CompletionToken>(token));
    }

    /// Preview OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/preview.
    ///
    /// Inspect an open blocktrade by `secretToken` (no `orderId` needed). Taker uses this to
    /// preview the maker order before fulfilling. Returns the same shape as `Get Blocktrade
    /// Detail`, but `orderId` is `null` and `secretToken` is never returned from this endpoint.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#preview-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<PreviewOtcBlocktradeResponse>
    preview_otc_blocktrade(const PreviewOtcBlocktradeParams& params) const {
        return otc_api_.preview_otc_blocktrade(params);
    }
    /// Asynchronous `preview_otc_blocktrade()`.
    template <class CompletionToken>
    auto async_preview_otc_blocktrade(const PreviewOtcBlocktradeParams& params,
                                      CompletionToken&& token) const {
        return otc_api_.async_preview_otc_blocktrade(params, std::forward<CompletionToken>(token));
    }

    /// Remove OTC Blocktrades (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/remove.
    ///
    /// Cancel open or fulfilled-but-unsettled blocktrades. Terminal orders (already
    /// `MATCHED`/`CANCELLED`/`EXPIRED`/`FAILED`) are returned in `noop` instead of `removed`.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#remove-otc-blocktrades
    [[nodiscard]] common::RestApiResponse<RemoveOtcBlocktradesResponse>
    remove_otc_blocktrades(const RemoveOtcBlocktradesParams& params) const {
        return otc_api_.remove_otc_blocktrades(params);
    }
    /// Asynchronous `remove_otc_blocktrades()`.
    template <class CompletionToken>
    auto async_remove_otc_blocktrades(const RemoveOtcBlocktradesParams& params,
                                      CompletionToken&& token) const {
        return otc_api_.async_remove_otc_blocktrades(params, std::forward<CompletionToken>(token));
    }

    // PositionApi

    /// Get Position by Token (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/position/token.
    ///
    /// Get the authenticated user's position detail for a specific prediction token.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/position#get-position-by-token
    [[nodiscard]] common::RestApiResponse<GetPositionByTokenResponse>
    get_position_by_token(const GetPositionByTokenParams& params) const {
        return position_api_.get_position_by_token(params);
    }
    /// Asynchronous `get_position_by_token()`.
    template <class CompletionToken>
    auto async_get_position_by_token(const GetPositionByTokenParams& params,
                                     CompletionToken&& token) const {
        return position_api_.async_get_position_by_token(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Query PnL (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/pnl/query.
    ///
    /// Query profit and loss records for the authenticated user's prediction positions. When
    /// `tokenId` is provided, returns a single record in `pnl`; otherwise returns a list in
    /// `pnlList`.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/position#query-pn-l
    [[nodiscard]] common::RestApiResponse<QueryPnLResponse>
    query_pnl(const QueryPnLParams& params) const {
        return position_api_.query_pnl(params);
    }
    /// Asynchronous `query_pnl()`.
    template <class CompletionToken>
    auto async_query_pnl(const QueryPnLParams& params, CompletionToken&& token) const {
        return position_api_.async_query_pnl(params, std::forward<CompletionToken>(token));
    }

    /// Query Positions (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/position/list.
    ///
    /// Get the authenticated user's prediction token positions with portfolio summary and tab-based
    /// filtering.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/position#query-positions
    [[nodiscard]] common::RestApiResponse<QueryPositionsResponse>
    query_positions(const QueryPositionsParams& params) const {
        return position_api_.query_positions(params);
    }
    /// Asynchronous `query_positions()`.
    template <class CompletionToken>
    auto async_query_positions(const QueryPositionsParams& params, CompletionToken&& token) const {
        return position_api_.async_query_positions(params, std::forward<CompletionToken>(token));
    }

    /// Query Positions by Filter (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/position/filter.
    ///
    /// Get prediction positions filtered by wallet address and/or market topic ID. Both parameters
    /// are optional.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/position#query-positions-by-filter
    [[nodiscard]] common::RestApiResponse<QueryPositionsByFilterResponse>
    query_positions_by_filter(const QueryPositionsByFilterParams& params = {}) const {
        return position_api_.query_positions_by_filter(params);
    }
    /// Asynchronous `query_positions_by_filter()`.
    template <class CompletionToken>
    auto async_query_positions_by_filter(const QueryPositionsByFilterParams& params,
                                         CompletionToken&& token) const {
        return position_api_.async_query_positions_by_filter(params,
                                                             std::forward<CompletionToken>(token));
    }

    /// Query Settled Position History (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/position/settled-history.
    ///
    /// Get the authenticated user's settled (resolved) prediction position history with optional
    /// filters.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Response Notes:
    /// - There is no separate cancelled, invalid or refunded status. A resolved market pays each
    /// outcome by its payout ratio, which can be fractional, for example `0.5` for each of two
    /// outcomes. This is not a refund of the purchase cost. Use `finalOutcome`, `isWinner`,
    /// `claimAmount` and `redeemStatus` together with your own claim records, and Get Market Detail
    /// for `outcomes[].winner`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/position#query-settled-position-history
    [[nodiscard]] common::RestApiResponse<QuerySettledPositionHistoryResponse>
    query_settled_position_history(const QuerySettledPositionHistoryParams& params) const {
        return position_api_.query_settled_position_history(params);
    }
    /// Asynchronous `query_settled_position_history()`.
    template <class CompletionToken>
    auto async_query_settled_position_history(const QuerySettledPositionHistoryParams& params,
                                              CompletionToken&& token) const {
        return position_api_.async_query_settled_position_history(
            params, std::forward<CompletionToken>(token));
    }

    // RedeemApi

    /// Batch Redeem (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/batch-redeem.
    ///
    /// Redeem one or more settled prediction tokens on-chain to claim winnings. Requires SAS
    /// authorization.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/redeem#batch-redeem
    [[nodiscard]] common::RestApiResponse<BatchRedeemResponse>
    batch_redeem(const BatchRedeemParams& params) const {
        return redeem_api_.batch_redeem(params);
    }
    /// Asynchronous `batch_redeem()`.
    template <class CompletionToken>
    auto async_batch_redeem(const BatchRedeemParams& params, CompletionToken&& token) const {
        return redeem_api_.async_batch_redeem(params, std::forward<CompletionToken>(token));
    }

    /// Get Redeem Status (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/redeem/status.
    ///
    /// Query the on-chain transaction status of a previously submitted redeem request.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Response Notes:
    /// - Status values:
    ///
    ///   | Value       | Description                                  |
    ///   | ----------- | -------------------------------------------- |
    ///   | `PENDING`   | Transaction submitted, awaiting confirmation |
    ///   | `CONFIRMED` | Transaction confirmed on-chain               |
    ///   | `FAILED`    | Transaction failed                           |
    ///   | `NOT_FOUND` | Transaction hash not found                   |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/redeem#get-redeem-status
    [[nodiscard]] common::RestApiResponse<GetRedeemStatusResponse>
    get_redeem_status(const GetRedeemStatusParams& params) const {
        return redeem_api_.get_redeem_status(params);
    }
    /// Asynchronous `get_redeem_status()`.
    template <class CompletionToken>
    auto async_get_redeem_status(const GetRedeemStatusParams& params,
                                 CompletionToken&& token) const {
        return redeem_api_.async_get_redeem_status(params, std::forward<CompletionToken>(token));
    }

    // TradeApi

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
    batch_cancel_orders(const BatchCancelOrdersParams& params) const {
        return trade_api_.batch_cancel_orders(params);
    }
    /// Asynchronous `batch_cancel_orders()`.
    template <class CompletionToken>
    auto async_batch_cancel_orders(const BatchCancelOrdersParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_batch_cancel_orders(params, std::forward<CompletionToken>(token));
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
    get_quote(const GetQuoteParams& params) const {
        return trade_api_.get_quote(params);
    }
    /// Asynchronous `get_quote()`.
    template <class CompletionToken>
    auto async_get_quote(const GetQuoteParams& params, CompletionToken&& token) const {
        return trade_api_.async_get_quote(params, std::forward<CompletionToken>(token));
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
    place_order(const PlaceOrderParams& params) const {
        return trade_api_.place_order(params);
    }
    /// Asynchronous `place_order()`.
    template <class CompletionToken>
    auto async_place_order(const PlaceOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_place_order(params, std::forward<CompletionToken>(token));
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
    query_active_orders(const QueryActiveOrdersParams& params) const {
        return trade_api_.query_active_orders(params);
    }
    /// Asynchronous `query_active_orders()`.
    template <class CompletionToken>
    auto async_query_active_orders(const QueryActiveOrdersParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_query_active_orders(params, std::forward<CompletionToken>(token));
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
    query_order_history(const QueryOrderHistoryParams& params) const {
        return trade_api_.query_order_history(params);
    }
    /// Asynchronous `query_order_history()`.
    template <class CompletionToken>
    auto async_query_order_history(const QueryOrderHistoryParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_query_order_history(params, std::forward<CompletionToken>(token));
    }

    // TransferApi

    /// Apply MM Deposit (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/deposit/apply.
    ///
    /// Move funds from the user's bound CeDeFi MPC wallet to their CEX account (SPOT/FUNDING) via a
    /// contract escrow + credit flow. The maker wallet is resolved server-side by `userId`; the
    /// caller does not pass wallet or signature.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - "Note on `fromToken` / `toToken`: typically the same symbol (e.g. both `USDT`). When they
    /// differ, the backend may attempt a swap, but cross-symbol conversion is not guaranteed for
    /// all pairs — prefer using the same symbol."
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#apply-mm-deposit
    [[nodiscard]] common::RestApiResponse<ApplyMmDepositResponse>
    apply_mm_deposit(const ApplyMmDepositParams& params) const {
        return transfer_api_.apply_mm_deposit(params);
    }
    /// Asynchronous `apply_mm_deposit()`.
    template <class CompletionToken>
    auto async_apply_mm_deposit(const ApplyMmDepositParams& params, CompletionToken&& token) const {
        return transfer_api_.async_apply_mm_deposit(params, std::forward<CompletionToken>(token));
    }

    /// Apply MM Withdraw (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/withdraw/apply.
    ///
    /// Withdraw funds from the user's CEX account (SPOT/FUNDING) to their bound CeDeFi MPC wallet
    /// address. Unlike `v1/capital/withdraw/apply`, the caller does NOT pass `address`; the backend
    /// resolves the user's bound CeDeFi MPC wallet address by `userId` and reuses the existing
    /// capital withdraw flow with that address as the target.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - walletType Validation:
    ///
    ///   | Value           | Behavior                       |
    ///   | --------------- | ------------------------------- |
    ///   | `null`          | Allowed — defaults to SPOT      |
    ///   | `0`             | Allowed — source = SPOT         |
    ///   | `1`             | Allowed — source = FUNDING      |
    ///   | Other (e.g. `99`) | Rejected — returns validation error |
    /// - "Note on field naming: this endpoint uses `walletType` (INT `0`/`1`) for the source CEX
    /// account, while Apply MM Deposit uses `accountType` (STRING `SPOT`/`FUNDING`) for the target.
    /// The difference is intentional: withdraw reuses the existing `v1/capital/withdraw/apply`
    /// flow, which inherits that flow's integer `walletType` field."
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#apply-mm-withdraw
    [[nodiscard]] common::RestApiResponse<ApplyMmWithdrawResponse>
    apply_mm_withdraw(const ApplyMmWithdrawParams& params) const {
        return transfer_api_.apply_mm_withdraw(params);
    }
    /// Asynchronous `apply_mm_withdraw()`.
    template <class CompletionToken>
    auto async_apply_mm_withdraw(const ApplyMmWithdrawParams& params,
                                 CompletionToken&& token) const {
        return transfer_api_.async_apply_mm_withdraw(params, std::forward<CompletionToken>(token));
    }

    /// Create Inbound Transfer (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/transfer/inbound.
    ///
    /// Transfer funds from the prediction wallet back to the user's CEX account (SPOT or FUNDING).
    /// Requires SAS authorization.
    ///
    /// ⚠️ **SAS Authorization Required:** This endpoint enforces SAS (Self-Authorization Service)
    /// authorization. If SAS is not enabled for the wallet, the request will be rejected with
    /// `-31003 SAS authorization required`. Enable SAS for your wallet before calling this
    /// endpoint.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#create-inbound-transfer
    [[nodiscard]] common::RestApiResponse<CreateInboundTransferResponse>
    create_inbound_transfer(const CreateInboundTransferParams& params) const {
        return transfer_api_.create_inbound_transfer(params);
    }
    /// Asynchronous `create_inbound_transfer()`.
    template <class CompletionToken>
    auto async_create_inbound_transfer(const CreateInboundTransferParams& params,
                                       CompletionToken&& token) const {
        return transfer_api_.async_create_inbound_transfer(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Create Outbound Transfer (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/transfer/outbound.
    ///
    /// Transfer funds from the user's CEX account (SPOT or FUNDING) into the prediction wallet.
    /// Requires SAS authorization.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#create-outbound-transfer
    [[nodiscard]] common::RestApiResponse<CreateOutboundTransferResponse>
    create_outbound_transfer(const CreateOutboundTransferParams& params) const {
        return transfer_api_.create_outbound_transfer(params);
    }
    /// Asynchronous `create_outbound_transfer()`.
    template <class CompletionToken>
    auto async_create_outbound_transfer(const CreateOutboundTransferParams& params,
                                        CompletionToken&& token) const {
        return transfer_api_.async_create_outbound_transfer(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query Transfer List (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/transfer/list.
    ///
    /// Get the authenticated user's prediction wallet transfer history within a date range.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#query-transfer-list
    [[nodiscard]] common::RestApiResponse<QueryTransferListResponse>
    query_transfer_list(const QueryTransferListParams& params) const {
        return transfer_api_.query_transfer_list(params);
    }
    /// Asynchronous `query_transfer_list()`.
    template <class CompletionToken>
    auto async_query_transfer_list(const QueryTransferListParams& params,
                                   CompletionToken&& token) const {
        return transfer_api_.async_query_transfer_list(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Query Transfer Status (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/transfer/status.
    ///
    /// Query the current status of a prediction wallet transfer by transfer ID.
    ///
    /// **`status` values:** Terminal states are `COMPLETED` and `FAILED`. Intermediate states are
    /// `PROCESSING` and `PENDING`. **Do not** poll for `SUCCESS` — it is not a valid terminal
    /// state.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/transfer#query-transfer-status
    [[nodiscard]] common::RestApiResponse<QueryTransferStatusResponse>
    query_transfer_status(const QueryTransferStatusParams& params) const {
        return transfer_api_.query_transfer_status(params);
    }
    /// Asynchronous `query_transfer_status()`.
    template <class CompletionToken>
    auto async_query_transfer_status(const QueryTransferStatusParams& params,
                                     CompletionToken&& token) const {
        return transfer_api_.async_query_transfer_status(params,
                                                         std::forward<CompletionToken>(token));
    }

    // WalletApi

    /// Get Portfolio (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/pnl/portfolio.
    ///
    /// Get the authenticated user's prediction portfolio overview including active positions count,
    /// aggregated PnL, and full position list.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/wallet#get-portfolio
    [[nodiscard]] common::RestApiResponse<GetPortfolioResponse>
    get_portfolio(const GetPortfolioParams& params) const {
        return wallet_api_.get_portfolio(params);
    }
    /// Asynchronous `get_portfolio()`.
    template <class CompletionToken>
    auto async_get_portfolio(const GetPortfolioParams& params, CompletionToken&& token) const {
        return wallet_api_.async_get_portfolio(params, std::forward<CompletionToken>(token));
    }

    /// Get Quota Status (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/quota/limit/status.
    ///
    /// Query the current user's daily trading quota limit and remaining allowance for prediction
    /// markets.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/wallet#get-quota-status
    [[nodiscard]] common::RestApiResponse<GetQuotaStatusResponse>
    get_quota_status(const GetQuotaStatusParams& params = {}) const {
        return wallet_api_.get_quota_status(params);
    }
    /// Asynchronous `get_quota_status()`.
    template <class CompletionToken>
    auto async_get_quota_status(const GetQuotaStatusParams& params, CompletionToken&& token) const {
        return wallet_api_.async_get_quota_status(params, std::forward<CompletionToken>(token));
    }

    /// List Prediction Wallets (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/wallet/list.
    ///
    /// Get all prediction wallets registered for the authenticated user.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/wallet#list-prediction-wallets
    [[nodiscard]] common::RestApiResponse<ListPredictionWalletsResponse>
    list_prediction_wallets(const ListPredictionWalletsParams& params = {}) const {
        return wallet_api_.list_prediction_wallets(params);
    }
    /// Asynchronous `list_prediction_wallets()`.
    template <class CompletionToken>
    auto async_list_prediction_wallets(const ListPredictionWalletsParams& params,
                                       CompletionToken&& token) const {
        return wallet_api_.async_list_prediction_wallets(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Query Payment Option Balances (PREDICTION_TRADE)
    ///
    /// GET /sapi/v1/w3w/wallet/prediction/balance/payment-options.
    ///
    /// Get available balances for each payment option that can be used for prediction trading.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/wallet#query-payment-option-balances
    [[nodiscard]] common::RestApiResponse<QueryPaymentOptionBalancesResponse>
    query_payment_option_balances(const QueryPaymentOptionBalancesParams& params = {}) const {
        return wallet_api_.query_payment_option_balances(params);
    }
    /// Asynchronous `query_payment_option_balances()`.
    template <class CompletionToken>
    auto async_query_payment_option_balances(const QueryPaymentOptionBalancesParams& params,
                                             CompletionToken&& token) const {
        return wallet_api_.async_query_payment_option_balances(
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
    MarketDataApi market_data_api_;
    OtcApi otc_api_;
    PositionApi position_api_;
    RedeemApi redeem_api_;
    TradeApi trade_api_;
    TransferApi transfer_api_;
    WalletApi wallet_api_;
};

} // namespace binance::w3w_prediction::rest_api
