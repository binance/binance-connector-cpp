//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/account_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(AccountFundingFlowCurrencyEnum value) noexcept {
    switch (value) {
    case AccountFundingFlowCurrencyEnum::Usdt:
        return "USDT";
    case AccountFundingFlowCurrencyEnum::Unknown:
        break;
    }
    return "";
}

AccountFundingFlowCurrencyEnum
tag_invoke(boost::json::value_to_tag<AccountFundingFlowCurrencyEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USDT") {
        return AccountFundingFlowCurrencyEnum::Usdt;
    }
    return AccountFundingFlowCurrencyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                AccountFundingFlowCurrencyEnum value) {
    if (value == AccountFundingFlowCurrencyEnum::Unknown) {
        throw std::invalid_argument("AccountFundingFlowCurrencyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
AccountApi::account_funding_flow_request(const AccountFundingFlowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/bill";
    common::detail::json::set_param(req.query, "currency", params.currency);
    common::detail::json::set_param(req.query, "recordId", params.record_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AccountFundingFlowResponseInner>>
AccountApi::account_funding_flow(const AccountFundingFlowParams& params) const {
    return common::send<std::vector<AccountFundingFlowResponseInner>>(
        *client_, account_funding_flow_request(params));
}

common::RestRequest AccountApi::option_margin_account_information_request(
    const OptionMarginAccountInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/marginAccount";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionMarginAccountInformationResponse>
AccountApi::option_margin_account_information(
    const OptionMarginAccountInformationParams& params) const {
    return common::send<OptionMarginAccountInformationResponse>(
        *client_, option_margin_account_information_request(params));
}

} // namespace binance::derivatives_trading_options::rest_api
