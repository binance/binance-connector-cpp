//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/market_data_api.hpp>

namespace binance::convert::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
MarketDataApi::list_all_convert_pairs_request(const ListAllConvertPairsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/convert/exchangeInfo";
    common::detail::json::set_param(req.query, "fromAsset", params.from_asset);
    common::detail::json::set_param(req.query, "toAsset", params.to_asset);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>
MarketDataApi::list_all_convert_pairs(const ListAllConvertPairsParams& params) const {
    return common::send<std::vector<ListAllConvertPairsResponseInner>>(
        *client_, list_all_convert_pairs_request(params));
}

common::RestRequest MarketDataApi::query_order_quantity_precision_per_asset_request(
    const QueryOrderQuantityPrecisionPerAssetParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/convert/assetInfo";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>
MarketDataApi::query_order_quantity_precision_per_asset(
    const QueryOrderQuantityPrecisionPerAssetParams& params) const {
    return common::send<std::vector<QueryOrderQuantityPrecisionPerAssetResponseInner>>(
        *client_, query_order_quantity_precision_per_asset_request(params));
}

} // namespace binance::convert::rest_api
