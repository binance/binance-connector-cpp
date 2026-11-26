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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/sub_account/export.hpp>
#include <binance/sub_account/rest_api/models/futures_transfer_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_futures_account_v2_response.hpp>
#include <binance/sub_account/rest_api/models/get_detail_on_sub_accounts_margin_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_move_position_history_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_sub_account_deposit_address_response.hpp>
#include <binance/sub_account/rest_api/models/get_sub_account_deposit_history_response_inner.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_response.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_futures_account_v2_response.hpp>
#include <binance/sub_account/rest_api/models/get_summary_of_sub_accounts_margin_account_response.hpp>
#include <binance/sub_account/rest_api/models/margin_transfer_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/move_position_for_sub_account_order_args_parameter_inner.hpp>
#include <binance/sub_account/rest_api/models/move_position_for_sub_account_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_assets_asset_management_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_assets_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_futures_asset_transfer_history_response.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_asset_transfer_history_response_inner.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_spot_assets_summary_response.hpp>
#include <binance/sub_account/rest_api/models/query_universal_transfer_history_response.hpp>
#include <binance/sub_account/rest_api/models/sub_account_futures_asset_transfer_response.hpp>
#include <binance/sub_account/rest_api/models/sub_account_transfer_history_response_inner.hpp>
#include <binance/sub_account/rest_api/models/transfer_to_master_response.hpp>
#include <binance/sub_account/rest_api/models/transfer_to_sub_account_of_same_master_response.hpp>
#include <binance/sub_account/rest_api/models/universal_transfer_response.hpp>

namespace binance::sub_account::rest_api {

enum class GetMovePositionHistoryForSubAccountProductTypeEnum {
    Um,
    Option,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(GetMovePositionHistoryForSubAccountProductTypeEnum value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT GetMovePositionHistoryForSubAccountProductTypeEnum
tag_invoke(boost::json::value_to_tag<GetMovePositionHistoryForSubAccountProductTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetMovePositionHistoryForSubAccountProductTypeEnum value);

enum class MovePositionForSubAccountProductTypeEnum {
    Um,
    Option,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(MovePositionForSubAccountProductTypeEnum value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT MovePositionForSubAccountProductTypeEnum
tag_invoke(boost::json::value_to_tag<MovePositionForSubAccountProductTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           MovePositionForSubAccountProductTypeEnum value);

enum class UniversalTransferFromAccountTypeEnum {
    Spot,
    UsdtFuture,
    CoinFuture,
    Margin,
    IsolatedMargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(UniversalTransferFromAccountTypeEnum value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT UniversalTransferFromAccountTypeEnum
tag_invoke(boost::json::value_to_tag<UniversalTransferFromAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           UniversalTransferFromAccountTypeEnum value);

enum class UniversalTransferToAccountTypeEnum {
    Spot,
    UsdtFuture,
    CoinFuture,
    Margin,
    IsolatedMargin,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SUB_ACCOUNT_EXPORT std::string_view
to_string(UniversalTransferToAccountTypeEnum value) noexcept;
BINANCE_SUB_ACCOUNT_EXPORT UniversalTransferToAccountTypeEnum
tag_invoke(boost::json::value_to_tag<UniversalTransferToAccountTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           UniversalTransferToAccountTypeEnum value);

struct FuturesTransferForSubAccountParams {
    common::Required<std::string> email;
    /// The asset being transferred
    common::Required<std::string> asset;
    /// The amount to be transferred
    common::Required<common::Decimal> amount;
    /// 1: transfer from subaccount's spot account to its USDT-margined futures account 2: transfer
    /// from subaccount's USDT-margined futures account to its spot account 3: transfer from
    /// subaccount's spot account to its COIN-margined futures account 4: transfer from subaccount's
    /// COIN-margined futures account to its spot account
    common::Required<std::int64_t> type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDetailOnSubAccountsFuturesAccountParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDetailOnSubAccountsFuturesAccountV2Params {
    common::Required<std::string> email;
    /// 1: USDT-margined Futures，2: Coin-margined Futures
    common::Required<std::int64_t> futures_type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDetailOnSubAccountsMarginAccountParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetMovePositionHistoryForSubAccountParams {
    common::Required<std::string> symbol;
    common::Required<std::int64_t> page;
    /// Max 100.
    common::Required<std::int64_t> rows;
    /// Default UM.
    std::optional<GetMovePositionHistoryForSubAccountProductTypeEnum> product_type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MovePositionForSubAccountParams {
    common::Required<std::string> from_user_email;
    common::Required<std::string> to_user_email;
    /// A single request cannot mix UM and OPTION positions.
    common::Required<MovePositionForSubAccountProductTypeEnum> product_type;
    /// Max 10 positions supported. When input request parameter,orderArgs.symbol should be STRING,
    /// orderArgs.quantity should be BIGDECIMAL, and orderArgs.positionSide should be STRING,
    /// positionSide support BOTH,LONG and SHORT. Each entry should be like
    /// orderArgs[0].symbol=BTCUSDT,orderArgs[0].quantity=0.001,orderArgs[0].positionSide=BOTH.
    /// Example of the request parameter array: orderArgs[0].symbol=BTCUSDT
    /// orderArgs[0].quantity=0.001 orderArgs[0].positionSide=BOTH orderArgs[1].symbol=ETHUSDT
    /// orderArgs[1].quantity=0.01 orderArgs[1].positionSide=BOTH
    common::Required<std::vector<MovePositionForSubAccountOrderArgsParameterInner>> order_args;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSubAccountDepositAddressParams {
    common::Required<std::string> email;
    common::Required<std::string> coin;
    /// networks can be found in `GET /sapi/v1/capital/deposit/address`
    std::optional<std::string> network = std::nullopt;
    std::optional<common::Decimal> amount = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSubAccountDepositHistoryParams {
    common::Required<std::string> email;
    /// Default `false`, return `sourceAddress` field when set to `true`
    std::optional<bool> include_source = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// Deposit status: 0=pending, 6=credited but cannot withdraw, 7=wrong deposit, 8=waiting user
    /// confirmation, 1=success.
    std::optional<std::int64_t> status = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
    std::optional<std::string> tx_id = std::nullopt;
};

struct GetSummaryOfSubAccountsFuturesAccountParams {
    common::Required<std::int64_t> page;
    common::Required<std::int64_t> limit;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSummaryOfSubAccountsFuturesAccountV2Params {
    /// 1: USDT-margined Futures，2: Coin-margined Futures
    common::Required<std::int64_t> futures_type;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetSummaryOfSubAccountsMarginAccountParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginTransferForSubAccountParams {
    common::Required<std::string> email;
    /// The asset being transferred
    common::Required<std::string> asset;
    /// The amount to be transferred
    common::Required<common::Decimal> amount;
    /// 1: transfer from subaccount's spot account to margin account 2: transfer from subaccount's
    /// margin account to its spot account
    common::Required<std::int64_t> type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountAssetsParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountAssetsAssetManagementParams {
    common::Required<std::string> email;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountFuturesAssetTransferHistoryParams {
    common::Required<std::string> email;
    /// 1: USDT-margined Futures，2: Coin-margined Futures
    common::Required<std::int64_t> futures_type;
    /// Cannot be earlier than 1 month ago
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubAccountFuturesAssetTransferParams {
    /// Sender email
    common::Required<std::string> from_email;
    /// Recipient email
    common::Required<std::string> to_email;
    /// 1: USDT-margined Futures，2: Coin-margined Futures
    common::Required<std::int64_t> futures_type;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountSpotAssetTransferHistoryParams {
    std::optional<std::string> from_email = std::nullopt;
    std::optional<std::string> to_email = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySubAccountSpotAssetsSummaryParams {
    /// Managed sub-account email
    std::optional<std::string> email = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUniversalTransferHistoryParams {
    std::optional<std::string> from_email = std::nullopt;
    std::optional<std::string> to_email = std::nullopt;
    std::optional<std::string> client_tran_id = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UniversalTransferParams {
    common::Required<UniversalTransferFromAccountTypeEnum> from_account_type;
    common::Required<UniversalTransferToAccountTypeEnum> to_account_type;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::string> from_email = std::nullopt;
    std::optional<std::string> to_email = std::nullopt;
    /// Must be unique
    std::optional<std::string> client_tran_id = std::nullopt;
    /// Only supported under ISOLATED_MARGIN type
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubAccountTransferHistoryParams {
    /// If not sent, result of all assets will be returned
    std::optional<std::string> asset = std::nullopt;
    /// 1: transfer in, 2: transfer out
    std::optional<std::int64_t> type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Default `False`, return PROCESS and SUCCESS status history; If `True`,return PROCESS and
    /// SUCCESS and FAILURE status history
    std::optional<bool> return_fail_history = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TransferToMasterParams {
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TransferToSubAccountOfSameMasterParams {
    common::Required<std::string> to_email;
    common::Required<std::string> asset;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_SUB_ACCOUNT_EXPORT AssetManagementApi {
public:
    explicit AssetManagementApi(std::shared_ptr<common::RestClient> client);

    /// Futures Transfer for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/transfer.
    ///
    /// Futures Transfer for Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#futures-transfer-for-sub-account
    [[nodiscard]] common::RestApiResponse<FuturesTransferForSubAccountResponse>
    futures_transfer_for_sub_account(const FuturesTransferForSubAccountParams& params) const;

    /// Asynchronous `futures_transfer_for_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FuturesTransferForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_futures_transfer_for_sub_account(const FuturesTransferForSubAccountParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<FuturesTransferForSubAccountResponse>(
            client_, futures_transfer_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Futures Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/account.
    ///
    /// Get Detail on Sub-account's Futures Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-futures-account
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountResponse>
    get_detail_on_sub_accounts_futures_account(
        const GetDetailOnSubAccountsFuturesAccountParams& params) const;

    /// Asynchronous `get_detail_on_sub_accounts_futures_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_futures_account(
        const GetDetailOnSubAccountsFuturesAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetDetailOnSubAccountsFuturesAccountResponse>(
            client_, get_detail_on_sub_accounts_futures_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Futures Account V2 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v2/sub-account/futures/account.
    ///
    /// Get Detail on Sub-account's Futures Account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-futures-account-v2
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountV2Response>
    get_detail_on_sub_accounts_futures_account_v2(
        const GetDetailOnSubAccountsFuturesAccountV2Params& params) const;

    /// Asynchronous `get_detail_on_sub_accounts_futures_account_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDetailOnSubAccountsFuturesAccountV2Response>)`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_futures_account_v2(
        const GetDetailOnSubAccountsFuturesAccountV2Params& params, CompletionToken&& token) const {
        return common::async_send<GetDetailOnSubAccountsFuturesAccountV2Response>(
            client_, get_detail_on_sub_accounts_futures_account_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Detail on Sub-account's Margin Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/margin/account.
    ///
    /// Get Detail on Sub-account's Margin Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-detail-on-sub-accounts-margin-account
    [[nodiscard]] common::RestApiResponse<GetDetailOnSubAccountsMarginAccountResponse>
    get_detail_on_sub_accounts_margin_account(
        const GetDetailOnSubAccountsMarginAccountParams& params) const;

    /// Asynchronous `get_detail_on_sub_accounts_margin_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDetailOnSubAccountsMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_detail_on_sub_accounts_margin_account(
        const GetDetailOnSubAccountsMarginAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetDetailOnSubAccountsMarginAccountResponse>(
            client_, get_detail_on_sub_accounts_margin_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Move Position History for Sub-account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/move-position.
    ///
    /// Query move position history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are both omitted, records from the last 90 days are returned
    /// by default (up to 100 records).
    /// - If `startTime` is sent and `endTime` is omitted, records in `[max(startTime, now-90d),
    /// now]` are returned.
    /// - If `startTime` is omitted and `endTime` is sent, records in `[max(now, endTime-90d),
    /// endTime]` are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-move-position-history-for-sub-account
    [[nodiscard]] common::RestApiResponse<GetMovePositionHistoryForSubAccountResponse>
    get_move_position_history_for_sub_account(
        const GetMovePositionHistoryForSubAccountParams& params) const;

    /// Asynchronous `get_move_position_history_for_sub_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetMovePositionHistoryForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_move_position_history_for_sub_account(
        const GetMovePositionHistoryForSubAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetMovePositionHistoryForSubAccountResponse>(
            client_, get_move_position_history_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Move Position for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/move-position.
    ///
    /// Move position between sub-master, master-sub, or sub-sub accounts when necessary
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable the `Trading` permission for the API key used to call this endpoint.
    /// - This function is only available for VIP levels 7-9.
    /// - Only master accounts can call this endpoint.
    /// - `quantity` must be a positive number.
    /// - Supported account types: normal account, PM PRO, PM PRO SPAN, and PM Retail.
    /// - The source account must have positions.
    /// - For orders in the same `orderArgs` request, if any symbol's total close position quantity
    /// exceeds current position quantity, all orders in that batch fail.
    /// - Only cross margin mode is supported.
    /// - The move position price supports `MARK_PRICE` only.
    /// - MSA is not supported.
    /// - Symbols configured with `Reduce-Only` are not supported.
    /// - Move Position charges a trading fee. The fee rate is based on the master account's VIP
    /// level: the source account (`fromUserEmail`) is the taker and pays the taker fee, and the
    /// destination account (`toUserEmail`) is the maker and pays the maker fee.
    /// - The `clientOrderId` of orders generated by Move Position now starts with `otcCHGFE`
    /// (previously `otc-`).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#move-position-for-sub-account
    [[nodiscard]] common::RestApiResponse<MovePositionForSubAccountResponse>
    move_position_for_sub_account(const MovePositionForSubAccountParams& params) const;

    /// Asynchronous `move_position_for_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MovePositionForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_move_position_for_sub_account(const MovePositionForSubAccountParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<MovePositionForSubAccountResponse>(
            client_, move_position_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Sub-account Deposit Address (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/subAddress.
    ///
    /// Fetch sub-account deposit address
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `amount` needs to be sent if using LIGHTNING network
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-sub-account-deposit-address
    [[nodiscard]] common::RestApiResponse<GetSubAccountDepositAddressResponse>
    get_sub_account_deposit_address(const GetSubAccountDepositAddressParams& params) const;

    /// Asynchronous `get_sub_account_deposit_address()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSubAccountDepositAddressResponse>)`.
    template <class CompletionToken>
    auto async_get_sub_account_deposit_address(const GetSubAccountDepositAddressParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetSubAccountDepositAddressResponse>(
            client_, get_sub_account_deposit_address_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Sub-account Deposit History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/subHisrec.
    ///
    /// Fetch sub-account deposit history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-sub-account-deposit-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetSubAccountDepositHistoryResponseInner>>
    get_sub_account_deposit_history(const GetSubAccountDepositHistoryParams& params) const;

    /// Asynchronous `get_sub_account_deposit_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetSubAccountDepositHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_sub_account_deposit_history(const GetSubAccountDepositHistoryParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<GetSubAccountDepositHistoryResponseInner>>(
            client_, get_sub_account_deposit_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Futures Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/accountSummary.
    ///
    /// Get Summary of Sub-account's Futures Account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-futures-account
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountResponse>
    get_summary_of_sub_accounts_futures_account(
        const GetSummaryOfSubAccountsFuturesAccountParams& params) const;

    /// Asynchronous `get_summary_of_sub_accounts_futures_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_futures_account(
        const GetSummaryOfSubAccountsFuturesAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetSummaryOfSubAccountsFuturesAccountResponse>(
            client_, get_summary_of_sub_accounts_futures_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Futures Account V2 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v2/sub-account/futures/accountSummary.
    ///
    /// Get Summary of Sub-account's Futures Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-futures-account-v2
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountV2Response>
    get_summary_of_sub_accounts_futures_account_v2(
        const GetSummaryOfSubAccountsFuturesAccountV2Params& params) const;

    /// Asynchronous `get_summary_of_sub_accounts_futures_account_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetSummaryOfSubAccountsFuturesAccountV2Response>)`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_futures_account_v2(
        const GetSummaryOfSubAccountsFuturesAccountV2Params& params,
        CompletionToken&& token) const {
        return common::async_send<GetSummaryOfSubAccountsFuturesAccountV2Response>(
            client_, get_summary_of_sub_accounts_futures_account_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Summary of Sub-account's Margin Account (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/margin/accountSummary.
    ///
    /// Get Summary of Sub-account's Margin Account
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#get-summary-of-sub-accounts-margin-account
    [[nodiscard]] common::RestApiResponse<GetSummaryOfSubAccountsMarginAccountResponse>
    get_summary_of_sub_accounts_margin_account(
        const GetSummaryOfSubAccountsMarginAccountParams& params = {}) const;

    /// Asynchronous `get_summary_of_sub_accounts_margin_account()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetSummaryOfSubAccountsMarginAccountResponse>)`.
    template <class CompletionToken>
    auto async_get_summary_of_sub_accounts_margin_account(
        const GetSummaryOfSubAccountsMarginAccountParams& params, CompletionToken&& token) const {
        return common::async_send<GetSummaryOfSubAccountsMarginAccountResponse>(
            client_, get_summary_of_sub_accounts_margin_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Transfer for Sub-account (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/margin/transfer.
    ///
    /// Margin Transfer for Sub-account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#margin-transfer-for-sub-account
    [[nodiscard]] common::RestApiResponse<MarginTransferForSubAccountResponse>
    margin_transfer_for_sub_account(const MarginTransferForSubAccountParams& params) const;

    /// Asynchronous `margin_transfer_for_sub_account()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginTransferForSubAccountResponse>)`.
    template <class CompletionToken>
    auto async_margin_transfer_for_sub_account(const MarginTransferForSubAccountParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<MarginTransferForSubAccountResponse>(
            client_, margin_transfer_for_sub_account_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Assets (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v3/sub-account/assets.
    ///
    /// Fetch sub-account assets
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-assets
    [[nodiscard]] common::RestApiResponse<QuerySubAccountAssetsResponse>
    query_sub_account_assets(const QuerySubAccountAssetsParams& params) const;

    /// Asynchronous `query_sub_account_assets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySubAccountAssetsResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_assets(const QuerySubAccountAssetsParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<QuerySubAccountAssetsResponse>(
            client_, query_sub_account_assets_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Assets V4 (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v4/sub-account/assets.
    ///
    /// Fetch sub-account assets
    ///
    /// Weight(UID): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-assets-asset-management
    [[nodiscard]] common::RestApiResponse<QuerySubAccountAssetsAssetManagementResponse>
    query_sub_account_assets_asset_management(
        const QuerySubAccountAssetsAssetManagementParams& params) const;

    /// Asynchronous `query_sub_account_assets_asset_management()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QuerySubAccountAssetsAssetManagementResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_assets_asset_management(
        const QuerySubAccountAssetsAssetManagementParams& params, CompletionToken&& token) const {
        return common::async_send<QuerySubAccountAssetsAssetManagementResponse>(
            client_, query_sub_account_assets_asset_management_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Futures Asset Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/futures/internalTransfer.
    ///
    /// Query Sub-account Futures Asset Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-futures-asset-transfer-history
    [[nodiscard]] common::RestApiResponse<QuerySubAccountFuturesAssetTransferHistoryResponse>
    query_sub_account_futures_asset_transfer_history(
        const QuerySubAccountFuturesAssetTransferHistoryParams& params) const;

    /// Asynchronous `query_sub_account_futures_asset_transfer_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QuerySubAccountFuturesAssetTransferHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_futures_asset_transfer_history(
        const QuerySubAccountFuturesAssetTransferHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<QuerySubAccountFuturesAssetTransferHistoryResponse>(
            client_, query_sub_account_futures_asset_transfer_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Sub-account Futures Asset Transfer (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/futures/internalTransfer.
    ///
    /// Sub-account Futures Asset Transfer
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - A master account can transfer at most 2000 times per minute.
    /// - The futures wallet must have sufficient margin balance to execute the transfer.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#sub-account-futures-asset-transfer
    [[nodiscard]] common::RestApiResponse<SubAccountFuturesAssetTransferResponse>
    sub_account_futures_asset_transfer(const SubAccountFuturesAssetTransferParams& params) const;

    /// Asynchronous `sub_account_futures_asset_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubAccountFuturesAssetTransferResponse>)`.
    template <class CompletionToken>
    auto
    async_sub_account_futures_asset_transfer(const SubAccountFuturesAssetTransferParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<SubAccountFuturesAssetTransferResponse>(
            client_, sub_account_futures_asset_transfer_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Spot Asset Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/sub/transfer/history.
    ///
    /// Query Sub-account Spot Asset Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `fromEmail` and `toEmail` cannot be sent at the same time.
    /// - If both `fromEmail` and `toEmail` are omitted, records with `fromEmail` equal to the
    /// master account are returned by default.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-spot-asset-transfer-history
    [[nodiscard]] common::RestApiResponse<
        std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>
    query_sub_account_spot_asset_transfer_history(
        const QuerySubAccountSpotAssetTransferHistoryParams& params = {}) const;

    /// Asynchronous `query_sub_account_spot_asset_transfer_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_sub_account_spot_asset_transfer_history(
        const QuerySubAccountSpotAssetTransferHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<QuerySubAccountSpotAssetTransferHistoryResponseInner>>(
            client_, query_sub_account_spot_asset_transfer_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Sub-account Spot Assets Summary (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/spotSummary.
    ///
    /// Get BTC valued asset summary of subaccounts.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-sub-account-spot-assets-summary
    [[nodiscard]] common::RestApiResponse<QuerySubAccountSpotAssetsSummaryResponse>
    query_sub_account_spot_assets_summary(
        const QuerySubAccountSpotAssetsSummaryParams& params = {}) const;

    /// Asynchronous `query_sub_account_spot_assets_summary()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QuerySubAccountSpotAssetsSummaryResponse>)`.
    template <class CompletionToken>
    auto async_query_sub_account_spot_assets_summary(
        const QuerySubAccountSpotAssetsSummaryParams& params, CompletionToken&& token) const {
        return common::async_send<QuerySubAccountSpotAssetsSummaryResponse>(
            client_, query_sub_account_spot_assets_summary_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Universal Transfer History (For Master Account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/universalTransfer.
    ///
    /// Query Universal Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `fromEmail` and `toEmail` cannot be sent at the same time.
    /// - If both `fromEmail` and `toEmail` are omitted, records with `fromEmail` equal to the
    /// master account are returned by default.
    /// - The query time range must be less than 7 days.
    /// - If `startTime` and `endTime` are omitted, records from the last 7 days are returned by
    /// default.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#query-universal-transfer-history
    [[nodiscard]] common::RestApiResponse<QueryUniversalTransferHistoryResponse>
    query_universal_transfer_history(const QueryUniversalTransferHistoryParams& params = {}) const;

    /// Asynchronous `query_universal_transfer_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryUniversalTransferHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_universal_transfer_history(const QueryUniversalTransferHistoryParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<QueryUniversalTransferHistoryResponse>(
            client_, query_universal_transfer_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Universal Transfer (For Master Account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/universalTransfer.
    ///
    /// Universal Transfer
    ///
    /// Weight(IP): 1
    ///
    /// Weight(UID): 360
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to enable the `internal transfer` option for the API key used to call this
    /// endpoint.
    /// - If `fromEmail` is not sent, transfer out from the master account by default.
    /// - If `toEmail` is not sent, transfer into the master account by default.
    /// - When `fromAccountType` and `toAccountType` are the same, at least one of `fromEmail` or
    /// `toEmail` must be sent.
    /// - Supported transfer scenarios:
    ///   - `SPOT` -> `SPOT` / `USDT_FUTURE` / `COIN_FUTURE` (master or sub-account).
    ///   - `SPOT` / `USDT_FUTURE` / `COIN_FUTURE` -> `SPOT` (master or sub-account).
    ///   - Master account `SPOT` -> sub-account `MARGIN(Cross)` / `ISOLATED_MARGIN`.
    ///   - Sub-account `MARGIN(Cross)` / `ISOLATED_MARGIN` -> master account `SPOT`.
    ///   - Sub-account `MARGIN(Cross)` -> sub-account `MARGIN(Cross)`.
    ///   - `ALPHA` -> `ALPHA` (master or sub-account).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#universal-transfer
    [[nodiscard]] common::RestApiResponse<UniversalTransferResponse>
    universal_transfer(const UniversalTransferParams& params) const;

    /// Asynchronous `universal_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UniversalTransferResponse>)`.
    template <class CompletionToken>
    auto async_universal_transfer(const UniversalTransferParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<UniversalTransferResponse>(
            client_, universal_transfer_request(params), std::forward<CompletionToken>(token));
    }

    /// Sub-account Transfer History (For Sub-account) (USER_DATA)
    ///
    /// GET /sapi/v1/sub-account/transfer/subUserHistory.
    ///
    /// Sub-account Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `type` is not sent, records of type `2` (transfer out) are returned by default.
    /// - If `startTime` and `endTime` are not sent, data from the most recent 30 days is returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#sub-account-transfer-history
    [[nodiscard]] common::RestApiResponse<std::vector<SubAccountTransferHistoryResponseInner>>
    sub_account_transfer_history(const SubAccountTransferHistoryParams& params = {}) const;

    /// Asynchronous `sub_account_transfer_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<SubAccountTransferHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_sub_account_transfer_history(const SubAccountTransferHistoryParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<std::vector<SubAccountTransferHistoryResponseInner>>(
            client_, sub_account_transfer_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Transfer to Master (For Sub-account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/transfer/subToMaster.
    ///
    /// Transfer to Master
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#transfer-to-master
    [[nodiscard]] common::RestApiResponse<TransferToMasterResponse>
    transfer_to_master(const TransferToMasterParams& params) const;

    /// Asynchronous `transfer_to_master()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TransferToMasterResponse>)`.
    template <class CompletionToken>
    auto async_transfer_to_master(const TransferToMasterParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<TransferToMasterResponse>(
            client_, transfer_to_master_request(params), std::forward<CompletionToken>(token));
    }

    /// Transfer to Sub-account of Same Master (For Sub-account) (USER_DATA)
    ///
    /// POST /sapi/v1/sub-account/transfer/subToSub.
    ///
    /// Transfer to Sub-account of Same Master
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You need to open Enable Spot & Margin Trading permission for the API Key which requests
    /// this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/vip-and-institutional-sub-account/api/rest-api/asset-management#transfer-to-sub-account-of-same-master
    [[nodiscard]] common::RestApiResponse<TransferToSubAccountOfSameMasterResponse>
    transfer_to_sub_account_of_same_master(
        const TransferToSubAccountOfSameMasterParams& params) const;

    /// Asynchronous `transfer_to_sub_account_of_same_master()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<TransferToSubAccountOfSameMasterResponse>)`.
    template <class CompletionToken>
    auto async_transfer_to_sub_account_of_same_master(
        const TransferToSubAccountOfSameMasterParams& params, CompletionToken&& token) const {
        return common::async_send<TransferToSubAccountOfSameMasterResponse>(
            client_, transfer_to_sub_account_of_same_master_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest futures_transfer_for_sub_account_request(
        const FuturesTransferForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_detail_on_sub_accounts_futures_account_request(
        const GetDetailOnSubAccountsFuturesAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_detail_on_sub_accounts_futures_account_v2_request(
        const GetDetailOnSubAccountsFuturesAccountV2Params& params) const;
    [[nodiscard]] common::RestRequest get_detail_on_sub_accounts_margin_account_request(
        const GetDetailOnSubAccountsMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_move_position_history_for_sub_account_request(
        const GetMovePositionHistoryForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    move_position_for_sub_account_request(const MovePositionForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    get_sub_account_deposit_address_request(const GetSubAccountDepositAddressParams& params) const;
    [[nodiscard]] common::RestRequest
    get_sub_account_deposit_history_request(const GetSubAccountDepositHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_summary_of_sub_accounts_futures_account_request(
        const GetSummaryOfSubAccountsFuturesAccountParams& params) const;
    [[nodiscard]] common::RestRequest get_summary_of_sub_accounts_futures_account_v2_request(
        const GetSummaryOfSubAccountsFuturesAccountV2Params& params) const;
    [[nodiscard]] common::RestRequest get_summary_of_sub_accounts_margin_account_request(
        const GetSummaryOfSubAccountsMarginAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_transfer_for_sub_account_request(const MarginTransferForSubAccountParams& params) const;
    [[nodiscard]] common::RestRequest
    query_sub_account_assets_request(const QuerySubAccountAssetsParams& params) const;
    [[nodiscard]] common::RestRequest query_sub_account_assets_asset_management_request(
        const QuerySubAccountAssetsAssetManagementParams& params) const;
    [[nodiscard]] common::RestRequest query_sub_account_futures_asset_transfer_history_request(
        const QuerySubAccountFuturesAssetTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest sub_account_futures_asset_transfer_request(
        const SubAccountFuturesAssetTransferParams& params) const;
    [[nodiscard]] common::RestRequest query_sub_account_spot_asset_transfer_history_request(
        const QuerySubAccountSpotAssetTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest query_sub_account_spot_assets_summary_request(
        const QuerySubAccountSpotAssetsSummaryParams& params) const;
    [[nodiscard]] common::RestRequest query_universal_transfer_history_request(
        const QueryUniversalTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    universal_transfer_request(const UniversalTransferParams& params) const;
    [[nodiscard]] common::RestRequest
    sub_account_transfer_history_request(const SubAccountTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    transfer_to_master_request(const TransferToMasterParams& params) const;
    [[nodiscard]] common::RestRequest transfer_to_sub_account_of_same_master_request(
        const TransferToSubAccountOfSameMasterParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::sub_account::rest_api
