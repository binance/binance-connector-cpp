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

#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_asset_leverage_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_tiered_collateral_rates_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_collateral_rate_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/portfolio_margin_pro_tiered_collateral_rate_response_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/query_portfolio_margin_asset_index_price_response_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct PortfolioMarginProTieredCollateralRateParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryPortfolioMarginAssetIndexPriceParams {
    std::optional<std::string> asset = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Get Portfolio Margin Asset Leverage (USER_DATA)
    ///
    /// GET /sapi/v1/portfolio/margin-asset-leverage.
    ///
    /// Get Portfolio Margin Asset Leverage
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#get-portfolio-margin-asset-leverage
    [[nodiscard]] common::RestApiResponse<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>
    get_portfolio_margin_asset_leverage() const;

    /// Asynchronous `get_portfolio_margin_asset_leverage()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_asset_leverage(CompletionToken&& token) const {
        return common::async_send<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>(
            client_, get_portfolio_margin_asset_leverage_request(),
            std::forward<CompletionToken>(token));
    }

    /// Get Portfolio Margin Tiered Collateral Rates (MARKET_DATA)
    ///
    /// GET /sapi/v2/portfolio/retail/collateralRate.
    ///
    /// Query the tiered collateral rate configurations for Portfolio Margin assets.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#get-portfolio-margin-tiered-collateral-rates
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>
    get_portfolio_margin_tiered_collateral_rates() const;

    /// Asynchronous `get_portfolio_margin_tiered_collateral_rates()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_portfolio_margin_tiered_collateral_rates(CompletionToken&& token) const {
        return common::async_send<
            std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>(
            client_, get_portfolio_margin_tiered_collateral_rates_request(),
            std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Collateral Rate (MARKET_DATA)
    ///
    /// GET /sapi/v1/portfolio/collateralRate.
    ///
    /// Portfolio Margin Collateral Rate
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#portfolio-margin-collateral-rate
    [[nodiscard]] common::RestApiResponse<std::vector<PortfolioMarginCollateralRateResponseInner>>
    portfolio_margin_collateral_rate() const;

    /// Asynchronous `portfolio_margin_collateral_rate()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PortfolioMarginCollateralRateResponseInner>>)`.
    template <class CompletionToken>
    auto async_portfolio_margin_collateral_rate(CompletionToken&& token) const {
        return common::async_send<std::vector<PortfolioMarginCollateralRateResponseInner>>(
            client_, portfolio_margin_collateral_rate_request(),
            std::forward<CompletionToken>(token));
    }

    /// Portfolio Margin Pro Tiered Collateral Rate (USER_DATA)
    ///
    /// GET /sapi/v2/portfolio/collateralRate.
    ///
    /// Portfolio Margin PRO Tiered Collateral Rate
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#portfolio-margin-pro-tiered-collateral-rate
    [[nodiscard]] common::RestApiResponse<
        std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>
    portfolio_margin_pro_tiered_collateral_rate(
        const PortfolioMarginProTieredCollateralRateParams& params = {}) const;

    /// Asynchronous `portfolio_margin_pro_tiered_collateral_rate()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>)`.
    template <class CompletionToken>
    auto async_portfolio_margin_pro_tiered_collateral_rate(
        const PortfolioMarginProTieredCollateralRateParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>(
            client_, portfolio_margin_pro_tiered_collateral_rate_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Portfolio Margin Asset Index Price (MARKET_DATA)
    ///
    /// GET /sapi/v1/portfolio/asset-index-price.
    ///
    /// Query Portfolio Margin Asset Index Price
    ///
    /// Weight: - 1 if `asset` is sent
    /// - 50 if `asset` is not sent
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin-pro/api/rest-api/market-data#query-portfolio-margin-asset-index-price
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>
    query_portfolio_margin_asset_index_price(
        const QueryPortfolioMarginAssetIndexPriceParams& params = {}) const;

    /// Asynchronous `query_portfolio_margin_asset_index_price()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_portfolio_margin_asset_index_price(
        const QueryPortfolioMarginAssetIndexPriceParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>(
            client_, query_portfolio_margin_asset_index_price_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_portfolio_margin_asset_leverage_request() const;
    [[nodiscard]] common::RestRequest get_portfolio_margin_tiered_collateral_rates_request() const;
    [[nodiscard]] common::RestRequest portfolio_margin_collateral_rate_request() const;
    [[nodiscard]] common::RestRequest portfolio_margin_pro_tiered_collateral_rate_request(
        const PortfolioMarginProTieredCollateralRateParams& params) const;
    [[nodiscard]] common::RestRequest query_portfolio_margin_asset_index_price_request(
        const QueryPortfolioMarginAssetIndexPriceParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
