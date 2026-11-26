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
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quota_status_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_wallets_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetPortfolioParams {
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

struct GetQuotaStatusParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ListPredictionWalletsParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPaymentOptionBalancesParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_W3W_PREDICTION_EXPORT WalletApi {
public:
    explicit WalletApi(std::shared_ptr<common::RestClient> client);

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
    get_portfolio(const GetPortfolioParams& params) const;

    /// Asynchronous `get_portfolio()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetPortfolioResponse>)`.
    template <class CompletionToken>
    auto async_get_portfolio(const GetPortfolioParams& params, CompletionToken&& token) const {
        return common::async_send<GetPortfolioResponse>(client_, get_portfolio_request(params),
                                                        std::forward<CompletionToken>(token));
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
    get_quota_status(const GetQuotaStatusParams& params = {}) const;

    /// Asynchronous `get_quota_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetQuotaStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_quota_status(const GetQuotaStatusParams& params, CompletionToken&& token) const {
        return common::async_send<GetQuotaStatusResponse>(client_, get_quota_status_request(params),
                                                          std::forward<CompletionToken>(token));
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
    list_prediction_wallets(const ListPredictionWalletsParams& params = {}) const;

    /// Asynchronous `list_prediction_wallets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ListPredictionWalletsResponse>)`.
    template <class CompletionToken>
    auto async_list_prediction_wallets(const ListPredictionWalletsParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ListPredictionWalletsResponse>(
            client_, list_prediction_wallets_request(params), std::forward<CompletionToken>(token));
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
    query_payment_option_balances(const QueryPaymentOptionBalancesParams& params = {}) const;

    /// Asynchronous `query_payment_option_balances()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryPaymentOptionBalancesResponse>)`.
    template <class CompletionToken>
    auto async_query_payment_option_balances(const QueryPaymentOptionBalancesParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryPaymentOptionBalancesResponse>(
            client_, query_payment_option_balances_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_portfolio_request(const GetPortfolioParams& params) const;
    [[nodiscard]] common::RestRequest
    get_quota_status_request(const GetQuotaStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    list_prediction_wallets_request(const ListPredictionWalletsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_payment_option_balances_request(const QueryPaymentOptionBalancesParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
