//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/portfolio_margin_endpoints_api.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

PortfolioMarginEndpointsApi::PortfolioMarginEndpointsApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
PortfolioMarginEndpointsApi::classic_portfolio_margin_account_information_request(
    const ClassicPortfolioMarginAccountInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/pmAccountInfo";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ClassicPortfolioMarginAccountInformationResponse>
PortfolioMarginEndpointsApi::classic_portfolio_margin_account_information(
    const ClassicPortfolioMarginAccountInformationParams& params) const {
    return common::send<ClassicPortfolioMarginAccountInformationResponse>(
        *client_, classic_portfolio_margin_account_information_request(params));
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
