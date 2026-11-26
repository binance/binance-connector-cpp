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

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/apply_mm_deposit_response.hpp>
#include <binance/w3w_prediction/rest_api/models/apply_mm_withdraw_response.hpp>
#include <binance/w3w_prediction/rest_api/models/create_inbound_transfer_response.hpp>
#include <binance/w3w_prediction/rest_api/models/create_outbound_transfer_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_list_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_status_response.hpp>

namespace binance::w3w_prediction::rest_api {

enum class ApplyMmDepositAccountTypeEnum {
    Spot,
    Funding,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(ApplyMmDepositAccountTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT ApplyMmDepositAccountTypeEnum tag_invoke(
    boost::json::value_to_tag<ApplyMmDepositAccountTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              ApplyMmDepositAccountTypeEnum value);

enum class ApplyMmWithdrawWalletTypeEnum {
    WalletType0,
    WalletType1,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(ApplyMmWithdrawWalletTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT ApplyMmWithdrawWalletTypeEnum tag_invoke(
    boost::json::value_to_tag<ApplyMmWithdrawWalletTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              ApplyMmWithdrawWalletTypeEnum value);

enum class CreateInboundTransferAccountTypeEnum {
    Spot,
    Funding,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(CreateInboundTransferAccountTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT CreateInboundTransferAccountTypeEnum
tag_invoke(boost::json::value_to_tag<CreateInboundTransferAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              CreateInboundTransferAccountTypeEnum value);

enum class CreateOutboundTransferAccountTypeEnum {
    Spot,
    Funding,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(CreateOutboundTransferAccountTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT CreateOutboundTransferAccountTypeEnum
tag_invoke(boost::json::value_to_tag<CreateOutboundTransferAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              CreateOutboundTransferAccountTypeEnum value);

enum class CreateOutboundTransferSourceBizEnum {
    UserTransfer,
    PredictionBuy,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(CreateOutboundTransferSourceBizEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT CreateOutboundTransferSourceBizEnum
tag_invoke(boost::json::value_to_tag<CreateOutboundTransferSourceBizEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              CreateOutboundTransferSourceBizEnum value);

enum class QueryTransferListDirectionEnum {
    Inbound,
    Outbound,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(QueryTransferListDirectionEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT QueryTransferListDirectionEnum
tag_invoke(boost::json::value_to_tag<QueryTransferListDirectionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryTransferListDirectionEnum value);

struct ApplyMmDepositParams {
    /// Source token symbol (e.g. `USDT`)
    common::Required<std::string> from_token;
    /// Source token amount in WEI (18 decimals). Example: `1000000000000000000` = 1 USDT
    common::Required<std::string> from_token_amount;
    /// Target token symbol (e.g. `USDT`)
    common::Required<std::string> to_token;
    /// Target CEX account type. Enum: `SPOT`, `FUNDING`
    common::Required<ApplyMmDepositAccountTypeEnum> account_type;
    /// Chain ID. Default `56` (BSC)
    std::optional<std::string> chain_id = std::nullopt;
};

struct ApplyMmWithdrawParams {
    /// Coin to withdraw (e.g. `USDT`)
    common::Required<std::string> coin;
    /// Network (e.g. `BEP20`)
    common::Required<std::string> network;
    /// Amount to withdraw (must be > 0)
    common::Required<std::string> amount;
    /// Client withdraw order id (idempotency key)
    std::optional<std::string> withdraw_order_id = std::nullopt;
    /// Source CEX account type. Enum: `0` (SPOT), `1` (FUNDING). Default `0`. Must be `0` or `1`;
    /// any other value is rejected
    std::optional<ApplyMmWithdrawWalletTypeEnum> wallet_type = std::nullopt;
    /// Remark for the withdraw
    std::optional<std::string> name = std::nullopt;
};

struct CreateInboundTransferParams {
    /// Wallet ID
    common::Required<std::string> wallet_id;
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Transfer amount in wei (18 decimals). Must be > 0. Example: `1000000000000000000` = 1 USDT
    common::Required<std::string> from_token_amount;
    /// Destination CEX account. Enum: `SPOT`, `FUNDING`
    common::Required<CreateInboundTransferAccountTypeEnum> account_type;
    /// Source token symbol. Default `USDT`
    std::optional<std::string> from_token = std::nullopt;
    /// Destination token symbol. Default `USDT`
    std::optional<std::string> to_token = std::nullopt;
    /// Chain ID. Default `56` (BSC)
    std::optional<std::string> chain_id = std::nullopt;
};

struct CreateOutboundTransferParams {
    /// Wallet ID
    common::Required<std::string> wallet_id;
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Transfer amount in wei (18 decimals). Must be > 0. Example: `1000000000000000000` = 1 USDT
    common::Required<std::string> from_token_amount;
    /// Source CEX account. Enum: `SPOT`, `FUNDING`
    common::Required<CreateOutboundTransferAccountTypeEnum> account_type;
    /// Business source. Enum: `USER_TRANSFER`, `PREDICTION_BUY`
    common::Required<CreateOutboundTransferSourceBizEnum> source_biz;
    /// Source token symbol. Default `USDT`
    std::optional<std::string> from_token = std::nullopt;
    /// Destination token symbol. Default `USDT`
    std::optional<std::string> to_token = std::nullopt;
    /// Chain ID. Default `56` (BSC)
    std::optional<std::string> chain_id = std::nullopt;
};

struct QueryTransferListParams {
    /// User's prediction wallet address
    common::Required<std::string> wallet_address;
    /// Start date. Format: `yyyy-MM-dd`. Must be ≤ `endDate`
    common::Required<std::string> start_date;
    /// End date. Format: `yyyy-MM-dd`. Must be ≥ `startDate`
    common::Required<std::string> end_date;
    /// Filter by token symbol (e.g. `USDT`)
    std::optional<std::string> token_symbol = std::nullopt;
    /// Filter by direction. Enum: `INBOUND`, `OUTBOUND`
    std::optional<QueryTransferListDirectionEnum> direction = std::nullopt;
    /// Pagination offset. Default `0`
    std::optional<std::int64_t> offset = std::nullopt;
    /// Page size. Default `20`, range 1–100
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryTransferStatusParams {
    /// Transfer ID returned from outbound/inbound transfer
    common::Required<std::string> transfer_id;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_W3W_PREDICTION_EXPORT TransferApi {
public:
    explicit TransferApi(std::shared_ptr<common::RestClient> client);

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
    apply_mm_deposit(const ApplyMmDepositParams& params) const;

    /// Asynchronous `apply_mm_deposit()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ApplyMmDepositResponse>)`.
    template <class CompletionToken>
    auto async_apply_mm_deposit(const ApplyMmDepositParams& params, CompletionToken&& token) const {
        return common::async_send<ApplyMmDepositResponse>(client_, apply_mm_deposit_request(params),
                                                          std::forward<CompletionToken>(token));
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
    apply_mm_withdraw(const ApplyMmWithdrawParams& params) const;

    /// Asynchronous `apply_mm_withdraw()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ApplyMmWithdrawResponse>)`.
    template <class CompletionToken>
    auto async_apply_mm_withdraw(const ApplyMmWithdrawParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<ApplyMmWithdrawResponse>(
            client_, apply_mm_withdraw_request(params), std::forward<CompletionToken>(token));
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
    create_inbound_transfer(const CreateInboundTransferParams& params) const;

    /// Asynchronous `create_inbound_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateInboundTransferResponse>)`.
    template <class CompletionToken>
    auto async_create_inbound_transfer(const CreateInboundTransferParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<CreateInboundTransferResponse>(
            client_, create_inbound_transfer_request(params), std::forward<CompletionToken>(token));
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
    create_outbound_transfer(const CreateOutboundTransferParams& params) const;

    /// Asynchronous `create_outbound_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateOutboundTransferResponse>)`.
    template <class CompletionToken>
    auto async_create_outbound_transfer(const CreateOutboundTransferParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<CreateOutboundTransferResponse>(
            client_, create_outbound_transfer_request(params),
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
    query_transfer_list(const QueryTransferListParams& params) const;

    /// Asynchronous `query_transfer_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryTransferListResponse>)`.
    template <class CompletionToken>
    auto async_query_transfer_list(const QueryTransferListParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<QueryTransferListResponse>(
            client_, query_transfer_list_request(params), std::forward<CompletionToken>(token));
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
    query_transfer_status(const QueryTransferStatusParams& params) const;

    /// Asynchronous `query_transfer_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryTransferStatusResponse>)`.
    template <class CompletionToken>
    auto async_query_transfer_status(const QueryTransferStatusParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<QueryTransferStatusResponse>(
            client_, query_transfer_status_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    apply_mm_deposit_request(const ApplyMmDepositParams& params) const;
    [[nodiscard]] common::RestRequest
    apply_mm_withdraw_request(const ApplyMmWithdrawParams& params) const;
    [[nodiscard]] common::RestRequest
    create_inbound_transfer_request(const CreateInboundTransferParams& params) const;
    [[nodiscard]] common::RestRequest
    create_outbound_transfer_request(const CreateOutboundTransferParams& params) const;
    [[nodiscard]] common::RestRequest
    query_transfer_list_request(const QueryTransferListParams& params) const;
    [[nodiscard]] common::RestRequest
    query_transfer_status_request(const QueryTransferStatusParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
