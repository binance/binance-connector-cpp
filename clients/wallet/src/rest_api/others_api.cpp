//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/others_api.hpp>

namespace binance::wallet::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

OthersApi::OthersApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest OthersApi::get_symbols_delist_schedule_for_spot_request(
    const GetSymbolsDelistScheduleForSpotParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/spot/delist-schedule";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>
OthersApi::get_symbols_delist_schedule_for_spot(
    const GetSymbolsDelistScheduleForSpotParams& params) const {
    return common::send<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>(
        *client_, get_symbols_delist_schedule_for_spot_request(params));
}

common::RestRequest OthersApi::system_status_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/system/status";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<SystemStatusResponse> OthersApi::system_status() const {
    return common::send<SystemStatusResponse>(*client_, system_status_request());
}

} // namespace binance::wallet::rest_api
