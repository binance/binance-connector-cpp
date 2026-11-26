//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/rebate/rest_api/api.hpp>

namespace binance::rebate::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

Api::Api(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest Api::get_spot_rebate_history_records_request(
    const GetSpotRebateHistoryRecordsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/rebate/taxQuery";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetSpotRebateHistoryRecordsResponse>
Api::get_spot_rebate_history_records(const GetSpotRebateHistoryRecordsParams& params) const {
    return common::send<GetSpotRebateHistoryRecordsResponse>(
        *client_, get_spot_rebate_history_records_request(params));
}

} // namespace binance::rebate::rest_api
