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

#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/account_information_response_result.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/futures_account_balance_response_result_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

struct AccountInformationParams {
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesAccountBalanceParams {
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::WebsocketApi> client);

    /// Account Information (USER_DATA)
    ///
    /// `account.status`.
    ///
    /// Get current account information. User in single-asset/ multi-assets mode
    /// will see different value, see comments in response section for detail.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/account#account-information
    [[nodiscard]] common::WebsocketApiResponse<AccountInformationResponseResult>
    account_information(const AccountInformationParams& params = {}) const;

    /// Asynchronous `account_information()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<AccountInformationResponseResult>)`.
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<AccountInformationResponseResult>(
            client_, "account.status", account_information_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance (USER_DATA)
    ///
    /// `account.balance`.
    ///
    /// Futures Account Balance
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/account#futures-account-balance
    [[nodiscard]] common::WebsocketApiResponse<
        std::vector<FuturesAccountBalanceResponseResultInner>>
    futures_account_balance(const FuturesAccountBalanceParams& params = {}) const;

    /// Asynchronous `futures_account_balance()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<FuturesAccountBalanceResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_futures_account_balance(const FuturesAccountBalanceParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<FuturesAccountBalanceResponseResultInner>>(
            client_, "account.balance", futures_account_balance_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params
    account_information_payload(const AccountInformationParams& params);
    [[nodiscard]] static common::Params
    futures_account_balance_payload(const FuturesAccountBalanceParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::derivatives_trading_coin_futures::websocket_api
