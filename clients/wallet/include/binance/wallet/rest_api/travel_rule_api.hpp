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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/broker_withdraw_response.hpp>
#include <binance/wallet/rest_api/models/check_questionnaire_requirements_response.hpp>
#include <binance/wallet/rest_api/models/deposit_history_travel_rule_response_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_response.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_travel_rule_response.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_v2_response.hpp>
#include <binance/wallet/rest_api/models/vasp_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_history_v1_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_travel_rule_response.hpp>

namespace binance::wallet::rest_api {

struct BrokerWithdrawParams {
    common::Required<std::string> address;
    common::Required<std::string> coin;
    common::Required<common::Decimal> amount;
    /// withdrawID defined by the client (i.e. client's internal withdrawID)
    common::Required<std::string> withdraw_order_id;
    /// JSON format questionnaire answers.
    common::Required<std::string> questionnaire;
    /// JSON format originator Pii, see StandardPii section below
    common::Required<std::string> originator_pii;
    /// Secondary address identifier for coins like XRP,XMR etc.
    std::optional<std::string> address_tag = std::nullopt;
    std::optional<std::string> network = std::nullopt;
    /// Description of the address. Address book cap is 200, space in name should be encoded into
    /// `%20`
    std::optional<std::string> address_name = std::nullopt;
    /// When making internal transfer, `true` for returning the fee to the destination account;
    /// `false` for returning the fee back to the departure account. Default `false`.
    std::optional<bool> transaction_fee_flag = std::nullopt;
    /// The wallet type for withdraw，0-spot wallet ，1-funding wallet. Default walletType is the
    /// current "selected wallet" under wallet->Fiat and Spot/Funding->Deposit
    std::optional<std::int64_t> wallet_type = std::nullopt;
};

struct CheckQuestionnaireRequirementsParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DepositHistoryTravelRuleParams {
    /// Comma(,) separated list of travel rule record Ids.
    std::optional<std::string> tr_id = std::nullopt;
    /// Comma(,) separated list of transaction Ids.
    std::optional<std::string> tx_id = std::nullopt;
    /// Comma(,) separated list of wallet tran Ids.
    std::optional<std::string> tran_id = std::nullopt;
    std::optional<std::string> network = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// 0: Completed,1: Pending,2: Failed
    std::optional<std::int64_t> travel_rule_status = std::nullopt;
    /// true: Only return records that pending deposit questionnaire. false/not provided: return all
    /// records.
    std::optional<bool> pending_questionnaire = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Default: 0
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct DepositHistoryV2Params {
    /// Comma(,) separated list of wallet tran Ids.
    std::optional<std::int64_t> deposit_id = std::nullopt;
    /// Comma(,) separated list of transaction Ids.
    std::optional<std::string> tx_id = std::nullopt;
    std::optional<std::string> network = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// true: return `questionnaire` within response.
    std::optional<bool> retrieve_questionnaire = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct FetchAddressVerificationListParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCountryListParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetRegionListParams {
    /// ISO 2-digit country code (from Country List API).
    common::Required<std::string> country_code;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubmitDepositQuestionnaireParams {
    /// External user ID.
    common::Required<std::string> sub_account_id;
    /// Wallet deposit ID.
    common::Required<std::int64_t> deposit_id;
    /// JSON format questionnaire answers.
    common::Required<std::string> questionnaire;
    /// JSON format beneficiary Pii, see StandardPii section below
    common::Required<std::string> beneficiary_pii;
    std::optional<std::string> network = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    std::optional<common::Decimal> amount = std::nullopt;
    std::optional<std::string> address = std::nullopt;
    std::optional<std::string> address_tag = std::nullopt;
};

struct SubmitDepositQuestionnaireTravelRuleParams {
    /// Wallet tran ID
    common::Required<std::int64_t> tran_id;
    /// JSON format questionnaire answers.
    common::Required<std::string> questionnaire;
};

struct SubmitDepositQuestionnaireV2Params {
    /// Wallet deposit ID
    common::Required<std::int64_t> deposit_id;
    /// JSON format questionnaire answers.
    common::Required<std::string> questionnaire;
};

struct VaspListParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WithdrawHistoryV1Params {
    /// Comma(,) separated list of travel rule record Ids.
    std::optional<std::string> tr_id = std::nullopt;
    /// Comma(,) separated list of transaction Ids.
    std::optional<std::string> tx_id = std::nullopt;
    /// client side id for withdrawal, if provided in POST `/sapi/v1/capital/withdraw/apply`, can be
    /// used here for query.
    std::optional<std::string> withdraw_order_id = std::nullopt;
    std::optional<std::string> network = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// 0: Completed,1: Pending,2: Failed
    std::optional<std::int64_t> travel_rule_status = std::nullopt;
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WithdrawHistoryV2Params {
    /// Comma(,) separated list of travel rule record Ids.
    std::optional<std::string> tr_id = std::nullopt;
    /// Comma(,) separated list of transaction Ids.
    std::optional<std::string> tx_id = std::nullopt;
    /// client side id for withdrawal, if provided in POST `/sapi/v1/capital/withdraw/apply`, can be
    /// used here for query.
    std::optional<std::string> withdraw_order_id = std::nullopt;
    std::optional<std::string> network = std::nullopt;
    std::optional<std::string> coin = std::nullopt;
    /// 0: Completed,1: Pending,2: Failed
    std::optional<std::int64_t> travel_rule_status = std::nullopt;
    std::optional<std::int64_t> offset = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
    /// Default: 90 days from current timestamp
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Default: present timestamp
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct WithdrawTravelRuleParams {
    common::Required<std::string> coin;
    /// Withdrawal address
    common::Required<std::string> address;
    /// Amount
    common::Required<common::Decimal> amount;
    /// JSON format questionnaire answers.
    common::Required<std::string> questionnaire;
    /// withdrawID defined by the client (i.e. client's internal withdrawID)
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

class BINANCE_WALLET_EXPORT TravelRuleApi {
public:
    explicit TravelRuleApi(std::shared_ptr<common::RestClient> client);

    /// Broker Withdraw (for brokers of local entities that require travel rule) (USER_DATA)
    ///
    /// POST /sapi/v1/localentity/broker/withdraw/apply.
    ///
    /// Submit a withdrawal request for brokers of local entities that required travel rule.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin, but if the address could
    /// not match default network, the withdraw will be rejected.
    /// - You can get `network` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - Questionnaire is different for each local entity, please refer to the `Withdraw
    /// Questionnaire Contents` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// **StandardPii**
    ///
    /// **For Natural Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 0: Natural Person
    /// - `latinNames` (List<PiiName>, Mandatory): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `localNames` (List<PiiName>, Optional): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `nationality` (STRING, Optional)
    /// - `residenceCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `dateOfBirth` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// Providing DOB could greatly reduce false positive rate during risk checking process.
    /// - `placeOfBirth` (STRING, Optional)
    /// - `address` (STRING, Optional)
    ///
    /// **For Legal Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 1: Legal Person
    /// - `latinName` (STRING, Mandatory): It's company name for Legal Person
    /// - `localName` (STRING, Optional)
    /// - `registrationCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `registrationDate` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// - `address` (STRING, Optional)
    /// - `walletAddress` (STRING, Optional)
    /// - `walletTag` (STRING, Optional)
    ///
    /// **PiiName**
    ///
    /// - `firstName` (STRING, Mandatory): Mandatory for Natural person
    /// - `middleName` (STRING, Optional)
    /// - `lastName` (STRING, Optional)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#broker-withdraw
    [[nodiscard]] common::RestApiResponse<BrokerWithdrawResponse>
    broker_withdraw(const BrokerWithdrawParams& params) const;

    /// Asynchronous `broker_withdraw()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<BrokerWithdrawResponse>)`.
    template <class CompletionToken>
    auto async_broker_withdraw(const BrokerWithdrawParams& params, CompletionToken&& token) const {
        return common::async_send<BrokerWithdrawResponse>(client_, broker_withdraw_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Check Questionnaire Requirements (for local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/questionnaire-requirements.
    ///
    /// This API will return user-specific Travel Rule questionnaire requirement information in
    /// reference to the current API key.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#check-questionnaire-requirements
    [[nodiscard]] common::RestApiResponse<CheckQuestionnaireRequirementsResponse>
    check_questionnaire_requirements(const CheckQuestionnaireRequirementsParams& params = {}) const;

    /// Asynchronous `check_questionnaire_requirements()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckQuestionnaireRequirementsResponse>)`.
    template <class CompletionToken>
    auto async_check_questionnaire_requirements(const CheckQuestionnaireRequirementsParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<CheckQuestionnaireRequirementsResponse>(
            client_, check_questionnaire_requirements_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Deposit History Travel Rule (for local entities that required travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/deposit/history.
    ///
    /// Fetch deposit history for local entities that required travel rule.
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
    /// - Please, note that due to network-specific characteristics, the returned source address may
    /// be inaccurate. If multiple source addresses are found, only the first one will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#deposit-history-travel-rule
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryTravelRuleResponseInner>>
    deposit_history_travel_rule(const DepositHistoryTravelRuleParams& params = {}) const;

    /// Asynchronous `deposit_history_travel_rule()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<DepositHistoryTravelRuleResponseInner>>)`.
    template <class CompletionToken>
    auto async_deposit_history_travel_rule(const DepositHistoryTravelRuleParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<DepositHistoryTravelRuleResponseInner>>(
            client_, deposit_history_travel_rule_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Deposit History V2 (for local entities that required travel rule) (supporting network)
    /// (USER_DATA)
    ///
    /// GET /sapi/v2/localentity/deposit/history.
    ///
    /// Fetch deposit history for local entities that with required travel rule information.
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
    /// - Please, note that due to network-specific characteristics, the returned source address may
    /// be inaccurate. If multiple source addresses are found, only the first one will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#deposit-history-v2
    [[nodiscard]] common::RestApiResponse<std::vector<DepositHistoryV2ResponseInner>>
    deposit_history_v2(const DepositHistoryV2Params& params = {}) const;

    /// Asynchronous `deposit_history_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<DepositHistoryV2ResponseInner>>)`.
    template <class CompletionToken>
    auto async_deposit_history_v2(const DepositHistoryV2Params& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<DepositHistoryV2ResponseInner>>(
            client_, deposit_history_v2_request(params), std::forward<CompletionToken>(token));
    }

    /// Fetch address verification list (USER_DATA)
    ///
    /// GET /sapi/v1/addressVerify/list.
    ///
    /// Fetch address verification list for user to check on status and other details for the
    /// addresses stored in Address Book.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#fetch-address-verification-list
    [[nodiscard]] common::RestApiResponse<std::vector<FetchAddressVerificationListResponseInner>>
    fetch_address_verification_list(const FetchAddressVerificationListParams& params = {}) const;

    /// Asynchronous `fetch_address_verification_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FetchAddressVerificationListResponseInner>>)`.
    template <class CompletionToken>
    auto async_fetch_address_verification_list(const FetchAddressVerificationListParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<FetchAddressVerificationListResponseInner>>(
            client_, fetch_address_verification_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Country List (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/country/list.
    ///
    /// Query the active country list for travel rule questionnaires. Currently supports AU and BR
    /// entities.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#get-country-list
    [[nodiscard]] common::RestApiResponse<GetCountryListResponse>
    get_country_list(const GetCountryListParams& params = {}) const;

    /// Asynchronous `get_country_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCountryListResponse>)`.
    template <class CompletionToken>
    auto async_get_country_list(const GetCountryListParams& params, CompletionToken&& token) const {
        return common::async_send<GetCountryListResponse>(client_, get_country_list_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Get Region List (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/region/list.
    ///
    /// Query the active region/city list for a given country. Currently, only supports AU entity.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#get-region-list
    [[nodiscard]] common::RestApiResponse<GetRegionListResponse>
    get_region_list(const GetRegionListParams& params) const;

    /// Asynchronous `get_region_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetRegionListResponse>)`.
    template <class CompletionToken>
    auto async_get_region_list(const GetRegionListParams& params, CompletionToken&& token) const {
        return common::async_send<GetRegionListResponse>(client_, get_region_list_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire Broker (For local entities that require travel rule)
    /// (supporting network) (USER_DATA)
    ///
    /// PUT /sapi/v1/localentity/broker/deposit/provide-info.
    ///
    /// Submit questionnaire for brokers of local entities that require travel rule.
    /// The questionnaire is only applies to transactions from un-hosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// **StandardPii**
    ///
    /// **For Natural Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 0: Natural Person
    /// - `latinNames` (List<PiiName>, Mandatory): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `localNames` (List<PiiName>, Optional): In case a person have complicated names or
    /// multiple names, this parameter is a list
    /// - `nationality` (STRING, Optional)
    /// - `residenceCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `dateOfBirth` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// Providing DOB could greatly reduce false positive rate during risk checking process.
    /// - `placeOfBirth` (STRING, Optional)
    /// - `address` (STRING, Optional)
    ///
    /// **For Legal Person**
    ///
    /// - `piiType` (INTEGER, Mandatory): Fix to 1: Legal Person
    /// - `latinName` (STRING, Mandatory): It's company name for Legal Person
    /// - `localName` (STRING, Optional)
    /// - `registrationCountry` (STRING, Mandatory)
    /// - `nationalIdentifier` (STRING, Optional)
    /// - `nationalIdentifierType` (STRING, Optional)
    /// - `nationalIdentifierIssueCountry` (STRING, Optional)
    /// - `registrationDate` (STRING, Optional): yyyy-mm-dd. Not required but strongly recommended.
    /// - `address` (STRING, Optional)
    /// - `walletAddress` (STRING, Optional)
    /// - `walletTag` (STRING, Optional)
    ///
    /// **PiiName**
    ///
    /// - `firstName` (STRING, Mandatory): Mandatory for Natural person
    /// - `middleName` (STRING, Optional)
    /// - `lastName` (STRING, Optional)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireResponse>
    submit_deposit_questionnaire(const SubmitDepositQuestionnaireParams& params) const;

    /// Asynchronous `submit_deposit_questionnaire()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubmitDepositQuestionnaireResponse>)`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire(const SubmitDepositQuestionnaireParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<SubmitDepositQuestionnaireResponse>(
            client_, submit_deposit_questionnaire_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire (For local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// PUT /sapi/v1/localentity/deposit/provide-info.
    ///
    /// Submit questionnaire for local entities that require travel rule.
    /// The questionnaire is only applies to transactions from unhosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire-travel-rule
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireTravelRuleResponse>
    submit_deposit_questionnaire_travel_rule(
        const SubmitDepositQuestionnaireTravelRuleParams& params) const;

    /// Asynchronous `submit_deposit_questionnaire_travel_rule()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<SubmitDepositQuestionnaireTravelRuleResponse>)`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire_travel_rule(
        const SubmitDepositQuestionnaireTravelRuleParams& params, CompletionToken&& token) const {
        return common::async_send<SubmitDepositQuestionnaireTravelRuleResponse>(
            client_, submit_deposit_questionnaire_travel_rule_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Submit Deposit Questionnaire V2 (For local entities that require travel rule) (supporting
    /// network) (USER_DATA)
    ///
    /// PUT /sapi/v2/localentity/deposit/provide-info.
    ///
    /// Submit questionnaire for local entities that require travel rule.
    /// The questionnaire is only applies to transactions from unhosted wallets or VASPs that are
    /// not yet onboarded with GTR.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Questionnaire is different for each local entity, please refer to `Deposit Questionnaire
    /// Content` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#submit-deposit-questionnaire-v2
    [[nodiscard]] common::RestApiResponse<SubmitDepositQuestionnaireV2Response>
    submit_deposit_questionnaire_v2(const SubmitDepositQuestionnaireV2Params& params) const;

    /// Asynchronous `submit_deposit_questionnaire_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SubmitDepositQuestionnaireV2Response>)`.
    template <class CompletionToken>
    auto async_submit_deposit_questionnaire_v2(const SubmitDepositQuestionnaireV2Params& params,
                                               CompletionToken&& token) const {
        return common::async_send<SubmitDepositQuestionnaireV2Response>(
            client_, submit_deposit_questionnaire_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// VASP list (for local entities that require travel rule) (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/vasp.
    ///
    /// Fetch the VASP list for local entities.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#vasp-list
    [[nodiscard]] common::RestApiResponse<std::vector<VaspListResponseInner>>
    vasp_list(const VaspListParams& params = {}) const;

    /// Asynchronous `vasp_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<VaspListResponseInner>>)`.
    template <class CompletionToken>
    auto async_vasp_list(const VaspListParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<VaspListResponseInner>>(
            client_, vasp_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Withdraw History Travel Rule (supporting network) (USER_DATA)
    ///
    /// GET /sapi/v1/localentity/withdraw/history.
    ///
    /// Fetch withdraw history for local entities that required travel rule.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-history-v1
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
    withdraw_history_v1(const WithdrawHistoryV1Params& params = {}) const;

    /// Asynchronous `withdraw_history_v1()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>)`.
    template <class CompletionToken>
    auto async_withdraw_history_v1(const WithdrawHistoryV1Params& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<WithdrawHistoryV1ResponseInner>>(
            client_, withdraw_history_v1_request(params), std::forward<CompletionToken>(token));
    }

    /// Withdraw History V2 (for local entities that require travel rule) (supporting network)
    /// (USER_DATA)
    ///
    /// GET /sapi/v2/localentity/withdraw/history.
    ///
    /// Fetch withdraw history for local entities that required travel rule.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `network` may not be in the response for old withdraw.
    /// - Withdrawal made through /sapi/v1/capital/withdraw/apply may not be in the response.
    /// - Please notice the default `startTime` and `endTime` to make sure that time interval is
    /// within 0-90 days.
    /// - If both `startTime` and `endTime`are sent, time between `startTime`and `endTime`must be
    /// less than 90 days.
    /// - If withdrawOrderId is sent, time between startTime and endTime must be less than 7 days.
    /// - If withdrawOrderId is sent, startTime and endTime are not sent, will return last 7 days
    /// records by default.
    /// - Maximum support trId,txId number is 45.
    /// - WithdrawOrderId only support 1.
    /// - If responsible does not include withdrawalStatus, please input trId or txId retrieve the
    /// data.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-history-v2
    [[nodiscard]] common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>
    withdraw_history_v2(const WithdrawHistoryV2Params& params = {}) const;

    /// Asynchronous `withdraw_history_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<WithdrawHistoryV1ResponseInner>>)`.
    template <class CompletionToken>
    auto async_withdraw_history_v2(const WithdrawHistoryV2Params& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<WithdrawHistoryV1ResponseInner>>(
            client_, withdraw_history_v2_request(params), std::forward<CompletionToken>(token));
    }

    /// Withdraw Travel Rule (USER_DATA)
    ///
    /// POST /sapi/v1/localentity/withdraw/apply.
    ///
    /// Submit a withdrawal request for local entities that required travel rule.
    ///
    /// Weight(UID): 600
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `network` not send, return with default network of the coin, but if the address could
    /// not match default network, the withdraw will be rejected.
    /// - You can get `network` and `isDefault` in `networkList` of a coin in the response of `Get
    /// /sapi/v1/capital/config/getall (HMAC SHA256)`.
    /// - Questionnaire is different for each local entity, please refer to the `Withdraw
    /// Questionnaire Contents` page.
    /// - If getting error like `Questionnaire format not valid.` or `Questionnaire must not be
    /// blank`, please try to verify the format of the questionnaire and use URL-encoded format.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/travel-rule#withdraw-travel-rule
    [[nodiscard]] common::RestApiResponse<WithdrawTravelRuleResponse>
    withdraw_travel_rule(const WithdrawTravelRuleParams& params) const;

    /// Asynchronous `withdraw_travel_rule()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<WithdrawTravelRuleResponse>)`.
    template <class CompletionToken>
    auto async_withdraw_travel_rule(const WithdrawTravelRuleParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<WithdrawTravelRuleResponse>(
            client_, withdraw_travel_rule_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    broker_withdraw_request(const BrokerWithdrawParams& params) const;
    [[nodiscard]] common::RestRequest check_questionnaire_requirements_request(
        const CheckQuestionnaireRequirementsParams& params) const;
    [[nodiscard]] common::RestRequest
    deposit_history_travel_rule_request(const DepositHistoryTravelRuleParams& params) const;
    [[nodiscard]] common::RestRequest
    deposit_history_v2_request(const DepositHistoryV2Params& params) const;
    [[nodiscard]] common::RestRequest
    fetch_address_verification_list_request(const FetchAddressVerificationListParams& params) const;
    [[nodiscard]] common::RestRequest
    get_country_list_request(const GetCountryListParams& params) const;
    [[nodiscard]] common::RestRequest
    get_region_list_request(const GetRegionListParams& params) const;
    [[nodiscard]] common::RestRequest
    submit_deposit_questionnaire_request(const SubmitDepositQuestionnaireParams& params) const;
    [[nodiscard]] common::RestRequest submit_deposit_questionnaire_travel_rule_request(
        const SubmitDepositQuestionnaireTravelRuleParams& params) const;
    [[nodiscard]] common::RestRequest
    submit_deposit_questionnaire_v2_request(const SubmitDepositQuestionnaireV2Params& params) const;
    [[nodiscard]] common::RestRequest vasp_list_request(const VaspListParams& params) const;
    [[nodiscard]] common::RestRequest
    withdraw_history_v1_request(const WithdrawHistoryV1Params& params) const;
    [[nodiscard]] common::RestRequest
    withdraw_history_v2_request(const WithdrawHistoryV2Params& params) const;
    [[nodiscard]] common::RestRequest
    withdraw_travel_rule_request(const WithdrawTravelRuleParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::wallet::rest_api
