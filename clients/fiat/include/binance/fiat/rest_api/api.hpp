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
#include <binance/fiat/export.hpp>
#include <binance/fiat/rest_api/models/deposit_response.hpp>
#include <binance/fiat/rest_api/models/fiat_withdraw_request_account_info.hpp>
#include <binance/fiat/rest_api/models/fiat_withdraw_response.hpp>
#include <binance/fiat/rest_api/models/get_fiat_deposit_withdraw_history_response.hpp>
#include <binance/fiat/rest_api/models/get_fiat_payments_history_response.hpp>
#include <binance/fiat/rest_api/models/get_order_detail_response.hpp>

namespace binance::fiat::rest_api {

enum class DepositApiPaymentMethodEnum {
    Pix,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_FIAT_EXPORT std::string_view
to_string(DepositApiPaymentMethodEnum value) noexcept;
BINANCE_FIAT_EXPORT DepositApiPaymentMethodEnum tag_invoke(
    boost::json::value_to_tag<DepositApiPaymentMethodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    DepositApiPaymentMethodEnum value);

enum class FiatWithdrawApiPaymentMethodEnum {
    BankTransfer,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_FIAT_EXPORT std::string_view
to_string(FiatWithdrawApiPaymentMethodEnum value) noexcept;
BINANCE_FIAT_EXPORT FiatWithdrawApiPaymentMethodEnum
tag_invoke(boost::json::value_to_tag<FiatWithdrawApiPaymentMethodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    FiatWithdrawApiPaymentMethodEnum value);

struct DepositParams {
    common::Required<std::string> currency;
    /// payment method; current supported: pix
    common::Required<DepositApiPaymentMethodEnum> api_payment_method;
    /// deposit amount
    common::Required<std::string> amount;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
    std::optional<boost::json::value> ext = std::nullopt;
};

struct FiatWithdrawParams {
    /// Fiat currency, such as BRL, ARS, MXN
    common::Required<std::string> currency;
    /// payment method; current supported: bank_transfer
    common::Required<FiatWithdrawApiPaymentMethodEnum> api_payment_method;
    /// withdraw amount
    common::Required<std::int64_t> amount;
    common::Required<FiatWithdrawRequestAccountInfo> account_info;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
    std::optional<boost::json::value> ext = std::nullopt;
};

struct GetFiatDepositWithdrawHistoryParams {
    /// 0: deposit, 1: withdraw
    common::Required<std::string> transaction_type;
    std::optional<std::int64_t> begin_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> rows = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFiatPaymentsHistoryParams {
    /// 0: buy, 1: sell
    common::Required<std::string> transaction_type;
    std::optional<std::int64_t> begin_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> page = std::nullopt;
    std::optional<std::int64_t> rows = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOrderDetailParams {
    /// Order ID retrieved from the withdrawal API
    common::Required<std::string> order_no;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_FIAT_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::RestClient> client);

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
    deposit(const DepositParams& params) const;

    /// Asynchronous `deposit()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DepositResponse>)`.
    template <class CompletionToken>
    auto async_deposit(const DepositParams& params, CompletionToken&& token) const {
        return common::async_send<DepositResponse>(client_, deposit_request(params),
                                                   std::forward<CompletionToken>(token));
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
    fiat_withdraw(const FiatWithdrawParams& params) const;

    /// Asynchronous `fiat_withdraw()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FiatWithdrawResponse>)`.
    template <class CompletionToken>
    auto async_fiat_withdraw(const FiatWithdrawParams& params, CompletionToken&& token) const {
        return common::async_send<FiatWithdrawResponse>(client_, fiat_withdraw_request(params),
                                                        std::forward<CompletionToken>(token));
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
    get_fiat_deposit_withdraw_history(const GetFiatDepositWithdrawHistoryParams& params) const;

    /// Asynchronous `get_fiat_deposit_withdraw_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFiatDepositWithdrawHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_fiat_deposit_withdraw_history(const GetFiatDepositWithdrawHistoryParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<GetFiatDepositWithdrawHistoryResponse>(
            client_, get_fiat_deposit_withdraw_history_request(params),
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
    get_fiat_payments_history(const GetFiatPaymentsHistoryParams& params) const;

    /// Asynchronous `get_fiat_payments_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFiatPaymentsHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_fiat_payments_history(const GetFiatPaymentsHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetFiatPaymentsHistoryResponse>(
            client_, get_fiat_payments_history_request(params),
            std::forward<CompletionToken>(token));
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
    get_order_detail(const GetOrderDetailParams& params) const;

    /// Asynchronous `get_order_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOrderDetailResponse>)`.
    template <class CompletionToken>
    auto async_get_order_detail(const GetOrderDetailParams& params, CompletionToken&& token) const {
        return common::async_send<GetOrderDetailResponse>(client_, get_order_detail_request(params),
                                                          std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest deposit_request(const DepositParams& params) const;
    [[nodiscard]] common::RestRequest fiat_withdraw_request(const FiatWithdrawParams& params) const;
    [[nodiscard]] common::RestRequest get_fiat_deposit_withdraw_history_request(
        const GetFiatDepositWithdrawHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_fiat_payments_history_request(const GetFiatPaymentsHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_order_detail_request(const GetOrderDetailParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::fiat::rest_api
