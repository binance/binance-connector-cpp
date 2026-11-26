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
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/cross_margin_collateral_ratio_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_all_cross_margin_pairs_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_all_isolated_margin_symbol_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_all_margin_assets_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_delist_schedule_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_limit_price_pairs_response.hpp>
#include <binance/margin_trading/rest_api/models/get_list_schedule_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_margin_asset_risk_based_liquidation_ratio_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/get_margin_restricted_assets_response.hpp>
#include <binance/margin_trading/rest_api/models/query_isolated_margin_tier_data_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_response_inner.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_available_inventory_response.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_priceindex_response.hpp>

namespace binance::margin_trading::rest_api {

enum class QueryMarginAvailableInventoryTypeEnum {
    Margin,
    Isolated,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(QueryMarginAvailableInventoryTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT QueryMarginAvailableInventoryTypeEnum
tag_invoke(boost::json::value_to_tag<QueryMarginAvailableInventoryTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              QueryMarginAvailableInventoryTypeEnum value);

struct GetAllCrossMarginPairsParams {
    std::optional<std::string> symbol = std::nullopt;
};

struct GetAllIsolatedMarginSymbolParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetAllMarginAssetsParams {
    std::optional<std::string> asset = std::nullopt;
};

struct GetDelistScheduleParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetListScheduleParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryIsolatedMarginTierDataParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> tier = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMarginAvailableInventoryParams {
    common::Required<QueryMarginAvailableInventoryTypeEnum> type;
};

struct QueryMarginPriceindexParams {
    common::Required<std::string> symbol;
};

class BINANCE_MARGIN_TRADING_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Cross margin collateral ratio (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/crossMarginCollateralRatio.
    ///
    /// Cross margin collateral ratio
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#cross-margin-collateral-ratio
    [[nodiscard]] common::RestApiResponse<std::vector<CrossMarginCollateralRatioResponseInner>>
    cross_margin_collateral_ratio() const;

    /// Asynchronous `cross_margin_collateral_ratio()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CrossMarginCollateralRatioResponseInner>>)`.
    template <class CompletionToken>
    auto async_cross_margin_collateral_ratio(CompletionToken&& token) const {
        return common::async_send<std::vector<CrossMarginCollateralRatioResponseInner>>(
            client_, cross_margin_collateral_ratio_request(), std::forward<CompletionToken>(token));
    }

    /// Get All Cross Margin Pairs (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/allPairs.
    ///
    /// Get All Cross Margin Pairs
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-cross-margin-pairs
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllCrossMarginPairsResponseInner>>
    get_all_cross_margin_pairs(const GetAllCrossMarginPairsParams& params = {}) const;

    /// Asynchronous `get_all_cross_margin_pairs()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetAllCrossMarginPairsResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_all_cross_margin_pairs(const GetAllCrossMarginPairsParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<GetAllCrossMarginPairsResponseInner>>(
            client_, get_all_cross_margin_pairs_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get All Isolated Margin Symbol (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/isolated/allPairs.
    ///
    /// Get All Isolated Margin Symbol
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-isolated-margin-symbol
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllIsolatedMarginSymbolResponseInner>>
    get_all_isolated_margin_symbol(const GetAllIsolatedMarginSymbolParams& params = {}) const;

    /// Asynchronous `get_all_isolated_margin_symbol()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetAllIsolatedMarginSymbolResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_all_isolated_margin_symbol(const GetAllIsolatedMarginSymbolParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<GetAllIsolatedMarginSymbolResponseInner>>(
            client_, get_all_isolated_margin_symbol_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get All Margin Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/allAssets.
    ///
    /// Get All Margin Assets.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-all-margin-assets
    [[nodiscard]] common::RestApiResponse<std::vector<GetAllMarginAssetsResponseInner>>
    get_all_margin_assets(const GetAllMarginAssetsParams& params = {}) const;

    /// Asynchronous `get_all_margin_assets()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetAllMarginAssetsResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_all_margin_assets(const GetAllMarginAssetsParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<GetAllMarginAssetsResponseInner>>(
            client_, get_all_margin_assets_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Delist Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/delist-schedule.
    ///
    /// Get tokens or symbols delist schedule for cross margin and isolated margin
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-delist-schedule
    [[nodiscard]] common::RestApiResponse<std::vector<GetDelistScheduleResponseInner>>
    get_delist_schedule(const GetDelistScheduleParams& params = {}) const;

    /// Asynchronous `get_delist_schedule()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetDelistScheduleResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_delist_schedule(const GetDelistScheduleParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<GetDelistScheduleResponseInner>>(
            client_, get_delist_schedule_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Limit Price Pairs (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/limit-price-pairs.
    ///
    /// Query trading pairs with restriction on limit price range.
    ///
    /// In margin trading, you can place orders with limit price. Limit price
    /// should be within (-15%, 15%) of current index price for a list of margin
    /// trading pairs. This rule only impacts limit sell orders with limit price
    /// that is lower than current index price and limit buy orders with limit
    /// price that is higher than current index price.
    ///
    /// - Buy order: Your order will be rejected with an error message
    /// notification if the limit price is 15% above the index price.
    ///
    /// - Sell order: Your order will be rejected with an error message
    /// notification if the limit price is 15% below the index price.
    ///
    /// Please review the limit price order placing strategy, backtest and
    /// calibrate the planned order size with the trading volume and order book
    /// depth to prevent trading loss.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-limit-price-pairs
    [[nodiscard]] common::RestApiResponse<GetLimitPricePairsResponse> get_limit_price_pairs() const;

    /// Asynchronous `get_limit_price_pairs()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetLimitPricePairsResponse>)`.
    template <class CompletionToken>
    auto async_get_limit_price_pairs(CompletionToken&& token) const {
        return common::async_send<GetLimitPricePairsResponse>(
            client_, get_limit_price_pairs_request(), std::forward<CompletionToken>(token));
    }

    /// Get list Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/list-schedule.
    ///
    /// Get the upcoming tokens or symbols listing schedule for Cross Margin and Isolated Margin.
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-list-schedule
    [[nodiscard]] common::RestApiResponse<std::vector<GetListScheduleResponseInner>>
    get_list_schedule(const GetListScheduleParams& params = {}) const;

    /// Asynchronous `get_list_schedule()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetListScheduleResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_list_schedule(const GetListScheduleParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<std::vector<GetListScheduleResponseInner>>(
            client_, get_list_schedule_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Margin Asset Risk-Based Liquidation Ratio (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/risk-based-liquidation-ratio.
    ///
    /// Get Margin Asset Risk-Based Liquidation Ratio
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-margin-asset-risk-based-liquidation-ratio
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>
    get_margin_asset_risk_based_liquidation_ratio() const;

    /// Asynchronous `get_margin_asset_risk_based_liquidation_ratio()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_margin_asset_risk_based_liquidation_ratio(CompletionToken&& token) const {
        return common::async_send<
            std::vector<GetMarginAssetRiskBasedLiquidationRatioResponseInner>>(
            client_, get_margin_asset_risk_based_liquidation_ratio_request(),
            std::forward<CompletionToken>(token));
    }

    /// Get Margin Restricted Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/restricted-asset.
    ///
    /// Get the list of margin-restricted assets.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#get-margin-restricted-assets
    [[nodiscard]] common::RestApiResponse<GetMarginRestrictedAssetsResponse>
    get_margin_restricted_assets() const;

    /// Asynchronous `get_margin_restricted_assets()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetMarginRestrictedAssetsResponse>)`.
    template <class CompletionToken>
    auto async_get_margin_restricted_assets(CompletionToken&& token) const {
        return common::async_send<GetMarginRestrictedAssetsResponse>(
            client_, get_margin_restricted_assets_request(), std::forward<CompletionToken>(token));
    }

    /// Query Isolated Margin Tier Data (USER_DATA)
    ///
    /// GET /sapi/v1/margin/isolatedMarginTier.
    ///
    /// Get isolated margin tier data collection with any tier as
    /// https://www.binance.com/en/margin-data
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-isolated-margin-tier-data
    [[nodiscard]] common::RestApiResponse<std::vector<QueryIsolatedMarginTierDataResponseInner>>
    query_isolated_margin_tier_data(const QueryIsolatedMarginTierDataParams& params) const;

    /// Asynchronous `query_isolated_margin_tier_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryIsolatedMarginTierDataResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_isolated_margin_tier_data(const QueryIsolatedMarginTierDataParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<QueryIsolatedMarginTierDataResponseInner>>(
            client_, query_isolated_margin_tier_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Liability Coin Leverage Bracket in Cross Margin Pro Mode (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/leverageBracket.
    ///
    /// Liability Coin Leverage Bracket in Cross Margin Pro Mode
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-liability-coin-leverage-bracket-in-cross-margin-pro-mode
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>
    query_liability_coin_leverage_bracket_in_cross_margin_pro_mode() const;

    /// Asynchronous `query_liability_coin_leverage_bracket_in_cross_margin_pro_mode()`. Completes
    /// with `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_liability_coin_leverage_bracket_in_cross_margin_pro_mode(
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<QueryLiabilityCoinLeverageBracketInCrossMarginProModeResponseInner>>(
            client_, query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_request(),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin Available Inventory (USER_DATA)
    ///
    /// GET /sapi/v1/margin/available-inventory.
    ///
    /// Margin available Inventory query
    ///
    /// Weight(UID): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-margin-available-inventory
    [[nodiscard]] common::RestApiResponse<QueryMarginAvailableInventoryResponse>
    query_margin_available_inventory(const QueryMarginAvailableInventoryParams& params) const;

    /// Asynchronous `query_margin_available_inventory()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginAvailableInventoryResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_available_inventory(const QueryMarginAvailableInventoryParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<QueryMarginAvailableInventoryResponse>(
            client_, query_margin_available_inventory_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Margin PriceIndex (MARKET_DATA)
    ///
    /// GET /sapi/v1/margin/priceIndex.
    ///
    /// Query Margin PriceIndex
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/market-data#query-margin-priceindex
    [[nodiscard]] common::RestApiResponse<QueryMarginPriceindexResponse>
    query_margin_priceindex(const QueryMarginPriceindexParams& params) const;

    /// Asynchronous `query_margin_priceindex()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMarginPriceindexResponse>)`.
    template <class CompletionToken>
    auto async_query_margin_priceindex(const QueryMarginPriceindexParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<QueryMarginPriceindexResponse>(
            client_, query_margin_priceindex_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest cross_margin_collateral_ratio_request() const;
    [[nodiscard]] common::RestRequest
    get_all_cross_margin_pairs_request(const GetAllCrossMarginPairsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_all_isolated_margin_symbol_request(const GetAllIsolatedMarginSymbolParams& params) const;
    [[nodiscard]] common::RestRequest
    get_all_margin_assets_request(const GetAllMarginAssetsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_delist_schedule_request(const GetDelistScheduleParams& params) const;
    [[nodiscard]] common::RestRequest get_limit_price_pairs_request() const;
    [[nodiscard]] common::RestRequest
    get_list_schedule_request(const GetListScheduleParams& params) const;
    [[nodiscard]] common::RestRequest get_margin_asset_risk_based_liquidation_ratio_request() const;
    [[nodiscard]] common::RestRequest get_margin_restricted_assets_request() const;
    [[nodiscard]] common::RestRequest
    query_isolated_margin_tier_data_request(const QueryIsolatedMarginTierDataParams& params) const;
    [[nodiscard]] common::RestRequest
    query_liability_coin_leverage_bracket_in_cross_margin_pro_mode_request() const;
    [[nodiscard]] common::RestRequest query_margin_available_inventory_request(
        const QueryMarginAvailableInventoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_margin_priceindex_request(const QueryMarginPriceindexParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
