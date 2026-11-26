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

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/vip_loan/export.hpp>
#include <binance/vip_loan/rest_api/models/get_borrow_interest_rate_response_inner.hpp>
#include <binance/vip_loan/rest_api/models/get_collateral_asset_data_response.hpp>
#include <binance/vip_loan/rest_api/models/get_loanable_assets_data_response.hpp>
#include <binance/vip_loan/rest_api/models/get_vip_loan_interest_rate_history_response.hpp>
#include <binance/vip_loan/rest_api/models/query_vip_loan_fixed_rate_market_response.hpp>

namespace binance::vip_loan::rest_api {

struct GetBorrowInterestRateParams {
    /// Max 10 assets, Multiple split by ","
    common::Required<std::string> loan_coin;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetCollateralAssetDataParams {
    std::optional<std::string> collateral_coin = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetLoanableAssetsDataParams {
    std::optional<std::string> loan_coin = std::nullopt;
    /// Defaults to the user's VIP level.
    std::optional<std::int64_t> vip_level = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetVIPLoanInterestRateHistoryParams {
    common::Required<std::string> coin;
    common::Required<std::int64_t> recv_window;
    /// If both startTime and endTime are omitted, the most recent 90 days are returned.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Maximum interval between startTime and endTime is 180 days. Time is based on UTC+0.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Current page number, starting from 1.
    std::optional<std::int64_t> current = std::nullopt;
    /// Number of records per page.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct QueryVIPLoanFixedRateMarketParams {
    /// Loan coin
    common::Required<std::string> loan_coin;
    /// Duration in days, minimum 1
    std::optional<std::int64_t> duration = std::nullopt;
    /// Page number, default 1, minimum 1
    std::optional<std::int64_t> current = std::nullopt;
    /// Page size, default 10, range [1, 100]
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_VIP_LOAN_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Get Borrow Interest Rate (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/request/interestRate.
    ///
    /// Get Borrow Interest Rate
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-borrow-interest-rate
    [[nodiscard]] common::RestApiResponse<std::vector<GetBorrowInterestRateResponseInner>>
    get_borrow_interest_rate(const GetBorrowInterestRateParams& params) const;

    /// Asynchronous `get_borrow_interest_rate()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetBorrowInterestRateResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_borrow_interest_rate(const GetBorrowInterestRateParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<GetBorrowInterestRateResponseInner>>(
            client_, get_borrow_interest_rate_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Collateral Asset Data (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/collateral/data.
    ///
    /// Get Collateral Asset Data
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-collateral-asset-data
    [[nodiscard]] common::RestApiResponse<GetCollateralAssetDataResponse>
    get_collateral_asset_data(const GetCollateralAssetDataParams& params = {}) const;

    /// Asynchronous `get_collateral_asset_data()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCollateralAssetDataResponse>)`.
    template <class CompletionToken>
    auto async_get_collateral_asset_data(const GetCollateralAssetDataParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetCollateralAssetDataResponse>(
            client_, get_collateral_asset_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Loanable Assets Data (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/loanable/data.
    ///
    /// Get interest rate and borrow limit of loanable assets. The borrow limit is shown in USD
    /// value.
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-loanable-assets-data
    [[nodiscard]] common::RestApiResponse<GetLoanableAssetsDataResponse>
    get_loanable_assets_data(const GetLoanableAssetsDataParams& params = {}) const;

    /// Asynchronous `get_loanable_assets_data()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLoanableAssetsDataResponse>)`.
    template <class CompletionToken>
    auto async_get_loanable_assets_data(const GetLoanableAssetsDataParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<GetLoanableAssetsDataResponse>(
            client_, get_loanable_assets_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get VIP Loan Interest Rate History (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/interestRateHistory.
    ///
    /// Check VIP Loan flexible interest rate history
    ///
    /// Weight(IP): 400
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, recent 90-day data is returned.
    /// - The maximum interval between `startTime` and `endTime` is 180 days.
    /// - Time is based on UTC+0.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#get-viploan-interest-rate-history
    [[nodiscard]] common::RestApiResponse<GetVIPLoanInterestRateHistoryResponse>
    get_vip_loan_interest_rate_history(const GetVIPLoanInterestRateHistoryParams& params) const;

    /// Asynchronous `get_vip_loan_interest_rate_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetVIPLoanInterestRateHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_vip_loan_interest_rate_history(const GetVIPLoanInterestRateHistoryParams& params,
                                                  CompletionToken&& token) const {
        return common::async_send<GetVIPLoanInterestRateHistoryResponse>(
            client_, get_vip_loan_interest_rate_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query VIP Loan Fixed Rate Market (USER_DATA)
    ///
    /// GET /sapi/v1/loan/vip/fixed/market.
    ///
    /// Query the VIP Loan fixed rate market. Returns a paginated list of fixed-rate supply orders.
    ///
    /// Weight(IP): 6000
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/market-data#query-viploan-fixed-rate-market
    [[nodiscard]] common::RestApiResponse<QueryVIPLoanFixedRateMarketResponse>
    query_vip_loan_fixed_rate_market(const QueryVIPLoanFixedRateMarketParams& params) const;

    /// Asynchronous `query_vip_loan_fixed_rate_market()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryVIPLoanFixedRateMarketResponse>)`.
    template <class CompletionToken>
    auto async_query_vip_loan_fixed_rate_market(const QueryVIPLoanFixedRateMarketParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<QueryVIPLoanFixedRateMarketResponse>(
            client_, query_vip_loan_fixed_rate_market_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_borrow_interest_rate_request(const GetBorrowInterestRateParams& params) const;
    [[nodiscard]] common::RestRequest
    get_collateral_asset_data_request(const GetCollateralAssetDataParams& params) const;
    [[nodiscard]] common::RestRequest
    get_loanable_assets_data_request(const GetLoanableAssetsDataParams& params) const;
    [[nodiscard]] common::RestRequest get_vip_loan_interest_rate_history_request(
        const GetVIPLoanInterestRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_vip_loan_fixed_rate_market_request(const QueryVIPLoanFixedRateMarketParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::vip_loan::rest_api
