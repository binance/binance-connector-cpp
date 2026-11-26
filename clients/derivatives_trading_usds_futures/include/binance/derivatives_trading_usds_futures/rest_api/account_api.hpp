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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v2_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/account_information_v3_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_account_balance_v2_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_account_configuration_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/futures_trading_quantitative_rules_indicators_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_bnb_burn_status_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_current_multi_assets_mode_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_current_position_mode_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_download_id_for_futures_order_history_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_download_id_for_futures_trade_history_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_download_id_for_futures_transaction_history_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_futures_order_history_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_futures_trade_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_futures_transaction_history_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_income_history_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/notional_and_leverage_brackets_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_user_rate_limit_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_configuration_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/toggle_bnb_burn_on_futures_trade_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/user_commission_rate_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

enum class GetIncomeHistoryIncomeTypeEnum {
    Transfer,
    WelcomeBonus,
    RealizedPnl,
    FundingFee,
    Commission,
    InsuranceClear,
    ReferralKickback,
    CommissionRebate,
    ApiRebate,
    ContestReward,
    CrossCollateralTransfer,
    OptionsPremiumFee,
    OptionsSettleProfit,
    InternalTransfer,
    AutoExchange,
    DeliveredSettelment,
    CoinSwapDeposit,
    CoinSwapWithdraw,
    PositionLimitIncreaseFee,
    StrategyUmfuturesTransfer,
    FeeReturn,
    BfusdReward,
    SpecialFundingFee,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(GetIncomeHistoryIncomeTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetIncomeHistoryIncomeTypeEnum value);

struct AccountInformationV2Params {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AccountInformationV3Params {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesAccountBalanceV2Params {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesAccountBalanceV3Params {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesAccountConfigurationParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FuturesTradingQuantitativeRulesIndicatorsParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetBnbBurnStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ToggleBnbBurnOnFuturesTradeParams {
    /// "true": Fee Discount On; "false": Fee Discount Off
    common::Required<std::string> fee_burn;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCurrentMultiAssetsModeParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCurrentPositionModeParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesOrderHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesTradeHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForFuturesTransactionHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesOrderHistoryDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesTradeDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesTransactionHistoryDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetIncomeHistoryParams {
    /// Trading symbol.
    std::optional<std::string> symbol = std::nullopt;
    /// Income type.
    std::optional<GetIncomeHistoryIncomeTypeEnum> income_type = std::nullopt;
    /// Timestamp in milliseconds (inclusive start).
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in milliseconds (inclusive end).
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NotionalAndLeverageBracketsParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUserRateLimitParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SymbolConfigurationParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserCommissionRateParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Account Information V2 (USER_DATA)
    ///
    /// GET /fapi/v2/account.
    ///
    /// Get current account information. User in single-asset/ multi-assets mode will see different
    /// value, see comments in response section for detail.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#account-information-v2
    [[nodiscard]] common::RestApiResponse<AccountInformationV2Response>
    account_information_v2(const AccountInformationV2Params& params = {}) const;

    /// Asynchronous `account_information_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountInformationV2Response>)`.
    template <class CompletionToken>
    auto async_account_information_v2(const AccountInformationV2Params& params,
                                      CompletionToken&& token) const {
        return common::async_send<AccountInformationV2Response>(
            client_, account_information_v2_request(params), std::forward<CompletionToken>(token));
    }

    /// Account Information V3 (USER_DATA)
    ///
    /// GET /fapi/v3/account.
    ///
    /// Get current account information. User in single-asset/ multi-assets mode will see different
    /// value, see comments in response section for detail.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#account-information-v3
    [[nodiscard]] common::RestApiResponse<AccountInformationV3Response>
    account_information_v3(const AccountInformationV3Params& params = {}) const;

    /// Asynchronous `account_information_v3()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountInformationV3Response>)`.
    template <class CompletionToken>
    auto async_account_information_v3(const AccountInformationV3Params& params,
                                      CompletionToken&& token) const {
        return common::async_send<AccountInformationV3Response>(
            client_, account_information_v3_request(params), std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance V2 (USER_DATA)
    ///
    /// GET /fapi/v2/balance.
    ///
    /// Query account balance information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#futures-account-balance-v2
    [[nodiscard]] common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>
    futures_account_balance_v2(const FuturesAccountBalanceV2Params& params = {}) const;

    /// Asynchronous `futures_account_balance_v2()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>)`.
    template <class CompletionToken>
    auto async_futures_account_balance_v2(const FuturesAccountBalanceV2Params& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<FuturesAccountBalanceV2ResponseInner>>(
            client_, futures_account_balance_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Futures Account Balance V3 (USER_DATA)
    ///
    /// GET /fapi/v3/balance.
    ///
    /// Query account balance information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#futures-account-balance-v3
    [[nodiscard]] common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>
    futures_account_balance_v3(const FuturesAccountBalanceV3Params& params = {}) const;

    /// Asynchronous `futures_account_balance_v3()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<FuturesAccountBalanceV2ResponseInner>>)`.
    template <class CompletionToken>
    auto async_futures_account_balance_v3(const FuturesAccountBalanceV3Params& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<FuturesAccountBalanceV2ResponseInner>>(
            client_, futures_account_balance_v3_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Futures Account Configuration (USER_DATA)
    ///
    /// GET /fapi/v1/accountConfig.
    ///
    /// Query account configuration
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#futures-account-configuration
    [[nodiscard]] common::RestApiResponse<FuturesAccountConfigurationResponse>
    futures_account_configuration(const FuturesAccountConfigurationParams& params = {}) const;

    /// Asynchronous `futures_account_configuration()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FuturesAccountConfigurationResponse>)`.
    template <class CompletionToken>
    auto async_futures_account_configuration(const FuturesAccountConfigurationParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<FuturesAccountConfigurationResponse>(
            client_, futures_account_configuration_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Futures Trading Quantitative Rules Indicators (USER_DATA)
    ///
    /// GET /fapi/v1/apiTradingStatus.
    ///
    /// Futures trading quantitative rules indicators, for more information on this, please refer to
    /// the Futures Trading Quantitative Rules
    ///
    /// Weight: - **1** for a single symbol
    /// - **10** when the symbol parameter is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#futures-trading-quantitative-rules-indicators
    [[nodiscard]] common::RestApiResponse<FuturesTradingQuantitativeRulesIndicatorsResponse>
    futures_trading_quantitative_rules_indicators(
        const FuturesTradingQuantitativeRulesIndicatorsParams& params = {}) const;

    /// Asynchronous `futures_trading_quantitative_rules_indicators()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<FuturesTradingQuantitativeRulesIndicatorsResponse>)`.
    template <class CompletionToken>
    auto async_futures_trading_quantitative_rules_indicators(
        const FuturesTradingQuantitativeRulesIndicatorsParams& params,
        CompletionToken&& token) const {
        return common::async_send<FuturesTradingQuantitativeRulesIndicatorsResponse>(
            client_, futures_trading_quantitative_rules_indicators_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get BNB Burn Status (USER_DATA)
    ///
    /// GET /fapi/v1/feeBurn.
    ///
    /// Get user's BNB Fee Discount (Fee Discount On or Fee Discount Off )
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-bnb-burn-status
    [[nodiscard]] common::RestApiResponse<GetBnbBurnStatusResponse>
    get_bnb_burn_status(const GetBnbBurnStatusParams& params = {}) const;

    /// Asynchronous `get_bnb_burn_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetBnbBurnStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_bnb_burn_status(const GetBnbBurnStatusParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<GetBnbBurnStatusResponse>(
            client_, get_bnb_burn_status_request(params), std::forward<CompletionToken>(token));
    }

    /// Toggle BNB Burn On Futures Trade (TRADE)
    ///
    /// POST /fapi/v1/feeBurn.
    ///
    /// Change user's BNB Fee Discount (Fee Discount On or Fee Discount Off ) on ***EVERY symbol***
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#toggle-bnb-burn-on-futures-trade
    [[nodiscard]] common::RestApiResponse<ToggleBnbBurnOnFuturesTradeResponse>
    toggle_bnb_burn_on_futures_trade(const ToggleBnbBurnOnFuturesTradeParams& params) const;

    /// Asynchronous `toggle_bnb_burn_on_futures_trade()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ToggleBnbBurnOnFuturesTradeResponse>)`.
    template <class CompletionToken>
    auto async_toggle_bnb_burn_on_futures_trade(const ToggleBnbBurnOnFuturesTradeParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<ToggleBnbBurnOnFuturesTradeResponse>(
            client_, toggle_bnb_burn_on_futures_trade_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Current Multi-Assets Mode (USER_DATA)
    ///
    /// GET /fapi/v1/multiAssetsMargin.
    ///
    /// Get user's Multi-Assets mode (Multi-Assets Mode or Single-Asset Mode) on ***Every symbol***
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-current-multi-assets-mode
    [[nodiscard]] common::RestApiResponse<GetCurrentMultiAssetsModeResponse>
    get_current_multi_assets_mode(const GetCurrentMultiAssetsModeParams& params = {}) const;

    /// Asynchronous `get_current_multi_assets_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCurrentMultiAssetsModeResponse>)`.
    template <class CompletionToken>
    auto async_get_current_multi_assets_mode(const GetCurrentMultiAssetsModeParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetCurrentMultiAssetsModeResponse>(
            client_, get_current_multi_assets_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Current Position Mode (USER_DATA)
    ///
    /// GET /fapi/v1/positionSide/dual.
    ///
    /// Get user's position mode (Hedge Mode or One-way Mode ) on ***EVERY symbol***
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-current-position-mode
    [[nodiscard]] common::RestApiResponse<GetCurrentPositionModeResponse>
    get_current_position_mode(const GetCurrentPositionModeParams& params = {}) const;

    /// Asynchronous `get_current_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCurrentPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_get_current_position_mode(const GetCurrentPositionModeParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetCurrentPositionModeResponse>(
            client_, get_current_position_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Order History (USER_DATA)
    ///
    /// GET /fapi/v1/order/asyn.
    ///
    /// Get Download Id For Futures Order History
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 10 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-download-id-for-futures-order-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesOrderHistoryResponse>
    get_download_id_for_futures_order_history(
        const GetDownloadIdForFuturesOrderHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_order_history(
        const GetDownloadIdForFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesOrderHistoryResponse>(
            client_, get_download_id_for_futures_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Trade History (USER_DATA)
    ///
    /// GET /fapi/v1/trade/asyn.
    ///
    /// Get download id for futures trade history
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 5 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-download-id-for-futures-trade-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesTradeHistoryResponse>
    get_download_id_for_futures_trade_history(
        const GetDownloadIdForFuturesTradeHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_trade_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_trade_history(
        const GetDownloadIdForFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesTradeHistoryResponse>(
            client_, get_download_id_for_futures_trade_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For Futures Transaction History (USER_DATA)
    ///
    /// GET /fapi/v1/income/asyn.
    ///
    /// Get download id for futures transaction history
    ///
    /// Weight(IP): 1000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The request limit is 100 times per month, shared across the front end download page and
    /// rest api, as well as between USDⓈ-M and COIN-M contracts.
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-download-id-for-futures-transaction-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForFuturesTransactionHistoryResponse>
    get_download_id_for_futures_transaction_history(
        const GetDownloadIdForFuturesTransactionHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_futures_transaction_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForFuturesTransactionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_futures_transaction_history(
        const GetDownloadIdForFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForFuturesTransactionHistoryResponse>(
            client_, get_download_id_for_futures_transaction_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Order History Download Link by Id (USER_DATA)
    ///
    /// GET /fapi/v1/order/asyn/id.
    ///
    /// Get futures order history download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-futures-order-history-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesOrderHistoryDownloadLinkByIdResponse>
    get_futures_order_history_download_link_by_id(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_order_history_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesOrderHistoryDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_order_history_download_link_by_id(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetFuturesOrderHistoryDownloadLinkByIdResponse>(
            client_, get_futures_order_history_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Trade Download Link by Id (USER_DATA)
    ///
    /// GET /fapi/v1/trade/asyn/id.
    ///
    /// Get futures trade download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-futures-trade-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesTradeDownloadLinkByIdResponse>
    get_futures_trade_download_link_by_id(
        const GetFuturesTradeDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_trade_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesTradeDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto
    async_get_futures_trade_download_link_by_id(const GetFuturesTradeDownloadLinkByIdParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetFuturesTradeDownloadLinkByIdResponse>(
            client_, get_futures_trade_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Transaction History Download Link by Id (USER_DATA)
    ///
    /// GET /fapi/v1/income/asyn/id.
    ///
    /// Get futures transaction history download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-futures-transaction-history-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetFuturesTransactionHistoryDownloadLinkByIdResponse>
    get_futures_transaction_history_download_link_by_id(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_futures_transaction_history_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesTransactionHistoryDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_transaction_history_download_link_by_id(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetFuturesTransactionHistoryDownloadLinkByIdResponse>(
            client_, get_futures_transaction_history_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Income History (USER_DATA)
    ///
    /// GET /fapi/v1/income.
    ///
    /// Query income history
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `incomeType ` is not sent, all kinds of flow will be returned
    /// - If `startTime` and `endTime` are not sent, the recent 7-day data will be returned.
    /// - `trandId` is unique in the same `incomeType` for a user.
    /// - Income history only contains data for the last three months.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#get-income-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetIncomeHistoryResponseInner>>
    get_income_history(const GetIncomeHistoryParams& params = {}) const;

    /// Asynchronous `get_income_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetIncomeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_income_history(const GetIncomeHistoryParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<GetIncomeHistoryResponseInner>>(
            client_, get_income_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Notional and Leverage Brackets (USER_DATA)
    ///
    /// GET /fapi/v1/leverageBracket.
    ///
    /// Query user notional and leverage bracket on speicfic symbol
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#notional-and-leverage-brackets
    [[nodiscard]] common::RestApiResponse<NotionalAndLeverageBracketsResponse>
    notional_and_leverage_brackets(const NotionalAndLeverageBracketsParams& params = {}) const;

    /// Asynchronous `notional_and_leverage_brackets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NotionalAndLeverageBracketsResponse>)`.
    template <class CompletionToken>
    auto async_notional_and_leverage_brackets(const NotionalAndLeverageBracketsParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<NotionalAndLeverageBracketsResponse>(
            client_, notional_and_leverage_brackets_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User Rate Limit (USER_DATA)
    ///
    /// GET /fapi/v1/rateLimit/order.
    ///
    /// Query User Rate Limit
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#query-user-rate-limit
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUserRateLimitResponseInner>>
    query_user_rate_limit(const QueryUserRateLimitParams& params = {}) const;

    /// Asynchronous `query_user_rate_limit()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUserRateLimitResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_user_rate_limit(const QueryUserRateLimitParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUserRateLimitResponseInner>>(
            client_, query_user_rate_limit_request(params), std::forward<CompletionToken>(token));
    }

    /// Symbol Configuration (USER_DATA)
    ///
    /// GET /fapi/v1/symbolConfig.
    ///
    /// Get current account symbol configuration.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#symbol-configuration
    [[nodiscard]] common::RestApiResponse<std::vector<SymbolConfigurationResponseInner>>
    symbol_configuration(const SymbolConfigurationParams& params = {}) const;

    /// Asynchronous `symbol_configuration()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<SymbolConfigurationResponseInner>>)`.
    template <class CompletionToken>
    auto async_symbol_configuration(const SymbolConfigurationParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<SymbolConfigurationResponseInner>>(
            client_, symbol_configuration_request(params), std::forward<CompletionToken>(token));
    }

    /// User Commission Rate (USER_DATA)
    ///
    /// GET /fapi/v1/commissionRate.
    ///
    /// Get User Commission Rate
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/account#user-commission-rate
    [[nodiscard]] common::RestApiResponse<UserCommissionRateResponse>
    user_commission_rate(const UserCommissionRateParams& params) const;

    /// Asynchronous `user_commission_rate()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UserCommissionRateResponse>)`.
    template <class CompletionToken>
    auto async_user_commission_rate(const UserCommissionRateParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<UserCommissionRateResponse>(
            client_, user_commission_rate_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_information_v2_request(const AccountInformationV2Params& params) const;
    [[nodiscard]] common::RestRequest
    account_information_v3_request(const AccountInformationV3Params& params) const;
    [[nodiscard]] common::RestRequest
    futures_account_balance_v2_request(const FuturesAccountBalanceV2Params& params) const;
    [[nodiscard]] common::RestRequest
    futures_account_balance_v3_request(const FuturesAccountBalanceV3Params& params) const;
    [[nodiscard]] common::RestRequest
    futures_account_configuration_request(const FuturesAccountConfigurationParams& params) const;
    [[nodiscard]] common::RestRequest futures_trading_quantitative_rules_indicators_request(
        const FuturesTradingQuantitativeRulesIndicatorsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_bnb_burn_status_request(const GetBnbBurnStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    toggle_bnb_burn_on_futures_trade_request(const ToggleBnbBurnOnFuturesTradeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_current_multi_assets_mode_request(const GetCurrentMultiAssetsModeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_current_position_mode_request(const GetCurrentPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_order_history_request(
        const GetDownloadIdForFuturesOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_trade_history_request(
        const GetDownloadIdForFuturesTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_futures_transaction_history_request(
        const GetDownloadIdForFuturesTransactionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_order_history_download_link_by_id_request(
        const GetFuturesOrderHistoryDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_trade_download_link_by_id_request(
        const GetFuturesTradeDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_transaction_history_download_link_by_id_request(
        const GetFuturesTransactionHistoryDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest
    get_income_history_request(const GetIncomeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    notional_and_leverage_brackets_request(const NotionalAndLeverageBracketsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_user_rate_limit_request(const QueryUserRateLimitParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_configuration_request(const SymbolConfigurationParams& params) const;
    [[nodiscard]] common::RestRequest
    user_commission_rate_request(const UserCommissionRateParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_usds_futures::rest_api
