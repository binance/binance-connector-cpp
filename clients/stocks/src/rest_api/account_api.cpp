//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/account_api.hpp>

namespace binance::stocks::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

AccountApi::AccountApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
AccountApi::sign_us_equity_disclaimer_request(const SignUsEquityDisclaimerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/account/disclaimer";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SignUsEquityDisclaimerResponse>
AccountApi::sign_us_equity_disclaimer(const SignUsEquityDisclaimerParams& params) const {
    return common::send<SignUsEquityDisclaimerResponse>(*client_,
                                                        sign_us_equity_disclaimer_request(params));
}

} // namespace binance::stocks::rest_api
