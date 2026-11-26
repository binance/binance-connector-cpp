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
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_markets_response.hpp>
#include <binance/w3w_prediction/rest_api/models/market_search_response_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_last_trade_price_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response.hpp>

namespace binance::w3w_prediction::rest_api {

enum class ListPredictionMarketsSortByEnum {
    Recommended,
    Volume,
    Participants,
    CreatedTime,
    EndDate,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(ListPredictionMarketsSortByEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT ListPredictionMarketsSortByEnum
tag_invoke(boost::json::value_to_tag<ListPredictionMarketsSortByEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              ListPredictionMarketsSortByEnum value);

enum class ListPredictionMarketsOrderByEnum {
    Asc,
    Desc,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(ListPredictionMarketsOrderByEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT ListPredictionMarketsOrderByEnum
tag_invoke(boost::json::value_to_tag<ListPredictionMarketsOrderByEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              ListPredictionMarketsOrderByEnum value);

struct GetMarketDetailParams {
    /// Market topic ID. Must be > 0
    common::Required<std::int64_t> market_topic_id;
};

struct ListPredictionMarketsParams {
    /// Level-1 category filter
    std::optional<std::string> l1_category = std::nullopt;
    /// Level-2 category filter
    std::optional<std::string> l2_category = std::nullopt;
    /// Sort field. Enum: `RECOMMENDED`, `VOLUME`, `PARTICIPANTS`, `CREATED_TIME`, `END_DATE`
    std::optional<ListPredictionMarketsSortByEnum> sort_by = std::nullopt;
    /// Sort direction. Enum: `ASC`, `DESC`
    std::optional<ListPredictionMarketsOrderByEnum> order_by = std::nullopt;
    /// Pagination offset. Default `0`
    std::optional<std::int64_t> offset = std::nullopt;
    /// Page size. Default `20`, range 1–100
    std::optional<std::int64_t> limit = std::nullopt;
};

struct MarketSearchParams {
    /// Search keyword. Not blank
    common::Required<std::string> query;
    /// Max number of results to return. Default `20`, range 1–50
    std::optional<std::int64_t> top_k = std::nullopt;
};

struct QueryLastTradePriceParams {
    /// Market ID. Must be > 0
    common::Required<std::int64_t> market_id;
};

struct QueryOrderBookParams {
    /// Vendor identifier (e.g. `predict_fun`)
    common::Required<std::string> vendor;
    /// Market ID. Must be > 0
    common::Required<std::int64_t> market_id;
    /// Prediction outcome token ID
    common::Required<std::string> token_id;
};

class BINANCE_W3W_PREDICTION_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

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
    get_market_detail(const GetMarketDetailParams& params) const;

    /// Asynchronous `get_market_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetMarketDetailResponse>)`.
    template <class CompletionToken>
    auto async_get_market_detail(const GetMarketDetailParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<GetMarketDetailResponse>(
            client_, get_market_detail_request(params), std::forward<CompletionToken>(token));
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
    list_prediction_categories() const;

    /// Asynchronous `list_prediction_categories()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ListPredictionCategoriesResponse>)`.
    template <class CompletionToken>
    auto async_list_prediction_categories(CompletionToken&& token) const {
        return common::async_send<ListPredictionCategoriesResponse>(
            client_, list_prediction_categories_request(), std::forward<CompletionToken>(token));
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
    list_prediction_markets(const ListPredictionMarketsParams& params = {}) const;

    /// Asynchronous `list_prediction_markets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ListPredictionMarketsResponse>)`.
    template <class CompletionToken>
    auto async_list_prediction_markets(const ListPredictionMarketsParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ListPredictionMarketsResponse>(
            client_, list_prediction_markets_request(params), std::forward<CompletionToken>(token));
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
    market_search(const MarketSearchParams& params) const;

    /// Asynchronous `market_search()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<MarketSearchResponseInner>>)`.
    template <class CompletionToken>
    auto async_market_search(const MarketSearchParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<MarketSearchResponseInner>>(
            client_, market_search_request(params), std::forward<CompletionToken>(token));
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
    query_last_trade_price(const QueryLastTradePriceParams& params) const;

    /// Asynchronous `query_last_trade_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryLastTradePriceResponse>)`.
    template <class CompletionToken>
    auto async_query_last_trade_price(const QueryLastTradePriceParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<QueryLastTradePriceResponse>(
            client_, query_last_trade_price_request(params), std::forward<CompletionToken>(token));
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
    query_order_book(const QueryOrderBookParams& params) const;

    /// Asynchronous `query_order_book()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryOrderBookResponse>)`.
    template <class CompletionToken>
    auto async_query_order_book(const QueryOrderBookParams& params, CompletionToken&& token) const {
        return common::async_send<QueryOrderBookResponse>(client_, query_order_book_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_market_detail_request(const GetMarketDetailParams& params) const;
    [[nodiscard]] common::RestRequest list_prediction_categories_request() const;
    [[nodiscard]] common::RestRequest
    list_prediction_markets_request(const ListPredictionMarketsParams& params) const;
    [[nodiscard]] common::RestRequest market_search_request(const MarketSearchParams& params) const;
    [[nodiscard]] common::RestRequest
    query_last_trade_price_request(const QueryLastTradePriceParams& params) const;
    [[nodiscard]] common::RestRequest
    query_order_book_request(const QueryOrderBookParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
