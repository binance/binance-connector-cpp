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
#include <binance/dual_investment/export.hpp>
#include <binance/dual_investment/rest_api/market_data_api.hpp>
#include <binance/dual_investment/rest_api/models.hpp>
#include <binance/dual_investment/rest_api/trade_api.hpp>

namespace binance::dual_investment::rest_api {

/// DualInvestment REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_DUAL_INVESTMENT_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Dual Investment REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

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

    // MarketDataApi

    /// Get Dual Investment product list
    ///
    /// GET /sapi/v1/dci/product/list.
    ///
    /// Get Dual Investment product list
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/market-data#get-dual-investment-product-list
    [[nodiscard]] common::RestApiResponse<GetDualInvestmentProductListResponse>
    get_dual_investment_product_list(const GetDualInvestmentProductListParams& params) const {
        return market_data_api_.get_dual_investment_product_list(params);
    }
    /// Asynchronous `get_dual_investment_product_list()`.
    template <class CompletionToken>
    auto async_get_dual_investment_product_list(const GetDualInvestmentProductListParams& params,
                                                CompletionToken&& token) const {
        return market_data_api_.async_get_dual_investment_product_list(
            params, std::forward<CompletionToken>(token));
    }

    // TradeApi

    /// Check Dual Investment accounts (USER_DATA)
    ///
    /// GET /sapi/v1/dci/product/accounts.
    ///
    /// Check Dual Investment accounts
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#check-dual-investment-accounts
    [[nodiscard]] common::RestApiResponse<CheckDualInvestmentAccountsResponse>
    check_dual_investment_accounts(const CheckDualInvestmentAccountsParams& params = {}) const {
        return trade_api_.check_dual_investment_accounts(params);
    }
    /// Asynchronous `check_dual_investment_accounts()`.
    template <class CompletionToken>
    auto async_check_dual_investment_accounts(const CheckDualInvestmentAccountsParams& params,
                                              CompletionToken&& token) const {
        return trade_api_.async_check_dual_investment_accounts(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Dual Investment positions (USER_DATA)
    ///
    /// GET /sapi/v1/dci/product/positions.
    ///
    /// Get Dual Investment positions (batch)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#get-dual-investment-positions
    [[nodiscard]] common::RestApiResponse<GetDualInvestmentPositionsResponse>
    get_dual_investment_positions(const GetDualInvestmentPositionsParams& params = {}) const {
        return trade_api_.get_dual_investment_positions(params);
    }
    /// Asynchronous `get_dual_investment_positions()`.
    template <class CompletionToken>
    auto async_get_dual_investment_positions(const GetDualInvestmentPositionsParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_get_dual_investment_positions(params,
                                                              std::forward<CompletionToken>(token));
    }

    /// Subscribe Dual Investment products (USER_DATA)
    ///
    /// POST /sapi/v1/dci/product/subscribe.
    ///
    /// Subscribe Dual Investment products
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Failed messages:
    ///   - Products are not available. This means APR changed to a lower value, or the order is
    ///   unavailable.
    ///   - Failed. This means system or network errors.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#subscribe-dual-investment-products
    [[nodiscard]] common::RestApiResponse<SubscribeDualInvestmentProductsResponse>
    subscribe_dual_investment_products(const SubscribeDualInvestmentProductsParams& params) const {
        return trade_api_.subscribe_dual_investment_products(params);
    }
    /// Asynchronous `subscribe_dual_investment_products()`.
    template <class CompletionToken>
    auto
    async_subscribe_dual_investment_products(const SubscribeDualInvestmentProductsParams& params,
                                             CompletionToken&& token) const {
        return trade_api_.async_subscribe_dual_investment_products(
            params, std::forward<CompletionToken>(token));
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
    MarketDataApi market_data_api_;
    TradeApi trade_api_;
};

} // namespace binance::dual_investment::rest_api
