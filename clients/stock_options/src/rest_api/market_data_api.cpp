//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/market_data_api.hpp>

namespace binance::stock_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
MarketDataApi::option_contracts_request(const OptionContractsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/market/contracts";
    common::detail::json::set_param(req.query, "underlyingSymbol", params.underlying_symbol);
    common::detail::json::set_param(req.query, "expirationDate", params.expiration_date);
    common::detail::json::set_param(req.query, "rootSymbol", params.root_symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OptionContractsResponseInner>>
MarketDataApi::option_contracts(const OptionContractsParams& params) const {
    return common::send<std::vector<OptionContractsResponseInner>>(
        *client_, option_contracts_request(params));
}

common::RestRequest
MarketDataApi::option_exchange_info_request(const OptionExchangeInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/market/exchangeInfo";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<OptionExchangeInfoResponse>
MarketDataApi::option_exchange_info(const OptionExchangeInfoParams& params) const {
    return common::send<OptionExchangeInfoResponse>(*client_, option_exchange_info_request(params));
}

common::RestRequest
MarketDataApi::option_expirations_request(const OptionExpirationsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/market/expirations";
    common::detail::json::set_param(req.query, "underlyingSymbol", params.underlying_symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OptionExpirationsResponseInner>>
MarketDataApi::option_expirations(const OptionExpirationsParams& params) const {
    return common::send<std::vector<OptionExpirationsResponseInner>>(
        *client_, option_expirations_request(params));
}

} // namespace binance::stock_options::rest_api
