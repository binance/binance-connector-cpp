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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_redeem_status_response.hpp>

namespace binance::w3w_prediction::rest_api {

struct BatchRedeemParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Wallet ID
    common::Required<std::string> wallet_id;
    /// List of prediction token IDs to redeem. Not empty. Example:
    /// `tokenIds=112233&tokenIds=112234`
    common::Required<std::vector<std::string>> token_ids;
    /// Chain ID. Default `56` (BSC)
    std::optional<std::string> chain_id = std::nullopt;
};

struct GetRedeemStatusParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Redeem transaction hash
    common::Required<std::string> tx_hash;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_W3W_PREDICTION_EXPORT RedeemApi {
public:
    explicit RedeemApi(std::shared_ptr<common::RestClient> client);

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
    batch_redeem(const BatchRedeemParams& params) const;

    /// Asynchronous `batch_redeem()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<BatchRedeemResponse>)`.
    template <class CompletionToken>
    auto async_batch_redeem(const BatchRedeemParams& params, CompletionToken&& token) const {
        return common::async_send<BatchRedeemResponse>(client_, batch_redeem_request(params),
                                                       std::forward<CompletionToken>(token));
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
    get_redeem_status(const GetRedeemStatusParams& params) const;

    /// Asynchronous `get_redeem_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRedeemStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_redeem_status(const GetRedeemStatusParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<GetRedeemStatusResponse>(
            client_, get_redeem_status_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest batch_redeem_request(const BatchRedeemParams& params) const;
    [[nodiscard]] common::RestRequest
    get_redeem_status_request(const GetRedeemStatusParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
