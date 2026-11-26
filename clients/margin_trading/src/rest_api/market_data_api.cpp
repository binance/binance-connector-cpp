//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/market_data_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(QueryMarginAvailableInventoryTypeEnum value) noexcept {
    switch (value) {
    case QueryMarginAvailableInventoryTypeEnum::Margin:
        return "MARGIN";
    case QueryMarginAvailableInventoryTypeEnum::Isolated:
        return "ISOLATED";
    case QueryMarginAvailableInventoryTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryMarginAvailableInventoryTypeEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAvailableInventoryTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARGIN") {
        return QueryMarginAvailableInventoryTypeEnum::Margin;
    }
    if (s == "ISOLATED") {
        return QueryMarginAvailableInventoryTypeEnum::Isolated;
    }
    return QueryMarginAvailableInventoryTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryMarginAvailableInventoryTypeEnum value) {
    if (value == QueryMarginAvailableInventoryTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryMarginAvailableInventoryTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::cross_margin_collateral_ratio_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/crossMarginCollateralRatio";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<CrossMarginCollateralRatioResponseInner>>
MarketDataApi::cross_margin_collateral_ratio() const {
    return common::send<std::vector<CrossMarginCollateralRatioResponseInner>>(
        *client_, cross_margin_collateral_ratio_request());
}

common::RestRequest MarketDataApi::get_all_cross_margin_pairs_request(
    const GetAllCrossMarginPairsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/allPairs";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetAllCrossMarginPairsResponseInner>>
MarketDataApi::get_all_cross_margin_pairs(const GetAllCrossMarginPairsParams& params) const {
    return common::send<std::vector<GetAllCrossMarginPairsResponseInner>>(
        *client_, get_all_cross_margin_pairs_request(params));
}

common::RestRequest MarketDataApi::get_all_isolated_margin_symbol_request(
    const GetAllIsolatedMarginSymbolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/isolated/allPairs";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetAllIsolatedMarginSymbolResponseInner>>
MarketDataApi::get_all_isolated_margin_symbol(
    const GetAllIsolatedMarginSymbolParams& params) const {
    return common::send<std::vector<GetAllIsolatedMarginSymbolResponseInner>>(
        *client_, get_all_isolated_margin_symbol_request(params));
}

common::RestRequest
MarketDataApi::get_all_margin_assets_request(const GetAllMarginAssetsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/allAssets";
    common::detail::json::set_param(req.query, "asset", params.asset);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetAllMarginAssetsResponseInner>>
MarketDataApi::get_all_margin_assets(const GetAllMarginAssetsParams& params) const {
    return common::send<std::vector<GetAllMarginAssetsResponseInner>>(
        *client_, get_all_margin_assets_request(params));
}

common::RestRequest
MarketDataApi::get_delist_schedule_request(const GetDelistScheduleParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/delist-schedule";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetDelistScheduleResponseInner>>
MarketDataApi::get_delist_schedule(const GetDelistScheduleParams& params) const {
    return common::send<std::vector<GetDelistScheduleResponseInner>>(
        *client_, get_delist_schedule_request(params));
}

common::RestRequest MarketDataApi::get_limit_price_pairs_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/limit-price-pairs";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<GetLimitPricePairsResponse> MarketDataApi::get_limit_price_pairs() const {
    return common::send<GetLimitPricePairsResponse>(*client_, get_limit_price_pairs_request());
}

common::RestRequest
MarketDataApi::get_list_schedule_request(const GetListScheduleParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/list-schedule";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetListScheduleResponseInner>>
MarketDataApi::get_list_schedule(const GetListScheduleParams& params) const {
    return common::send<std::vector<GetListScheduleResponseInner>>(
        *client_, get_list_schedule_request(params));
}

common::RestRequest MarketDataApi::get_margin_asset_risk_based_liquidation_ratio_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/risk-based-liquidation-ratio";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>
MarketDataApi::get_margin_asset_risk_based_liquidation_ratio() const {
    return common::send<std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>(
        *client_, get_margin_asset_risk_based_liquidation_ratio_request());
}

common::RestRequest MarketDataApi::get_margin_restricted_assets_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/restricted-asset";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<GetMarginRestrictedAssetsResponse>
MarketDataApi::get_margin_restricted_assets() const {
    return common::send<GetMarginRestrictedAssetsResponse>(*client_,
                                                           get_margin_restricted_assets_request());
}

common::RestRequest MarketDataApi::query_isolated_margin_tier_data_request(
    const QueryIsolatedMarginTierDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/isolatedMarginTier";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "tier", params.tier);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryIsolatedMarginTierDataResponseInner>>
MarketDataApi::query_isolated_margin_tier_data(
    const QueryIsolatedMarginTierDataParams& params) const {
    return common::send<std::vector<QueryIsolatedMarginTierDataResponseInner>>(
        *client_, query_isolated_margin_tier_data_request(params));
}

common::RestRequest
MarketDataApi::query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/leverageBracket";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<
    std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>
MarketDataApi::query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() const {
    return common::send<
        std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>(
        *client_, query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_request());
}

common::RestRequest MarketDataApi::query_margin_available_inventory_request(
    const QueryMarginAvailableInventoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/available-inventory";
    common::detail::json::set_param(req.query, "type", params.type);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMarginAvailableInventoryResponse>
MarketDataApi::query_margin_available_inventory(
    const QueryMarginAvailableInventoryParams& params) const {
    return common::send<QueryMarginAvailableInventoryResponse>(
        *client_, query_margin_available_inventory_request(params));
}

common::RestRequest
MarketDataApi::query_margin_priceindex_request(const QueryMarginPriceindexParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/priceIndex";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<QueryMarginPriceindexResponse>
MarketDataApi::query_margin_priceindex(const QueryMarginPriceindexParams& params) const {
    return common::send<QueryMarginPriceindexResponse>(*client_,
                                                       query_margin_priceindex_request(params));
}

} // namespace binance::margin_trading::rest_api
