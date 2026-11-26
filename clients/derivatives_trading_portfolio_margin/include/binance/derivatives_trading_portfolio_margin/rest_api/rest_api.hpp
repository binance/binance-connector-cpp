//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/account_api.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/market_data_api.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/trade_api.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/user_data_streams_api.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

/// DerivativesTradingPortfolioMargin REST API client. Cheap to copy: copies share one
/// `common::RestClient` (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Derivatives Trading Portfolio Margin REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);
    /// A client for the testnet.
    [[nodiscard]] static RestApi testnet(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // AccountApi

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
    account_balance(const AccountBalanceParams& params = {}) const {
        return account_api_.account_balance(params);
    }
    /// Asynchronous `account_balance()`.
    template <class CompletionToken>
    auto async_account_balance(const AccountBalanceParams& params, CompletionToken&& token) const {
        return account_api_.async_account_balance(params, std::forward<CompletionToken>(token));
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
    account_information(const AccountInformationParams& params = {}) const {
        return account_api_.account_information(params);
    }
    /// Asynchronous `account_information()`.
    template <class CompletionToken>
    auto async_account_information(const AccountInformationParams& params,
                                   CompletionToken&& token) const {
        return account_api_.async_account_information(params, std::forward<CompletionToken>(token));
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
    bnb_transfer(const BnbTransferParams& params) const {
        return account_api_.bnb_transfer(params);
    }
    /// Asynchronous `bnb_transfer()`.
    template <class CompletionToken>
    auto async_bnb_transfer(const BnbTransferParams& params, CompletionToken&& token) const {
        return account_api_.async_bnb_transfer(params, std::forward<CompletionToken>(token));
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
    change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params) const {
        return account_api_.change_auto_repay_futures_status(params);
    }
    /// Asynchronous `change_auto_repay_futures_status()`.
    template <class CompletionToken>
    auto async_change_auto_repay_futures_status(const ChangeAutoRepayFuturesStatusParams& params,
                                                CompletionToken&& token) const {
        return account_api_.async_change_auto_repay_futures_status(
            params, std::forward<CompletionToken>(token));
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
    get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params = {}) const {
        return account_api_.get_auto_repay_futures_status(params);
    }
    /// Asynchronous `get_auto_repay_futures_status()`.
    template <class CompletionToken>
    auto async_get_auto_repay_futures_status(const GetAutoRepayFuturesStatusParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_get_auto_repay_futures_status(
            params, std::forward<CompletionToken>(token));
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
    change_cm_initial_leverage(const ChangeCmInitialLeverageParams& params) const {
        return account_api_.change_cm_initial_leverage(params);
    }
    /// Asynchronous `change_cm_initial_leverage()`.
    template <class CompletionToken>
    auto async_change_cm_initial_leverage(const ChangeCmInitialLeverageParams& params,
                                          CompletionToken&& token) const {
        return account_api_.async_change_cm_initial_leverage(params,
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
    change_cm_position_mode(const ChangeCmPositionModeParams& params) const {
        return account_api_.change_cm_position_mode(params);
    }
    /// Asynchronous `change_cm_position_mode()`.
    template <class CompletionToken>
    auto async_change_cm_position_mode(const ChangeCmPositionModeParams& params,
                                       CompletionToken&& token) const {
        return account_api_.async_change_cm_position_mode(params,
                                                          std::forward<CompletionToken>(token));
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
    get_cm_current_position_mode(const GetCmCurrentPositionModeParams& params = {}) const {
        return account_api_.get_cm_current_position_mode(params);
    }
    /// Asynchronous `get_cm_current_position_mode()`.
    template <class CompletionToken>
    auto async_get_cm_current_position_mode(const GetCmCurrentPositionModeParams& params,
                                            CompletionToken&& token) const {
        return account_api_.async_get_cm_current_position_mode(
            params, std::forward<CompletionToken>(token));
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
    change_um_initial_leverage(const ChangeUmInitialLeverageParams& params) const {
        return account_api_.change_um_initial_leverage(params);
    }
    /// Asynchronous `change_um_initial_leverage()`.
    template <class CompletionToken>
    auto async_change_um_initial_leverage(const ChangeUmInitialLeverageParams& params,
                                          CompletionToken&& token) const {
        return account_api_.async_change_um_initial_leverage(params,
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
    change_um_position_mode(const ChangeUmPositionModeParams& params) const {
        return account_api_.change_um_position_mode(params);
    }
    /// Asynchronous `change_um_position_mode()`.
    template <class CompletionToken>
    auto async_change_um_position_mode(const ChangeUmPositionModeParams& params,
                                       CompletionToken&& token) const {
        return account_api_.async_change_um_position_mode(params,
                                                          std::forward<CompletionToken>(token));
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
    get_um_current_position_mode(const GetUmCurrentPositionModeParams& params = {}) const {
        return account_api_.get_um_current_position_mode(params);
    }
    /// Asynchronous `get_um_current_position_mode()`.
    template <class CompletionToken>
    auto async_get_um_current_position_mode(const GetUmCurrentPositionModeParams& params,
                                            CompletionToken&& token) const {
        return account_api_.async_get_um_current_position_mode(
            params, std::forward<CompletionToken>(token));
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
    cm_notional_and_leverage_brackets(
        const CmNotionalAndLeverageBracketsParams& params = {}) const {
        return account_api_.cm_notional_and_leverage_brackets(params);
    }
    /// Asynchronous `cm_notional_and_leverage_brackets()`.
    template <class CompletionToken>
    auto async_cm_notional_and_leverage_brackets(const CmNotionalAndLeverageBracketsParams& params,
                                                 CompletionToken&& token) const {
        return account_api_.async_cm_notional_and_leverage_brackets(
            params, std::forward<CompletionToken>(token));
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
    fund_auto_collection(const FundAutoCollectionParams& params = {}) const {
        return account_api_.fund_auto_collection(params);
    }
    /// Asynchronous `fund_auto_collection()`.
    template <class CompletionToken>
    auto async_fund_auto_collection(const FundAutoCollectionParams& params,
                                    CompletionToken&& token) const {
        return account_api_.async_fund_auto_collection(params,
                                                       std::forward<CompletionToken>(token));
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
    fund_collection_by_asset(const FundCollectionByAssetParams& params) const {
        return account_api_.fund_collection_by_asset(params);
    }
    /// Asynchronous `fund_collection_by_asset()`.
    template <class CompletionToken>
    auto async_fund_collection_by_asset(const FundCollectionByAssetParams& params,
                                        CompletionToken&& token) const {
        return account_api_.async_fund_collection_by_asset(params,
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
    get_cm_account_detail(const GetCmAccountDetailParams& params = {}) const {
        return account_api_.get_cm_account_detail(params);
    }
    /// Asynchronous `get_cm_account_detail()`.
    template <class CompletionToken>
    auto async_get_cm_account_detail(const GetCmAccountDetailParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_cm_account_detail(params,
                                                        std::forward<CompletionToken>(token));
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
        const GetCmFuturesOrderDownloadLinkByIdParams& params) const {
        return account_api_.get_cm_futures_order_download_link_by_id(params);
    }
    /// Asynchronous `get_cm_futures_order_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_cm_futures_order_download_link_by_id(
        const GetCmFuturesOrderDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return account_api_.async_get_cm_futures_order_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetCmFuturesTradeDownloadLinkByIdParams& params) const {
        return account_api_.get_cm_futures_trade_download_link_by_id(params);
    }
    /// Asynchronous `get_cm_futures_trade_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_cm_futures_trade_download_link_by_id(
        const GetCmFuturesTradeDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return account_api_.async_get_cm_futures_trade_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetCmFuturesTransactionDownloadLinkByIdParams& params) const {
        return account_api_.get_cm_futures_transaction_download_link_by_id(params);
    }
    /// Asynchronous `get_cm_futures_transaction_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_cm_futures_transaction_download_link_by_id(
        const GetCmFuturesTransactionDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_cm_futures_transaction_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
    get_cm_income_history(const GetCmIncomeHistoryParams& params = {}) const {
        return account_api_.get_cm_income_history(params);
    }
    /// Asynchronous `get_cm_income_history()`.
    template <class CompletionToken>
    auto async_get_cm_income_history(const GetCmIncomeHistoryParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_cm_income_history(params,
                                                        std::forward<CompletionToken>(token));
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
        const GetDownloadIdForCmFuturesOrderHistoryParams& params) const {
        return account_api_.get_download_id_for_cm_futures_order_history(params);
    }
    /// Asynchronous `get_download_id_for_cm_futures_order_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_order_history(
        const GetDownloadIdForCmFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_cm_futures_order_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForCmFuturesTradeHistoryParams& params) const {
        return account_api_.get_download_id_for_cm_futures_trade_history(params);
    }
    /// Asynchronous `get_download_id_for_cm_futures_trade_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_trade_history(
        const GetDownloadIdForCmFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_cm_futures_trade_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForCmFuturesTransactionHistoryParams& params) const {
        return account_api_.get_download_id_for_cm_futures_transaction_history(params);
    }
    /// Asynchronous `get_download_id_for_cm_futures_transaction_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_cm_futures_transaction_history(
        const GetDownloadIdForCmFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_cm_futures_transaction_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForUmFuturesOrderHistoryParams& params) const {
        return account_api_.get_download_id_for_um_futures_order_history(params);
    }
    /// Asynchronous `get_download_id_for_um_futures_order_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_order_history(
        const GetDownloadIdForUmFuturesOrderHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_um_futures_order_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForUmFuturesTradeHistoryParams& params) const {
        return account_api_.get_download_id_for_um_futures_trade_history(params);
    }
    /// Asynchronous `get_download_id_for_um_futures_trade_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_trade_history(
        const GetDownloadIdForUmFuturesTradeHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_um_futures_trade_history(
            params, std::forward<CompletionToken>(token));
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
        const GetDownloadIdForUmFuturesTransactionHistoryParams& params) const {
        return account_api_.get_download_id_for_um_futures_transaction_history(params);
    }
    /// Asynchronous `get_download_id_for_um_futures_transaction_history()`.
    template <class CompletionToken>
    auto async_get_download_id_for_um_futures_transaction_history(
        const GetDownloadIdForUmFuturesTransactionHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_download_id_for_um_futures_transaction_history(
            params, std::forward<CompletionToken>(token));
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
        const GetMarginBorrowLoanInterestHistoryParams& params = {}) const {
        return account_api_.get_margin_borrow_loan_interest_history(params);
    }
    /// Asynchronous `get_margin_borrow_loan_interest_history()`.
    template <class CompletionToken>
    auto async_get_margin_borrow_loan_interest_history(
        const GetMarginBorrowLoanInterestHistoryParams& params, CompletionToken&& token) const {
        return account_api_.async_get_margin_borrow_loan_interest_history(
            params, std::forward<CompletionToken>(token));
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
    get_um_account_detail(const GetUmAccountDetailParams& params = {}) const {
        return account_api_.get_um_account_detail(params);
    }
    /// Asynchronous `get_um_account_detail()`.
    template <class CompletionToken>
    auto async_get_um_account_detail(const GetUmAccountDetailParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_um_account_detail(params,
                                                        std::forward<CompletionToken>(token));
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
    get_um_account_detail_v2(const GetUmAccountDetailV2Params& params = {}) const {
        return account_api_.get_um_account_detail_v2(params);
    }
    /// Asynchronous `get_um_account_detail_v2()`.
    template <class CompletionToken>
    auto async_get_um_account_detail_v2(const GetUmAccountDetailV2Params& params,
                                        CompletionToken&& token) const {
        return account_api_.async_get_um_account_detail_v2(params,
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
        const GetUmFuturesOrderDownloadLinkByIdParams& params) const {
        return account_api_.get_um_futures_order_download_link_by_id(params);
    }
    /// Asynchronous `get_um_futures_order_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_um_futures_order_download_link_by_id(
        const GetUmFuturesOrderDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return account_api_.async_get_um_futures_order_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetUmFuturesTradeDownloadLinkByIdParams& params) const {
        return account_api_.get_um_futures_trade_download_link_by_id(params);
    }
    /// Asynchronous `get_um_futures_trade_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_um_futures_trade_download_link_by_id(
        const GetUmFuturesTradeDownloadLinkByIdParams& params, CompletionToken&& token) const {
        return account_api_.async_get_um_futures_trade_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
        const GetUmFuturesTransactionDownloadLinkByIdParams& params) const {
        return account_api_.get_um_futures_transaction_download_link_by_id(params);
    }
    /// Asynchronous `get_um_futures_transaction_download_link_by_id()`.
    template <class CompletionToken>
    auto async_get_um_futures_transaction_download_link_by_id(
        const GetUmFuturesTransactionDownloadLinkByIdParams& params,
        CompletionToken&& token) const {
        return account_api_.async_get_um_futures_transaction_download_link_by_id(
            params, std::forward<CompletionToken>(token));
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
    get_um_income_history(const GetUmIncomeHistoryParams& params = {}) const {
        return account_api_.get_um_income_history(params);
    }
    /// Asynchronous `get_um_income_history()`.
    template <class CompletionToken>
    auto async_get_um_income_history(const GetUmIncomeHistoryParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_get_um_income_history(params,
                                                        std::forward<CompletionToken>(token));
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
    get_user_commission_rate_for_cm(const GetUserCommissionRateForCmParams& params) const {
        return account_api_.get_user_commission_rate_for_cm(params);
    }
    /// Asynchronous `get_user_commission_rate_for_cm()`.
    template <class CompletionToken>
    auto async_get_user_commission_rate_for_cm(const GetUserCommissionRateForCmParams& params,
                                               CompletionToken&& token) const {
        return account_api_.async_get_user_commission_rate_for_cm(
            params, std::forward<CompletionToken>(token));
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
    get_user_commission_rate_for_um(const GetUserCommissionRateForUmParams& params) const {
        return account_api_.get_user_commission_rate_for_um(params);
    }
    /// Asynchronous `get_user_commission_rate_for_um()`.
    template <class CompletionToken>
    auto async_get_user_commission_rate_for_um(const GetUserCommissionRateForUmParams& params,
                                               CompletionToken&& token) const {
        return account_api_.async_get_user_commission_rate_for_um(
            params, std::forward<CompletionToken>(token));
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
    margin_max_borrow(const MarginMaxBorrowParams& params) const {
        return account_api_.margin_max_borrow(params);
    }
    /// Asynchronous `margin_max_borrow()`.
    template <class CompletionToken>
    auto async_margin_max_borrow(const MarginMaxBorrowParams& params,
                                 CompletionToken&& token) const {
        return account_api_.async_margin_max_borrow(params, std::forward<CompletionToken>(token));
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
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params = {}) const {
        return account_api_.portfolio_margin_um_trading_quantitative_rules_indicators(params);
    }
    /// Asynchronous `portfolio_margin_um_trading_quantitative_rules_indicators()`.
    template <class CompletionToken>
    auto async_portfolio_margin_um_trading_quantitative_rules_indicators(
        const PortfolioMarginUmTradingQuantitativeRulesIndicatorsParams& params,
        CompletionToken&& token) const {
        return account_api_.async_portfolio_margin_um_trading_quantitative_rules_indicators(
            params, std::forward<CompletionToken>(token));
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
    query_cm_position_information(const QueryCmPositionInformationParams& params = {}) const {
        return account_api_.query_cm_position_information(params);
    }
    /// Asynchronous `query_cm_position_information()`.
    template <class CompletionToken>
    auto async_query_cm_position_information(const QueryCmPositionInformationParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_query_cm_position_information(
            params, std::forward<CompletionToken>(token));
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
    query_margin_loan_record(const QueryMarginLoanRecordParams& params) const {
        return account_api_.query_margin_loan_record(params);
    }
    /// Asynchronous `query_margin_loan_record()`.
    template <class CompletionToken>
    auto async_query_margin_loan_record(const QueryMarginLoanRecordParams& params,
                                        CompletionToken&& token) const {
        return account_api_.async_query_margin_loan_record(params,
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
    query_margin_max_withdraw(const QueryMarginMaxWithdrawParams& params) const {
        return account_api_.query_margin_max_withdraw(params);
    }
    /// Asynchronous `query_margin_max_withdraw()`.
    template <class CompletionToken>
    auto async_query_margin_max_withdraw(const QueryMarginMaxWithdrawParams& params,
                                         CompletionToken&& token) const {
        return account_api_.async_query_margin_max_withdraw(params,
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
    query_margin_repay_record(const QueryMarginRepayRecordParams& params) const {
        return account_api_.query_margin_repay_record(params);
    }
    /// Asynchronous `query_margin_repay_record()`.
    template <class CompletionToken>
    auto async_query_margin_repay_record(const QueryMarginRepayRecordParams& params,
                                         CompletionToken&& token) const {
        return account_api_.async_query_margin_repay_record(params,
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
        const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params = {}) const {
        return account_api_.query_portfolio_margin_negative_balance_interest_history(params);
    }
    /// Asynchronous `query_portfolio_margin_negative_balance_interest_history()`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_negative_balance_interest_history(
        const QueryPortfolioMarginNegativeBalanceInterestHistoryParams& params,
        CompletionToken&& token) const {
        return account_api_.async_query_portfolio_margin_negative_balance_interest_history(
            params, std::forward<CompletionToken>(token));
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
    query_um_position_information(const QueryUmPositionInformationParams& params = {}) const {
        return account_api_.query_um_position_information(params);
    }
    /// Asynchronous `query_um_position_information()`.
    template <class CompletionToken>
    auto async_query_um_position_information(const QueryUmPositionInformationParams& params,
                                             CompletionToken&& token) const {
        return account_api_.async_query_um_position_information(
            params, std::forward<CompletionToken>(token));
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
        const QueryUserNegativeBalanceAutoExchangeRecordParams& params) const {
        return account_api_.query_user_negative_balance_auto_exchange_record(params);
    }
    /// Asynchronous `query_user_negative_balance_auto_exchange_record()`.
    template <class CompletionToken>
    auto async_query_user_negative_balance_auto_exchange_record(
        const QueryUserNegativeBalanceAutoExchangeRecordParams& params,
        CompletionToken&& token) const {
        return account_api_.async_query_user_negative_balance_auto_exchange_record(
            params, std::forward<CompletionToken>(token));
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
    query_user_rate_limit(const QueryUserRateLimitParams& params = {}) const {
        return account_api_.query_user_rate_limit(params);
    }
    /// Asynchronous `query_user_rate_limit()`.
    template <class CompletionToken>
    auto async_query_user_rate_limit(const QueryUserRateLimitParams& params,
                                     CompletionToken&& token) const {
        return account_api_.async_query_user_rate_limit(params,
                                                        std::forward<CompletionToken>(token));
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
    repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params = {}) const {
        return account_api_.repay_futures_negative_balance(params);
    }
    /// Asynchronous `repay_futures_negative_balance()`.
    template <class CompletionToken>
    auto async_repay_futures_negative_balance(const RepayFuturesNegativeBalanceParams& params,
                                              CompletionToken&& token) const {
        return account_api_.async_repay_futures_negative_balance(
            params, std::forward<CompletionToken>(token));
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
    um_futures_account_configuration(const UmFuturesAccountConfigurationParams& params = {}) const {
        return account_api_.um_futures_account_configuration(params);
    }
    /// Asynchronous `um_futures_account_configuration()`.
    template <class CompletionToken>
    auto async_um_futures_account_configuration(const UmFuturesAccountConfigurationParams& params,
                                                CompletionToken&& token) const {
        return account_api_.async_um_futures_account_configuration(
            params, std::forward<CompletionToken>(token));
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
    um_futures_symbol_configuration(const UmFuturesSymbolConfigurationParams& params = {}) const {
        return account_api_.um_futures_symbol_configuration(params);
    }
    /// Asynchronous `um_futures_symbol_configuration()`.
    template <class CompletionToken>
    auto async_um_futures_symbol_configuration(const UmFuturesSymbolConfigurationParams& params,
                                               CompletionToken&& token) const {
        return account_api_.async_um_futures_symbol_configuration(
            params, std::forward<CompletionToken>(token));
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
    um_notional_and_leverage_brackets(
        const UmNotionalAndLeverageBracketsParams& params = {}) const {
        return account_api_.um_notional_and_leverage_brackets(params);
    }
    /// Asynchronous `um_notional_and_leverage_brackets()`.
    template <class CompletionToken>
    auto async_um_notional_and_leverage_brackets(const UmNotionalAndLeverageBracketsParams& params,
                                                 CompletionToken&& token) const {
        return account_api_.async_um_notional_and_leverage_brackets(
            params, std::forward<CompletionToken>(token));
    }

    // MarketDataApi

    /// Test Connectivity
    ///
    /// GET /papi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const {
        return market_data_api_.test_connectivity();
    }
    /// Asynchronous `test_connectivity()`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return market_data_api_.async_test_connectivity(std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Cancel All CM Open Conditional Orders (TRADE)
    ///
    /// DELETE /papi/v1/cm/conditional/allOpenOrders.
    ///
    /// Cancel All CM Open Conditional Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-cm-open-conditional-orders
    [[nodiscard]] common::RestApiResponse<CancelAllCmOpenConditionalOrdersResponse>
    cancel_all_cm_open_conditional_orders(
        const CancelAllCmOpenConditionalOrdersParams& params) const {
        return trade_api_.cancel_all_cm_open_conditional_orders(params);
    }
    /// Asynchronous `cancel_all_cm_open_conditional_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_cm_open_conditional_orders(
        const CancelAllCmOpenConditionalOrdersParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_all_cm_open_conditional_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel All CM Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/cm/allOpenOrders.
    ///
    /// Cancel all active LIMIT orders on specific symbol
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-cm-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllCmOpenOrdersResponse>
    cancel_all_cm_open_orders(const CancelAllCmOpenOrdersParams& params) const {
        return trade_api_.cancel_all_cm_open_orders(params);
    }
    /// Asynchronous `cancel_all_cm_open_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_cm_open_orders(const CancelAllCmOpenOrdersParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_cancel_all_cm_open_orders(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel All UM Algo Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/um/algo/allOpenOrders.
    ///
    /// Cancel All UM Algo Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-um-algo-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllUmAlgoOpenOrdersResponse>
    cancel_all_um_algo_open_orders(const CancelAllUmAlgoOpenOrdersParams& params) const {
        return trade_api_.cancel_all_um_algo_open_orders(params);
    }
    /// Asynchronous `cancel_all_um_algo_open_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_um_algo_open_orders(const CancelAllUmAlgoOpenOrdersParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_cancel_all_um_algo_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel All UM Open Orders (TRADE)
    ///
    /// DELETE /papi/v1/um/allOpenOrders.
    ///
    /// Cancel all active LIMIT orders on specific symbol
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-all-um-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllUmOpenOrdersResponse>
    cancel_all_um_open_orders(const CancelAllUmOpenOrdersParams& params) const {
        return trade_api_.cancel_all_um_open_orders(params);
    }
    /// Asynchronous `cancel_all_um_open_orders()`.
    template <class CompletionToken>
    auto async_cancel_all_um_open_orders(const CancelAllUmOpenOrdersParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_cancel_all_um_open_orders(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel CM Conditional Order (TRADE)
    ///
    /// DELETE /papi/v1/cm/conditional/order.
    ///
    /// Cancel CM Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-cm-conditional-order
    [[nodiscard]] common::RestApiResponse<CancelCmConditionalOrderResponse>
    cancel_cm_conditional_order(const CancelCmConditionalOrderParams& params) const {
        return trade_api_.cancel_cm_conditional_order(params);
    }
    /// Asynchronous `cancel_cm_conditional_order()`.
    template <class CompletionToken>
    auto async_cancel_cm_conditional_order(const CancelCmConditionalOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_cancel_cm_conditional_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// New CM Conditional Order (TRADE)
    ///
    /// POST /papi/v1/cm/conditional/order.
    ///
    /// New CM Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on type:
    ///   - Order with type `STOP/TAKE_PROFIT`, parameter `timeInForce` can be sent ( default
    ///   `GTC`).
    ///   - Condition orders will be triggered when:
    ///   - `STOP`, `STOP_MARKET`:
    ///   - BUY: "MARK_PRICE" >= `stopPrice`
    ///   - SELL: "MARK_PRICE" <= `stopPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///   - BUY: "MARK_PRICE" <= `stopPrice`
    ///   - SELL: "MARK_PRICE" >= `stopPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///   - BUY: the lowest mark price after order placed <= `activationPrice`, and the latest mark
    ///   price >= the lowest mark price * (1 + `callbackRate`)
    ///   - SELL: the highest mark price after order placed >= `activationPrice`, and the latest
    ///   mark price <= the highest mark price * (1 - `callbackRate`)
    ///   - For `TRAILING_STOP_MARKET`, if you got such error code. `{"code": -2021, "msg": "Order
    ///   would immediately trigger."}` means that the parameters you send do not meet the following
    ///   requirements:
    ///   - BUY: `activationPrice` should be smaller than latest mark price.
    ///   - SELL: `activationPrice` should be larger than latest mark price.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-cm-conditional-order
    [[nodiscard]] common::RestApiResponse<NewCmConditionalOrderResponse>
    new_cm_conditional_order(const NewCmConditionalOrderParams& params) const {
        return trade_api_.new_cm_conditional_order(params);
    }
    /// Asynchronous `new_cm_conditional_order()`.
    template <class CompletionToken>
    auto async_new_cm_conditional_order(const NewCmConditionalOrderParams& params,
                                        CompletionToken&& token) const {
        return trade_api_.async_new_cm_conditional_order(params,
                                                         std::forward<CompletionToken>(token));
    }

    /// Cancel CM Order (TRADE)
    ///
    /// DELETE /papi/v1/cm/order.
    ///
    /// Cancel an active LIMIT order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-cm-order
    [[nodiscard]] common::RestApiResponse<CancelCmOrderResponse>
    cancel_cm_order(const CancelCmOrderParams& params) const {
        return trade_api_.cancel_cm_order(params);
    }
    /// Asynchronous `cancel_cm_order()`.
    template <class CompletionToken>
    auto async_cancel_cm_order(const CancelCmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_cm_order(params, std::forward<CompletionToken>(token));
    }

    /// Modify CM Order (TRADE)
    ///
    /// PUT /papi/v1/cm/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Both `quantity` and `price` must be sent
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER / PERCENT_FILTER /
    /// LOT_SIZE, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#modify-cm-order
    [[nodiscard]] common::RestApiResponse<ModifyCmOrderResponse>
    modify_cm_order(const ModifyCmOrderParams& params) const {
        return trade_api_.modify_cm_order(params);
    }
    /// Asynchronous `modify_cm_order()`.
    template <class CompletionToken>
    auto async_modify_cm_order(const ModifyCmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_modify_cm_order(params, std::forward<CompletionToken>(token));
    }

    /// New CM Order (TRADE)
    ///
    /// POST /papi/v1/cm/order.
    ///
    /// Place new CM order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on `type`:
    ///   - If `newOrderRespType` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-cm-order
    [[nodiscard]] common::RestApiResponse<NewCmOrderResponse>
    new_cm_order(const NewCmOrderParams& params) const {
        return trade_api_.new_cm_order(params);
    }
    /// Asynchronous `new_cm_order()`.
    template <class CompletionToken>
    auto async_new_cm_order(const NewCmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_cm_order(params, std::forward<CompletionToken>(token));
    }

    /// Query CM Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/order.
    ///
    /// Check an CM order's status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-order
    [[nodiscard]] common::RestApiResponse<QueryCmOrderResponse>
    query_cm_order(const QueryCmOrderParams& params) const {
        return trade_api_.query_cm_order(params);
    }
    /// Asynchronous `query_cm_order()`.
    template <class CompletionToken>
    auto async_query_cm_order(const QueryCmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_cm_order(params, std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account All Open Orders on a Symbol (TRADE)
    ///
    /// DELETE /papi/v1/margin/allOpenOrders.
    ///
    /// Cancel Margin Account All Open Orders on a Symbol
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-all-open-orders-on-asymbol
    [[nodiscard]] common::RestApiResponse<
        std::vector<CancelMarginAccountAllOpenOrdersOnASymbolResponseInner>>
    cancel_margin_account_all_open_orders_on_a_symbol(
        const CancelMarginAccountAllOpenOrdersOnASymbolParams& params) const {
        return trade_api_.cancel_margin_account_all_open_orders_on_a_symbol(params);
    }
    /// Asynchronous `cancel_margin_account_all_open_orders_on_a_symbol()`.
    template <class CompletionToken>
    auto async_cancel_margin_account_all_open_orders_on_a_symbol(
        const CancelMarginAccountAllOpenOrdersOnASymbolParams& params,
        CompletionToken&& token) const {
        return trade_api_.async_cancel_margin_account_all_open_orders_on_a_symbol(
            params, std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account OCO Orders (TRADE)
    ///
    /// DELETE /papi/v1/margin/orderList.
    ///
    /// Cancel Margin Account OCO Orders
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional notes: Canceling an individual leg will cancel the entire OCO
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-oco-orders
    [[nodiscard]] common::RestApiResponse<CancelMarginAccountOcoOrdersResponse>
    cancel_margin_account_oco_orders(const CancelMarginAccountOcoOrdersParams& params) const {
        return trade_api_.cancel_margin_account_oco_orders(params);
    }
    /// Asynchronous `cancel_margin_account_oco_orders()`.
    template <class CompletionToken>
    auto async_cancel_margin_account_oco_orders(const CancelMarginAccountOcoOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_cancel_margin_account_oco_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/orderList.
    ///
    /// Retrieves a specific OCO based on provided optional parameters
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-oco
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountsOcoResponse>
    query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_oco(params);
    }
    /// Asynchronous `query_margin_accounts_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_oco(const QueryMarginAccountsOcoParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_oco(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Cancel Margin Account Order (TRADE)
    ///
    /// DELETE /papi/v1/margin/order.
    ///
    /// Cancel Margin Account Order
    ///
    /// Weight(IP): 2
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-margin-account-order
    [[nodiscard]] common::RestApiResponse<CancelMarginAccountOrderResponse>
    cancel_margin_account_order(const CancelMarginAccountOrderParams& params) const {
        return trade_api_.cancel_margin_account_order(params);
    }
    /// Asynchronous `cancel_margin_account_order()`.
    template <class CompletionToken>
    auto async_cancel_margin_account_order(const CancelMarginAccountOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_cancel_margin_account_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// New Margin Order (TRADE)
    ///
    /// POST /papi/v1/margin/order.
    ///
    /// New Margin Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-margin-order
    [[nodiscard]] common::RestApiResponse<NewMarginOrderResponse>
    new_margin_order(const NewMarginOrderParams& params) const {
        return trade_api_.new_margin_order(params);
    }
    /// Asynchronous `new_margin_order()`.
    template <class CompletionToken>
    auto async_new_margin_order(const NewMarginOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_margin_order(params, std::forward<CompletionToken>(token));
    }

    /// Query Margin Account Order (USER_DATA)
    ///
    /// GET /papi/v1/margin/order.
    ///
    /// Query Margin Account Order
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - For some historical orders, `cummulativeQuoteQty < 0` means the data is unavailable at
    /// this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-account-order
    [[nodiscard]] common::RestApiResponse<QueryMarginAccountOrderResponse>
    query_margin_account_order(const QueryMarginAccountOrderParams& params) const {
        return trade_api_.query_margin_account_order(params);
    }
    /// Asynchronous `query_margin_account_order()`.
    template <class CompletionToken>
    auto async_query_margin_account_order(const QueryMarginAccountOrderParams& params,
                                          CompletionToken&& token) const {
        return trade_api_.async_query_margin_account_order(params,
                                                           std::forward<CompletionToken>(token));
    }

    /// Cancel UM Algo Order (TRADE)
    ///
    /// DELETE /papi/v1/um/algo/order.
    ///
    /// Cancel an active UM algo order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-um-algo-order
    [[nodiscard]] common::RestApiResponse<CancelUmAlgoOrderResponse>
    cancel_um_algo_order(const CancelUmAlgoOrderParams& params = {}) const {
        return trade_api_.cancel_um_algo_order(params);
    }
    /// Asynchronous `cancel_um_algo_order()`.
    template <class CompletionToken>
    auto async_cancel_um_algo_order(const CancelUmAlgoOrderParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_cancel_um_algo_order(params, std::forward<CompletionToken>(token));
    }

    /// New UM Algo Order (TRADE)
    ///
    /// POST /papi/v1/um/algo/order.
    ///
    /// Place new UM conditional order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Algo order with type `STOP`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Algo order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent (default `GTC`).
    /// - Condition orders will be triggered when price reaches the `triggerPrice`.
    /// - `STOP`, `STOP_MARKET`: BUY: latest price >= `triggerPrice`; SELL: latest price <=
    /// `triggerPrice`.
    /// - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`: BUY: latest price <= `triggerPrice`; SELL: latest
    /// price >= `triggerPrice`.
    /// - `TRAILING_STOP_MARKET`: BUY: lowest price after order placed <= `activatePrice`, and
    /// latest price >= lowest price * (1 + `callbackRate`); SELL: highest price after order placed
    /// >= `activatePrice`, and latest price <= highest price * (1 - `callbackRate`).
    /// - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`: follow the same rules for
    /// conditional orders; if triggered, close all current long position (if `SELL`) or current
    /// short position (if `BUY`); cannot be used with `quantity` parameter; cannot be used with
    /// `reduceOnly` parameter; in Hedge Mode, cannot be used with `BUY` orders in `LONG` position
    /// side, and cannot be used with `SELL` orders in `SHORT` position side.
    /// - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    /// `GTD`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-um-algo-order
    [[nodiscard]] common::RestApiResponse<NewUmAlgoOrderResponse>
    new_um_algo_order(const NewUmAlgoOrderParams& params) const {
        return trade_api_.new_um_algo_order(params);
    }
    /// Asynchronous `new_um_algo_order()`.
    template <class CompletionToken>
    auto async_new_um_algo_order(const NewUmAlgoOrderParams& params,
                                 CompletionToken&& token) const {
        return trade_api_.async_new_um_algo_order(params, std::forward<CompletionToken>(token));
    }

    /// Cancel UM Order (TRADE)
    ///
    /// DELETE /papi/v1/um/order.
    ///
    /// Cancel an active UM LIMIT order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cancel-um-order
    [[nodiscard]] common::RestApiResponse<CancelUmOrderResponse>
    cancel_um_order(const CancelUmOrderParams& params) const {
        return trade_api_.cancel_um_order(params);
    }
    /// Asynchronous `cancel_um_order()`.
    template <class CompletionToken>
    auto async_cancel_um_order(const CancelUmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_cancel_um_order(params, std::forward<CompletionToken>(token));
    }

    /// Modify UM Order (TRADE)
    ///
    /// PUT /papi/v1/um/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either orderId or origClientOrderId must be sent, and the orderId will prevail if both are
    /// sent.
    /// - Both quantity and price must be sent
    /// - When the new quantity or price doesn't satisfy PRICE_FILTER / PERCENT_FILTER / LOT_SIZE,
    /// amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new quantity <= executedQty
    ///   - When the order is GTX and the new price will cause it to be executed immediately
    /// - The amendment keeps the order's original selfTradePreventionMode.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#modify-um-order
    [[nodiscard]] common::RestApiResponse<ModifyUmOrderResponse>
    modify_um_order(const ModifyUmOrderParams& params) const {
        return trade_api_.modify_um_order(params);
    }
    /// Asynchronous `modify_um_order()`.
    template <class CompletionToken>
    auto async_modify_um_order(const ModifyUmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_modify_um_order(params, std::forward<CompletionToken>(token));
    }

    /// New UM Order (TRADE)
    ///
    /// POST /papi/v1/um/order.
    ///
    /// Place new UM order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on type:
    ///   - If `newOrderRespType` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///   - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC` or
    ///   `GTD`.
    ///   - In extreme market conditions, timeInForce `GTD` order auto cancel time might be delayed
    ///   comparing to `goodTillDate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#new-um-order
    [[nodiscard]] common::RestApiResponse<NewUmOrderResponse>
    new_um_order(const NewUmOrderParams& params) const {
        return trade_api_.new_um_order(params);
    }
    /// Asynchronous `new_um_order()`.
    template <class CompletionToken>
    auto async_new_um_order(const NewUmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_new_um_order(params, std::forward<CompletionToken>(token));
    }

    /// Query UM Order (USER_DATA)
    ///
    /// GET /papi/v1/um/order.
    ///
    /// Check an UM order's status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - These orders will not be found:
    ///   - Either `orderId` or `origClientOrderId` must be sent.
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-order
    [[nodiscard]] common::RestApiResponse<QueryUmOrderResponse>
    query_um_order(const QueryUmOrderParams& params) const {
        return trade_api_.query_um_order(params);
    }
    /// Asynchronous `query_um_order()`.
    template <class CompletionToken>
    auto async_query_um_order(const QueryUmOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_um_order(params, std::forward<CompletionToken>(token));
    }

    /// CM Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/cm/userTrades.
    ///
    /// Get trades for a specific account and CM symbol.
    ///
    /// Weight: - 20 with `symbol`
    /// - 40 with `pair`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent
    /// - `symbol` and `pair` cannot be sent together
    /// - `pair` and `fromId` cannot be sent together
    /// - `OrderId` can only be sent together with symbol
    /// - If a `pair` is sent, tickers for all symbols of the `pair` will be returned
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`
    /// - If `startTime` and `endTime` are both not sent, then the last '24 hours' data will be
    /// returned.
    /// - The time between `startTime` and `endTime` cannot be longer than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cm-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<CmAccountTradeListResponseInner>>
    cm_account_trade_list(const CmAccountTradeListParams& params = {}) const {
        return trade_api_.cm_account_trade_list(params);
    }
    /// Asynchronous `cm_account_trade_list()`.
    template <class CompletionToken>
    auto async_cm_account_trade_list(const CmAccountTradeListParams& params,
                                     CompletionToken&& token) const {
        return trade_api_.async_cm_account_trade_list(params, std::forward<CompletionToken>(token));
    }

    /// CM Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /papi/v1/cm/adlQuantile.
    ///
    /// Query CM Position ADL Quantile Estimation
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    /// * "HEDGE" as a sign will be returned instead of "BOTH";
    /// * A same value caculated on unrealized pnls on long and short sides' positions will be shown
    /// for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#cm-position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<CmPositionAdlQuantileEstimationResponseInner>>
    cm_position_adl_quantile_estimation(
        const CmPositionAdlQuantileEstimationParams& params = {}) const {
        return trade_api_.cm_position_adl_quantile_estimation(params);
    }
    /// Asynchronous `cm_position_adl_quantile_estimation()`.
    template <class CompletionToken>
    auto
    async_cm_position_adl_quantile_estimation(const CmPositionAdlQuantileEstimationParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_cm_position_adl_quantile_estimation(
            params, std::forward<CompletionToken>(token));
    }

    /// Futures TradFi Perps Contract (USER_DATA)
    ///
    /// POST /papi/v1/um/stock/contract.
    ///
    /// Sign TradFi-Perps agreement contract
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#futures-tradfi-perps-contract
    [[nodiscard]] common::RestApiResponse<FuturesTradfiPerpsContractResponse>
    futures_tradfi_perps_contract(const FuturesTradfiPerpsContractParams& params = {}) const {
        return trade_api_.futures_tradfi_perps_contract(params);
    }
    /// Asynchronous `futures_tradfi_perps_contract()`.
    template <class CompletionToken>
    auto async_futures_tradfi_perps_contract(const FuturesTradfiPerpsContractParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_futures_tradfi_perps_contract(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Get UM Futures BNB Burn Status (USER_DATA)
    ///
    /// GET /papi/v1/um/feeBurn.
    ///
    /// Get user's BNB Fee Discount for UM Futures (Fee Discount On or Fee Discount Off )
    ///
    /// Weight(IP): 30
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#get-um-futures-bnb-burn-status
    [[nodiscard]] common::RestApiResponse<GetUmFuturesBnbBurnStatusResponse>
    get_um_futures_bnb_burn_status(const GetUmFuturesBnbBurnStatusParams& params = {}) const {
        return trade_api_.get_um_futures_bnb_burn_status(params);
    }
    /// Asynchronous `get_um_futures_bnb_burn_status()`.
    template <class CompletionToken>
    auto async_get_um_futures_bnb_burn_status(const GetUmFuturesBnbBurnStatusParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_get_um_futures_bnb_burn_status(
            params, std::forward<CompletionToken>(token));
    }

    /// Toggle BNB Burn On UM Futures Trade (TRADE)
    ///
    /// POST /papi/v1/um/feeBurn.
    ///
    /// Change user's BNB Fee Discount for UM Futures (Fee Discount On or Fee Discount Off ) on
    /// ***EVERY symbol***
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The BNB would not be collected from UM-PM account to the Portfolio Margin account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#toggle-bnb-burn-on-um-futures-trade
    [[nodiscard]] common::RestApiResponse<ToggleBnbBurnOnUmFuturesTradeResponse>
    toggle_bnb_burn_on_um_futures_trade(const ToggleBnbBurnOnUmFuturesTradeParams& params) const {
        return trade_api_.toggle_bnb_burn_on_um_futures_trade(params);
    }
    /// Asynchronous `toggle_bnb_burn_on_um_futures_trade()`.
    template <class CompletionToken>
    auto
    async_toggle_bnb_burn_on_um_futures_trade(const ToggleBnbBurnOnUmFuturesTradeParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_toggle_bnb_burn_on_um_futures_trade(
            params, std::forward<CompletionToken>(token));
    }

    /// Margin Account Borrow (MARGIN)
    ///
    /// POST /papi/v1/marginLoan.
    ///
    /// Apply for a margin loan.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-borrow
    [[nodiscard]] common::RestApiResponse<MarginAccountBorrowResponse>
    margin_account_borrow(const MarginAccountBorrowParams& params) const {
        return trade_api_.margin_account_borrow(params);
    }
    /// Asynchronous `margin_account_borrow()`.
    template <class CompletionToken>
    auto async_margin_account_borrow(const MarginAccountBorrowParams& params,
                                     CompletionToken&& token) const {
        return trade_api_.async_margin_account_borrow(params, std::forward<CompletionToken>(token));
    }

    /// Margin Account New OCO (TRADE)
    ///
    /// POST /papi/v1/margin/order/oco.
    ///
    /// Send in a new OCO for a margin account
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Other Info:
    ///   - Price Restrictions:
    ///   - `SELL`: Limit Price > Last Price > Stop Price
    ///   - `BUY`: Limit Price  * Quantity Restrictions:
    ///   - Both legs must have the same quantity
    ///   - `ICEBERG` quantities however do not have to be the same.
    ///   - Order Rate Limit
    ///   - `OCO` counts as 2 orders against the order rate limit.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-new-oco
    [[nodiscard]] common::RestApiResponse<MarginAccountNewOcoResponse>
    margin_account_new_oco(const MarginAccountNewOcoParams& params) const {
        return trade_api_.margin_account_new_oco(params);
    }
    /// Asynchronous `margin_account_new_oco()`.
    template <class CompletionToken>
    auto async_margin_account_new_oco(const MarginAccountNewOcoParams& params,
                                      CompletionToken&& token) const {
        return trade_api_.async_margin_account_new_oco(params,
                                                       std::forward<CompletionToken>(token));
    }

    /// Margin Account Repay (MARGIN)
    ///
    /// POST /papi/v1/repayLoan.
    ///
    /// Repay for a margin loan.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARGIN
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-repay
    [[nodiscard]] common::RestApiResponse<MarginAccountRepayResponse>
    margin_account_repay(const MarginAccountRepayParams& params) const {
        return trade_api_.margin_account_repay(params);
    }
    /// Asynchronous `margin_account_repay()`.
    template <class CompletionToken>
    auto async_margin_account_repay(const MarginAccountRepayParams& params,
                                    CompletionToken&& token) const {
        return trade_api_.async_margin_account_repay(params, std::forward<CompletionToken>(token));
    }

    /// Margin Account Repay Debt (TRADE)
    ///
    /// POST /papi/v1/margin/repay-debt.
    ///
    /// Repay debt for a margin loan.
    ///
    /// Weight(IP): 3000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The repay asset amount cannot exceed 50000 USD equivalent value for a single request.
    /// - If `amount` is not sent, all the asset loan will be repaid if having enough specific repay
    /// assets.
    /// - If `amount` is sent, only the certain amount of the asset loan will be repaid if having
    /// enough specific repay assets.
    /// - The system will use the same asset to repay the loan first (if have) no matter whether put
    /// the asset in `specifyRepayAssets`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-repay-debt
    [[nodiscard]] common::RestApiResponse<MarginAccountRepayDebtResponse>
    margin_account_repay_debt(const MarginAccountRepayDebtParams& params) const {
        return trade_api_.margin_account_repay_debt(params);
    }
    /// Asynchronous `margin_account_repay_debt()`.
    template <class CompletionToken>
    auto async_margin_account_repay_debt(const MarginAccountRepayDebtParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_margin_account_repay_debt(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Margin Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/margin/myTrades.
    ///
    /// Margin Account Trade List
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - **Note:** * If `fromId` is set, returns orders with id >= `fromId`; otherwise returns
    /// recent order history.
    /// - The interval between `startTime` and `endTime` must be less than 24 hours.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#margin-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<MarginAccountTradeListResponseInner>>
    margin_account_trade_list(const MarginAccountTradeListParams& params) const {
        return trade_api_.margin_account_trade_list(params);
    }
    /// Asynchronous `margin_account_trade_list()`.
    template <class CompletionToken>
    auto async_margin_account_trade_list(const MarginAccountTradeListParams& params,
                                         CompletionToken&& token) const {
        return trade_api_.async_margin_account_trade_list(params,
                                                          std::forward<CompletionToken>(token));
    }

    /// Query All CM Conditional Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/allOrders.
    ///
    /// Query All CM Conditional Orders
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - These orders will not be found:
    ///   - order strategyStatus is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 7 days  * The query time period must be less than 7 days( default as the
    ///   recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-cm-conditional-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmConditionalOrdersResponseInner>>
    query_all_cm_conditional_orders(const QueryAllCmConditionalOrdersParams& params = {}) const {
        return trade_api_.query_all_cm_conditional_orders(params);
    }
    /// Asynchronous `query_all_cm_conditional_orders()`.
    template <class CompletionToken>
    auto async_query_all_cm_conditional_orders(const QueryAllCmConditionalOrdersParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_query_all_cm_conditional_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All CM Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/allOrders.
    ///
    /// Get all account CM orders; active, canceled, or filled.
    ///
    /// Weight: - 20 with `symbol`
    /// - 40 with `pair`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent.
    /// - If `orderId` is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 3 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-cm-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_all_cm_orders(const QueryAllCmOrdersParams& params = {}) const {
        return trade_api_.query_all_cm_orders(params);
    }
    /// Asynchronous `query_all_cm_orders()`.
    template <class CompletionToken>
    auto async_query_all_cm_orders(const QueryAllCmOrdersParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_query_all_cm_orders(params, std::forward<CompletionToken>(token));
    }

    /// Query All Current CM Open Conditional Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/openOrders.
    ///
    /// Get all open conditional orders on a symbol. **Careful** when accessing this with no symbol.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-cm-open-conditional-orders
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryAllCurrentCmOpenConditionalOrdersResponseInner>>
    query_all_current_cm_open_conditional_orders(
        const QueryAllCurrentCmOpenConditionalOrdersParams& params = {}) const {
        return trade_api_.query_all_current_cm_open_conditional_orders(params);
    }
    /// Asynchronous `query_all_current_cm_open_conditional_orders()`.
    template <class CompletionToken>
    auto async_query_all_current_cm_open_conditional_orders(
        const QueryAllCurrentCmOpenConditionalOrdersParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_all_current_cm_open_conditional_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All Current CM Open Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/openOrders.
    ///
    /// Get all open orders on a symbol.
    ///
    /// * If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-cm-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_all_current_cm_open_orders(const QueryAllCurrentCmOpenOrdersParams& params = {}) const {
        return trade_api_.query_all_current_cm_open_orders(params);
    }
    /// Asynchronous `query_all_current_cm_open_orders()`.
    template <class CompletionToken>
    auto async_query_all_current_cm_open_orders(const QueryAllCurrentCmOpenOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_all_current_cm_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All Current UM Open Algo Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/openAlgoOrders.
    ///
    /// Get all UM open algo orders on a symbol. If the symbol is not sent, orders for all symbols
    /// will be returned.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Weight: 1 for a single symbol; 40 when the symbol parameter is omitted.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-um-open-algo-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenAlgoOrdersResponseInner>>
    query_all_current_um_open_algo_orders(
        const QueryAllCurrentUmOpenAlgoOrdersParams& params = {}) const {
        return trade_api_.query_all_current_um_open_algo_orders(params);
    }
    /// Asynchronous `query_all_current_um_open_algo_orders()`.
    template <class CompletionToken>
    auto
    async_query_all_current_um_open_algo_orders(const QueryAllCurrentUmOpenAlgoOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_all_current_um_open_algo_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All Current UM Open Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/openOrders.
    ///
    /// Get all open orders on a symbol.
    ///
    /// Weight: - 1 for a single `symbol`
    /// - 40 when `symbol` is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If the symbol is not sent, orders for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-current-um-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
    query_all_current_um_open_orders(const QueryAllCurrentUmOpenOrdersParams& params = {}) const {
        return trade_api_.query_all_current_um_open_orders(params);
    }
    /// Asynchronous `query_all_current_um_open_orders()`.
    template <class CompletionToken>
    auto async_query_all_current_um_open_orders(const QueryAllCurrentUmOpenOrdersParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_all_current_um_open_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All Margin Account Orders (USER_DATA)
    ///
    /// GET /papi/v1/margin/allOrders.
    ///
    /// Query All Margin Account Orders
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `orderId` is set, returns orders with id >= `orderId`; otherwise returns recent order
    /// history.
    /// - For some historical orders, `cummulativeQuoteQty < 0` means the data is unavailable at
    /// this time.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-margin-account-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllMarginAccountOrdersResponseInner>>
    query_all_margin_account_orders(const QueryAllMarginAccountOrdersParams& params) const {
        return trade_api_.query_all_margin_account_orders(params);
    }
    /// Asynchronous `query_all_margin_account_orders()`.
    template <class CompletionToken>
    auto async_query_all_margin_account_orders(const QueryAllMarginAccountOrdersParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_query_all_margin_account_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query All UM Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/allOrders.
    ///
    /// Get all account UM orders; active, canceled, or filled.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `orderId` is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-all-um-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCurrentUmOpenOrdersResponseInner>>
    query_all_um_orders(const QueryAllUmOrdersParams& params) const {
        return trade_api_.query_all_um_orders(params);
    }
    /// Asynchronous `query_all_um_orders()`.
    template <class CompletionToken>
    auto async_query_all_um_orders(const QueryAllUmOrdersParams& params,
                                   CompletionToken&& token) const {
        return trade_api_.async_query_all_um_orders(params, std::forward<CompletionToken>(token));
    }

    /// Query CM Conditional Order History (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/orderHistory.
    ///
    /// Query CM Conditional Order History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    /// - `NEW` orders will not be found.
    /// - These orders will not be found:
    ///   - order status is `CANCELED` or `EXPIRED`, **AND**
    ///   - order has NO filled trade, **AND**
    ///   - created time + 7 days < current time
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-conditional-order-history
    [[nodiscard]] common::RestApiResponse<QueryCmConditionalOrderHistoryResponse>
    query_cm_conditional_order_history(const QueryCmConditionalOrderHistoryParams& params) const {
        return trade_api_.query_cm_conditional_order_history(params);
    }
    /// Asynchronous `query_cm_conditional_order_history()`.
    template <class CompletionToken>
    auto
    async_query_cm_conditional_order_history(const QueryCmConditionalOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_query_cm_conditional_order_history(
            params, std::forward<CompletionToken>(token));
    }

    /// Query CM Modify Order History (TRADE)
    ///
    /// GET /papi/v1/cm/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-cm-modify-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCmModifyOrderHistoryResponseInner>>
    query_cm_modify_order_history(const QueryCmModifyOrderHistoryParams& params) const {
        return trade_api_.query_cm_modify_order_history(params);
    }
    /// Asynchronous `query_cm_modify_order_history()`.
    template <class CompletionToken>
    auto async_query_cm_modify_order_history(const QueryCmModifyOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_query_cm_modify_order_history(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query Current CM Open Conditional Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/conditional/openOrder.
    ///
    /// Query Current CM Open Conditional Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `strategyId` or `newClientStrategyId` must be sent.
    /// - If the queried order has been triggered, cancelled or expired, the error message "Order
    /// does not exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-cm-open-conditional-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentCmOpenConditionalOrderResponse>
    query_current_cm_open_conditional_order(
        const QueryCurrentCmOpenConditionalOrderParams& params) const {
        return trade_api_.query_current_cm_open_conditional_order(params);
    }
    /// Asynchronous `query_current_cm_open_conditional_order()`.
    template <class CompletionToken>
    auto async_query_current_cm_open_conditional_order(
        const QueryCurrentCmOpenConditionalOrderParams& params, CompletionToken&& token) const {
        return trade_api_.async_query_current_cm_open_conditional_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Current CM Open Order (USER_DATA)
    ///
    /// GET /papi/v1/cm/openOrder.
    ///
    /// Query current CM open order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-cm-open-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryAllCmOrdersResponseInner>>
    query_current_cm_open_order(const QueryCurrentCmOpenOrderParams& params) const {
        return trade_api_.query_current_cm_open_order(params);
    }
    /// Asynchronous `query_current_cm_open_order()`.
    template <class CompletionToken>
    auto async_query_current_cm_open_order(const QueryCurrentCmOpenOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_current_cm_open_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query Current Margin Open Order (USER_DATA)
    ///
    /// GET /papi/v1/margin/openOrders.
    ///
    /// Query Current Margin Open Order
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `symbol` is not sent, order records for all symbols are returned.
    /// - When returning all symbols, the request count charged to the rate limiter equals the
    /// number of symbols currently trading on the exchange.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-margin-open-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCurrentMarginOpenOrderResponseInner>>
    query_current_margin_open_order(const QueryCurrentMarginOpenOrderParams& params) const {
        return trade_api_.query_current_margin_open_order(params);
    }
    /// Asynchronous `query_current_margin_open_order()`.
    template <class CompletionToken>
    auto async_query_current_margin_open_order(const QueryCurrentMarginOpenOrderParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_query_current_margin_open_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Current UM Open Algo Order (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/algoOrder.
    ///
    /// Check an UM algo order's status. Orders will not be found if: status is CANCELED/EXPIRED
    /// with no fills and created 3+ days ago; or created 90+ days ago.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `algoId` or `clientAlgoId` must be sent. `algoId` is self-increment for each
    /// specific `symbol`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-um-open-algo-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentUmOpenAlgoOrderResponse>
    query_current_um_open_algo_order(const QueryCurrentUmOpenAlgoOrderParams& params = {}) const {
        return trade_api_.query_current_um_open_algo_order(params);
    }
    /// Asynchronous `query_current_um_open_algo_order()`.
    template <class CompletionToken>
    auto async_query_current_um_open_algo_order(const QueryCurrentUmOpenAlgoOrderParams& params,
                                                CompletionToken&& token) const {
        return trade_api_.async_query_current_um_open_algo_order(
            params, std::forward<CompletionToken>(token));
    }

    /// Query Current UM Open Order (USER_DATA)
    ///
    /// GET /papi/v1/um/openOrder.
    ///
    /// Query current UM open order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-current-um-open-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentUmOpenOrderResponse>
    query_current_um_open_order(const QueryCurrentUmOpenOrderParams& params) const {
        return trade_api_.query_current_um_open_order(params);
    }
    /// Asynchronous `query_current_um_open_order()`.
    template <class CompletionToken>
    auto async_query_current_um_open_order(const QueryCurrentUmOpenOrderParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_current_um_open_order(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's all OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/allOrderList.
    ///
    /// Query all OCO for a specific margin account based on provided optional parameters
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-all-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsAllOcoResponseInner>>
    query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_all_oco(params);
    }
    /// Asynchronous `query_margin_accounts_all_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_all_oco(const QueryMarginAccountsAllOcoParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_all_oco(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query Margin Account's Open OCO (USER_DATA)
    ///
    /// GET /papi/v1/margin/openOrderList.
    ///
    /// Query Margin Account's Open OCO
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-margin-accounts-open-oco
    [[nodiscard]] common::RestApiResponse<std::vector<QueryMarginAccountsOpenOcoResponseInner>>
    query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params = {}) const {
        return trade_api_.query_margin_accounts_open_oco(params);
    }
    /// Asynchronous `query_margin_accounts_open_oco()`.
    template <class CompletionToken>
    auto async_query_margin_accounts_open_oco(const QueryMarginAccountsOpenOcoParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_query_margin_accounts_open_oco(
            params, std::forward<CompletionToken>(token));
    }

    /// Query UM Algo Order History (USER_DATA)
    ///
    /// GET /papi/v1/um/algo/allAlgoOrders.
    ///
    /// Get all algo orders: ACTIVE, CANCELED, TRIGGERED or FINISHED.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `algoId` is set, it will get orders >= that `algoId`. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less than 7 days (default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-algo-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUmAlgoOrderHistoryResponseInner>>
    query_um_algo_order_history(const QueryUmAlgoOrderHistoryParams& params) const {
        return trade_api_.query_um_algo_order_history(params);
    }
    /// Asynchronous `query_um_algo_order_history()`.
    template <class CompletionToken>
    auto async_query_um_algo_order_history(const QueryUmAlgoOrderHistoryParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_um_algo_order_history(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query UM Modify Order History (TRADE)
    ///
    /// GET /papi/v1/um/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-um-modify-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUmModifyOrderHistoryResponseInner>>
    query_um_modify_order_history(const QueryUmModifyOrderHistoryParams& params) const {
        return trade_api_.query_um_modify_order_history(params);
    }
    /// Asynchronous `query_um_modify_order_history()`.
    template <class CompletionToken>
    auto async_query_um_modify_order_history(const QueryUmModifyOrderHistoryParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_query_um_modify_order_history(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Query User's CM Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/cm/forceOrders.
    ///
    /// Query User's CM Force Orders
    ///
    /// Weight: - 20 with `symbol`
    /// - 50 without `symbol`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "autoCloseType" is not sent, orders with both of the types will be returned
    /// - If "startTime" is not sent, data within 7 days before "endTime" can be queried
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-cm-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUsersCmForceOrdersResponseInner>>
    query_users_cm_force_orders(const QueryUsersCmForceOrdersParams& params = {}) const {
        return trade_api_.query_users_cm_force_orders(params);
    }
    /// Asynchronous `query_users_cm_force_orders()`.
    template <class CompletionToken>
    auto async_query_users_cm_force_orders(const QueryUsersCmForceOrdersParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_users_cm_force_orders(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// Query User's Margin Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/margin/forceOrders.
    ///
    /// Query user's margin force orders
    ///
    /// > **Note:** Portfolio Margin accounts liquidated through the Risk-Based Liquidation
    /// Adjustment flow will not have any order or trade records returned by this endpoint. Query
    /// the capital flow endpoint instead: Query Cross Isolated Margin Capital Flow.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-margin-force-orders
    [[nodiscard]] common::RestApiResponse<QueryUsersMarginForceOrdersResponse>
    query_users_margin_force_orders(const QueryUsersMarginForceOrdersParams& params = {}) const {
        return trade_api_.query_users_margin_force_orders(params);
    }
    /// Asynchronous `query_users_margin_force_orders()`.
    template <class CompletionToken>
    auto async_query_users_margin_force_orders(const QueryUsersMarginForceOrdersParams& params,
                                               CompletionToken&& token) const {
        return trade_api_.async_query_users_margin_force_orders(
            params, std::forward<CompletionToken>(token));
    }

    /// Query User's UM Force Orders (USER_DATA)
    ///
    /// GET /papi/v1/um/forceOrders.
    ///
    /// Query User's UM Force Orders
    ///
    /// Weight: - 20 with `symbol`
    /// - 50 without `symbol`
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `autoCloseType` is not sent, orders with both of the types will be returned
    /// - If `startTime` is not sent, data within 7 days before `endTime` can be queried
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#query-users-um-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryUsersUmForceOrdersResponseInner>>
    query_users_um_force_orders(const QueryUsersUmForceOrdersParams& params = {}) const {
        return trade_api_.query_users_um_force_orders(params);
    }
    /// Asynchronous `query_users_um_force_orders()`.
    template <class CompletionToken>
    auto async_query_users_um_force_orders(const QueryUsersUmForceOrdersParams& params,
                                           CompletionToken&& token) const {
        return trade_api_.async_query_users_um_force_orders(params,
                                                            std::forward<CompletionToken>(token));
    }

    /// UM Account Trade List (USER_DATA)
    ///
    /// GET /papi/v1/um/userTrades.
    ///
    /// Get trades for a specific account and UM symbol.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are both not sent, then the last '7 days' data will be
    /// returned.
    /// - The time between `startTime` and `endTime` cannot be longer than 7 days.
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#um-account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<UmAccountTradeListResponseInner>>
    um_account_trade_list(const UmAccountTradeListParams& params) const {
        return trade_api_.um_account_trade_list(params);
    }
    /// Asynchronous `um_account_trade_list()`.
    template <class CompletionToken>
    auto async_um_account_trade_list(const UmAccountTradeListParams& params,
                                     CompletionToken&& token) const {
        return trade_api_.async_um_account_trade_list(params, std::forward<CompletionToken>(token));
    }

    /// UM Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /papi/v1/um/adlQuantile.
    ///
    /// Query UM Position ADL Quantile Estimation
    ///
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    /// * "HEDGE" as a sign will be returned instead of "BOTH";
    /// * A same value caculated on unrealized pnls on long and short sides' positions will be shown
    /// for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/trade#um-position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<UmPositionAdlQuantileEstimationResponseInner>>
    um_position_adl_quantile_estimation(
        const UmPositionAdlQuantileEstimationParams& params = {}) const {
        return trade_api_.um_position_adl_quantile_estimation(params);
    }
    /// Asynchronous `um_position_adl_quantile_estimation()`.
    template <class CompletionToken>
    auto
    async_um_position_adl_quantile_estimation(const UmPositionAdlQuantileEstimationParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_um_position_adl_quantile_estimation(
            params, std::forward<CompletionToken>(token));
    }

    // UserDataStreamsApi

    /// Close User Data Stream (USER_STREAM)
    ///
    /// DELETE /papi/v1/listenKey.
    ///
    /// Close out a user data stream.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/user-data-streams#close-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> close_user_data_stream() const {
        return user_data_streams_api_.close_user_data_stream();
    }
    /// Asynchronous `close_user_data_stream()`.
    template <class CompletionToken>
    auto async_close_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_close_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Keepalive User Data Stream (USER_STREAM)
    ///
    /// PUT /papi/v1/listenKey.
    ///
    /// Keepalive a user data stream to prevent a time out. User data streams
    /// will close after 60 minutes. It's recommended to send a ping about every
    /// 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/user-data-streams#keepalive-user-data-stream
    [[nodiscard]] common::RestApiResponse<boost::json::value> keepalive_user_data_stream() const {
        return user_data_streams_api_.keepalive_user_data_stream();
    }
    /// Asynchronous `keepalive_user_data_stream()`.
    template <class CompletionToken>
    auto async_keepalive_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_keepalive_user_data_stream(
            std::forward<CompletionToken>(token));
    }

    /// Start User Data Stream (USER_STREAM)
    ///
    /// POST /papi/v1/listenKey.
    ///
    /// Start a new user data stream. The stream will close after 60 minutes unless a keepalive is
    /// sent. If the account has an active `listenKey`, that `listenKey` will be returned and its
    /// validity will be extended for 60 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/user-data-streams#start-user-data-stream
    [[nodiscard]] common::RestApiResponse<StartUserDataStreamResponse>
    start_user_data_stream() const {
        return user_data_streams_api_.start_user_data_stream();
    }
    /// Asynchronous `start_user_data_stream()`.
    template <class CompletionToken>
    auto async_start_user_data_stream(CompletionToken&& token) const {
        return user_data_streams_api_.async_start_user_data_stream(
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    AccountApi account_api_;
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
    UserDataStreamsApi user_data_streams_api_;
};

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
