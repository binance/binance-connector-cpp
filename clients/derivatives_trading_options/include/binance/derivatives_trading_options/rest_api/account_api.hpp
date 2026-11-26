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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_funding_flow_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class AccountFundingFlowCurrencyEnum {
    Usdt,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(AccountFundingFlowCurrencyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountFundingFlowCurrencyEnum
tag_invoke(boost::json::value_to_tag<AccountFundingFlowCurrencyEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           AccountFundingFlowCurrencyEnum value);

struct AccountFundingFlowParams {
    /// Asset type, only support USDT  as of now
    common::Required<AccountFundingFlowCurrencyEnum> currency;
    /// Return the recordId and subsequent data, the latest data is returned by default
    std::optional<std::int64_t> record_id = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned
    std::optional<std::int64_t> limit = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionMarginAccountInformationParams {
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Account Funding Flow (USER_DATA)
    ///
    /// GET /eapi/v1/bill.
    ///
    /// Query account funding flows.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Only support querying data in the past 3 months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/account#account-funding-flow
    [[nodiscard]] common::RestApiResponse<std::vector<AccountFundingFlowResponseInner>>
    account_funding_flow(const AccountFundingFlowParams& params) const;

    /// Asynchronous `account_funding_flow()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AccountFundingFlowResponseInner>>)`.
    template <class CompletionToken>
    auto async_account_funding_flow(const AccountFundingFlowParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<AccountFundingFlowResponseInner>>(
            client_, account_funding_flow_request(params), std::forward<CompletionToken>(token));
    }

    /// Option Margin Account Information (USER_DATA)
    ///
    /// GET /eapi/v1/marginAccount.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 3
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/account#option-margin-account-information
    [[nodiscard]] common::RestApiResponse<OptionMarginAccountInformationResponse>
    option_margin_account_information(
        const OptionMarginAccountInformationParams& params = {}) const;

    /// Asynchronous `option_margin_account_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionMarginAccountInformationResponse>)`.
    template <class CompletionToken>
    auto async_option_margin_account_information(const OptionMarginAccountInformationParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<OptionMarginAccountInformationResponse>(
            client_, option_margin_account_information_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_funding_flow_request(const AccountFundingFlowParams& params) const;
    [[nodiscard]] common::RestRequest option_margin_account_information_request(
        const OptionMarginAccountInformationParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_options::rest_api
