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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/bnb_transfer_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/change_auto_repay_futures_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/delete_margin_call_level_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/fund_auto_collection_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/fund_collection_by_asset_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_auto_repay_futures_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_delta_mode_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_margin_call_level_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_account_balance_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_account_info_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_span_account_info_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_transferable_earn_asset_balance_for_portfolio_margin_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_pro_bankruptcy_loan_repay_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_bankruptcy_loan_amount_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_bankruptcy_loan_repay_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_pro_negative_balance_interest_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/repay_futures_negative_balance_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/set_margin_call_level_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/switch_delta_mode_response.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/transfer_ldusdt_rwusd_for_portfolio_margin_response.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

enum class BnbTransferTransferSideEnum {
    ToUm,
    FromUm,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(BnbTransferTransferSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT BnbTransferTransferSideEnum tag_invoke(
    boost::json::value_to_tag<BnbTransferTransferSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           BnbTransferTransferSideEnum value);

enum class ChangeAutoRepayFuturesStatusAutoRepayEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(ChangeAutoRepayFuturesStatusAutoRepayEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT ChangeAutoRepayFuturesStatusAutoRepayEnum
tag_invoke(boost::json::value_to_tag<ChangeAutoRepayFuturesStatusAutoRepayEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeAutoRepayFuturesStatusAutoRepayEnum value);

enum class FundCollectionByAssetFutureTypeEnum {
    Um,
    Cm,
    Option,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(FundCollectionByAssetFutureTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT FundCollectionByAssetFutureTypeEnum
tag_invoke(boost::json::value_to_tag<FundCollectionByAssetFutureTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           FundCollectionByAssetFutureTypeEnum value);

enum class SwitchDeltaModeDeltaEnabledEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(SwitchDeltaModeDeltaEnabledEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT SwitchDeltaModeDeltaEnabledEnum
tag_invoke(boost::json::value_to_tag<SwitchDeltaModeDeltaEnabledEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           SwitchDeltaModeDeltaEnabledEnum value);

enum class GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum {
    EarnToFuture,
    FutureToEarn,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum
tag_invoke(boost::json::value_to_tag<
               GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum value);

enum class TransferLdusdtRwusdForPortfolioMarginAssetEnum {
    Ldusdt,
    Rwusd,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(TransferLdusdtRwusdForPortfolioMarginAssetEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
TransferLdusdtRwusdForPortfolioMarginAssetEnum
tag_invoke(boost::json::value_to_tag<TransferLdusdtRwusdForPortfolioMarginAssetEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TransferLdusdtRwusdForPortfolioMarginAssetEnum value);

enum class TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum {
    EarnToFuture,
    FutureToEarn,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT std::string_view
to_string(TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT
TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum
tag_invoke(boost::json::value_to_tag<TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum value);

struct BnbTransferParams {
    common::Required<common::Decimal> amount;
    common::Required<BnbTransferTransferSideEnum> transfer_side;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeAutoRepayFuturesStatusParams {
    /// `false` for turn off the auto-repay futures negative balance function
    common::Required<ChangeAutoRepayFuturesStatusAutoRepayEnum> auto_repay;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetAutoRepayFuturesStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct DeleteMarginCallLevelParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetMarginCallLevelParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetMarginCallLevelParams {
    /// The value must be within the range [1.1, 2.0].
    common::Required<common::Decimal> margin_call_level;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FundAutoCollectionParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct FundCollectionByAssetParams {
    common::Required<std::string> asset;
    /// Amount to collect. When provided, `futureType` is required.
    std::optional<common::Decimal> amount = std::nullopt;
    /// Target wallet for the collection. `OPTION` is for SPAN only. Cannot be sent without
    /// `amount`. `amount` and `futureType` must be provided together. If neither is provided,
    /// existing behavior is unchanged (query all wallets + transfer).
    std::optional<FundCollectionByAssetFutureTypeEnum> future_type = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDeltaModeStatusParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SwitchDeltaModeParams {
    /// `true` to enable Delta mode; `false` to disable Delta mode
    common::Required<SwitchDeltaModeDeltaEnabledEnum> delta_enabled;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetPortfolioMarginProAccountBalanceParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetPortfolioMarginProAccountInfoParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetPortfolioMarginProSpanAccountInfoParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetTransferableEarnAssetBalanceForPortfolioMarginParams {
    /// `LDUSDT` only
    common::Required<std::string> asset;
    common::Required<GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum>
        transfer_type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PortfolioMarginProBankruptcyLoanRepayParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPortfolioMarginProBankruptcyLoanAmountParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams {
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    /// Currently querying page. Start from 1.
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPortfolioMarginProNegativeBalanceInterestHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RepayFuturesNegativeBalanceParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TransferLdusdtRwusdForPortfolioMarginParams {
    common::Required<TransferLdusdtRwusdForPortfolioMarginAssetEnum> asset;
    common::Required<TransferLdusdtRwusdForPortfolioMarginTransferTypeEnum> transfer_type;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// BNB transfer (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/bnb-transfer.
    ///
    /// BNB transfer can be between Margin Account and USDM Account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - You can only use this function 2 times per 10 minutes in a rolling manner
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#bnb-transfer
    [[nodiscard]] common::RestApiResponse<BnbTransferResponse>
    bnb_transfer(const BnbTransferParams& params) const;

    /// Asynchronous `bnb_transfer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<BnbTransferResponse>)`.
    template <class CompletionToken>
    auto async_bnb_transfer(const BnbTransferParams& params, CompletionToken&& token) const {
        return common::async_send<BnbTransferResponse>(client_, bnb_transfer_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Change Auto-repay-futures Status (TRADE)
    ///
    /// POST /sapi/v1/portfolio/repay-futures-switch.
    ///
    /// Change Auto-repay-futures Status
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#change-auto-repay-futures-status
    [[nodiscard]] common::RestApiResponse<ChangeAutoRepayFuturesStatusResponse>
    change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params) const;

    /// Asynchronous `change_auto_repay_futures_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeAutoRepayFuturesStatusResponse>)`.
    template <class CompletionToken>
    auto async_change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<ChangeAutoRepayFuturesStatusResponse>(
            client_, change_auto_repay_futures_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Auto-repay-futures Status (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/repay-futures-switch.
    ///
    /// Query Auto-repay-futures Status
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-auto-repay-futures-status
    [[nodiscard]] common::RestApiResponse<GetAutoRepayFuturesStatusResponse>
    get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params = {}) const;

    /// Asynchronous `get_auto_repay_futures_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetAutoRepayFuturesStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetAutoRepayFuturesStatusResponse>(
            client_, get_auto_repay_futures_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Delete Margin Call Level (USER_DATA)
    ///
    /// DELETE /sapi/v1/portfolio/margin-call-level.
    ///
    /// Delete the margin call level for a Portfolio Margin account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#delete-margin-call-level
    [[nodiscard]] common::RestApiResponse<DeleteMarginCallLevelResponse>
    delete_margin_call_level(const DeleteMarginCallLevelParams& params = {}) const;

    /// Asynchronous `delete_margin_call_level()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<DeleteMarginCallLevelResponse>)`.
    template <class CompletionToken>
    auto async_delete_margin_call_level(const DeleteMarginCallLevelParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<DeleteMarginCallLevelResponse>(
            client_, delete_margin_call_level_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Margin Call Level (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/margin-call-level.
    ///
    /// Get the margin call level for a Portfolio Margin account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-margin-call-level
    [[nodiscard]] common::RestApiResponse<GetMarginCallLevelResponse>
    get_margin_call_level(const GetMarginCallLevelParams& params = {}) const;

    /// Asynchronous `get_margin_call_level()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetMarginCallLevelResponse>)`.
    template <class CompletionToken>
    auto async_get_margin_call_level(const GetMarginCallLevelParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetMarginCallLevelResponse>(
            client_, get_margin_call_level_request(params), std::forward<CompletionToken>(token));
    }

    /// Set Margin Call Level (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/margin-call-level.
    ///
    /// Set the margin call level for a Portfolio Margin account. When the account's uniMMR drops to
    /// the specified level, a notification will be sent via email and push/inbox.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#set-margin-call-level
    [[nodiscard]] common::RestApiResponse<SetMarginCallLevelResponse>
    set_margin_call_level(const SetMarginCallLevelParams& params) const;

    /// Asynchronous `set_margin_call_level()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetMarginCallLevelResponse>)`.
    template <class CompletionToken>
    auto async_set_margin_call_level(const SetMarginCallLevelParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<SetMarginCallLevelResponse>(
            client_, set_margin_call_level_request(params), std::forward<CompletionToken>(token));
    }

    /// Fund Auto-collection (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/auto-collection.
    ///
    /// Transfers all assets from Futures Account to Margin account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The BNB would not be collected from UM-PM account to the Portfolio Margin account.
    /// - You can only use this function 500 times per hour in a rolling manner.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#fund-auto-collection
    [[nodiscard]] common::RestApiResponse<FundAutoCollectionResponse>
    fund_auto_collection(const FundAutoCollectionParams& params = {}) const;

    /// Asynchronous `fund_auto_collection()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FundAutoCollectionResponse>)`.
    template <class CompletionToken>
    auto async_fund_auto_collection(const FundAutoCollectionParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<FundAutoCollectionResponse>(
            client_, fund_auto_collection_request(params), std::forward<CompletionToken>(token));
    }

    /// Fund Collection by Asset (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/asset-collection.
    ///
    /// Transfers specific asset from Futures Account to Margin account
    ///
    /// Weight(IP): 60
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The BNB transfer is not be supported
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#fund-collection-by-asset
    [[nodiscard]] common::RestApiResponse<FundCollectionByAssetResponse>
    fund_collection_by_asset(const FundCollectionByAssetParams& params) const;

    /// Asynchronous `fund_collection_by_asset()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FundCollectionByAssetResponse>)`.
    template <class CompletionToken>
    auto async_fund_collection_by_asset(const FundCollectionByAssetParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<FundCollectionByAssetResponse>(
            client_, fund_collection_by_asset_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Delta Mode Status (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/delta-mode.
    ///
    /// Query the Delta mode status of current account.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-delta-mode-status
    [[nodiscard]] common::RestApiResponse<GetDeltaModeStatusResponse>
    get_delta_mode_status(const GetDeltaModeStatusParams& params = {}) const;

    /// Asynchronous `get_delta_mode_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetDeltaModeStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_delta_mode_status(const GetDeltaModeStatusParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetDeltaModeStatusResponse>(
            client_, get_delta_mode_status_request(params), std::forward<CompletionToken>(token));
    }

    /// Switch Delta Mode (TRADE)
    ///
    /// POST /sapi/v1/portfolio/delta-mode.
    ///
    /// Switch the Delta mode for existing PM PRO / PM RETAIL accounts.
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#switch-delta-mode
    [[nodiscard]] common::RestApiResponse<SwitchDeltaModeResponse>
    switch_delta_mode(const SwitchDeltaModeParams& params) const;

    /// Asynchronous `switch_delta_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SwitchDeltaModeResponse>)`.
    template <class CompletionToken>
    auto async_switch_delta_mode(const SwitchDeltaModeParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<SwitchDeltaModeResponse>(
            client_, switch_delta_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro Account Balance (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/balance.
    ///
    /// Query Portfolio Margin Pro account balance
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-account-balance
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>
    get_portfolio_margin_pro_account_balance(
        const GetPortfolioMarginProAccountBalanceParams& params = {}) const;

    /// Asynchronous `get_portfolio_margin_pro_account_balance()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_account_balance(
        const GetPortfolioMarginProAccountBalanceParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<GetPortfolioMarginProAccountBalanceResponseInner>>(
            client_, get_portfolio_margin_pro_account_balance_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro Account Info (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/account.
    ///
    /// Get Portfolio Margin Pro Account Info
    ///
    /// Weight(UID): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-account-info
    [[nodiscard]] common::RestApiResponse<GetPortfolioMarginProAccountInfoResponse>
    get_portfolio_margin_pro_account_info(
        const GetPortfolioMarginProAccountInfoParams& params = {}) const;

    /// Asynchronous `get_portfolio_margin_pro_account_info()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetPortfolioMarginProAccountInfoResponse>)`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_account_info(
        const GetPortfolioMarginProAccountInfoParams& params, CompletionToken&& token) const {
        return common::async_send<GetPortfolioMarginProAccountInfoResponse>(
            client_, get_portfolio_margin_pro_account_info_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Pro SPAN Account Info (USER_DATA)
    ///
    /// GET /sapi/v2/portfolio/account.
    ///
    /// Get Portfolio Margin Pro SPAN Account Info (For Portfolio Margin Pro SPAN users only)
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-portfolio-margin-pro-span-account-info
    [[nodiscard]] common::RestApiResponse<GetPortfolioMarginProSpanAccountInfoResponse>
    get_portfolio_margin_pro_span_account_info(
        const GetPortfolioMarginProSpanAccountInfoParams& params = {}) const;

    /// Asynchronous `get_portfolio_margin_pro_span_account_info()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetPortfolioMarginProSpanAccountInfoResponse>)`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_pro_span_account_info(
        const GetPortfolioMarginProSpanAccountInfoParams& params, CompletionToken&& token) const {
        return common::async_send<GetPortfolioMarginProSpanAccountInfoResponse>(
            client_, get_portfolio_margin_pro_span_account_info_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Transferable Earn Asset Balance for Portfolio Margin (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/earn-asset-balance.
    ///
    /// Get transferable earn asset balance for all types of Portfolio Margin account
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#get-transferable-earn-asset-balance-for-portfolio-margin
    [[nodiscard]] common::RestApiResponse<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>
    get_transferable_earn_asset_balance_for_portfolio_margin(
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params) const;

    /// Asynchronous `get_transferable_earn_asset_balance_for_portfolio_margin()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>)`.
    template <class CompletionToken>
    auto async_get_transferable_earn_asset_balance_for_portfolio_margin(
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetTransferableEarnAssetBalanceForPortfolioMarginResponse>(
            client_, get_transferable_earn_asset_balance_for_portfolio_margin_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Pro Bankruptcy Loan Repay (TRADE)
    ///
    /// POST /sapi/v1/portfolio/repay.
    ///
    /// Repay Portfolio Margin Pro Bankruptcy Loan
    ///
    /// Weight(UID): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Please note that the API Key has enabled Spot & Margin Trading permissions to access this
    /// endpoint.
    /// - USDT is taken from the Spot account and transferred to the Cross Margin account to repay
    /// the loan.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#portfolio-margin-pro-bankruptcy-loan-repay
    [[nodiscard]] common::RestApiResponse<PortfolioMarginProBankruptcyLoanRepayResponse>
    portfolio_margin_pro_bankruptcy_loan_repay(
        const PortfolioMarginProBankruptcyLoanRepayParams& params = {}) const;

    /// Asynchronous `portfolio_margin_pro_bankruptcy_loan_repay()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<PortfolioMarginProBankruptcyLoanRepayResponse>)`.
    template <class CompletionToken>
    auto async_portfolio_margin_pro_bankruptcy_loan_repay(
        const PortfolioMarginProBankruptcyLoanRepayParams& params, CompletionToken&& token) const {
        return common::async_send<PortfolioMarginProBankruptcyLoanRepayResponse>(
            client_, portfolio_margin_pro_bankruptcy_loan_repay_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Bankruptcy Loan Amount (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/pmLoan.
    ///
    /// Query Portfolio Margin Pro Bankruptcy Loan Amount
    ///
    /// Weight(UID): 500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If there’s no classic portfolio margin bankruptcy loan, the amount would be 0
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-bankruptcy-loan-amount
    [[nodiscard]] common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanAmountResponse>
    query_portfolio_margin_pro_bankruptcy_loan_amount(
        const QueryPortfolioMarginProBankruptcyLoanAmountParams& params = {}) const;

    /// Asynchronous `query_portfolio_margin_pro_bankruptcy_loan_amount()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanAmountResponse>)`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_bankruptcy_loan_amount(
        const QueryPortfolioMarginProBankruptcyLoanAmountParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryPortfolioMarginProBankruptcyLoanAmountResponse>(
            client_, query_portfolio_margin_pro_bankruptcy_loan_amount_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Bankruptcy Loan Repay History (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/pmloan-history.
    ///
    /// Query repay history of pmloan for portfolio margin pro.
    ///
    /// Weight(IP): 500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - `startTime` and `endTime` cannot be longer than 360 days
    /// - If `startTime` and `endTime` not sent, return records of the last 30 days by default.
    /// - If `startTime`is sent and `endTime` is not sent, return records of [startTime,
    /// startTime+30d].
    /// - If `startTime` is not sent and `endTime` is sent, return records of [endTime-30d,
    /// endTime].
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-bankruptcy-loan-repay-history
    [[nodiscard]] common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>
    query_portfolio_margin_pro_bankruptcy_loan_repay_history(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params = {}) const;

    /// Asynchronous `query_portfolio_margin_pro_bankruptcy_loan_repay_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>)`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_bankruptcy_loan_repay_history(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryPortfolioMarginProBankruptcyLoanRepayHistoryResponse>(
            client_, query_portfolio_margin_pro_bankruptcy_loan_repay_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Pro Negative Balance Interest History (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/interest-history.
    ///
    /// Query interest history of negative balance for portfolio margin.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#query-portfolio-margin-pro-negative-balance-interest-history
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>
    query_portfolio_margin_pro_negative_balance_interest_history(
        const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params = {}) const;

    /// Asynchronous `query_portfolio_margin_pro_negative_balance_interest_history()`. Completes
    /// with `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_pro_negative_balance_interest_history(
        const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<QueryPortfolioMarginProNegativeBalanceInterestHistoryResponseInner>>(
            client_, query_portfolio_margin_pro_negative_balance_interest_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Repay futures Negative Balance (USER_DATA)
    ///
    /// POST /sapi/v1/portfolio/repay-futures-negative-balance.
    ///
    /// Repay futures Negative Balance
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The negative balance is repaid from the Cross Margin account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#repay-futures-negative-balance
    [[nodiscard]] common::RestApiResponse<RepayFuturesNegativeBalanceResponse>
    repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params = {}) const;

    /// Asynchronous `repay_futures_negative_balance()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RepayFuturesNegativeBalanceResponse>)`.
    template <class CompletionToken>
    auto async_repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<RepayFuturesNegativeBalanceResponse>(
            client_, repay_futures_negative_balance_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Transfer LDUSDT/RWUSD for Portfolio Margin (TRADE)
    ///
    /// POST /sapi/v1/portfolio/earn-asset-transfer.
    ///
    /// Transfer LDUSDT/RWUSD as collateral for all types of Portfolio Margin account
    ///
    /// Weight(UID): 1500
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/account#transfer-ldusdt-rwusd-for-portfolio-margin
    [[nodiscard]] common::RestApiResponse<TransferLdusdtRwusdForPortfolioMarginResponse>
    transfer_ldusdt_rwusd_for_portfolio_margin(
        const TransferLdusdtRwusdForPortfolioMarginParams& params) const;

    /// Asynchronous `transfer_ldusdt_rwusd_for_portfolio_margin()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<TransferLdusdtRwusdForPortfolioMarginResponse>)`.
    template <class CompletionToken>
    auto async_transfer_ldusdt_rwusd_for_portfolio_margin(
        const TransferLdusdtRwusdForPortfolioMarginParams& params, CompletionToken&& token) const {
        return common::async_send<TransferLdusdtRwusdForPortfolioMarginResponse>(
            client_, transfer_ldusdt_rwusd_for_portfolio_margin_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest bnb_transfer_request(const BnbTransferParams& params) const;
    [[nodiscard]] common::RestRequest change_auto_repay_futures_status_request(
        const ChangeAutoRepayFuturesStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    get_auto_repay_futures_status_request(const GetAutoRepayFuturesStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    delete_margin_call_level_request(const DeleteMarginCallLevelParams& params) const;
    [[nodiscard]] common::RestRequest
    get_margin_call_level_request(const GetMarginCallLevelParams& params) const;
    [[nodiscard]] common::RestRequest
    set_margin_call_level_request(const SetMarginCallLevelParams& params) const;
    [[nodiscard]] common::RestRequest
    fund_auto_collection_request(const FundAutoCollectionParams& params) const;
    [[nodiscard]] common::RestRequest
    fund_collection_by_asset_request(const FundCollectionByAssetParams& params) const;
    [[nodiscard]] common::RestRequest
    get_delta_mode_status_request(const GetDeltaModeStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    switch_delta_mode_request(const SwitchDeltaModeParams& params) const;
    [[nodiscard]] common::RestRequest get_portfolio_margin_pro_account_balance_request(
        const GetPortfolioMarginProAccountBalanceParams& params) const;
    [[nodiscard]] common::RestRequest get_portfolio_margin_pro_account_info_request(
        const GetPortfolioMarginProAccountInfoParams& params) const;
    [[nodiscard]] common::RestRequest get_portfolio_margin_pro_span_account_info_request(
        const GetPortfolioMarginProSpanAccountInfoParams& params) const;
    [[nodiscard]] common::RestRequest
    get_transferable_earn_asset_balance_for_portfolio_margin_request(
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams& params) const;
    [[nodiscard]] common::RestRequest portfolio_margin_pro_bankruptcy_loan_repay_request(
        const PortfolioMarginProBankruptcyLoanRepayParams& params) const;
    [[nodiscard]] common::RestRequest query_portfolio_margin_pro_bankruptcy_loan_amount_request(
        const QueryPortfolioMarginProBankruptcyLoanAmountParams& params) const;
    [[nodiscard]] common::RestRequest
    query_portfolio_margin_pro_bankruptcy_loan_repay_history_request(
        const QueryPortfolioMarginProBankruptcyLoanRepayHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_portfolio_margin_pro_negative_balance_interest_history_request(
        const QueryPortfolioMarginProNegativeBalanceInterestHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    repay_futures_negative_balance_request(const RepayFuturesNegativeBalanceParams& params) const;
    [[nodiscard]] common::RestRequest transfer_ldusdt_rwusd_for_portfolio_margin_request(
        const TransferLdusdtRwusdForPortfolioMarginParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
