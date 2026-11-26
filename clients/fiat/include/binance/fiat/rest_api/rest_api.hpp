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
#include <binance/fiat/export.hpp>
#include <binance/fiat/rest_api/api.hpp>
#include <binance/fiat/rest_api/models.hpp>

namespace binance::fiat::rest_api {

/// Fiat REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_FIAT_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Fiat REST API).
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

    // Api

    /// Deposit (TRADE)
    ///
    /// POST /sapi/v1/fiat/deposit.
    ///
    /// Submit deposit request, in this version, we only support BRL deposit via pix.
    ///
    /// For BRL deposit via pix, you need to place an order before making a transfer from your bank.
    ///
    /// Before calling this api, please make sure you have already completed your KYC or KYB, and
    /// already activated your fiat service on our website.
    ///
    /// Weight(UID): 45000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `timestamp`, `signature` and `recvWindow` are sent as query-string parameters, while the
    /// business fields (`currency`, `apiPaymentMethod`, `amount`, `ext`) are sent in the JSON
    /// request body with `Content-Type: application/json`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-fiat/api/rest-api/~#deposit
    [[nodiscard]] common::RestApiResponse<DepositResponse>
    deposit(const DepositParams& params) const {
        return api_.deposit(params);
    }
    /// Asynchronous `deposit()`.
    template <class CompletionToken>
    auto async_deposit(const DepositParams& params, CompletionToken&& token) const {
        return api_.async_deposit(params, std::forward<CompletionToken>(token));
    }

    /// Fiat Withdraw (TRADE)
    ///
    /// POST /sapi/v2/fiat/withdraw.
    ///
    /// Submit withdraw request, in this version, we support BRL,ARS,MXN withdrawal via
    /// bank_transfer.
    ///
    /// You need to call this api first, and call query order detail api in a loop to get the status
    /// of the order until this order is successful.
    ///
    /// Before calling this api, please make sure you have already completed your KYC or KYB, and
    /// already activated your fiat service on our website.
    ///
    /// Weight(UID): 45000
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-fiat/api/rest-api/~#fiat-withdraw
    [[nodiscard]] common::RestApiResponse<FiatWithdrawResponse>
    fiat_withdraw(const FiatWithdrawParams& params) const {
        return api_.fiat_withdraw(params);
    }
    /// Asynchronous `fiat_withdraw()`.
    template <class CompletionToken>
    auto async_fiat_withdraw(const FiatWithdrawParams& params, CompletionToken&& token) const {
        return api_.async_fiat_withdraw(params, std::forward<CompletionToken>(token));
    }

    /// Get Fiat Deposit/Withdraw History (USER_DATA)
    ///
    /// GET /sapi/v1/fiat/orders.
    ///
    /// Get Fiat Deposit/Withdraw History
    ///
    /// Weight(UID): 45000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `beginTime` and `endTime` are not sent, recent 30-day data is returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-fiat/api/rest-api/~#get-fiat-deposit-withdraw-history
    [[nodiscard]] common::RestApiResponse<GetFiatDepositWithdrawHistoryResponse>
    get_fiat_deposit_withdraw_history(const GetFiatDepositWithdrawHistoryParams& params) const {
        return api_.get_fiat_deposit_withdraw_history(params);
    }
    /// Asynchronous `get_fiat_deposit_withdraw_history()`.
    template <class CompletionToken>
    auto async_get_fiat_deposit_withdraw_history(const GetFiatDepositWithdrawHistoryParams& params,
                                                 CompletionToken&& token) const {
        return api_.async_get_fiat_deposit_withdraw_history(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Get Fiat Payments History (USER_DATA)
    ///
    /// GET /sapi/v1/fiat/payments.
    ///
    /// Get Fiat Payments History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `beginTime` and `endTime` are not sent, recent 30-day data is returned.
    /// - `paymentMethod` is returned only when querying buy history (`transactionType=0`).
    /// - Supported payment methods: `Cash Balance`, `Credit Card`, `Online Banking`, `Bank
    /// Transfer`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-fiat/api/rest-api/~#get-fiat-payments-history
    [[nodiscard]] common::RestApiResponse<GetFiatPaymentsHistoryResponse>
    get_fiat_payments_history(const GetFiatPaymentsHistoryParams& params) const {
        return api_.get_fiat_payments_history(params);
    }
    /// Asynchronous `get_fiat_payments_history()`.
    template <class CompletionToken>
    auto async_get_fiat_payments_history(const GetFiatPaymentsHistoryParams& params,
                                         CompletionToken&& token) const {
        return api_.async_get_fiat_payments_history(params, std::forward<CompletionToken>(token));
    }

    /// Get Order Detail (USER_DATA)
    ///
    /// GET /sapi/v1/fiat/get-order-detail.
    ///
    /// Get Order Detail
    ///
    /// Before calling this api, please make sure you have already completed your KYC or KYB, and
    /// already activated your fiat service on our website.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-fiat/api/rest-api/~#get-order-detail
    [[nodiscard]] common::RestApiResponse<GetOrderDetailResponse>
    get_order_detail(const GetOrderDetailParams& params) const {
        return api_.get_order_detail(params);
    }
    /// Asynchronous `get_order_detail()`.
    template <class CompletionToken>
    auto async_get_order_detail(const GetOrderDetailParams& params, CompletionToken&& token) const {
        return api_.async_get_order_detail(params, std::forward<CompletionToken>(token));
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
    Api api_;
};

} // namespace binance::fiat::rest_api
