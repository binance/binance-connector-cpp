//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/user_data_api.hpp>

namespace binance::stock_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(OptionOrderHistorySideEnum value) noexcept {
    switch (value) {
    case OptionOrderHistorySideEnum::Buy:
        return "BUY";
    case OptionOrderHistorySideEnum::Sell:
        return "SELL";
    case OptionOrderHistorySideEnum::Unknown:
        break;
    }
    return "";
}

OptionOrderHistorySideEnum tag_invoke(boost::json::value_to_tag<OptionOrderHistorySideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OptionOrderHistorySideEnum::Buy;
    }
    if (s == "SELL") {
        return OptionOrderHistorySideEnum::Sell;
    }
    return OptionOrderHistorySideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OptionOrderHistorySideEnum value) {
    if (value == OptionOrderHistorySideEnum::Unknown) {
        throw std::invalid_argument("OptionOrderHistorySideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(OptionTradeHistorySideEnum value) noexcept {
    switch (value) {
    case OptionTradeHistorySideEnum::Buy:
        return "BUY";
    case OptionTradeHistorySideEnum::Sell:
        return "SELL";
    case OptionTradeHistorySideEnum::Unknown:
        break;
    }
    return "";
}

OptionTradeHistorySideEnum tag_invoke(boost::json::value_to_tag<OptionTradeHistorySideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return OptionTradeHistorySideEnum::Buy;
    }
    if (s == "SELL") {
        return OptionTradeHistorySideEnum::Sell;
    }
    return OptionTradeHistorySideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                OptionTradeHistorySideEnum value) {
    if (value == OptionTradeHistorySideEnum::Unknown) {
        throw std::invalid_argument("OptionTradeHistorySideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

UserDataApi::UserDataApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
UserDataApi::current_open_option_orders_request(const CurrentOpenOptionOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/order/open-orders";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CurrentOpenOptionOrdersResponseInner>>
UserDataApi::current_open_option_orders(const CurrentOpenOptionOrdersParams& params) const {
    return common::send<std::vector<CurrentOpenOptionOrdersResponseInner>>(
        *client_, current_open_option_orders_request(params));
}

common::RestRequest
UserDataApi::exercisable_options_request(const ExercisableOptionsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/exercise/exercisable";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<ExercisableOptionsResponseInner>>
UserDataApi::exercisable_options(const ExercisableOptionsParams& params) const {
    return common::send<std::vector<ExercisableOptionsResponseInner>>(
        *client_, exercisable_options_request(params));
}

common::RestRequest
UserDataApi::option_exercise_detail_request(const OptionExerciseDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/exercise/detail";
    common::detail::json::set_param(req.query, "tranId", params.tran_id);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionExerciseDetailResponse>
UserDataApi::option_exercise_detail(const OptionExerciseDetailParams& params) const {
    return common::send<OptionExerciseDetailResponse>(*client_,
                                                      option_exercise_detail_request(params));
}

common::RestRequest
UserDataApi::option_exercise_history_request(const OptionExerciseHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/exercise/history";
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionExerciseHistoryResponse>
UserDataApi::option_exercise_history(const OptionExerciseHistoryParams& params) const {
    return common::send<OptionExerciseHistoryResponse>(*client_,
                                                       option_exercise_history_request(params));
}

common::RestRequest
UserDataApi::option_order_detail_request(const OptionOrderDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/order/detail";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionOrderDetailResponse>
UserDataApi::option_order_detail(const OptionOrderDetailParams& params) const {
    return common::send<OptionOrderDetailResponse>(*client_, option_order_detail_request(params));
}

common::RestRequest
UserDataApi::option_order_history_request(const OptionOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/order/history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "underlyingSymbol", params.underlying_symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderStatus", params.order_status);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionOrderHistoryResponse>
UserDataApi::option_order_history(const OptionOrderHistoryParams& params) const {
    return common::send<OptionOrderHistoryResponse>(*client_, option_order_history_request(params));
}

common::RestRequest
UserDataApi::option_positions_request(const OptionPositionsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/position";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<OptionPositionsResponseInner>>
UserDataApi::option_positions(const OptionPositionsParams& params) const {
    return common::send<std::vector<OptionPositionsResponseInner>>(
        *client_, option_positions_request(params));
}

common::RestRequest UserDataApi::option_settlement_event_detail_request(
    const OptionSettlementEventDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/event/detail";
    common::detail::json::set_param(req.query, "eventId", params.event_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionSettlementEventDetailResponse>
UserDataApi::option_settlement_event_detail(const OptionSettlementEventDetailParams& params) const {
    return common::send<OptionSettlementEventDetailResponse>(
        *client_, option_settlement_event_detail_request(params));
}

common::RestRequest UserDataApi::option_settlement_event_history_request(
    const OptionSettlementEventHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/event/history";
    common::detail::json::set_param(req.query, "underlyingSymbol", params.underlying_symbol);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "eventType", params.event_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "lastId", params.last_id);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionSettlementEventHistoryResponse>
UserDataApi::option_settlement_event_history(
    const OptionSettlementEventHistoryParams& params) const {
    return common::send<OptionSettlementEventHistoryResponse>(
        *client_, option_settlement_event_history_request(params));
}

common::RestRequest
UserDataApi::option_trade_history_request(const OptionTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/option/trade/history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "underlyingSymbol", params.underlying_symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OptionTradeHistoryResponse>
UserDataApi::option_trade_history(const OptionTradeHistoryParams& params) const {
    return common::send<OptionTradeHistoryResponse>(*client_, option_trade_history_request(params));
}

} // namespace binance::stock_options::rest_api
