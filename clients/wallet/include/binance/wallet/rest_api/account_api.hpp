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
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response.hpp>
#include <binance/wallet/rest_api/models/account_info_response.hpp>
#include <binance/wallet/rest_api/models/account_status_response.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response.hpp>
#include <binance/wallet/rest_api/models/get_api_key_permission_response.hpp>

namespace binance::wallet::rest_api {

enum class DailyAccountSnapshotTypeEnum {
    Spot,
    Margin,
    Futures,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_WALLET_EXPORT std::string_view
to_string(DailyAccountSnapshotTypeEnum value) noexcept;
BINANCE_WALLET_EXPORT DailyAccountSnapshotTypeEnum tag_invoke(
    boost::json::value_to_tag<DailyAccountSnapshotTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      DailyAccountSnapshotTypeEnum value);

struct AccountApiTradingStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AccountInfoParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AccountStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DailyAccountSnapshotParams {
    common::Required<DailyAccountSnapshotTypeEnum> type;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DisableFastWithdrawSwitchParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct EnableFastWithdrawSwitchParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetApiKeyPermissionParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_WALLET_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Account API Trading Status (USER_DATA)
    ///
    /// GET /sapi/v1/account/apiTradingStatus.
    ///
    /// Fetch account api trading status detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-api-trading-status
    [[nodiscard]] common::RestApiResponse<AccountApiTradingStatusResponse>
    account_api_trading_status(const AccountApiTradingStatusParams& params = {}) const;

    /// Asynchronous `account_api_trading_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountApiTradingStatusResponse>)`.
    template <class CompletionToken>
    auto async_account_api_trading_status(const AccountApiTradingStatusParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<AccountApiTradingStatusResponse>(
            client_, account_api_trading_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Account info (USER_DATA)
    ///
    /// GET /sapi/v1/account/info.
    ///
    /// Fetch account info detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-info
    [[nodiscard]] common::RestApiResponse<AccountInfoResponse>
    account_info(const AccountInfoParams& params = {}) const;

    /// Asynchronous `account_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountInfoResponse>)`.
    template <class CompletionToken>
    auto async_account_info(const AccountInfoParams& params, CompletionToken&& token) const {
        return common::async_send<AccountInfoResponse>(client_, account_info_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Account Status (USER_DATA)
    ///
    /// GET /sapi/v1/account/status.
    ///
    /// Fetch account status detail.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#account-status
    [[nodiscard]] common::RestApiResponse<AccountStatusResponse>
    account_status(const AccountStatusParams& params = {}) const;

    /// Asynchronous `account_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountStatusResponse>)`.
    template <class CompletionToken>
    auto async_account_status(const AccountStatusParams& params, CompletionToken&& token) const {
        return common::async_send<AccountStatusResponse>(client_, account_status_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Daily Account Snapshot (USER_DATA)
    ///
    /// GET /sapi/v1/accountSnapshot.
    ///
    /// Daily account snapshot
    ///
    /// Weight(IP): 2400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The query time period must be less then 30 days
    /// - Support query within the last one month only
    /// - If startTimeand endTime not sent, return records of the last 7 days by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#daily-account-snapshot
    [[nodiscard]] common::RestApiResponse<DailyAccountSnapshotResponse>
    daily_account_snapshot(const DailyAccountSnapshotParams& params) const;

    /// Asynchronous `daily_account_snapshot()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DailyAccountSnapshotResponse>)`.
    template <class CompletionToken>
    auto async_daily_account_snapshot(const DailyAccountSnapshotParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<DailyAccountSnapshotResponse>(
            client_, daily_account_snapshot_request(params), std::forward<CompletionToken>(token));
    }

    /// Disable Fast Withdraw Switch (USER_DATA)
    ///
    /// POST /sapi/v1/account/disableFastWithdrawSwitch.
    ///
    /// Disable Fast Withdraw Switch
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - This request will disable fastwithdraw switch under your account. You need to enable
    /// "trade" option for the api key which requests this endpoint.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#disable-fast-withdraw-switch
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    disable_fast_withdraw_switch(const DisableFastWithdrawSwitchParams& params = {}) const;

    /// Asynchronous `disable_fast_withdraw_switch()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_disable_fast_withdraw_switch(const DisableFastWithdrawSwitchParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      disable_fast_withdraw_switch_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Enable Fast Withdraw Switch (USER_DATA)
    ///
    /// POST /sapi/v1/account/enableFastWithdrawSwitch.
    ///
    /// Enable Fast Withdraw Switch (USER_DATA)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - This request will enable fastwithdraw switch under your account. You need to enable
    /// "trade" option for the api key which requests this endpoint.
    /// - When Fast Withdraw Switch is on, transferring funds to a Binance account will be done
    /// instantly. There is no on-chain transaction, no transaction ID and no withdrawal fee.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#enable-fast-withdraw-switch
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    enable_fast_withdraw_switch(const EnableFastWithdrawSwitchParams& params = {}) const;

    /// Asynchronous `enable_fast_withdraw_switch()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_enable_fast_withdraw_switch(const EnableFastWithdrawSwitchParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      enable_fast_withdraw_switch_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Get API Key Permission (USER_DATA)
    ///
    /// GET /sapi/v1/account/apiRestrictions.
    ///
    /// Get API Key Permission
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/account#get-api-key-permission
    [[nodiscard]] common::RestApiResponse<GetApiKeyPermissionResponse>
    get_api_key_permission(const GetApiKeyPermissionParams& params = {}) const;

    /// Asynchronous `get_api_key_permission()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetApiKeyPermissionResponse>)`.
    template <class CompletionToken>
    auto async_get_api_key_permission(const GetApiKeyPermissionParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<GetApiKeyPermissionResponse>(
            client_, get_api_key_permission_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_api_trading_status_request(const AccountApiTradingStatusParams& params) const;
    [[nodiscard]] common::RestRequest account_info_request(const AccountInfoParams& params) const;
    [[nodiscard]] common::RestRequest
    account_status_request(const AccountStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    daily_account_snapshot_request(const DailyAccountSnapshotParams& params) const;
    [[nodiscard]] common::RestRequest
    disable_fast_withdraw_switch_request(const DisableFastWithdrawSwitchParams& params) const;
    [[nodiscard]] common::RestRequest
    enable_fast_withdraw_switch_request(const EnableFastWithdrawSwitchParams& params) const;
    [[nodiscard]] common::RestRequest
    get_api_key_permission_request(const GetApiKeyPermissionParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::wallet::rest_api
