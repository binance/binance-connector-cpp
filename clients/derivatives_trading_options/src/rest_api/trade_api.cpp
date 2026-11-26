//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/trade_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(NewOrderSideEnum value) noexcept {
    switch (value) {
    case NewOrderSideEnum::Buy:
        return "BUY";
    case NewOrderSideEnum::Sell:
        return "SELL";
    case NewOrderSideEnum::Unknown:
        break;
    }
    return "";
}

NewOrderSideEnum tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return NewOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return NewOrderSideEnum::Sell;
    }
    return NewOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderSideEnum value) {
    if (value == NewOrderSideEnum::Unknown) {
        throw std::invalid_argument("NewOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderTypeEnum value) noexcept {
    switch (value) {
    case NewOrderTypeEnum::Limit:
        return "LIMIT";
    case NewOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIMIT") {
        return NewOrderTypeEnum::Limit;
    }
    return NewOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderTypeEnum value) {
    if (value == NewOrderTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case NewOrderTimeInForceEnum::Gtc:
        return "GTC";
    case NewOrderTimeInForceEnum::Ioc:
        return "IOC";
    case NewOrderTimeInForceEnum::Fok:
        return "FOK";
    case NewOrderTimeInForceEnum::Gtx:
        return "GTX";
    case NewOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

NewOrderTimeInForceEnum tag_invoke(boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "GTC") {
        return NewOrderTimeInForceEnum::Gtc;
    }
    if (s == "IOC") {
        return NewOrderTimeInForceEnum::Ioc;
    }
    if (s == "FOK") {
        return NewOrderTimeInForceEnum::Fok;
    }
    if (s == "GTX") {
        return NewOrderTimeInForceEnum::Gtx;
    }
    return NewOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderTimeInForceEnum value) {
    if (value == NewOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("NewOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderNewOrderRespTypeEnum value) noexcept {
    switch (value) {
    case NewOrderNewOrderRespTypeEnum::Ack:
        return "ACK";
    case NewOrderNewOrderRespTypeEnum::Result:
        return "RESULT";
    case NewOrderNewOrderRespTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderNewOrderRespTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ACK") {
        return NewOrderNewOrderRespTypeEnum::Ack;
    }
    if (s == "RESULT") {
        return NewOrderNewOrderRespTypeEnum::Result;
    }
    return NewOrderNewOrderRespTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderNewOrderRespTypeEnum value) {
    if (value == NewOrderNewOrderRespTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderNewOrderRespTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewOrderSelfTradePreventionModeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "NONE") {
        return NewOrderSelfTradePreventionModeEnum::None_;
    }
    if (s == "EXPIRE_TAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireTaker;
    }
    if (s == "EXPIRE_MAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireMaker;
    }
    if (s == "EXPIRE_BOTH") {
        return NewOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    return NewOrderSelfTradePreventionModeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderSelfTradePreventionModeEnum value) {
    if (value == NewOrderSelfTradePreventionModeEnum::Unknown) {
        throw std::invalid_argument("NewOrderSelfTradePreventionModeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::account_trade_list_request(const AccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/userTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
TradeApi::account_trade_list(const AccountTradeListParams& params) const {
    return common::send<std::vector<AccountTradeListResponseInner>>(
        *client_, account_trade_list_request(params));
}

common::RestRequest TradeApi::cancel_all_option_orders_by_underlying_request(
    const CancelAllOptionOrdersByUnderlyingParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/allOpenOrdersByUnderlying";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllOptionOrdersByUnderlyingResponse>
TradeApi::cancel_all_option_orders_by_underlying(
    const CancelAllOptionOrdersByUnderlyingParams& params) const {
    return common::send<CancelAllOptionOrdersByUnderlyingResponse>(
        *client_, cancel_all_option_orders_by_underlying_request(params));
}

common::RestRequest TradeApi::cancel_all_option_orders_on_specific_symbol_request(
    const CancelAllOptionOrdersOnSpecificSymbolParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllOptionOrdersOnSpecificSymbolResponse>
TradeApi::cancel_all_option_orders_on_specific_symbol(
    const CancelAllOptionOrdersOnSpecificSymbolParams& params) const {
    return common::send<CancelAllOptionOrdersOnSpecificSymbolResponse>(
        *client_, cancel_all_option_orders_on_specific_symbol_request(params));
}

common::RestRequest TradeApi::cancel_multiple_option_orders_request(
    const CancelMultipleOptionOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderIds", params.order_ids);
    common::detail::json::set_param(req.query, "clientOrderIds", params.client_order_ids);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CancelMultipleOptionOrdersResponseInner>>
TradeApi::cancel_multiple_option_orders(const CancelMultipleOptionOrdersParams& params) const {
    return common::send<std::vector<CancelMultipleOptionOrdersResponseInner>>(
        *client_, cancel_multiple_option_orders_request(params));
}

common::RestRequest
TradeApi::place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "orders", params.orders);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>
TradeApi::place_multiple_orders(const PlaceMultipleOrdersParams& params) const {
    return common::send<std::vector<PlaceMultipleOrdersResponseInner>>(
        *client_, place_multiple_orders_request(params));
}

common::RestRequest
TradeApi::cancel_option_order_request(const CancelOptionOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelOptionOrderResponse>
TradeApi::cancel_option_order(const CancelOptionOrderParams& params) const {
    return common::send<CancelOptionOrderResponse>(*client_, cancel_option_order_request(params));
}

common::RestRequest TradeApi::new_order_request(const NewOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "postOnly", params.post_only);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "isMmp", params.is_mmp);
    common::detail::json::set_param(req.query, "selfTradePreventionMode",
                                    params.self_trade_prevention_mode);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewOrderResponse> TradeApi::new_order(const NewOrderParams& params) const {
    return common::send<NewOrderResponse>(*client_, new_order_request(params));
}

common::RestRequest
TradeApi::query_single_order_request(const QuerySingleOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySingleOrderResponse>
TradeApi::query_single_order(const QuerySingleOrderParams& params) const {
    return common::send<QuerySingleOrderResponse>(*client_, query_single_order_request(params));
}

common::RestRequest
TradeApi::option_position_information_request(const OptionPositionInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/position";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<OptionPositionInformationResponseInner>>
TradeApi::option_position_information(const OptionPositionInformationParams& params) const {
    return common::send<std::vector<OptionPositionInformationResponseInner>>(
        *client_, option_position_information_request(params));
}

common::RestRequest TradeApi::query_current_open_option_orders_request(
    const QueryCurrentOpenOptionOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>
TradeApi::query_current_open_option_orders(const QueryCurrentOpenOptionOrdersParams& params) const {
    return common::send<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>(
        *client_, query_current_open_option_orders_request(params));
}

common::RestRequest
TradeApi::query_option_order_history_request(const QueryOptionOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/historyOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryOptionOrderHistoryResponseInner>>
TradeApi::query_option_order_history(const QueryOptionOrderHistoryParams& params) const {
    return common::send<std::vector<QueryOptionOrderHistoryResponseInner>>(
        *client_, query_option_order_history_request(params));
}

common::RestRequest
TradeApi::tradfi_options_contract_request(const TradfiOptionsContractParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/stock/contract";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TradfiOptionsContractResponse>
TradeApi::tradfi_options_contract(const TradfiOptionsContractParams& params) const {
    return common::send<TradfiOptionsContractResponse>(*client_,
                                                       tradfi_options_contract_request(params));
}

common::RestRequest TradeApi::user_commission_request(const UserCommissionParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/commission";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<UserCommissionResponse>
TradeApi::user_commission(const UserCommissionParams& params) const {
    return common::send<UserCommissionResponse>(*client_, user_commission_request(params));
}

common::RestRequest
TradeApi::user_exercise_record_request(const UserExerciseRecordParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/exerciseRecord";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UserExerciseRecordResponseInner>>
TradeApi::user_exercise_record(const UserExerciseRecordParams& params) const {
    return common::send<std::vector<UserExerciseRecordResponseInner>>(
        *client_, user_exercise_record_request(params));
}

} // namespace binance::derivatives_trading_options::rest_api
