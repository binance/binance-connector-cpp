//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/market_data_api.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::get_portfolio_margin_asset_leverage_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/margin-asset-leverage";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>
MarketDataApi::get_portfolio_margin_asset_leverage() const {
    return common::send<std::vector<GetPortfolioMarginAssetLeverageResponseInner>>(
        *client_, get_portfolio_margin_asset_leverage_request());
}

common::RestRequest MarketDataApi::get_portfolio_margin_tiered_collateral_rates_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/portfolio/retail/collateralRate";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>
MarketDataApi::get_portfolio_margin_tiered_collateral_rates() const {
    return common::send<std::vector<GetPortfolioMarginTieredCollateralRatesResponseInner>>(
        *client_, get_portfolio_margin_tiered_collateral_rates_request());
}

common::RestRequest MarketDataApi::portfolio_margin_collateral_rate_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/collateralRate";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<PortfolioMarginCollateralRateResponseInner>>
MarketDataApi::portfolio_margin_collateral_rate() const {
    return common::send<std::vector<PortfolioMarginCollateralRateResponseInner>>(
        *client_, portfolio_margin_collateral_rate_request());
}

common::RestRequest MarketDataApi::portfolio_margin_pro_tiered_collateral_rate_request(
    const PortfolioMarginProTieredCollateralRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v2/portfolio/collateralRate";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>
MarketDataApi::portfolio_margin_pro_tiered_collateral_rate(
    const PortfolioMarginProTieredCollateralRateParams& params) const {
    return common::send<std::vector<PortfolioMarginProTieredCollateralRateResponseInner>>(
        *client_, portfolio_margin_pro_tiered_collateral_rate_request(params));
}

common::RestRequest MarketDataApi::query_portfolio_margin_asset_index_price_request(
    const QueryPortfolioMarginAssetIndexPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/portfolio/asset-index-price";
    common::detail::json::set_param(req.query, "asset", params.asset);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>
MarketDataApi::query_portfolio_margin_asset_index_price(
    const QueryPortfolioMarginAssetIndexPriceParams& params) const {
    return common::send<std::vector<QueryPortfolioMarginAssetIndexPriceResponseInner>>(
        *client_, query_portfolio_margin_asset_index_price_request(params));
}

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
