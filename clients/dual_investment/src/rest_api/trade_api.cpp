//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/trade_api.hpp>

namespace binance::dual_investment::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetDualInvestmentPositionsStatusEnum value) noexcept {
    switch (value) {
    case GetDualInvestmentPositionsStatusEnum::Pending:
        return "PENDING";
    case GetDualInvestmentPositionsStatusEnum::PurchaseSuccess:
        return "PURCHASE_SUCCESS";
    case GetDualInvestmentPositionsStatusEnum::Settled:
        return "SETTLED";
    case GetDualInvestmentPositionsStatusEnum::PurchaseFail:
        return "PURCHASE_FAIL";
    case GetDualInvestmentPositionsStatusEnum::Refunding:
        return "REFUNDING";
    case GetDualInvestmentPositionsStatusEnum::RefundSuccess:
        return "REFUND_SUCCESS";
    case GetDualInvestmentPositionsStatusEnum::Settling:
        return "SETTLING";
    case GetDualInvestmentPositionsStatusEnum::Unknown:
        break;
    }
    return "";
}

GetDualInvestmentPositionsStatusEnum
tag_invoke(boost::json::value_to_tag<GetDualInvestmentPositionsStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "PENDING") {
        return GetDualInvestmentPositionsStatusEnum::Pending;
    }
    if (s == "PURCHASE_SUCCESS") {
        return GetDualInvestmentPositionsStatusEnum::PurchaseSuccess;
    }
    if (s == "SETTLED") {
        return GetDualInvestmentPositionsStatusEnum::Settled;
    }
    if (s == "PURCHASE_FAIL") {
        return GetDualInvestmentPositionsStatusEnum::PurchaseFail;
    }
    if (s == "REFUNDING") {
        return GetDualInvestmentPositionsStatusEnum::Refunding;
    }
    if (s == "REFUND_SUCCESS") {
        return GetDualInvestmentPositionsStatusEnum::RefundSuccess;
    }
    if (s == "SETTLING") {
        return GetDualInvestmentPositionsStatusEnum::Settling;
    }
    return GetDualInvestmentPositionsStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetDualInvestmentPositionsStatusEnum value) {
    if (value == GetDualInvestmentPositionsStatusEnum::Unknown) {
        throw std::invalid_argument("GetDualInvestmentPositionsStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest TradeApi::check_dual_investment_accounts_request(
    const CheckDualInvestmentAccountsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/dci/product/accounts";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CheckDualInvestmentAccountsResponse>
TradeApi::check_dual_investment_accounts(const CheckDualInvestmentAccountsParams& params) const {
    return common::send<CheckDualInvestmentAccountsResponse>(
        *client_, check_dual_investment_accounts_request(params));
}

common::RestRequest TradeApi::get_dual_investment_positions_request(
    const GetDualInvestmentPositionsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/dci/product/positions";
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetDualInvestmentPositionsResponse>
TradeApi::get_dual_investment_positions(const GetDualInvestmentPositionsParams& params) const {
    return common::send<GetDualInvestmentPositionsResponse>(
        *client_, get_dual_investment_positions_request(params));
}

common::RestRequest TradeApi::subscribe_dual_investment_products_request(
    const SubscribeDualInvestmentProductsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/dci/product/subscribe";
    common::detail::json::set_param(req.query, "id", params.id);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "depositAmount", params.deposit_amount);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubscribeDualInvestmentProductsResponse>
TradeApi::subscribe_dual_investment_products(
    const SubscribeDualInvestmentProductsParams& params) const {
    return common::send<SubscribeDualInvestmentProductsResponse>(
        *client_, subscribe_dual_investment_products_request(params));
}

} // namespace binance::dual_investment::rest_api
