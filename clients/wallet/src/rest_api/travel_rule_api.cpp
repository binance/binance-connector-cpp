//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/travel_rule_api.hpp>

namespace binance::wallet::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

TravelRuleApi::TravelRuleApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
TravelRuleApi::broker_withdraw_request(const BrokerWithdrawParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/localentity/broker/withdraw/apply";
    common::detail::json::set_param(req.query, "address", params.address);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "questionnaire", params.questionnaire);
    common::detail::json::set_param(req.query, "originatorPii", params.originator_pii);
    common::detail::json::set_param(req.query, "addressTag", params.address_tag);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "addressName", params.address_name);
    common::detail::json::set_param(req.query, "transactionFeeFlag", params.transaction_fee_flag);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<BrokerWithdrawResponse>
TravelRuleApi::broker_withdraw(const BrokerWithdrawParams& params) const {
    return common::send<BrokerWithdrawResponse>(*client_, broker_withdraw_request(params));
}

common::RestRequest TravelRuleApi::check_questionnaire_requirements_request(
    const CheckQuestionnaireRequirementsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/questionnaire-requirements";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CheckQuestionnaireRequirementsResponse>
TravelRuleApi::check_questionnaire_requirements(
    const CheckQuestionnaireRequirementsParams& params) const {
    return common::send<CheckQuestionnaireRequirementsResponse>(
        *client_, check_questionnaire_requirements_request(params));
}

common::RestRequest TravelRuleApi::deposit_history_travel_rule_request(
    const DepositHistoryTravelRuleParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/deposit/history";
    common::detail::json::set_param(req.query, "trId", params.tr_id);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "tranId", params.tran_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "travelRuleStatus", params.travel_rule_status);
    common::detail::json::set_param(req.query, "pendingQuestionnaire",
                                    params.pending_questionnaire);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<DepositHistoryTravelRuleResponseInner>>
TravelRuleApi::deposit_history_travel_rule(const DepositHistoryTravelRuleParams& params) const {
    return common::send<std::vector<DepositHistoryTravelRuleResponseInner>>(
        *client_, deposit_history_travel_rule_request(params));
}

common::RestRequest
TravelRuleApi::deposit_history_v2_request(const DepositHistoryV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/localentity/deposit/history";
    common::detail::json::set_param(req.query, "depositId", params.deposit_id);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "retrieveQuestionnaire",
                                    params.retrieve_questionnaire);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<DepositHistoryV2ResponseInner>>
TravelRuleApi::deposit_history_v2(const DepositHistoryV2Params& params) const {
    return common::send<std::vector<DepositHistoryV2ResponseInner>>(
        *client_, deposit_history_v2_request(params));
}

common::RestRequest TravelRuleApi::fetch_address_verification_list_request(
    const FetchAddressVerificationListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/addressVerify/list";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<FetchAddressVerificationListResponseInner>>
TravelRuleApi::fetch_address_verification_list(
    const FetchAddressVerificationListParams& params) const {
    return common::send<std::vector<FetchAddressVerificationListResponseInner>>(
        *client_, fetch_address_verification_list_request(params));
}

common::RestRequest
TravelRuleApi::get_country_list_request(const GetCountryListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/country/list";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCountryListResponse>
TravelRuleApi::get_country_list(const GetCountryListParams& params) const {
    return common::send<GetCountryListResponse>(*client_, get_country_list_request(params));
}

common::RestRequest
TravelRuleApi::get_region_list_request(const GetRegionListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/region/list";
    common::detail::json::set_param(req.query, "countryCode", params.country_code);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetRegionListResponse>
TravelRuleApi::get_region_list(const GetRegionListParams& params) const {
    return common::send<GetRegionListResponse>(*client_, get_region_list_request(params));
}

common::RestRequest TravelRuleApi::submit_deposit_questionnaire_request(
    const SubmitDepositQuestionnaireParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v1/localentity/broker/deposit/provide-info";
    common::detail::json::set_param(req.query, "subAccountId", params.sub_account_id);
    common::detail::json::set_param(req.query, "depositId", params.deposit_id);
    common::detail::json::set_param(req.query, "questionnaire", params.questionnaire);
    common::detail::json::set_param(req.query, "beneficiaryPii", params.beneficiary_pii);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "address", params.address);
    common::detail::json::set_param(req.query, "addressTag", params.address_tag);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubmitDepositQuestionnaireResponse>
TravelRuleApi::submit_deposit_questionnaire(const SubmitDepositQuestionnaireParams& params) const {
    return common::send<SubmitDepositQuestionnaireResponse>(
        *client_, submit_deposit_questionnaire_request(params));
}

common::RestRequest TravelRuleApi::submit_deposit_questionnaire_travel_rule_request(
    const SubmitDepositQuestionnaireTravelRuleParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v1/localentity/deposit/provide-info";
    common::detail::json::set_param(req.query, "tranId", params.tran_id);
    common::detail::json::set_param(req.query, "questionnaire", params.questionnaire);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubmitDepositQuestionnaireTravelRuleResponse>
TravelRuleApi::submit_deposit_questionnaire_travel_rule(
    const SubmitDepositQuestionnaireTravelRuleParams& params) const {
    return common::send<SubmitDepositQuestionnaireTravelRuleResponse>(
        *client_, submit_deposit_questionnaire_travel_rule_request(params));
}

common::RestRequest TravelRuleApi::submit_deposit_questionnaire_v2_request(
    const SubmitDepositQuestionnaireV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/sapi/v2/localentity/deposit/provide-info";
    common::detail::json::set_param(req.query, "depositId", params.deposit_id);
    common::detail::json::set_param(req.query, "questionnaire", params.questionnaire);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubmitDepositQuestionnaireV2Response>
TravelRuleApi::submit_deposit_questionnaire_v2(
    const SubmitDepositQuestionnaireV2Params& params) const {
    return common::send<SubmitDepositQuestionnaireV2Response>(
        *client_, submit_deposit_questionnaire_v2_request(params));
}

common::RestRequest TravelRuleApi::vasp_list_request(const VaspListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/vasp";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<VaspListResponseInner>>
TravelRuleApi::vasp_list(const VaspListParams& params) const {
    return common::send<std::vector<VaspListResponseInner>>(*client_, vasp_list_request(params));
}

common::RestRequest
TravelRuleApi::withdraw_history_v1_request(const WithdrawHistoryV1Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/localentity/withdraw/history";
    common::detail::json::set_param(req.query, "trId", params.tr_id);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "travelRuleStatus", params.travel_rule_status);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
TravelRuleApi::withdraw_history_v1(const WithdrawHistoryV1Params& params) const {
    return common::send<std::vector<WithdrawHistoryV1ResponseInner>>(
        *client_, withdraw_history_v1_request(params));
}

common::RestRequest
TravelRuleApi::withdraw_history_v2_request(const WithdrawHistoryV2Params& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/localentity/withdraw/history";
    common::detail::json::set_param(req.query, "trId", params.tr_id);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "travelRuleStatus", params.travel_rule_status);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
TravelRuleApi::withdraw_history_v2(const WithdrawHistoryV2Params& params) const {
    return common::send<std::vector<WithdrawHistoryV1ResponseInner>>(
        *client_, withdraw_history_v2_request(params));
}

common::RestRequest
TravelRuleApi::withdraw_travel_rule_request(const WithdrawTravelRuleParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/localentity/withdraw/apply";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "address", params.address);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "questionnaire", params.questionnaire);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "addressTag", params.address_tag);
    common::detail::json::set_param(req.query, "transactionFeeFlag", params.transaction_fee_flag);
    common::detail::json::set_param(req.query, "name", params.name);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<WithdrawTravelRuleResponse>
TravelRuleApi::withdraw_travel_rule(const WithdrawTravelRuleParams& params) const {
    return common::send<WithdrawTravelRuleResponse>(*client_, withdraw_travel_rule_request(params));
}

} // namespace binance::wallet::rest_api
