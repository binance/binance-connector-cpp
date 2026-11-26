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
#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/account_balance_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/account_information_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/bnb_transfer_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_auto_repay_futures_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_cm_initial_leverage_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_cm_position_mode_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_um_initial_leverage_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/change_um_position_mode_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/cm_notional_and_leverage_brackets_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/fund_auto_collection_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/fund_collection_by_asset_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_auto_repay_futures_status_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_account_detail_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_current_position_mode_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_futures_order_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_futures_trade_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_futures_transaction_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_cm_income_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_cm_futures_order_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_cm_futures_trade_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_cm_futures_transaction_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_um_futures_order_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_um_futures_trade_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_um_futures_transaction_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_margin_borrow_loan_interest_history_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_account_detail_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_account_detail_v2_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_current_position_mode_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_order_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_trade_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_transaction_download_link_by_id_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_income_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_user_commission_rate_for_cm_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_user_commission_rate_for_um_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/margin_max_borrow_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/portfolio_margin_um_trading_quantitative_rules_indicators_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_cm_position_information_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_loan_record_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_max_withdraw_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_margin_repay_record_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_portfolio_margin_negative_balance_interest_history_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_um_position_information_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_negative_balance_auto_exchange_record_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/query_user_rate_limit_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/repay_futures_negative_balance_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_futures_account_configuration_response.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_futures_symbol_configuration_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/um_notional_and_leverage_brackets_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

enum class BnbTransferTransferSideEnum {
    ToUm,
    FromUm,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(BnbTransferTransferSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT BnbTransferTransferSideEnum tag_invoke(
    boost::json::value_to_tag<BnbTransferTransferSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           BnbTransferTransferSideEnum value);

enum class ChangeAutoRepayFuturesStatusAutoRepayEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ChangeAutoRepayFuturesStatusAutoRepayEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ChangeAutoRepayFuturesStatusAutoRepayEnum
tag_invoke(boost::json::value_to_tag<ChangeAutoRepayFuturesStatusAutoRepayEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeAutoRepayFuturesStatusAutoRepayEnum value);

enum class ChangeCmPositionModeDualSidePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ChangeCmPositionModeDualSidePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ChangeCmPositionModeDualSidePositionEnum
tag_invoke(boost::json::value_to_tag<ChangeCmPositionModeDualSidePositionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeCmPositionModeDualSidePositionEnum value);

enum class ChangeUmPositionModeDualSidePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(ChangeUmPositionModeDualSidePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT ChangeUmPositionModeDualSidePositionEnum
tag_invoke(boost::json::value_to_tag<ChangeUmPositionModeDualSidePositionEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeUmPositionModeDualSidePositionEnum value);

enum class FundCollectionByAssetFutureTypeEnum {
    Um,
    Cm,
    Option,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(FundCollectionByAssetFutureTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT FundCollectionByAssetFutureTypeEnum
tag_invoke(boost::json::value_to_tag<FundCollectionByAssetFutureTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           FundCollectionByAssetFutureTypeEnum value);

enum class GetCmIncomeHistoryIncomeTypeEnum {
    Transfer,
    WelcomeBonus,
    FundingFee,
    RealizedPnl,
    Commission,
    InsuranceClear,
    DeliveredSettelment,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(GetCmIncomeHistoryIncomeTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetCmIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetCmIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetCmIncomeHistoryIncomeTypeEnum value);

enum class GetMarginBorrowLoanInterestHistoryArchivedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(GetMarginBorrowLoanInterestHistoryArchivedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetMarginBorrowLoanInterestHistoryArchivedEnum
tag_invoke(boost::json::value_to_tag<GetMarginBorrowLoanInterestHistoryArchivedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetMarginBorrowLoanInterestHistoryArchivedEnum value);

enum class GetUmIncomeHistoryIncomeTypeEnum {
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
    DeliveredSettelment,
    CoinSwapDeposit,
    CoinSwapWithdraw,
    PositionLimitIncreaseFee,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(GetUmIncomeHistoryIncomeTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUmIncomeHistoryIncomeTypeEnum
tag_invoke(boost::json::value_to_tag<GetUmIncomeHistoryIncomeTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetUmIncomeHistoryIncomeTypeEnum value);

enum class QueryMarginLoanRecordArchivedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(QueryMarginLoanRecordArchivedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginLoanRecordArchivedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginLoanRecordArchivedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryMarginLoanRecordArchivedEnum value);

enum class QueryMarginRepayRecordArchivedEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT std::string_view
to_string(QueryMarginRepayRecordArchivedEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT QueryMarginRepayRecordArchivedEnum
tag_invoke(boost::json::value_to_tag<QueryMarginRepayRecordArchivedEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           QueryMarginRepayRecordArchivedEnum value);

struct AccountBalanceParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AccountInformationParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

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

struct ChangeCmInitialLeverageParams {
    common::Required<std::string> symbol;
    /// target initial leverage
    common::Required<std::int64_t> leverage;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeCmPositionModeParams {
    /// "true": Hedge Mode; "false": One-way Mode
    common::Required<ChangeCmPositionModeDualSidePositionEnum> dual_side_position;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCmCurrentPositionModeParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeUmInitialLeverageParams {
    common::Required<std::string> symbol;
    /// Target initial leverage. The maximum is symbol-specific: use `initialLeverage` of bracket 1
    /// from `GET /papi/v1/um/leverageBracket`.
    common::Required<std::int64_t> leverage;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeUmPositionModeParams {
    /// "true": Hedge Mode; "false": One-way Mode
    common::Required<ChangeUmPositionModeDualSidePositionEnum> dual_side_position;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmCurrentPositionModeParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CmNotionalAndLeverageBracketsParams {
    std::optional<std::string> symbol = std::nullopt;
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

struct GetCmAccountDetailParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCmFuturesOrderDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCmFuturesTradeDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCmFuturesTransactionDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCmIncomeHistoryParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<GetCmIncomeHistoryIncomeTypeEnum> income_type = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForCmFuturesOrderHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForCmFuturesTradeHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForCmFuturesTransactionHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForUmFuturesOrderHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForUmFuturesTradeHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDownloadIdForUmFuturesTransactionHistoryParams {
    /// Timestamp in ms
    common::Required<std::int64_t> start_time;
    /// Timestamp in ms
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetMarginBorrowLoanInterestHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    /// Set to true to query archived data from 6 months ago.
    std::optional<GetMarginBorrowLoanInterestHistoryArchivedEnum> archived = std::nullopt;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmAccountDetailParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmAccountDetailV2Params {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmFuturesOrderDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmFuturesTradeDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmFuturesTransactionDownloadLinkByIdParams {
    /// get by download id api
    common::Required<std::string> download_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUmIncomeHistoryParams {
    std::optional<std::string> symbol = std::nullopt;
    /// Income type.
    std::optional<GetUmIncomeHistoryIncomeTypeEnum> income_type = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUserCommissionRateForCmParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetUserCommissionRateForUmParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct MarginMaxBorrowParams {
    common::Required<std::string> asset;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCmPositionInformationParams {
    std::optional<std::string> margin_asset = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginLoanRecordParams {
    common::Required<std::string> asset;
    /// the `tranId` in `POST/papi/v1/marginLoan`
    std::optional<std::int64_t> tx_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    /// Set to true to query archived data from 6 months ago.
    std::optional<QueryMarginLoanRecordArchivedEnum> archived = std::nullopt;
    /// The value cannot be greater than 60000
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginMaxWithdrawParams {
    common::Required<std::string> asset;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginRepayRecordParams {
    common::Required<std::string> asset;
    /// the `tranId` in `POST /papi/v1/repayLoan`
    std::optional<std::int64_t> tx_id = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    /// Set to true to query archived data from 6 months ago.
    std::optional<QueryMarginRepayRecordArchivedEnum> archived = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPortfolioMarginNegativeBalanceInterestHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    /// Timestamp in ms to get funding from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of results returned.
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUmPositionInformationParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUserNegativeBalanceAutoExchangeRecordParams {
    common::Required<std::int64_t> start_time;
    common::Required<std::int64_t> end_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryUserRateLimitParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct RepayFuturesNegativeBalanceParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UmFuturesAccountConfigurationParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UmFuturesSymbolConfigurationParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UmNotionalAndLeverageBracketsParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Account Balance (USER_DATA)
    ///
    /// GET /papi/v1/balance.
    ///
    /// Query account balance
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#account-balance
    [[nodiscard]] common::RestApiResponse<AccountBalanceResponse>
    account_balance(const AccountBalanceParams& params = {}) const;

    /// Asynchronous `account_balance()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountBalanceResponse>)`.
    template <class CompletionToken>
    auto async_account_balance(const AccountBalanceParams& params, CompletionToken&& token) const {
        return common::async_send<AccountBalanceResponse>(client_, account_balance_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Account Information (USER_DATA)
    ///
    /// GET /papi/v1/account.
    ///
    /// Query account information
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#account-information
    [[nodiscard]] common::RestApiResponse<AccountInformationResponse>
    account_information(const AccountInformationParams& params = {}) const;

    /// Asynchronous `account_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AccountInformationResponse>)`.
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<AccountInformationResponse>(
            client_, account_information_request(params), std::forward<CompletionToken>(token));
    }

    /// BNB transfer (TRADE)
    ///
    /// POST /papi/v1/bnb-transfer.
    ///
    /// Transfer BNB in and out of UM
    ///
    /// Weight(IP): 750
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The endpoint can only be called 10 times per 10 minutes in a rolling manner
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#bnb-transfer
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
    /// POST /papi/v1/repay-futures-switch.
    ///
    /// Change Auto-repay-futures Status
    ///
    /// Weight(IP): 750
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#change-auto-repay-futures-status
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
    /// GET /papi/v1/repay-futures-switch.
    ///
    /// Query Auto-repay-futures Status
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-auto-repay-futures-status
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

    /// Change CM Initial Leverage (TRADE)
    ///
    /// POST /papi/v1/cm/leverage.
    ///
    /// Change user's initial leverage of specific symbol in CM.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#change-cm-initial-leverage
    [[nodiscard]] common::RestApiResponse<ChangeCmInitialLeverageResponse>
    change_cm_initial_leverage(const ChangeCmInitialLeverageParams& params) const;

    /// Asynchronous `change_cm_initial_leverage()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeCmInitialLeverageResponse>)`.
    template <class CompletionToken>
    auto async_change_cm_initial_leverage(const ChangeCmInitialLeverageParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<ChangeCmInitialLeverageResponse>(
            client_, change_cm_initial_leverage_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Change CM Position Mode (TRADE)
    ///
    /// POST /papi/v1/cm/positionSide/dual.
    ///
    /// Change user's position mode (Hedge Mode or One-way Mode ) on EVERY symbol in CM
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#change-cm-position-mode
    [[nodiscard]] common::RestApiResponse<ChangeCmPositionModeResponse>
    change_cm_position_mode(const ChangeCmPositionModeParams& params) const;

    /// Asynchronous `change_cm_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeCmPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_change_cm_position_mode(const ChangeCmPositionModeParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ChangeCmPositionModeResponse>(
            client_, change_cm_position_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Get CM Current Position Mode (USER_DATA)
    ///
    /// GET /papi/v1/cm/positionSide/dual.
    ///
    /// Get user's position mode (Hedge Mode or One-way Mode ) on EVERY symbol in CM
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-current-position-mode
    [[nodiscard]] common::RestApiResponse<GetCmCurrentPositionModeResponse>
    get_cm_current_position_mode(const GetCmCurrentPositionModeParams& params = {}) const;

    /// Asynchronous `get_cm_current_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCmCurrentPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_get_cm_current_position_mode(const GetCmCurrentPositionModeParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetCmCurrentPositionModeResponse>(
            client_, get_cm_current_position_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Change UM Initial Leverage (TRADE)
    ///
    /// POST /papi/v1/um/leverage.
    ///
    /// Change user's initial leverage of specific symbol in UM.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#change-um-initial-leverage
    [[nodiscard]] common::RestApiResponse<ChangeUmInitialLeverageResponse>
    change_um_initial_leverage(const ChangeUmInitialLeverageParams& params) const;

    /// Asynchronous `change_um_initial_leverage()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeUmInitialLeverageResponse>)`.
    template <class CompletionToken>
    auto async_change_um_initial_leverage(const ChangeUmInitialLeverageParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<ChangeUmInitialLeverageResponse>(
            client_, change_um_initial_leverage_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Change UM Position Mode (TRADE)
    ///
    /// POST /papi/v1/um/positionSide/dual.
    ///
    /// Change user's position mode (Hedge Mode or One-way Mode ) on EVERY symbol in UM
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#change-um-position-mode
    [[nodiscard]] common::RestApiResponse<ChangeUmPositionModeResponse>
    change_um_position_mode(const ChangeUmPositionModeParams& params) const;

    /// Asynchronous `change_um_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeUmPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_change_um_position_mode(const ChangeUmPositionModeParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ChangeUmPositionModeResponse>(
            client_, change_um_position_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Get UM Current Position Mode (USER_DATA)
    ///
    /// GET /papi/v1/um/positionSide/dual.
    ///
    /// Get user's position mode (Hedge Mode or One-way Mode ) on EVERY symbol in UM
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-current-position-mode
    [[nodiscard]] common::RestApiResponse<GetUmCurrentPositionModeResponse>
    get_um_current_position_mode(const GetUmCurrentPositionModeParams& params = {}) const;

    /// Asynchronous `get_um_current_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUmCurrentPositionModeResponse>)`.
    template <class CompletionToken>
    auto async_get_um_current_position_mode(const GetUmCurrentPositionModeParams& params,
                                            CompletionToken&& token) const {
        return common::async_send<GetUmCurrentPositionModeResponse>(
            client_, get_um_current_position_mode_request(params),
            std::forward<CompletionToken>(token));
    }

    /// CM Notional and Leverage Brackets (USER_DATA)
    ///
    /// GET /papi/v1/cm/leverageBracket.
    ///
    /// Query CM notional and leverage brackets
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#cm-notional-and-leverage-brackets
    [[nodiscard]] common::RestApiResponse<std::vector<CmNotionalAndLeverageBracketsResponseInner>>
    cm_notional_and_leverage_brackets(const CmNotionalAndLeverageBracketsParams& params = {}) const;

    /// Asynchronous `cm_notional_and_leverage_brackets()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CmNotionalAndLeverageBracketsResponseInner>>)`.
    template <class CompletionToken>
    auto async_cm_notional_and_leverage_brackets(const CmNotionalAndLeverageBracketsParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<std::vector<CmNotionalAndLeverageBracketsResponseInner>>(
            client_, cm_notional_and_leverage_brackets_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Fund Auto-collection (TRADE)
    ///
    /// POST /papi/v1/auto-collection.
    ///
    /// Fund collection for Portfolio Margin
    ///
    /// Weight(IP): 750
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - BNB assets will not be auto-collected.
    /// - Rolling window endpoint can be called at most 500 times per hour.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#fund-auto-collection
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

    /// Fund Collection by Asset (TRADE)
    ///
    /// POST /papi/v1/asset-collection.
    ///
    /// Transfers specific asset from Futures Account to Margin account
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The BNB transfer is not be supported
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#fund-collection-by-asset
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

    /// Get CM Account Detail (USER_DATA)
    ///
    /// GET /papi/v1/cm/account.
    ///
    /// Get current CM account asset and position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-account-detail
    [[nodiscard]] common::RestApiResponse<GetCmAccountDetailResponse>
    get_cm_account_detail(const GetCmAccountDetailParams& params = {}) const;

    /// Asynchronous `get_cm_account_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCmAccountDetailResponse>)`.
    template <class CompletionToken>
    auto async_get_cm_account_detail(const GetCmAccountDetailParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetCmAccountDetailResponse>(
            client_, get_cm_account_detail_request(params), std::forward<CompletionToken>(token));
    }

    /// Get CM Futures Order Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/cm/order/asyn/id.
    ///
    /// Get CM futures order download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-futures-order-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetCmFuturesOrderDownloadLinkByIdResponse>
    get_cm_futures_order_download_link_by_id(
        const GetCmFuturesOrderDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_cm_futures_order_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetCmFuturesOrderDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_cm_futures_order_download_link_by_id(
        const GetCmFuturesOrderDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetCmFuturesOrderDownloadLinkByIdResponse>(
            client_, get_cm_futures_order_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get CM Futures Trade Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/cm/trade/asyn/id.
    ///
    /// Get CM futures trade download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-futures-trade-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetCmFuturesTradeDownloadLinkByIdResponse>
    get_cm_futures_trade_download_link_by_id(
        const GetCmFuturesTradeDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_cm_futures_trade_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetCmFuturesTradeDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_cm_futures_trade_download_link_by_id(
        const GetCmFuturesTradeDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetCmFuturesTradeDownloadLinkByIdResponse>(
            client_, get_cm_futures_trade_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get CM Futures Transaction Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/cm/income/asyn/id.
    ///
    /// Get CM futures Transaction download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-futures-transaction-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetCmFuturesTransactionDownloadLinkByIdResponse>
    get_cm_futures_transaction_download_link_by_id(
        const GetCmFuturesTransactionDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_cm_futures_transaction_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetCmFuturesTransactionDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_cm_futures_transaction_download_link_by_id(
        const GetCmFuturesTransactionDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetCmFuturesTransactionDownloadLinkByIdResponse>(
            client_, get_cm_futures_transaction_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get CM Income History (USER_DATA)
    ///
    /// GET /papi/v1/cm/income.
    ///
    /// Get CM Income History.
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `incomeType` is not sent, all kinds of flow will be returned
    /// - "trandId" is unique in the same "incomeType" for a user
    /// - The interval between `startTime` and `endTime` can not exceed 200 days:
    ///   - If `startTime` and `endTime` are not sent, the last 200 days will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-cm-income-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetCmIncomeHistoryResponseInner>>
    get_cm_income_history(const GetCmIncomeHistoryParams& params = {}) const;

    /// Asynchronous `get_cm_income_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetCmIncomeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_cm_income_history(const GetCmIncomeHistoryParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<GetCmIncomeHistoryResponseInner>>(
            client_, get_cm_income_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Download Id For CM Futures Order History (USER_DATA)
    ///
    /// GET /papi/v1/cm/order/asyn.
    ///
    /// Get download id for CM futures order history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 10 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-cm-futures-order-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForCmFuturesOrderHistoryResponse>
    get_download_id_for_cm_futures_order_history(
        const GetDownloadIdForCmFuturesOrderHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_cm_futures_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForCmFuturesOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_order_history(
        const GetDownloadIdForCmFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForCmFuturesOrderHistoryResponse>(
            client_, get_download_id_for_cm_futures_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For CM Futures Trade History (USER_DATA)
    ///
    /// GET /papi/v1/cm/trade/asyn.
    ///
    /// Get download id for CM futures trade history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 5 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-cm-futures-trade-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForCmFuturesTradeHistoryResponse>
    get_download_id_for_cm_futures_trade_history(
        const GetDownloadIdForCmFuturesTradeHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_cm_futures_trade_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForCmFuturesTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_trade_history(
        const GetDownloadIdForCmFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForCmFuturesTradeHistoryResponse>(
            client_, get_download_id_for_cm_futures_trade_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For CM Futures Transaction History (USER_DATA)
    ///
    /// GET /papi/v1/cm/income/asyn.
    ///
    /// Get download id for CM futures transaction history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 5 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-cm-futures-transaction-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForCmFuturesTransactionHistoryResponse>
    get_download_id_for_cm_futures_transaction_history(
        const GetDownloadIdForCmFuturesTransactionHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_cm_futures_transaction_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForCmFuturesTransactionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_transaction_history(
        const GetDownloadIdForCmFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForCmFuturesTransactionHistoryResponse>(
            client_, get_download_id_for_cm_futures_transaction_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For UM Futures Order History (USER_DATA)
    ///
    /// GET /papi/v1/um/order/asyn.
    ///
    /// Get download id for UM futures order history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 10 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-um-futures-order-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForUmFuturesOrderHistoryResponse>
    get_download_id_for_um_futures_order_history(
        const GetDownloadIdForUmFuturesOrderHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_um_futures_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForUmFuturesOrderHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_order_history(
        const GetDownloadIdForUmFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForUmFuturesOrderHistoryResponse>(
            client_, get_download_id_for_um_futures_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For UM Futures Trade History (USER_DATA)
    ///
    /// GET /papi/v1/um/trade/asyn.
    ///
    /// Get download id for UM futures trade history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 5 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-um-futures-trade-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForUmFuturesTradeHistoryResponse>
    get_download_id_for_um_futures_trade_history(
        const GetDownloadIdForUmFuturesTradeHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_um_futures_trade_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForUmFuturesTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_trade_history(
        const GetDownloadIdForUmFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForUmFuturesTradeHistoryResponse>(
            client_, get_download_id_for_um_futures_trade_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Download Id For UM Futures Transaction History (USER_DATA)
    ///
    /// GET /papi/v1/um/income/asyn.
    ///
    /// Get download id for UM futures transaction history
    ///
    /// Weight(IP): 1500
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Request Limitation is 5 times per month, shared by front end download page and rest api
    /// - The time between `startTime` and `endTime` can not be longer than 1 year
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-download-id-for-um-futures-transaction-history
    [[nodiscard]] common::RestApiResponse<GetDownloadIdForUmFuturesTransactionHistoryResponse>
    get_download_id_for_um_futures_transaction_history(
        const GetDownloadIdForUmFuturesTransactionHistoryParams& params) const;

    /// Asynchronous `get_download_id_for_um_futures_transaction_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetDownloadIdForUmFuturesTransactionHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_transaction_history(
        const GetDownloadIdForUmFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetDownloadIdForUmFuturesTransactionHistoryResponse>(
            client_, get_download_id_for_um_futures_transaction_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Margin Borrow/Loan Interest History (USER_DATA)
    ///
    /// GET /papi/v1/margin/marginInterestHistory.
    ///
    /// Get Margin Borrow/Loan Interest History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    /// - The max interval between startTime and endTime is 30 days. It is a MUST to ensure data
    /// correctness.
    /// - If `startTime` and `endTime` not sent, return records of the last 7 days by default
    /// - If `startTime` is sent and `endTime` is not sent, the records from `startTime` to the
    /// present will be returned; if `startTime` is more than 30 days ago, the records of the past
    /// 30 days will be returned.
    /// - If `startTime` is not sent and `endTime` is sent, the records of the 7 days before
    /// `endTime` is returned.
    /// - Type in response has 5 enums:
    ///   - `PERIODIC` interest charged per hour
    ///   - `ON_BORROW` first interest charged on borrow
    ///   - `PERIODIC_CONVERTED` interest charged per hour converted into BNB
    ///   - `ON_BORROW_CONVERTED` first interest charged on borrow converted into BNB
    ///   - `PORTFOLIO` Portfolio Margin negative balance daily interest
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-margin-borrow-loan-interest-history
    [[nodiscard]] common::RestApiResponse<GetMarginBorrowLoanInterestHistoryResponse>
    get_margin_borrow_loan_interest_history(
        const GetMarginBorrowLoanInterestHistoryParams& params = {}) const;

    /// Asynchronous `get_margin_borrow_loan_interest_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetMarginBorrowLoanInterestHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_margin_borrow_loan_interest_history(
        const GetMarginBorrowLoanInterestHistoryParams& params, CompletionToken&& token) const {
        return common::async_send<GetMarginBorrowLoanInterestHistoryResponse>(
            client_, get_margin_borrow_loan_interest_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get UM Account Detail (USER_DATA)
    ///
    /// GET /papi/v1/um/account.
    ///
    /// Get current UM account asset and position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-account-detail
    [[nodiscard]] common::RestApiResponse<GetUmAccountDetailResponse>
    get_um_account_detail(const GetUmAccountDetailParams& params = {}) const;

    /// Asynchronous `get_um_account_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUmAccountDetailResponse>)`.
    template <class CompletionToken>
    auto async_get_um_account_detail(const GetUmAccountDetailParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetUmAccountDetailResponse>(
            client_, get_um_account_detail_request(params), std::forward<CompletionToken>(token));
    }

    /// Get UM Account Detail V2 (USER_DATA)
    ///
    /// GET /papi/v2/um/account.
    ///
    /// Get current UM account asset and position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-account-detail-v2
    [[nodiscard]] common::RestApiResponse<GetUmAccountDetailV2Response>
    get_um_account_detail_v2(const GetUmAccountDetailV2Params& params = {}) const;

    /// Asynchronous `get_um_account_detail_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUmAccountDetailV2Response>)`.
    template <class CompletionToken>
    auto async_get_um_account_detail_v2(const GetUmAccountDetailV2Params& params,
                                        CompletionToken&& token) const {
        return common::async_send<GetUmAccountDetailV2Response>(
            client_, get_um_account_detail_v2_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get UM Futures Order Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/um/order/asyn/id.
    ///
    /// Get UM futures order download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-futures-order-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetUmFuturesOrderDownloadLinkByIdResponse>
    get_um_futures_order_download_link_by_id(
        const GetUmFuturesOrderDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_um_futures_order_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetUmFuturesOrderDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_um_futures_order_download_link_by_id(
        const GetUmFuturesOrderDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetUmFuturesOrderDownloadLinkByIdResponse>(
            client_, get_um_futures_order_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get UM Futures Trade Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/um/trade/asyn/id.
    ///
    /// Get UM futures trade download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-futures-trade-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetUmFuturesTradeDownloadLinkByIdResponse>
    get_um_futures_trade_download_link_by_id(
        const GetUmFuturesTradeDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_um_futures_trade_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetUmFuturesTradeDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_um_futures_trade_download_link_by_id(
        const GetUmFuturesTradeDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return common::async_send<GetUmFuturesTradeDownloadLinkByIdResponse>(
            client_, get_um_futures_trade_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get UM Futures Transaction Download Link by Id (USER_DATA)
    ///
    /// GET /papi/v1/um/income/asyn/id.
    ///
    /// Get UM futures Transaction download link by Id
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Download link expiration: 7 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-futures-transaction-download-link-by-id
    [[nodiscard]] common::RestApiResponse<GetUmFuturesTransactionDownloadLinkByIdResponse>
    get_um_futures_transaction_download_link_by_id(
        const GetUmFuturesTransactionDownloadLinkByIdParams& params) const;

    /// Asynchronous `get_um_futures_transaction_download_link_by_id()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetUmFuturesTransactionDownloadLinkByIdResponse>)`.
    template <class CompletionToken>
    auto async_get_um_futures_transaction_download_link_by_id(
        const GetUmFuturesTransactionDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return common::async_send<GetUmFuturesTransactionDownloadLinkByIdResponse>(
            client_, get_um_futures_transaction_download_link_by_id_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get UM Income History (USER_DATA)
    ///
    /// GET /papi/v1/um/income.
    ///
    /// Get UM Income History.
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If neither `startTime` nor `endTime` is sent, the recent 7-day data will be returned.
    /// - If `incomeType` is not sent, all kinds of flow will be returned
    /// - "trandId" is unique in the same incomeType for a user
    /// - Income history only contains data for the last three months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-um-income-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetUmIncomeHistoryResponseInner>>
    get_um_income_history(const GetUmIncomeHistoryParams& params = {}) const;

    /// Asynchronous `get_um_income_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetUmIncomeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_um_income_history(const GetUmIncomeHistoryParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<GetUmIncomeHistoryResponseInner>>(
            client_, get_um_income_history_request(params), std::forward<CompletionToken>(token));
    }

    /// Get User Commission Rate for CM (USER_DATA)
    ///
    /// GET /papi/v1/cm/commissionRate.
    ///
    /// Get User Commission Rate for CM
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-user-commission-rate-for-cm
    [[nodiscard]] common::RestApiResponse<GetUserCommissionRateForCmResponse>
    get_user_commission_rate_for_cm(const GetUserCommissionRateForCmParams& params) const;

    /// Asynchronous `get_user_commission_rate_for_cm()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUserCommissionRateForCmResponse>)`.
    template <class CompletionToken>
    auto async_get_user_commission_rate_for_cm(const GetUserCommissionRateForCmParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetUserCommissionRateForCmResponse>(
            client_, get_user_commission_rate_for_cm_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get User Commission Rate for UM (USER_DATA)
    ///
    /// GET /papi/v1/um/commissionRate.
    ///
    /// Get User Commission Rate for UM
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#get-user-commission-rate-for-um
    [[nodiscard]] common::RestApiResponse<GetUserCommissionRateForUmResponse>
    get_user_commission_rate_for_um(const GetUserCommissionRateForUmParams& params) const;

    /// Asynchronous `get_user_commission_rate_for_um()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetUserCommissionRateForUmResponse>)`.
    template <class CompletionToken>
    auto async_get_user_commission_rate_for_um(const GetUserCommissionRateForUmParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetUserCommissionRateForUmResponse>(
            client_, get_user_commission_rate_for_um_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Margin Max Borrow (USER_DATA)
    ///
    /// GET /papi/v1/margin/maxBorrowable.
    ///
    /// Query margin max borrow
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#margin-max-borrow
    [[nodiscard]] common::RestApiResponse<MarginMaxBorrowResponse>
    margin_max_borrow(const MarginMaxBorrowParams& params) const;

    /// Asynchronous `margin_max_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarginMaxBorrowResponse>)`.
    template <class CompletionToken>
    auto async_margin_max_borrow(const MarginMaxBorrowParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<MarginMaxBorrowResponse>(
            client_, margin_max_borrow_request(params), std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin UM Trading Quantitative Rules Indicators (USER_DATA)
    ///
    /// GET /papi/v1/um/apiTradingStatus.
    ///
    /// Portfolio Margin UM Trading Quantitative Rules Indicators
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 10 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#portfolio-margin-um-trading-quantitative-rules-indicators
    [[nodiscard]] common::RestApiResponse<
        PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse>
    portfolio_margin_um_trading_quantitative_rules_indicators(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params = {}) const;

    /// Asynchronous `portfolio_margin_um_trading_quantitative_rules_indicators()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse>)`.
    template <class CompletionToken>
    auto async_portfolio_margin_um_trading_quantitative_rules_indicators(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params,
        CompletionToken&& token) const {
        return common::async_send<PortfolioMarginUmTradingQuantitativeRulesIndicatorsResponse>(
            client_, portfolio_margin_um_trading_quantitative_rules_indicators_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query CM Position Information (USER_DATA)
    ///
    /// GET /papi/v1/cm/positionRisk.
    ///
    /// Get current CM position information.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If neither `marginAsset` nor `pair` is sent, positions of all symbols with `TRADING`
    /// status will be returned.
    /// - for One-way Mode user, the response will only show the "BOTH" positions
    /// - for Hedge Mode user, the response will show "LONG", and "SHORT" positions. **Note**
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-cm-position-information
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCmPositionInformationResponseInner>>
    query_cm_position_information(const QueryCmPositionInformationParams& params = {}) const;

    /// Asynchronous `query_cm_position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCmPositionInformationResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_cm_position_information(const QueryCmPositionInformationParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCmPositionInformationResponseInner>>(
            client_, query_cm_position_information_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Loan Record (USER_DATA)
    ///
    /// GET /papi/v1/margin/marginLoan.
    ///
    /// Query margin loan record
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - txId or startTime must be sent. txId takes precedence.
    /// - Response in descending order
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - If `startTime` and `endTime` not sent, return records of the last 7 days by default
    /// - Set `archived` to `true` to query data from 6 months ago
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-margin-loan-record
    [[nodiscard]] common::RestApiResponse<QueryMarginLoanRecordResponse>
    query_margin_loan_record(const QueryMarginLoanRecordParams& params) const;

    /// Asynchronous `query_margin_loan_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginLoanRecordResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_loan_record(const QueryMarginLoanRecordParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<QueryMarginLoanRecordResponse>(
            client_, query_margin_loan_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Max Withdraw (USER_DATA)
    ///
    /// GET /papi/v1/margin/maxWithdraw.
    ///
    /// Query Margin Max Withdraw
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-margin-max-withdraw
    [[nodiscard]] common::RestApiResponse<QueryMarginMaxWithdrawResponse>
    query_margin_max_withdraw(const QueryMarginMaxWithdrawParams& params) const;

    /// Asynchronous `query_margin_max_withdraw()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginMaxWithdrawResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_max_withdraw(const QueryMarginMaxWithdrawParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QueryMarginMaxWithdrawResponse>(
            client_, query_margin_max_withdraw_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin repay Record (USER_DATA)
    ///
    /// GET /papi/v1/margin/repayLoan.
    ///
    /// Query margin repay record.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - txId or startTime must be sent. txId takes precedence.
    /// - Response in descending order
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - If `startTime` and `endTime` not sent, return records of the last 7 days by default
    /// - Set `archived` to `true` to query data from 6 months ago
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-margin-repay-record
    [[nodiscard]] common::RestApiResponse<QueryMarginRepayRecordResponse>
    query_margin_repay_record(const QueryMarginRepayRecordParams& params) const;

    /// Asynchronous `query_margin_repay_record()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginRepayRecordResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_repay_record(const QueryMarginRepayRecordParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QueryMarginRepayRecordResponse>(
            client_, query_margin_repay_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Negative Balance Interest History (USER_DATA)
    ///
    /// GET /papi/v1/portfolio/interest-history.
    ///
    /// Query interest history of negative balance for portfolio margin.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Results are returned in descending order.
    /// - The query range cannot exceed 30 days to ensure data correctness.
    /// - If both `startTime` and `endTime` are omitted, the most recent 7 days are returned by
    /// default.
    /// - If `startTime` is provided but `endTime` is omitted, records from `startTime` to now are
    /// returned; if that exceeds 30 days, only the most recent 30 days are returned.
    /// - If `endTime` is provided but `startTime` is omitted, records from the 7 days before
    /// `endTime` are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-portfolio-margin-negative-balance-interest-history
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner>>
    query_portfolio_margin_negative_balance_interest_history(
        const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params = {}) const;

    /// Asynchronous `query_portfolio_margin_negative_balance_interest_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_negative_balance_interest_history(
        const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<QueryPortfolioMarginNegativeBalanceInterestHistoryResponseInner>>(
            client_, query_portfolio_margin_negative_balance_interest_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query UM Position Information (USER_DATA)
    ///
    /// GET /papi/v1/um/positionRisk.
    ///
    /// Get current UM position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with account push event `ACCOUNT_UPDATE` for timeliness and accuracy.
    /// - In One-way Mode, only positions with side `BOTH` are shown.
    /// - In Hedge Mode, positions with sides `BOTH`, `LONG`, and `SHORT` are shown.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-um-position-information
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUmPositionInformationResponseInner>>
    query_um_position_information(const QueryUmPositionInformationParams& params = {}) const;

    /// Asynchronous `query_um_position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryUmPositionInformationResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_um_position_information(const QueryUmPositionInformationParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<QueryUmPositionInformationResponseInner>>(
            client_, query_um_position_information_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User Negative Balance Auto Exchange Record (USER_DATA)
    ///
    /// GET /papi/v1/portfolio/negative-balance-exchange-record.
    ///
    /// Query user negative balance auto exchange record
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    /// - The max interval between `startTime` and `endTime` is 3 months.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-user-negative-balance-auto-exchange-record
    [[nodiscard]] common::RestApiResponse<QueryUserNegativeBalanceAutoExchangeRecordResponse>
    query_user_negative_balance_auto_exchange_record(
        const QueryUserNegativeBalanceAutoExchangeRecordParams& params) const;

    /// Asynchronous `query_user_negative_balance_auto_exchange_record()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryUserNegativeBalanceAutoExchangeRecordResponse>)`.
    template <class CompletionToken>
    auto async_query_user_negative_balance_auto_exchange_record(
        const QueryUserNegativeBalanceAutoExchangeRecordParams& params,
        CompletionToken&& token) const {
        return common::async_send<QueryUserNegativeBalanceAutoExchangeRecordResponse>(
            client_, query_user_negative_balance_auto_exchange_record_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query User Rate Limit (USER_DATA)
    ///
    /// GET /papi/v1/rateLimit/order.
    ///
    /// Query User Rate Limit
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#query-user-rate-limit
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

    /// Repay futures Negative Balance (USER_DATA)
    ///
    /// POST /papi/v1/repay-futures-negative-balance.
    ///
    /// Repay futures Negative Balance
    ///
    /// Weight(IP): 750
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#repay-futures-negative-balance
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

    /// UM Futures Account Configuration (USER_DATA)
    ///
    /// GET /papi/v1/um/accountConfig.
    ///
    /// Query UM Futures account configuration
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#um-futures-account-configuration
    [[nodiscard]] common::RestApiResponse<UmFuturesAccountConfigurationResponse>
    um_futures_account_configuration(const UmFuturesAccountConfigurationParams& params = {}) const;

    /// Asynchronous `um_futures_account_configuration()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UmFuturesAccountConfigurationResponse>)`.
    template <class CompletionToken>
    auto async_um_futures_account_configuration(const UmFuturesAccountConfigurationParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<UmFuturesAccountConfigurationResponse>(
            client_, um_futures_account_configuration_request(params),
            std::forward<CompletionToken>(token));
    }

    /// UM Futures Symbol Configuration (USER_DATA)
    ///
    /// GET /papi/v1/um/symbolConfig.
    ///
    /// Get current UM account symbol configuration.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#um-futures-symbol-configuration
    [[nodiscard]] common::RestApiResponse<std::vector<UmFuturesSymbolConfigurationResponseInner>>
    um_futures_symbol_configuration(const UmFuturesSymbolConfigurationParams& params = {}) const;

    /// Asynchronous `um_futures_symbol_configuration()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UmFuturesSymbolConfigurationResponseInner>>)`.
    template <class CompletionToken>
    auto async_um_futures_symbol_configuration(const UmFuturesSymbolConfigurationParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<UmFuturesSymbolConfigurationResponseInner>>(
            client_, um_futures_symbol_configuration_request(params),
            std::forward<CompletionToken>(token));
    }

    /// UM Notional and Leverage Brackets (USER_DATA)
    ///
    /// GET /papi/v1/um/leverageBracket.
    ///
    /// Query UM notional and leverage brackets
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/account#um-notional-and-leverage-brackets
    [[nodiscard]] common::RestApiResponse<std::vector<UmNotionalAndLeverageBracketsResponseInner>>
    um_notional_and_leverage_brackets(const UmNotionalAndLeverageBracketsParams& params = {}) const;

    /// Asynchronous `um_notional_and_leverage_brackets()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UmNotionalAndLeverageBracketsResponseInner>>)`.
    template <class CompletionToken>
    auto async_um_notional_and_leverage_brackets(const UmNotionalAndLeverageBracketsParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<std::vector<UmNotionalAndLeverageBracketsResponseInner>>(
            client_, um_notional_and_leverage_brackets_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_balance_request(const AccountBalanceParams& params) const;
    [[nodiscard]] common::RestRequest
    account_information_request(const AccountInformationParams& params) const;
    [[nodiscard]] common::RestRequest bnb_transfer_request(const BnbTransferParams& params) const;
    [[nodiscard]] common::RestRequest change_auto_repay_futures_status_request(
        const ChangeAutoRepayFuturesStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    get_auto_repay_futures_status_request(const GetAutoRepayFuturesStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    change_cm_initial_leverage_request(const ChangeCmInitialLeverageParams& params) const;
    [[nodiscard]] common::RestRequest
    change_cm_position_mode_request(const ChangeCmPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_cm_current_position_mode_request(const GetCmCurrentPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest
    change_um_initial_leverage_request(const ChangeUmInitialLeverageParams& params) const;
    [[nodiscard]] common::RestRequest
    change_um_position_mode_request(const ChangeUmPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_um_current_position_mode_request(const GetUmCurrentPositionModeParams& params) const;
    [[nodiscard]] common::RestRequest cm_notional_and_leverage_brackets_request(
        const CmNotionalAndLeverageBracketsParams& params) const;
    [[nodiscard]] common::RestRequest
    fund_auto_collection_request(const FundAutoCollectionParams& params) const;
    [[nodiscard]] common::RestRequest
    fund_collection_by_asset_request(const FundCollectionByAssetParams& params) const;
    [[nodiscard]] common::RestRequest
    get_cm_account_detail_request(const GetCmAccountDetailParams& params) const;
    [[nodiscard]] common::RestRequest get_cm_futures_order_download_link_by_id_request(
        const GetCmFuturesOrderDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_cm_futures_trade_download_link_by_id_request(
        const GetCmFuturesTradeDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_cm_futures_transaction_download_link_by_id_request(
        const GetCmFuturesTransactionDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest
    get_cm_income_history_request(const GetCmIncomeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_cm_futures_order_history_request(
        const GetDownloadIdForCmFuturesOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_cm_futures_trade_history_request(
        const GetDownloadIdForCmFuturesTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_cm_futures_transaction_history_request(
        const GetDownloadIdForCmFuturesTransactionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_um_futures_order_history_request(
        const GetDownloadIdForUmFuturesOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_um_futures_trade_history_request(
        const GetDownloadIdForUmFuturesTradeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_download_id_for_um_futures_transaction_history_request(
        const GetDownloadIdForUmFuturesTransactionHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_margin_borrow_loan_interest_history_request(
        const GetMarginBorrowLoanInterestHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_um_account_detail_request(const GetUmAccountDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    get_um_account_detail_v2_request(const GetUmAccountDetailV2Params& params) const;
    [[nodiscard]] common::RestRequest get_um_futures_order_download_link_by_id_request(
        const GetUmFuturesOrderDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_um_futures_trade_download_link_by_id_request(
        const GetUmFuturesTradeDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest get_um_futures_transaction_download_link_by_id_request(
        const GetUmFuturesTransactionDownloadLinkByIdParams& params) const;
    [[nodiscard]] common::RestRequest
    get_um_income_history_request(const GetUmIncomeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    get_user_commission_rate_for_cm_request(const GetUserCommissionRateForCmParams& params) const;
    [[nodiscard]] common::RestRequest
    get_user_commission_rate_for_um_request(const GetUserCommissionRateForUmParams& params) const;
    [[nodiscard]] common::RestRequest
    margin_max_borrow_request(const MarginMaxBorrowParams& params) const;
    [[nodiscard]] common::RestRequest
    portfolio_margin_um_trading_quantitative_rules_indicators_request(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params) const;
    [[nodiscard]] common::RestRequest
    query_cm_position_information_request(const QueryCmPositionInformationParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_loan_record_request(const QueryMarginLoanRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_max_withdraw_request(const QueryMarginMaxWithdrawParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_repay_record_request(const QueryMarginRepayRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    query_portfolio_margin_negative_balance_interest_history_request(
        const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_um_position_information_request(const QueryUmPositionInformationParams& params) const;
    [[nodiscard]] common::RestRequest query_user_negative_balance_auto_exchange_record_request(
        const QueryUserNegativeBalanceAutoExchangeRecordParams& params) const;
    [[nodiscard]] common::RestRequest
    query_user_rate_limit_request(const QueryUserRateLimitParams& params) const;
    [[nodiscard]] common::RestRequest
    repay_futures_negative_balance_request(const RepayFuturesNegativeBalanceParams& params) const;
    [[nodiscard]] common::RestRequest um_futures_account_configuration_request(
        const UmFuturesAccountConfigurationParams& params) const;
    [[nodiscard]] common::RestRequest
    um_futures_symbol_configuration_request(const UmFuturesSymbolConfigurationParams& params) const;
    [[nodiscard]] common::RestRequest um_notional_and_leverage_brackets_request(
        const UmNotionalAndLeverageBracketsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
