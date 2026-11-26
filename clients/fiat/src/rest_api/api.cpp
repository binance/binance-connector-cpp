//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/api.hpp>

namespace binance::fiat::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(DepositApiPaymentMethodEnum value) noexcept {
    switch (value) {
    case DepositApiPaymentMethodEnum::Pix:
        return "pix";
    case DepositApiPaymentMethodEnum::Unknown:
        break;
    }
    return "";
}

DepositApiPaymentMethodEnum
tag_invoke(boost::json::value_to_tag<DepositApiPaymentMethodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "pix") {
        return DepositApiPaymentMethodEnum::Pix;
    }
    return DepositApiPaymentMethodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                DepositApiPaymentMethodEnum value) {
    if (value == DepositApiPaymentMethodEnum::Unknown) {
        throw std::invalid_argument("DepositApiPaymentMethodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(FiatWithdrawApiPaymentMethodEnum value) noexcept {
    switch (value) {
    case FiatWithdrawApiPaymentMethodEnum::BankTransfer:
        return "bank_transfer";
    case FiatWithdrawApiPaymentMethodEnum::Unknown:
        break;
    }
    return "";
}

FiatWithdrawApiPaymentMethodEnum
tag_invoke(boost::json::value_to_tag<FiatWithdrawApiPaymentMethodEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "bank_transfer") {
        return FiatWithdrawApiPaymentMethodEnum::BankTransfer;
    }
    return FiatWithdrawApiPaymentMethodEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FiatWithdrawApiPaymentMethodEnum value) {
    if (value == FiatWithdrawApiPaymentMethodEnum::Unknown) {
        throw std::invalid_argument("FiatWithdrawApiPaymentMethodEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

Api::Api(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest Api::deposit_request(const DepositParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/fiat/deposit";
    common::detail::json::set_param(req.body, "currency", params.currency);
    common::detail::json::set_param(req.body, "apiPaymentMethod", params.api_payment_method);
    common::detail::json::set_param(req.body, "amount", params.amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.body, "ext", params.ext);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<DepositResponse> Api::deposit(const DepositParams& params) const {
    return common::send<DepositResponse>(*client_, deposit_request(params));
}

common::RestRequest Api::fiat_withdraw_request(const FiatWithdrawParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v2/fiat/withdraw";
    common::detail::json::set_param(req.body, "currency", params.currency);
    common::detail::json::set_param(req.body, "apiPaymentMethod", params.api_payment_method);
    common::detail::json::set_param(req.body, "amount", params.amount);
    common::detail::json::set_param(req.body, "accountInfo", params.account_info);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    common::detail::json::set_param(req.body, "ext", params.ext);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FiatWithdrawResponse>
Api::fiat_withdraw(const FiatWithdrawParams& params) const {
    return common::send<FiatWithdrawResponse>(*client_, fiat_withdraw_request(params));
}

common::RestRequest Api::get_fiat_deposit_withdraw_history_request(
    const GetFiatDepositWithdrawHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/fiat/orders";
    common::detail::json::set_param(req.query, "transactionType", params.transaction_type);
    common::detail::json::set_param(req.query, "beginTime", params.begin_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "rows", params.rows);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFiatDepositWithdrawHistoryResponse>
Api::get_fiat_deposit_withdraw_history(const GetFiatDepositWithdrawHistoryParams& params) const {
    return common::send<GetFiatDepositWithdrawHistoryResponse>(
        *client_, get_fiat_deposit_withdraw_history_request(params));
}

common::RestRequest
Api::get_fiat_payments_history_request(const GetFiatPaymentsHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/fiat/payments";
    common::detail::json::set_param(req.query, "transactionType", params.transaction_type);
    common::detail::json::set_param(req.query, "beginTime", params.begin_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "rows", params.rows);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFiatPaymentsHistoryResponse>
Api::get_fiat_payments_history(const GetFiatPaymentsHistoryParams& params) const {
    return common::send<GetFiatPaymentsHistoryResponse>(*client_,
                                                        get_fiat_payments_history_request(params));
}

common::RestRequest Api::get_order_detail_request(const GetOrderDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/fiat/get-order-detail";
    common::detail::json::set_param(req.query, "orderNo", params.order_no);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOrderDetailResponse>
Api::get_order_detail(const GetOrderDetailParams& params) const {
    return common::send<GetOrderDetailResponse>(*client_, get_order_detail_request(params));
}

} // namespace binance::fiat::rest_api
