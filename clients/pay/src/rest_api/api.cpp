//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/api.hpp>

namespace binance::pay::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

Api::Api(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
Api::get_pay_trade_history_request(const GetPayTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/pay/transactions";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetPayTradeHistoryResponse>
Api::get_pay_trade_history(const GetPayTradeHistoryParams& params) const {
    return common::send<GetPayTradeHistoryResponse>(*client_,
                                                    get_pay_trade_history_request(params));
}

} // namespace binance::pay::rest_api
