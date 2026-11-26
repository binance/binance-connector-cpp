//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/trade_api.hpp>

namespace binance::convert::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(PlaceLimitOrderSideEnum value) noexcept {
    switch (value) {
    case PlaceLimitOrderSideEnum::Buy:
        return "BUY";
    case PlaceLimitOrderSideEnum::Sell:
        return "SELL";
    case PlaceLimitOrderSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceLimitOrderSideEnum tag_invoke(boost::json::value_to_tag<PlaceLimitOrderSideEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return PlaceLimitOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return PlaceLimitOrderSideEnum::Sell;
    }
    return PlaceLimitOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceLimitOrderSideEnum value) {
    if (value == PlaceLimitOrderSideEnum::Unknown) {
        throw std::invalid_argument("PlaceLimitOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceLimitOrderExpiredTypeEnum value) noexcept {
    switch (value) {
    case PlaceLimitOrderExpiredTypeEnum::ExpiredType1D:
        return "1_D";
    case PlaceLimitOrderExpiredTypeEnum::ExpiredType3D:
        return "3_D";
    case PlaceLimitOrderExpiredTypeEnum::ExpiredType7D:
        return "7_D";
    case PlaceLimitOrderExpiredTypeEnum::ExpiredType30D:
        return "30_D";
    case PlaceLimitOrderExpiredTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceLimitOrderExpiredTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceLimitOrderExpiredTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1_D") {
        return PlaceLimitOrderExpiredTypeEnum::ExpiredType1D;
    }
    if (s == "3_D") {
        return PlaceLimitOrderExpiredTypeEnum::ExpiredType3D;
    }
    if (s == "7_D") {
        return PlaceLimitOrderExpiredTypeEnum::ExpiredType7D;
    }
    if (s == "30_D") {
        return PlaceLimitOrderExpiredTypeEnum::ExpiredType30D;
    }
    return PlaceLimitOrderExpiredTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceLimitOrderExpiredTypeEnum value) {
    if (value == PlaceLimitOrderExpiredTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceLimitOrderExpiredTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceLimitOrderWalletTypeEnum value) noexcept {
    switch (value) {
    case PlaceLimitOrderWalletTypeEnum::Spot:
        return "SPOT";
    case PlaceLimitOrderWalletTypeEnum::Funding:
        return "FUNDING";
    case PlaceLimitOrderWalletTypeEnum::Earn:
        return "EARN";
    case PlaceLimitOrderWalletTypeEnum::SpotFunding:
        return "SPOT_FUNDING";
    case PlaceLimitOrderWalletTypeEnum::FundingEarn:
        return "FUNDING_EARN";
    case PlaceLimitOrderWalletTypeEnum::SpotFundingEarn:
        return "SPOT_FUNDING_EARN";
    case PlaceLimitOrderWalletTypeEnum::SpotEarn:
        return "SPOT_EARN";
    case PlaceLimitOrderWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceLimitOrderWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceLimitOrderWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return PlaceLimitOrderWalletTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return PlaceLimitOrderWalletTypeEnum::Funding;
    }
    if (s == "EARN") {
        return PlaceLimitOrderWalletTypeEnum::Earn;
    }
    if (s == "SPOT_FUNDING") {
        return PlaceLimitOrderWalletTypeEnum::SpotFunding;
    }
    if (s == "FUNDING_EARN") {
        return PlaceLimitOrderWalletTypeEnum::FundingEarn;
    }
    if (s == "SPOT_FUNDING_EARN") {
        return PlaceLimitOrderWalletTypeEnum::SpotFundingEarn;
    }
    if (s == "SPOT_EARN") {
        return PlaceLimitOrderWalletTypeEnum::SpotEarn;
    }
    return PlaceLimitOrderWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceLimitOrderWalletTypeEnum value) {
    if (value == PlaceLimitOrderWalletTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceLimitOrderWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SendQuoteRequestWalletTypeEnum value) noexcept {
    switch (value) {
    case SendQuoteRequestWalletTypeEnum::Spot:
        return "SPOT";
    case SendQuoteRequestWalletTypeEnum::Funding:
        return "FUNDING";
    case SendQuoteRequestWalletTypeEnum::Earn:
        return "EARN";
    case SendQuoteRequestWalletTypeEnum::SpotFunding:
        return "SPOT_FUNDING";
    case SendQuoteRequestWalletTypeEnum::FundingEarn:
        return "FUNDING_EARN";
    case SendQuoteRequestWalletTypeEnum::SpotFundingEarn:
        return "SPOT_FUNDING_EARN";
    case SendQuoteRequestWalletTypeEnum::SpotEarn:
        return "SPOT_EARN";
    case SendQuoteRequestWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

SendQuoteRequestWalletTypeEnum
tag_invoke(boost::json::value_to_tag<SendQuoteRequestWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return SendQuoteRequestWalletTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return SendQuoteRequestWalletTypeEnum::Funding;
    }
    if (s == "EARN") {
        return SendQuoteRequestWalletTypeEnum::Earn;
    }
    if (s == "SPOT_FUNDING") {
        return SendQuoteRequestWalletTypeEnum::SpotFunding;
    }
    if (s == "FUNDING_EARN") {
        return SendQuoteRequestWalletTypeEnum::FundingEarn;
    }
    if (s == "SPOT_FUNDING_EARN") {
        return SendQuoteRequestWalletTypeEnum::SpotFundingEarn;
    }
    if (s == "SPOT_EARN") {
        return SendQuoteRequestWalletTypeEnum::SpotEarn;
    }
    return SendQuoteRequestWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SendQuoteRequestWalletTypeEnum value) {
    if (value == SendQuoteRequestWalletTypeEnum::Unknown) {
        throw std::invalid_argument("SendQuoteRequestWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(SendQuoteRequestValidTimeEnum value) noexcept {
    switch (value) {
    case SendQuoteRequestValidTimeEnum::ValidTime10s:
        return "10s";
    case SendQuoteRequestValidTimeEnum::ValidTime30s:
        return "30s";
    case SendQuoteRequestValidTimeEnum::ValidTime1m:
        return "1m";
    case SendQuoteRequestValidTimeEnum::Unknown:
        break;
    }
    return "";
}

SendQuoteRequestValidTimeEnum
tag_invoke(boost::json::value_to_tag<SendQuoteRequestValidTimeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "10s") {
        return SendQuoteRequestValidTimeEnum::ValidTime10s;
    }
    if (s == "30s") {
        return SendQuoteRequestValidTimeEnum::ValidTime30s;
    }
    if (s == "1m") {
        return SendQuoteRequestValidTimeEnum::ValidTime1m;
    }
    return SendQuoteRequestValidTimeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                SendQuoteRequestValidTimeEnum value) {
    if (value == SendQuoteRequestValidTimeEnum::Unknown) {
        throw std::invalid_argument("SendQuoteRequestValidTimeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest TradeApi::accept_quote_request(const AcceptQuoteParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/convert/acceptQuote";
    common::detail::json::set_param(req.query, "quoteId", params.quote_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AcceptQuoteResponse>
TradeApi::accept_quote(const AcceptQuoteParams& params) const {
    return common::send<AcceptQuoteResponse>(*client_, accept_quote_request(params));
}

common::RestRequest
TradeApi::cancel_limit_order_request(const CancelLimitOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/convert/limit/cancelOrder";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelLimitOrderResponse>
TradeApi::cancel_limit_order(const CancelLimitOrderParams& params) const {
    return common::send<CancelLimitOrderResponse>(*client_, cancel_limit_order_request(params));
}

common::RestRequest
TradeApi::get_convert_trade_history_request(const GetConvertTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/convert/tradeFlow";
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetConvertTradeHistoryResponse>
TradeApi::get_convert_trade_history(const GetConvertTradeHistoryParams& params) const {
    return common::send<GetConvertTradeHistoryResponse>(*client_,
                                                        get_convert_trade_history_request(params));
}

common::RestRequest TradeApi::order_status_request(const OrderStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/convert/orderStatus";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "quoteId", params.quote_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderStatusResponse>
TradeApi::order_status(const OrderStatusParams& params) const {
    return common::send<OrderStatusResponse>(*client_, order_status_request(params));
}

common::RestRequest TradeApi::place_limit_order_request(const PlaceLimitOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/convert/limit/placeOrder";
    common::detail::json::set_param(req.query, "baseAsset", params.base_asset);
    common::detail::json::set_param(req.query, "quoteAsset", params.quote_asset);
    common::detail::json::set_param(req.query, "limitPrice", params.limit_price);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "expiredType", params.expired_type);
    common::detail::json::set_param(req.query, "baseAmount", params.base_amount);
    common::detail::json::set_param(req.query, "quoteAmount", params.quote_amount);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PlaceLimitOrderResponse>
TradeApi::place_limit_order(const PlaceLimitOrderParams& params) const {
    return common::send<PlaceLimitOrderResponse>(*client_, place_limit_order_request(params));
}

common::RestRequest
TradeApi::query_limit_open_orders_request(const QueryLimitOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/convert/limit/queryOpenOrders";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryLimitOpenOrdersResponse>
TradeApi::query_limit_open_orders(const QueryLimitOpenOrdersParams& params) const {
    return common::send<QueryLimitOpenOrdersResponse>(*client_,
                                                      query_limit_open_orders_request(params));
}

common::RestRequest
TradeApi::send_quote_request_request(const SendQuoteRequestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/convert/getQuote";
    common::detail::json::set_param(req.query, "fromAsset", params.from_asset);
    common::detail::json::set_param(req.query, "toAsset", params.to_asset);
    common::detail::json::set_param(req.query, "fromAmount", params.from_amount);
    common::detail::json::set_param(req.query, "toAmount", params.to_amount);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "validTime", params.valid_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SendQuoteRequestResponse>
TradeApi::send_quote_request(const SendQuoteRequestParams& params) const {
    return common::send<SendQuoteRequestResponse>(*client_, send_quote_request_request(params));
}

} // namespace binance::convert::rest_api
