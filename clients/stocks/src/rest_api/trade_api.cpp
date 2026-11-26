//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/trade_api.hpp>

namespace binance::stocks::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(EquityOrderHistoryOrderTypeEnum value) noexcept {
    switch (value) {
    case EquityOrderHistoryOrderTypeEnum::Market:
        return "MARKET";
    case EquityOrderHistoryOrderTypeEnum::Limit:
        return "LIMIT";
    case EquityOrderHistoryOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

EquityOrderHistoryOrderTypeEnum
tag_invoke(boost::json::value_to_tag<EquityOrderHistoryOrderTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return EquityOrderHistoryOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return EquityOrderHistoryOrderTypeEnum::Limit;
    }
    return EquityOrderHistoryOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                EquityOrderHistoryOrderTypeEnum value) {
    if (value == EquityOrderHistoryOrderTypeEnum::Unknown) {
        throw std::invalid_argument("EquityOrderHistoryOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(EquityOrderHistorySideEnum value) noexcept {
    switch (value) {
    case EquityOrderHistorySideEnum::Buy:
        return "BUY";
    case EquityOrderHistorySideEnum::Sell:
        return "SELL";
    case EquityOrderHistorySideEnum::Unknown:
        break;
    }
    return "";
}

EquityOrderHistorySideEnum tag_invoke(boost::json::value_to_tag<EquityOrderHistorySideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return EquityOrderHistorySideEnum::Buy;
    }
    if (s == "SELL") {
        return EquityOrderHistorySideEnum::Sell;
    }
    return EquityOrderHistorySideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                EquityOrderHistorySideEnum value) {
    if (value == EquityOrderHistorySideEnum::Unknown) {
        throw std::invalid_argument("EquityOrderHistorySideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(EquityTradeHistorySideEnum value) noexcept {
    switch (value) {
    case EquityTradeHistorySideEnum::Buy:
        return "BUY";
    case EquityTradeHistorySideEnum::Sell:
        return "SELL";
    case EquityTradeHistorySideEnum::Unknown:
        break;
    }
    return "";
}

EquityTradeHistorySideEnum tag_invoke(boost::json::value_to_tag<EquityTradeHistorySideEnum> /*tag*/,
                                      const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return EquityTradeHistorySideEnum::Buy;
    }
    if (s == "SELL") {
        return EquityTradeHistorySideEnum::Sell;
    }
    return EquityTradeHistorySideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                EquityTradeHistorySideEnum value) {
    if (value == EquityTradeHistorySideEnum::Unknown) {
        throw std::invalid_argument("EquityTradeHistorySideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderSideEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderSideEnum::Buy:
        return "BUY";
    case PlaceEquityOrderSideEnum::Sell:
        return "SELL";
    case PlaceEquityOrderSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderSideEnum tag_invoke(boost::json::value_to_tag<PlaceEquityOrderSideEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return PlaceEquityOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return PlaceEquityOrderSideEnum::Sell;
    }
    return PlaceEquityOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderSideEnum value) {
    if (value == PlaceEquityOrderSideEnum::Unknown) {
        throw std::invalid_argument("PlaceEquityOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderOrderTypeEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderOrderTypeEnum::Market:
        return "MARKET";
    case PlaceEquityOrderOrderTypeEnum::Limit:
        return "LIMIT";
    case PlaceEquityOrderOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderOrderTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderOrderTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return PlaceEquityOrderOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return PlaceEquityOrderOrderTypeEnum::Limit;
    }
    return PlaceEquityOrderOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderOrderTypeEnum value) {
    if (value == PlaceEquityOrderOrderTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceEquityOrderOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderTimeInForceEnum::Day:
        return "DAY";
    case PlaceEquityOrderTimeInForceEnum::Gtc:
        return "GTC";
    case PlaceEquityOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "DAY") {
        return PlaceEquityOrderTimeInForceEnum::Day;
    }
    if (s == "GTC") {
        return PlaceEquityOrderTimeInForceEnum::Gtc;
    }
    return PlaceEquityOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderTimeInForceEnum value) {
    if (value == PlaceEquityOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("PlaceEquityOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderTradingSessionEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderTradingSessionEnum::Rth:
        return "RTH";
    case PlaceEquityOrderTradingSessionEnum::Extended:
        return "EXTENDED";
    case PlaceEquityOrderTradingSessionEnum::TradingSession24H:
        return "24H";
    case PlaceEquityOrderTradingSessionEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderTradingSessionEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTradingSessionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "RTH") {
        return PlaceEquityOrderTradingSessionEnum::Rth;
    }
    if (s == "EXTENDED") {
        return PlaceEquityOrderTradingSessionEnum::Extended;
    }
    if (s == "24H") {
        return PlaceEquityOrderTradingSessionEnum::TradingSession24H;
    }
    return PlaceEquityOrderTradingSessionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderTradingSessionEnum value) {
    if (value == PlaceEquityOrderTradingSessionEnum::Unknown) {
        throw std::invalid_argument("PlaceEquityOrderTradingSessionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderWalletTypeEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderWalletTypeEnum::Card:
        return "CARD";
    case PlaceEquityOrderWalletTypeEnum::Main:
        return "MAIN";
    case PlaceEquityOrderWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CARD") {
        return PlaceEquityOrderWalletTypeEnum::Card;
    }
    if (s == "MAIN") {
        return PlaceEquityOrderWalletTypeEnum::Main;
    }
    return PlaceEquityOrderWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderWalletTypeEnum value) {
    if (value == PlaceEquityOrderWalletTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceEquityOrderWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum value) noexcept {
    switch (value) {
    case PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Main:
        return "MAIN";
    case PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Card:
        return "CARD";
    case PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MAIN") {
        return PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Main;
    }
    if (s == "CARD") {
        return PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Card;
    }
    return PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum value) {
    if (value == PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Unknown) {
        throw std::invalid_argument(
            "PlaceEquityOrderTokenizedAssetSettleWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::cancel_all_equity_orders_request(const CancelAllEquityOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/order/cancel-all";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllEquityOrdersResponse>
TradeApi::cancel_all_equity_orders(const CancelAllEquityOrdersParams& params) const {
    return common::send<CancelAllEquityOrdersResponse>(*client_,
                                                       cancel_all_equity_orders_request(params));
}

common::RestRequest
TradeApi::cancel_equity_order_request(const CancelEquityOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/order/cancel";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelEquityOrderResponse>
TradeApi::cancel_equity_order(const CancelEquityOrderParams& params) const {
    return common::send<CancelEquityOrderResponse>(*client_, cancel_equity_order_request(params));
}

common::RestRequest
TradeApi::current_open_orders_request(const CurrentOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/order/open-orders";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<CurrentOpenOrdersResponseInner>>
TradeApi::current_open_orders(const CurrentOpenOrdersParams& params) const {
    return common::send<std::vector<CurrentOpenOrdersResponseInner>>(
        *client_, current_open_orders_request(params));
}

common::RestRequest
TradeApi::equity_order_detail_request(const EquityOrderDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/order/detail";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EquityOrderDetailResponse>
TradeApi::equity_order_detail(const EquityOrderDetailParams& params) const {
    return common::send<EquityOrderDetailResponse>(*client_, equity_order_detail_request(params));
}

common::RestRequest
TradeApi::equity_order_history_request(const EquityOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/order/history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "orderType", params.order_type);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderStatus", params.order_status);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EquityOrderHistoryResponse>
TradeApi::equity_order_history(const EquityOrderHistoryParams& params) const {
    return common::send<EquityOrderHistoryResponse>(*client_, equity_order_history_request(params));
}

common::RestRequest
TradeApi::equity_trade_history_request(const EquityTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/equity/trade/history";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<EquityTradeHistoryResponse>
TradeApi::equity_trade_history(const EquityTradeHistoryParams& params) const {
    return common::send<EquityTradeHistoryResponse>(*client_, equity_trade_history_request(params));
}

common::RestRequest
TradeApi::place_equity_order_request(const PlaceEquityOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/order/place";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "orderType", params.order_type);
    common::detail::json::set_param(req.query, "quoteAsset", params.quote_asset);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "notional", params.notional);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "tradingSession", params.trading_session);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "tokenize", params.tokenize);
    common::detail::json::set_param(req.query, "tokenizedAssetSettleWalletType",
                                    params.tokenized_asset_settle_wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PlaceEquityOrderResponse>
TradeApi::place_equity_order(const PlaceEquityOrderParams& params) const {
    return common::send<PlaceEquityOrderResponse>(*client_, place_equity_order_request(params));
}

} // namespace binance::stocks::rest_api
