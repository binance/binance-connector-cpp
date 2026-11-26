//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/market_data_api.hpp>

namespace binance::stocks::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::exchange_info_request(const ExchangeInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/market/exchangeInfo";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ExchangeInfoResponse>
MarketDataApi::exchange_info(const ExchangeInfoParams& params) const {
    return common::send<ExchangeInfoResponse>(*client_, exchange_info_request(params));
}

common::RestRequest MarketDataApi::latest_quote_request(const LatestQuoteParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/market/quote";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<LatestQuoteResponse>
MarketDataApi::latest_quote(const LatestQuoteParams& params) const {
    return common::send<LatestQuoteResponse>(*client_, latest_quote_request(params));
}

common::RestRequest MarketDataApi::tokenized_assets_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/market/tokenized-assets";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<TokenizedAssetsResponseInner>>
MarketDataApi::tokenized_assets() const {
    return common::send<std::vector<TokenizedAssetsResponseInner>>(*client_,
                                                                   tokenized_assets_request());
}

} // namespace binance::stocks::rest_api
