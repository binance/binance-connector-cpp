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
#include <binance/convert/export.hpp>
#include <binance/convert/rest_api/models/list_all_convert_pairs_response_inner.hpp>
#include <binance/convert/rest_api/models/query_order_quantity_precision_per_asset_response_inner.hpp>

namespace binance::convert::rest_api {

struct ListAllConvertPairsParams {
    /// User spends coin
    std::optional<std::string> from_asset = std::nullopt;
    /// User receives coin
    std::optional<std::string> to_asset = std::nullopt;
};

struct QueryOrderQuantityPrecisionPerAssetParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_CONVERT_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// List All Convert Pairs
    ///
    /// GET /sapi/v1/convert/exchangeInfo.
    ///
    /// Query for all convertible token pairs and the tokens’ respective
    /// upper/lower limits
    ///
    /// Weight(IP): 3000
    ///
    /// Notes:
    /// - User needs to supply either or both input parameters.
    /// - If only one of `fromAsset` and `toAsset` is provided, only partial token pairs are
    /// returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/market-data#list-all-convert-pairs
    [[nodiscard]] common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>
    list_all_convert_pairs(const ListAllConvertPairsParams& params = {}) const;

    /// Asynchronous `list_all_convert_pairs()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>)`.
    template <class CompletionToken>
    auto async_list_all_convert_pairs(const ListAllConvertPairsParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<ListAllConvertPairsResponseInner>>(
            client_, list_all_convert_pairs_request(params), std::forward<CompletionToken>(token));
    }

    /// Query order quantity precision per asset (USER_DATA)
    ///
    /// GET /sapi/v1/convert/assetInfo.
    ///
    /// Query for supported asset’s precision information
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-convert/api/rest-api/market-data#query-order-quantity-precision-per-asset
    [[nodiscard]] common::RestApiResponse<
        std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>
    query_order_quantity_precision_per_asset(
        const QueryOrderQuantityPrecisionPerAssetParams& params = {}) const;

    /// Asynchronous `query_order_quantity_precision_per_asset()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_order_quantity_precision_per_asset(
        const QueryOrderQuantityPrecisionPerAssetParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>(
            client_, query_order_quantity_precision_per_asset_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    list_all_convert_pairs_request(const ListAllConvertPairsParams& params) const;
    [[nodiscard]] common::RestRequest query_order_quantity_precision_per_asset_request(
        const QueryOrderQuantityPrecisionPerAssetParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::convert::rest_api
