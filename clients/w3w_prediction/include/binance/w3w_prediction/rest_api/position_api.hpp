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
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/get_position_by_token_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_pnl_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_by_filter_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetPositionByTokenParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Prediction outcome token ID
    common::Required<std::string> token_id;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPnLParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Filter by prediction token ID
    std::optional<std::string> token_id = std::nullopt;
    /// Filter by market ID. Must be > 0
    std::optional<std::int64_t> market_id = std::nullopt;
    /// Filter by market topic ID. Must be > 0
    std::optional<std::int64_t> market_topic_id = std::nullopt;
    /// If `true`, return only active (unresolved) positions
    std::optional<bool> active_only = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPositionsParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Position status tab. Values from `PositionQueryType`. Default `ONGOING`
    std::optional<std::string> tab = std::nullopt;
    /// Pagination offset. Default `0`
    std::optional<std::int64_t> offset = std::nullopt;
    /// Page size. Default `20`, range 1–100
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPositionsByFilterParams {
    /// User's prediction wallet address
    std::optional<std::string> wallet_address = std::nullopt;
    /// Filter by market topic ID
    std::optional<std::int64_t> market_topic_id = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySettledPositionHistoryParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Filter by level-1 category
    std::optional<std::string> l1_category = std::nullopt;
    /// Settlement result filter
    std::optional<std::int64_t> result = std::nullopt;
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

class BINANCE_W3W_PREDICTION_EXPORT PositionApi {
public:
    explicit PositionApi(std::shared_ptr<common::RestClient> client);

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
    get_position_by_token(const GetPositionByTokenParams& params) const;

    /// Asynchronous `get_position_by_token()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetPositionByTokenResponse>)`.
    template <class CompletionToken>
    auto async_get_position_by_token(const GetPositionByTokenParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetPositionByTokenResponse>(
            client_, get_position_by_token_request(params), std::forward<CompletionToken>(token));
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
    query_pnl(const QueryPnLParams& params) const;

    /// Asynchronous `query_pnl()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryPnLResponse>)`.
    template <class CompletionToken>
    auto async_query_pnl(const QueryPnLParams& params, CompletionToken&& token) const {
        return common::async_send<QueryPnLResponse>(client_, query_pnl_request(params),
                                                    std::forward<CompletionToken>(token));
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
    query_positions(const QueryPositionsParams& params) const;

    /// Asynchronous `query_positions()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryPositionsResponse>)`.
    template <class CompletionToken>
    auto async_query_positions(const QueryPositionsParams& params, CompletionToken&& token) const {
        return common::async_send<QueryPositionsResponse>(client_, query_positions_request(params),
                                                          std::forward<CompletionToken>(token));
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
    query_positions_by_filter(const QueryPositionsByFilterParams& params = {}) const;

    /// Asynchronous `query_positions_by_filter()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryPositionsByFilterResponse>)`.
    template <class CompletionToken>
    auto async_query_positions_by_filter(const QueryPositionsByFilterParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QueryPositionsByFilterResponse>(
            client_, query_positions_by_filter_request(params),
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
    query_settled_position_history(const QuerySettledPositionHistoryParams& params) const;

    /// Asynchronous `query_settled_position_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySettledPositionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_settled_position_history(const QuerySettledPositionHistoryParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<QuerySettledPositionHistoryResponse>(
            client_, query_settled_position_history_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_position_by_token_request(const GetPositionByTokenParams& params) const;
    [[nodiscard]] common::RestRequest query_pnl_request(const QueryPnLParams& params) const;
    [[nodiscard]] common::RestRequest
    query_positions_request(const QueryPositionsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_positions_by_filter_request(const QueryPositionsByFilterParams& params) const;
    [[nodiscard]] common::RestRequest
    query_settled_position_history_request(const QuerySettledPositionHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
