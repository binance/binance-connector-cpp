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
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_address_response.hpp>
#include <binance/wallet/rest_api/models/deposit_history_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_deposit_address_list_with_network_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_address_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_quota_response.hpp>
#include <binance/wallet/rest_api/models/one_click_arrival_deposit_apply_response.hpp>
#include <binance/wallet/rest_api/models/withdraw_history_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_response.hpp>

namespace binance::wallet::rest_api {

enum class DepositHistoryStatusEnum {
    Status0,
    Status1,
    Status2,
    Status6,
    Status7,
    Status8,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(DepositHistoryStatusEnum value) noexcept;
BINANCE_WALLET_EXPORT DepositHistoryStatusEnum tag_invoke(
    boost::json::value_to_tag<DepositHistoryStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      DepositHistoryStatusEnum value);

struct AllCoinsInformationParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DepositAddressParams {
    /// `coin` refers to the parent network address format that the address is using
    common::Required<std::string> coin;
    std::optional<std::string> network = std::nullopt;
    std::optional<common::Decimal> amount = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DepositHistoryParams {
    /// return `sourceAddress` field when set to `true`
    std::optional<bool> include_source = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// 0: pending, 1: success, 2: rejected, 6: credited but cannot withdraw, 7: Wrong Deposit, 8:
    /// Waiting User confirm
    std::optional<DepositHistoryStatusEnum> status = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
    std::optional<std::string> tx_id = std::nullopt;
};

struct FetchDepositAddressListWithNetworkParams {
    /// Coin name
    common::Required<std::string> coin;
    /// If network is not send, return with default network of the coin. You can get network and
    /// isDefault in networkList in the response of `Get /sapi/v1/capital/config/getall`
    std::optional<std::string> network = std::nullopt;
};

struct OneClickArrivalDepositApplyParams {
    /// Deposit record Id, priority use
    std::optional<std::int64_t> deposit_id = std::nullopt;
    /// Deposit txId, used when depositId is not specified
    std::optional<std::string> tx_id = std::nullopt;
    /// Sub-accountId of Cloud user
    std::optional<std::string> sub_account_id = std::nullopt;
    /// Sub-userId of parent user
    std::optional<std::int64_t> sub_user_id = std::nullopt;
};

struct WithdrawParams {
    common::Required<std::string> coin;
    /// Withdrawal address
    common::Required<std::string> address;
    /// Amount
    common::Required<common::Decimal> amount;
    /// client side id for withdrawal, if provide here, can be used in GET
    /// `/sapi/v1/capital/withdraw/history` for query.
    std::optional<std::string> withdraw_order_id = std::nullopt;
    /// Withdrawal network
    std::optional<std::string> network = std::nullopt;
    /// Secondary address identifier for coins like XRP,XMR etc.
    std::optional<std::string> address_tag = std::nullopt;
    /// When making internal transfer, `true` for returning the fee to the destination account;
    /// `false` for returning the fee back to the departure account. Default `false`.
    std::optional<bool> transaction_fee_flag = std::nullopt;
    std::optional<std::string> name = std::nullopt;
    /// The wallet type for withdraw，0-spot wallet ，1-funding wallet. Default walletType is the
    /// current "selected wallet" under wallet->Fiat and Spot/Funding->Deposit
    std::optional<std::int64_t> wallet_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WithdrawHistoryParams {
    std::optional<std::string> coin = std::nullopt;
    /// client side id for withdrawal, if provided in POST `/sapi/v1/capital/withdraw/apply`, can be
    /// used here for query.
    std::optional<std::string> withdraw_order_id = std::nullopt;
    /// 0(0: Email Sent, 2: Awaiting Approval 3: Rejected 4: Processing 6: Completed)
    std::optional<std::int64_t> status = std::nullopt;
    /// Default: 0
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// id list returned in the response of POST `/sapi/v1/capital/withdraw/apply`, separated by `,`
    std::optional<std::string> id_list = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_WALLET_EXPORT CapitalApi {
public:
    explicit CapitalApi(std::shared_ptr<common::RestClient> client);

    /// All Coins' Information (USER_DATA)
    ///
    /// GET /sapi/v1/capital/config/getall.
    ///
    /// Get information of coins (available for deposit and withdraw) for user.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#all-coins-information
    [[nodiscard]] common::RestApiResponse<std::vector<AllCoinsInformationResponseInner>>
    all_coins_information(const AllCoinsInformationParams& params = {}) const;

    /// Asynchronous `all_coins_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AllCoinsInformationResponseInner>>)`.
    template <class CompletionToken>
    auto async_all_coins_information(const AllCoinsInformationParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<AllCoinsInformationResponseInner>>(
            client_, all_coins_information_request(params), std::forward<CompletionToken>(token));
    }

    /// Deposit Address(supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/address.
    ///
    /// Fetch deposit address with network.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` is not send, return with default network of the coin.
    /// - You can get `network` and `isDefault` in `networkList` in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - `amount` needs to be sent if using LIGHTNING network
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#deposit-address
    [[nodiscard]] common::RestApiResponse<DepositAddressResponse>
    deposit_address(const DepositAddressParams& params) const;

    /// Asynchronous `deposit_address()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DepositAddressResponse>)`.
    template <class CompletionToken>
    auto async_deposit_address(const DepositAddressParams& params, CompletionToken&& token) const {
        return common::async_send<DepositAddressResponse>(client_, deposit_address_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Deposit History (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/hisrec.
    ///
    /// Fetch deposit history.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 90 days.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#deposit-history
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryResponseInner>>
    deposit_history(const DepositHistoryParams& params = {}) const;

    /// Asynchronous `deposit_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<DepositHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_deposit_history(const DepositHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<DepositHistoryResponseInner>>(
            client_, deposit_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Fetch deposit address list with network (USER_DATA)
    ///
    /// GET /sapi/v1/capital/deposit/address/list.
    ///
    /// Fetch deposit address list with network.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-deposit-address-list-with-network
    [[nodiscard]] common::RestApiResponse<
        std::vector<FetchDepositAddressListWithNetworkResponseInner>>
    fetch_deposit_address_list_with_network(
        const FetchDepositAddressListWithNetworkParams& params) const;

    /// Asynchronous `fetch_deposit_address_list_with_network()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FetchDepositAddressListWithNetworkResponseInner>>)`.
    template <class CompletionToken>
    auto async_fetch_deposit_address_list_with_network(
        const FetchDepositAddressListWithNetworkParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<FetchDepositAddressListWithNetworkResponseInner>>(
            client_, fetch_deposit_address_list_with_network_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Fetch withdraw address list (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/address/list.
    ///
    /// Fetch withdraw address list
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-withdraw-address-list
    [[nodiscard]] common::RestApiResponse<std::vector<FetchWithdrawAddressListResponseInner>>
    fetch_withdraw_address_list() const;

    /// Asynchronous `fetch_withdraw_address_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FetchWithdrawAddressListResponseInner>>)`.
    template <class CompletionToken>
    auto async_fetch_withdraw_address_list(CompletionToken&& token) const {
        return common::async_send<std::vector<FetchWithdrawAddressListResponseInner>>(
            client_, fetch_withdraw_address_list_request(), std::forward<CompletionToken>(token));
    }

    /// Fetch withdraw quota (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/quota.
    ///
    /// Fetch withdraw quota
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#fetch-withdraw-quota
    [[nodiscard]] common::RestApiResponse<FetchWithdrawQuotaResponse> fetch_withdraw_quota() const;

    /// Asynchronous `fetch_withdraw_quota()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FetchWithdrawQuotaResponse>)`.
    template <class CompletionToken>
    auto async_fetch_withdraw_quota(CompletionToken&& token) const {
        return common::async_send<FetchWithdrawQuotaResponse>(
            client_, fetch_withdraw_quota_request(), std::forward<CompletionToken>(token));
    }

    /// One click arrival deposit apply (for expired address deposit) (USER_DATA)
    ///
    /// POST /sapi/v1/capital/deposit/credit-apply.
    ///
    /// Apply deposit credit for expired address (One click arrival)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#one-click-arrival-deposit-apply
    [[nodiscard]] common::RestApiResponse<OneClickArrivalDepositApplyResponse>
    one_click_arrival_deposit_apply(const OneClickArrivalDepositApplyParams& params = {}) const;

    /// Asynchronous `one_click_arrival_deposit_apply()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OneClickArrivalDepositApplyResponse>)`.
    template <class CompletionToken>
    auto async_one_click_arrival_deposit_apply(const OneClickArrivalDepositApplyParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<OneClickArrivalDepositApplyResponse>(
            client_, one_click_arrival_deposit_apply_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Withdraw (USER_DATA)
    ///
    /// POST /sapi/v1/capital/withdraw/apply.
    ///
    /// Submit a withdraw request
    ///
    /// Weight(UID): 900
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin.
    /// - You can get `network` and `isDefault` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - To check if travel rule is required, by using `GET
    /// /sapi/v1/localentity/questionnaire-requirements` and if it returns anything other than `NIL`
    /// you will need update SAPI to `POST /sapi/v1/localentity/withdraw/apply` else you can
    /// continue `POST /sapi/v1/capital/withdraw/apply`. Please note that if you are required to
    /// comply to travel rule please refer to the Travel Rule SAPI.
    /// - "For networks that do not support memo/tag, submitting a withdrawal request with a
    /// non-empty `addressTag` will return error `-4106 TAG_NOT_SUPPORTED_FOR_NETWORK`. Please omit
    /// the `addressTag` field for such networks. You can check whether a network requires a tag via
    /// `GET /sapi/v1/capital/config/getall`: If `withdrawTag` = `true` → memo/tag is required. If
    /// `withdrawTag` = `false` → memo/tag is not supported; omit `addressTag`."
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#withdraw
    [[nodiscard]] common::RestApiResponse<WithdrawResponse>
    withdraw(const WithdrawParams& params) const;

    /// Asynchronous `withdraw()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<WithdrawResponse>)`.
    template <class CompletionToken>
    auto async_withdraw(const WithdrawParams& params, CompletionToken&& token) const {
        return common::async_send<WithdrawResponse>(client_, withdraw_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Withdraw History (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/capital/withdraw/history.
    ///
    /// Fetch withdraw history
    ///
    /// Weight(UID): 18000 (10 requests per second)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    /// - If `withdrawOrderId` is sent, time between `startTime` and `endTime` must be less than 7
    /// days.
    /// - If `withdrawOrderId` is sent, `startTime` and `endTime` are not sent, will return last 7
    /// days records by default.
    /// - Maximum support `idList` number is 45.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/capital#withdraw-history
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryResponseInner>>
    withdraw_history(const WithdrawHistoryParams& params = {}) const;

    /// Asynchronous `withdraw_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<WithdrawHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_withdraw_history(const WithdrawHistoryParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<WithdrawHistoryResponseInner>>(
            client_, withdraw_history_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    all_coins_information_request(const AllCoinsInformationParams& params) const;
    [[nodiscard]] common::RestRequest
    deposit_address_request(const DepositAddressParams& params) const;
    [[nodiscard]] common::RestRequest
    deposit_history_request(const DepositHistoryParams& params) const;
    [[nodiscard]] common::RestRequest fetch_deposit_address_list_with_network_request(
        const FetchDepositAddressListWithNetworkParams& params) const;
    [[nodiscard]] common::RestRequest fetch_withdraw_address_list_request() const;
    [[nodiscard]] common::RestRequest fetch_withdraw_quota_request() const;
    [[nodiscard]] common::RestRequest
    one_click_arrival_deposit_apply_request(const OneClickArrivalDepositApplyParams& params) const;
    [[nodiscard]] common::RestRequest withdraw_request(const WithdrawParams& params) const;
    [[nodiscard]] common::RestRequest
    withdraw_history_request(const WithdrawHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::wallet::rest_api
