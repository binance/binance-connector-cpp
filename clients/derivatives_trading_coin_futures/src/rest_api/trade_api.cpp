//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/trade_api.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(ModifyOrderSideEnum value) noexcept {
    switch (value) {
    case ModifyOrderSideEnum::Buy:
        return "BUY";
    case ModifyOrderSideEnum::Sell:
        return "SELL";
    case ModifyOrderSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyOrderSideEnum tag_invoke(boost::json::value_to_tag<ModifyOrderSideEnum> /*tag*/,
                               const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return ModifyOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return ModifyOrderSideEnum::Sell;
    }
    return ModifyOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyOrderSideEnum value) {
    if (value == ModifyOrderSideEnum::Unknown) {
        throw std::invalid_argument("ModifyOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case ModifyOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case ModifyOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case ModifyOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case ModifyOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case ModifyOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case ModifyOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case ModifyOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case ModifyOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case ModifyOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

ModifyOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<ModifyOrderPriceMatchEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return ModifyOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return ModifyOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return ModifyOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return ModifyOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return ModifyOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return ModifyOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return ModifyOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return ModifyOrderPriceMatchEnum::Queue20;
    }
    return ModifyOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyOrderPriceMatchEnum value) {
    if (value == ModifyOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("ModifyOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

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
    case NewOrderTypeEnum::Market:
        return "MARKET";
    case NewOrderTypeEnum::Stop:
        return "STOP";
    case NewOrderTypeEnum::StopMarket:
        return "STOP_MARKET";
    case NewOrderTypeEnum::TakeProfit:
        return "TAKE_PROFIT";
    case NewOrderTypeEnum::TakeProfitMarket:
        return "TAKE_PROFIT_MARKET";
    case NewOrderTypeEnum::TrailingStopMarket:
        return "TRAILING_STOP_MARKET";
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
    if (s == "MARKET") {
        return NewOrderTypeEnum::Market;
    }
    if (s == "STOP") {
        return NewOrderTypeEnum::Stop;
    }
    if (s == "STOP_MARKET") {
        return NewOrderTypeEnum::StopMarket;
    }
    if (s == "TAKE_PROFIT") {
        return NewOrderTypeEnum::TakeProfit;
    }
    if (s == "TAKE_PROFIT_MARKET") {
        return NewOrderTypeEnum::TakeProfitMarket;
    }
    if (s == "TRAILING_STOP_MARKET") {
        return NewOrderTypeEnum::TrailingStopMarket;
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

std::string_view to_string(NewOrderPositionSideEnum value) noexcept {
    switch (value) {
    case NewOrderPositionSideEnum::Both:
        return "BOTH";
    case NewOrderPositionSideEnum::Long:
        return "LONG";
    case NewOrderPositionSideEnum::Short:
        return "SHORT";
    case NewOrderPositionSideEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPositionSideEnum tag_invoke(boost::json::value_to_tag<NewOrderPositionSideEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return NewOrderPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return NewOrderPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return NewOrderPositionSideEnum::Short;
    }
    return NewOrderPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPositionSideEnum value) {
    if (value == NewOrderPositionSideEnum::Unknown) {
        throw std::invalid_argument("NewOrderPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderReduceOnlyEnum value) noexcept {
    switch (value) {
    case NewOrderReduceOnlyEnum::True_:
        return "true";
    case NewOrderReduceOnlyEnum::False_:
        return "false";
    case NewOrderReduceOnlyEnum::Unknown:
        break;
    }
    return "";
}

NewOrderReduceOnlyEnum tag_invoke(boost::json::value_to_tag<NewOrderReduceOnlyEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewOrderReduceOnlyEnum::True_;
    }
    if (s == "false") {
        return NewOrderReduceOnlyEnum::False_;
    }
    return NewOrderReduceOnlyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderReduceOnlyEnum value) {
    if (value == NewOrderReduceOnlyEnum::Unknown) {
        throw std::invalid_argument("NewOrderReduceOnlyEnum::Unknown cannot be sent");
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

std::string_view to_string(NewOrderWorkingTypeEnum value) noexcept {
    switch (value) {
    case NewOrderWorkingTypeEnum::MarkPrice:
        return "MARK_PRICE";
    case NewOrderWorkingTypeEnum::ContractPrice:
        return "CONTRACT_PRICE";
    case NewOrderWorkingTypeEnum::Unknown:
        break;
    }
    return "";
}

NewOrderWorkingTypeEnum tag_invoke(boost::json::value_to_tag<NewOrderWorkingTypeEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARK_PRICE") {
        return NewOrderWorkingTypeEnum::MarkPrice;
    }
    if (s == "CONTRACT_PRICE") {
        return NewOrderWorkingTypeEnum::ContractPrice;
    }
    return NewOrderWorkingTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderWorkingTypeEnum value) {
    if (value == NewOrderWorkingTypeEnum::Unknown) {
        throw std::invalid_argument("NewOrderWorkingTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderPriceProtectEnum value) noexcept {
    switch (value) {
    case NewOrderPriceProtectEnum::True_:
        return "true";
    case NewOrderPriceProtectEnum::False_:
        return "false";
    case NewOrderPriceProtectEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPriceProtectEnum tag_invoke(boost::json::value_to_tag<NewOrderPriceProtectEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "true") {
        return NewOrderPriceProtectEnum::True_;
    }
    if (s == "false") {
        return NewOrderPriceProtectEnum::False_;
    }
    return NewOrderPriceProtectEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPriceProtectEnum value) {
    if (value == NewOrderPriceProtectEnum::Unknown) {
        throw std::invalid_argument("NewOrderPriceProtectEnum::Unknown cannot be sent");
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

std::string_view to_string(NewOrderPriceMatchEnum value) noexcept {
    switch (value) {
    case NewOrderPriceMatchEnum::Opponent:
        return "OPPONENT";
    case NewOrderPriceMatchEnum::Opponent5:
        return "OPPONENT_5";
    case NewOrderPriceMatchEnum::Opponent10:
        return "OPPONENT_10";
    case NewOrderPriceMatchEnum::Opponent20:
        return "OPPONENT_20";
    case NewOrderPriceMatchEnum::Queue:
        return "QUEUE";
    case NewOrderPriceMatchEnum::Queue5:
        return "QUEUE_5";
    case NewOrderPriceMatchEnum::Queue10:
        return "QUEUE_10";
    case NewOrderPriceMatchEnum::Queue20:
        return "QUEUE_20";
    case NewOrderPriceMatchEnum::Unknown:
        break;
    }
    return "";
}

NewOrderPriceMatchEnum tag_invoke(boost::json::value_to_tag<NewOrderPriceMatchEnum> /*tag*/,
                                  const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPPONENT") {
        return NewOrderPriceMatchEnum::Opponent;
    }
    if (s == "OPPONENT_5") {
        return NewOrderPriceMatchEnum::Opponent5;
    }
    if (s == "OPPONENT_10") {
        return NewOrderPriceMatchEnum::Opponent10;
    }
    if (s == "OPPONENT_20") {
        return NewOrderPriceMatchEnum::Opponent20;
    }
    if (s == "QUEUE") {
        return NewOrderPriceMatchEnum::Queue;
    }
    if (s == "QUEUE_5") {
        return NewOrderPriceMatchEnum::Queue5;
    }
    if (s == "QUEUE_10") {
        return NewOrderPriceMatchEnum::Queue10;
    }
    if (s == "QUEUE_20") {
        return NewOrderPriceMatchEnum::Queue20;
    }
    return NewOrderPriceMatchEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewOrderPriceMatchEnum value) {
    if (value == NewOrderPriceMatchEnum::Unknown) {
        throw std::invalid_argument("NewOrderPriceMatchEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(NewOrderSelfTradePreventionModeEnum value) noexcept {
    switch (value) {
    case NewOrderSelfTradePreventionModeEnum::None_:
        return "NONE";
    case NewOrderSelfTradePreventionModeEnum::ExpireTaker:
        return "EXPIRE_TAKER";
    case NewOrderSelfTradePreventionModeEnum::ExpireBoth:
        return "EXPIRE_BOTH";
    case NewOrderSelfTradePreventionModeEnum::ExpireMaker:
        return "EXPIRE_MAKER";
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
    if (s == "EXPIRE_BOTH") {
        return NewOrderSelfTradePreventionModeEnum::ExpireBoth;
    }
    if (s == "EXPIRE_MAKER") {
        return NewOrderSelfTradePreventionModeEnum::ExpireMaker;
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

std::string_view to_string(ChangeMarginTypeMarginTypeEnum value) noexcept {
    switch (value) {
    case ChangeMarginTypeMarginTypeEnum::Isolated:
        return "ISOLATED";
    case ChangeMarginTypeMarginTypeEnum::Crossed:
        return "CROSSED";
    case ChangeMarginTypeMarginTypeEnum::Unknown:
        break;
    }
    return "";
}

ChangeMarginTypeMarginTypeEnum
tag_invoke(boost::json::value_to_tag<ChangeMarginTypeMarginTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ISOLATED") {
        return ChangeMarginTypeMarginTypeEnum::Isolated;
    }
    if (s == "CROSSED") {
        return ChangeMarginTypeMarginTypeEnum::Crossed;
    }
    return ChangeMarginTypeMarginTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ChangeMarginTypeMarginTypeEnum value) {
    if (value == ChangeMarginTypeMarginTypeEnum::Unknown) {
        throw std::invalid_argument("ChangeMarginTypeMarginTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ModifyIsolatedPositionMarginPositionSideEnum value) noexcept {
    switch (value) {
    case ModifyIsolatedPositionMarginPositionSideEnum::Both:
        return "BOTH";
    case ModifyIsolatedPositionMarginPositionSideEnum::Long:
        return "LONG";
    case ModifyIsolatedPositionMarginPositionSideEnum::Short:
        return "SHORT";
    case ModifyIsolatedPositionMarginPositionSideEnum::Unknown:
        break;
    }
    return "";
}

ModifyIsolatedPositionMarginPositionSideEnum
tag_invoke(boost::json::value_to_tag<ModifyIsolatedPositionMarginPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return ModifyIsolatedPositionMarginPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return ModifyIsolatedPositionMarginPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return ModifyIsolatedPositionMarginPositionSideEnum::Short;
    }
    return ModifyIsolatedPositionMarginPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ModifyIsolatedPositionMarginPositionSideEnum value) {
    if (value == ModifyIsolatedPositionMarginPositionSideEnum::Unknown) {
        throw std::invalid_argument(
            "ModifyIsolatedPositionMarginPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(UsersForceOrdersAutoCloseTypeEnum value) noexcept {
    switch (value) {
    case UsersForceOrdersAutoCloseTypeEnum::Liquidation:
        return "LIQUIDATION";
    case UsersForceOrdersAutoCloseTypeEnum::Adl:
        return "ADL";
    case UsersForceOrdersAutoCloseTypeEnum::Unknown:
        break;
    }
    return "";
}

UsersForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<UsersForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LIQUIDATION") {
        return UsersForceOrdersAutoCloseTypeEnum::Liquidation;
    }
    if (s == "ADL") {
        return UsersForceOrdersAutoCloseTypeEnum::Adl;
    }
    return UsersForceOrdersAutoCloseTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                UsersForceOrdersAutoCloseTypeEnum value) {
    if (value == UsersForceOrdersAutoCloseTypeEnum::Unknown) {
        throw std::invalid_argument("UsersForceOrdersAutoCloseTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::account_trade_list_request(const AccountTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/userTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
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

common::RestRequest TradeApi::all_orders_request(const AllOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/allOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AllOrdersResponseInner>>
TradeApi::all_orders(const AllOrdersParams& params) const {
    return common::send<std::vector<AllOrdersResponseInner>>(*client_, all_orders_request(params));
}

common::RestRequest
TradeApi::auto_cancel_all_open_orders_request(const AutoCancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/countdownCancelAll";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "countdownTime", params.countdown_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
TradeApi::auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const {
    return common::send<AutoCancelAllOpenOrdersResponse>(
        *client_, auto_cancel_all_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_all_open_orders_request(const CancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/dapi/v1/allOpenOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllOpenOrdersResponse>
TradeApi::cancel_all_open_orders(const CancelAllOpenOrdersParams& params) const {
    return common::send<CancelAllOpenOrdersResponse>(*client_,
                                                     cancel_all_open_orders_request(params));
}

common::RestRequest
TradeApi::cancel_multiple_orders_request(const CancelMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/dapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderIdList", params.order_id_list);
    common::detail::json::set_param(req.query, "origClientOrderIdList",
                                    params.orig_client_order_id_list);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>
TradeApi::cancel_multiple_orders(const CancelMultipleOrdersParams& params) const {
    return common::send<std::vector<CancelMultipleOrdersResponseInner>>(
        *client_, cancel_multiple_orders_request(params));
}

common::RestRequest
TradeApi::modify_multiple_orders_request(const ModifyMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/dapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "batchOrders", params.batch_orders);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>
TradeApi::modify_multiple_orders(const ModifyMultipleOrdersParams& params) const {
    return common::send<std::vector<ModifyMultipleOrdersResponseInner>>(
        *client_, modify_multiple_orders_request(params));
}

common::RestRequest
TradeApi::place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/batchOrders";
    common::detail::json::set_param(req.query, "batchOrders", params.batch_orders);
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

common::RestRequest TradeApi::cancel_order_request(const CancelOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/dapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelOrderResponse>
TradeApi::cancel_order(const CancelOrderParams& params) const {
    return common::send<CancelOrderResponse>(*client_, cancel_order_request(params));
}

common::RestRequest TradeApi::modify_order_request(const ModifyOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/dapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
    common::detail::json::set_param(req.query, "modifyId", params.modify_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyOrderResponse>
TradeApi::modify_order(const ModifyOrderParams& params) const {
    return common::send<ModifyOrderResponse>(*client_, modify_order_request(params));
}

common::RestRequest TradeApi::new_order_request(const NewOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "newClientOrderId", params.new_client_order_id);
    common::detail::json::set_param(req.query, "stopPrice", params.stop_price);
    common::detail::json::set_param(req.query, "closePosition", params.close_position);
    common::detail::json::set_param(req.query, "activationPrice", params.activation_price);
    common::detail::json::set_param(req.query, "callbackRate", params.callback_rate);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "workingType", params.working_type);
    common::detail::json::set_param(req.query, "priceProtect", params.price_protect);
    common::detail::json::set_param(req.query, "newOrderRespType", params.new_order_resp_type);
    common::detail::json::set_param(req.query, "priceMatch", params.price_match);
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

common::RestRequest TradeApi::query_order_request(const QueryOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/order";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryOrderResponse>
TradeApi::query_order(const QueryOrderParams& params) const {
    return common::send<QueryOrderResponse>(*client_, query_order_request(params));
}

common::RestRequest
TradeApi::change_initial_leverage_request(const ChangeInitialLeverageParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/leverage";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "leverage", params.leverage);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeInitialLeverageResponse>
TradeApi::change_initial_leverage(const ChangeInitialLeverageParams& params) const {
    return common::send<ChangeInitialLeverageResponse>(*client_,
                                                       change_initial_leverage_request(params));
}

common::RestRequest
TradeApi::change_margin_type_request(const ChangeMarginTypeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/marginType";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "marginType", params.margin_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangeMarginTypeResponse>
TradeApi::change_margin_type(const ChangeMarginTypeParams& params) const {
    return common::send<ChangeMarginTypeResponse>(*client_, change_margin_type_request(params));
}

common::RestRequest
TradeApi::change_position_mode_request(const ChangePositionModeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/positionSide/dual";
    common::detail::json::set_param(req.query, "dualSidePosition", params.dual_side_position);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ChangePositionModeResponse>
TradeApi::change_position_mode(const ChangePositionModeParams& params) const {
    return common::send<ChangePositionModeResponse>(*client_, change_position_mode_request(params));
}

common::RestRequest
TradeApi::current_all_open_orders_request(const CurrentAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/openOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>
TradeApi::current_all_open_orders(const CurrentAllOpenOrdersParams& params) const {
    return common::send<std::vector<CurrentAllOpenOrdersResponseInner>>(
        *client_, current_all_open_orders_request(params));
}

common::RestRequest
TradeApi::get_order_modify_history_request(const GetOrderModifyHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/orderAmendment";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>
TradeApi::get_order_modify_history(const GetOrderModifyHistoryParams& params) const {
    return common::send<std::vector<GetOrderModifyHistoryResponseInner>>(
        *client_, get_order_modify_history_request(params));
}

common::RestRequest TradeApi::get_position_margin_change_history_request(
    const GetPositionMarginChangeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/positionMargin/history";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>
TradeApi::get_position_margin_change_history(
    const GetPositionMarginChangeHistoryParams& params) const {
    return common::send<std::vector<GetPositionMarginChangeHistoryResponseInner>>(
        *client_, get_position_margin_change_history_request(params));
}

common::RestRequest TradeApi::modify_isolated_position_margin_request(
    const ModifyIsolatedPositionMarginParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/dapi/v1/positionMargin";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ModifyIsolatedPositionMarginResponse>
TradeApi::modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params) const {
    return common::send<ModifyIsolatedPositionMarginResponse>(
        *client_, modify_isolated_position_margin_request(params));
}

common::RestRequest TradeApi::position_adl_quantile_estimation_request(
    const PositionAdlQuantileEstimationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/adlQuantile";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>
TradeApi::position_adl_quantile_estimation(
    const PositionAdlQuantileEstimationParams& params) const {
    return common::send<std::vector<PositionAdlQuantileEstimationResponseInner>>(
        *client_, position_adl_quantile_estimation_request(params));
}

common::RestRequest
TradeApi::position_information_request(const PositionInformationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/positionRisk";
    common::detail::json::set_param(req.query, "marginAsset", params.margin_asset);
    common::detail::json::set_param(req.query, "pair", params.pair);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<PositionInformationResponseInner>>
TradeApi::position_information(const PositionInformationParams& params) const {
    return common::send<std::vector<PositionInformationResponseInner>>(
        *client_, position_information_request(params));
}

common::RestRequest
TradeApi::query_current_open_order_request(const QueryCurrentOpenOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/openOrder";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "origClientOrderId", params.orig_client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentOpenOrderResponse>
TradeApi::query_current_open_order(const QueryCurrentOpenOrderParams& params) const {
    return common::send<QueryCurrentOpenOrderResponse>(*client_,
                                                       query_current_open_order_request(params));
}

common::RestRequest
TradeApi::users_force_orders_request(const UsersForceOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/dapi/v1/forceOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "autoCloseType", params.auto_close_type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>
TradeApi::users_force_orders(const UsersForceOrdersParams& params) const {
    return common::send<std::vector<UsersForceOrdersResponseInner>>(
        *client_, users_force_orders_request(params));
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
