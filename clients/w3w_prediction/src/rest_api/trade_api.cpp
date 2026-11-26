//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/trade_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetQuoteSideEnum value) noexcept {
    switch (value) {
    case GetQuoteSideEnum::Buy:
        return "BUY";
    case GetQuoteSideEnum::Sell:
        return "SELL";
    case GetQuoteSideEnum::Unknown:
        break;
    }
    return "";
}

GetQuoteSideEnum tag_invoke(boost::json::value_to_tag<GetQuoteSideEnum> /*tag*/,
                            const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return GetQuoteSideEnum::Buy;
    }
    if (s == "SELL") {
        return GetQuoteSideEnum::Sell;
    }
    return GetQuoteSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetQuoteSideEnum value) {
    if (value == GetQuoteSideEnum::Unknown) {
        throw std::invalid_argument("GetQuoteSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetQuoteOrderTypeEnum value) noexcept {
    switch (value) {
    case GetQuoteOrderTypeEnum::Market:
        return "MARKET";
    case GetQuoteOrderTypeEnum::Limit:
        return "LIMIT";
    case GetQuoteOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

GetQuoteOrderTypeEnum tag_invoke(boost::json::value_to_tag<GetQuoteOrderTypeEnum> /*tag*/,
                                 const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return GetQuoteOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return GetQuoteOrderTypeEnum::Limit;
    }
    return GetQuoteOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetQuoteOrderTypeEnum value) {
    if (value == GetQuoteOrderTypeEnum::Unknown) {
        throw std::invalid_argument("GetQuoteOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(GetQuoteFundingSourceEnum value) noexcept {
    switch (value) {
    case GetQuoteFundingSourceEnum::Mpc:
        return "MPC";
    case GetQuoteFundingSourceEnum::Cex:
        return "CEX";
    case GetQuoteFundingSourceEnum::Unknown:
        break;
    }
    return "";
}

GetQuoteFundingSourceEnum tag_invoke(boost::json::value_to_tag<GetQuoteFundingSourceEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MPC") {
        return GetQuoteFundingSourceEnum::Mpc;
    }
    if (s == "CEX") {
        return GetQuoteFundingSourceEnum::Cex;
    }
    return GetQuoteFundingSourceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetQuoteFundingSourceEnum value) {
    if (value == GetQuoteFundingSourceEnum::Unknown) {
        throw std::invalid_argument("GetQuoteFundingSourceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOrderAccountTypeEnum value) noexcept {
    switch (value) {
    case PlaceOrderAccountTypeEnum::Spot:
        return "SPOT";
    case PlaceOrderAccountTypeEnum::Funding:
        return "FUNDING";
    case PlaceOrderAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceOrderAccountTypeEnum tag_invoke(boost::json::value_to_tag<PlaceOrderAccountTypeEnum> /*tag*/,
                                     const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return PlaceOrderAccountTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return PlaceOrderAccountTypeEnum::Funding;
    }
    return PlaceOrderAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOrderAccountTypeEnum value) {
    if (value == PlaceOrderAccountTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceOrderAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOrderOrderTypeEnum value) noexcept {
    switch (value) {
    case PlaceOrderOrderTypeEnum::Market:
        return "MARKET";
    case PlaceOrderOrderTypeEnum::Limit:
        return "LIMIT";
    case PlaceOrderOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceOrderOrderTypeEnum tag_invoke(boost::json::value_to_tag<PlaceOrderOrderTypeEnum> /*tag*/,
                                   const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return PlaceOrderOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return PlaceOrderOrderTypeEnum::Limit;
    }
    return PlaceOrderOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOrderOrderTypeEnum value) {
    if (value == PlaceOrderOrderTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceOrderOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOrderFundingSourceEnum value) noexcept {
    switch (value) {
    case PlaceOrderFundingSourceEnum::Mpc:
        return "MPC";
    case PlaceOrderFundingSourceEnum::Cex:
        return "CEX";
    case PlaceOrderFundingSourceEnum::Unknown:
        break;
    }
    return "";
}

PlaceOrderFundingSourceEnum
tag_invoke(boost::json::value_to_tag<PlaceOrderFundingSourceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MPC") {
        return PlaceOrderFundingSourceEnum::Mpc;
    }
    if (s == "CEX") {
        return PlaceOrderFundingSourceEnum::Cex;
    }
    return PlaceOrderFundingSourceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOrderFundingSourceEnum value) {
    if (value == PlaceOrderFundingSourceEnum::Unknown) {
        throw std::invalid_argument("PlaceOrderFundingSourceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryActiveOrdersTradeSideEnum value) noexcept {
    switch (value) {
    case QueryActiveOrdersTradeSideEnum::Buy:
        return "BUY";
    case QueryActiveOrdersTradeSideEnum::Sell:
        return "SELL";
    case QueryActiveOrdersTradeSideEnum::Unknown:
        break;
    }
    return "";
}

QueryActiveOrdersTradeSideEnum
tag_invoke(boost::json::value_to_tag<QueryActiveOrdersTradeSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return QueryActiveOrdersTradeSideEnum::Buy;
    }
    if (s == "SELL") {
        return QueryActiveOrdersTradeSideEnum::Sell;
    }
    return QueryActiveOrdersTradeSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryActiveOrdersTradeSideEnum value) {
    if (value == QueryActiveOrdersTradeSideEnum::Unknown) {
        throw std::invalid_argument("QueryActiveOrdersTradeSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryOrderHistoryOrderTypeEnum value) noexcept {
    switch (value) {
    case QueryOrderHistoryOrderTypeEnum::Market:
        return "MARKET";
    case QueryOrderHistoryOrderTypeEnum::Limit:
        return "LIMIT";
    case QueryOrderHistoryOrderTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryOrderHistoryOrderTypeEnum
tag_invoke(boost::json::value_to_tag<QueryOrderHistoryOrderTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MARKET") {
        return QueryOrderHistoryOrderTypeEnum::Market;
    }
    if (s == "LIMIT") {
        return QueryOrderHistoryOrderTypeEnum::Limit;
    }
    return QueryOrderHistoryOrderTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryOrderHistoryOrderTypeEnum value) {
    if (value == QueryOrderHistoryOrderTypeEnum::Unknown) {
        throw std::invalid_argument("QueryOrderHistoryOrderTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::batch_cancel_orders_request(const BatchCancelOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/trade/batch-cancel";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "walletId", params.wallet_id);
    common::detail::json::set_param(req.query, "cancelInfoList", params.cancel_info_list);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<BatchCancelOrdersResponse>
TradeApi::batch_cancel_orders(const BatchCancelOrdersParams& params) const {
    return common::send<BatchCancelOrdersResponse>(*client_, batch_cancel_orders_request(params));
}

common::RestRequest TradeApi::get_quote_request(const GetQuoteParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/trade/get-quote";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "amountIn", params.amount_in);
    common::detail::json::set_param(req.query, "orderType", params.order_type);
    common::detail::json::set_param(req.query, "slippageBps", params.slippage_bps);
    common::detail::json::set_param(req.query, "priceLimit", params.price_limit);
    common::detail::json::set_param(req.query, "chainId", params.chain_id);
    common::detail::json::set_param(req.query, "feeRateBps", params.fee_rate_bps);
    common::detail::json::set_param(req.query, "fundingSource", params.funding_source);
    common::detail::json::set_param(req.query, "fundTransferAmount", params.fund_transfer_amount);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetQuoteResponse> TradeApi::get_quote(const GetQuoteParams& params) const {
    return common::send<GetQuoteResponse>(*client_, get_quote_request(params));
}

common::RestRequest TradeApi::place_order_request(const PlaceOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/trade/place-order-bundle";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "walletId", params.wallet_id);
    common::detail::json::set_param(req.query, "quoteId", params.quote_id);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "orderType", params.order_type);
    common::detail::json::set_param(req.query, "slippageBps", params.slippage_bps);
    common::detail::json::set_param(req.query, "priceLimit", params.price_limit);
    common::detail::json::set_param(req.query, "fundingSource", params.funding_source);
    common::detail::json::set_param(req.query, "fundTransferAmount", params.fund_transfer_amount);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PlaceOrderResponse>
TradeApi::place_order(const PlaceOrderParams& params) const {
    return common::send<PlaceOrderResponse>(*client_, place_order_request(params));
}

common::RestRequest
TradeApi::query_active_orders_request(const QueryActiveOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/order/list";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tradeSide", params.trade_side);
    common::detail::json::set_param(req.query, "l1Category", params.l1_category);
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryActiveOrdersResponse>
TradeApi::query_active_orders(const QueryActiveOrdersParams& params) const {
    return common::send<QueryActiveOrdersResponse>(*client_, query_active_orders_request(params));
}

common::RestRequest
TradeApi::query_order_history_request(const QueryOrderHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/order/history";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "l1Category", params.l1_category);
    common::detail::json::set_param(req.query, "orderType", params.order_type);
    common::detail::json::set_param(req.query, "status", params.status);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryOrderHistoryResponse>
TradeApi::query_order_history(const QueryOrderHistoryParams& params) const {
    return common::send<QueryOrderHistoryResponse>(*client_, query_order_history_request(params));
}

} // namespace binance::w3w_prediction::rest_api
