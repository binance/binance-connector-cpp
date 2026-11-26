//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/market_maker_block_trade_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(NewBlockTradeOrderLiquidityEnum value) noexcept {
    switch (value) {
    case NewBlockTradeOrderLiquidityEnum::Maker:
        return "MAKER";
    case NewBlockTradeOrderLiquidityEnum::Taker:
        return "TAKER";
    case NewBlockTradeOrderLiquidityEnum::Unknown:
        break;
    }
    return "";
}

NewBlockTradeOrderLiquidityEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLiquidityEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "MAKER") {
        return NewBlockTradeOrderLiquidityEnum::Maker;
    }
    if (s == "TAKER") {
        return NewBlockTradeOrderLiquidityEnum::Taker;
    }
    return NewBlockTradeOrderLiquidityEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                NewBlockTradeOrderLiquidityEnum value) {
    if (value == NewBlockTradeOrderLiquidityEnum::Unknown) {
        throw std::invalid_argument("NewBlockTradeOrderLiquidityEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketMakerBlockTradeApi::MarketMakerBlockTradeApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketMakerBlockTradeApi::accept_block_trade_order_request(
    const AcceptBlockTradeOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/block/order/execute";
    common::detail::json::set_param(req.query, "blockOrderMatchingKey",
                                    params.block_order_matching_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AcceptBlockTradeOrderResponse>
MarketMakerBlockTradeApi::accept_block_trade_order(
    const AcceptBlockTradeOrderParams& params) const {
    return common::send<AcceptBlockTradeOrderResponse>(*client_,
                                                       accept_block_trade_order_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::query_block_trade_details_request(
    const QueryBlockTradeDetailsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/block/order/execute";
    common::detail::json::set_param(req.query, "blockOrderMatchingKey",
                                    params.block_order_matching_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryBlockTradeDetailsResponse>
MarketMakerBlockTradeApi::query_block_trade_details(
    const QueryBlockTradeDetailsParams& params) const {
    return common::send<QueryBlockTradeDetailsResponse>(*client_,
                                                        query_block_trade_details_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::account_block_trade_list_request(
    const AccountBlockTradeListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/block/user-trades";
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<AccountBlockTradeListResponseInner>>
MarketMakerBlockTradeApi::account_block_trade_list(
    const AccountBlockTradeListParams& params) const {
    return common::send<std::vector<AccountBlockTradeListResponseInner>>(
        *client_, account_block_trade_list_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::cancel_block_trade_order_request(
    const CancelBlockTradeOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/eapi/v1/block/order/create";
    common::detail::json::set_param(req.query, "blockOrderMatchingKey",
                                    params.block_order_matching_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<boost::json::value> MarketMakerBlockTradeApi::cancel_block_trade_order(
    const CancelBlockTradeOrderParams& params) const {
    return common::send<boost::json::value>(*client_, cancel_block_trade_order_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::extend_block_trade_order_request(
    const ExtendBlockTradeOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Put;
    req.endpoint = "/eapi/v1/block/order/create";
    common::detail::json::set_param(req.query, "blockOrderMatchingKey",
                                    params.block_order_matching_key);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ExtendBlockTradeOrderResponse>
MarketMakerBlockTradeApi::extend_block_trade_order(
    const ExtendBlockTradeOrderParams& params) const {
    return common::send<ExtendBlockTradeOrderResponse>(*client_,
                                                       extend_block_trade_order_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::new_block_trade_order_request(
    const NewBlockTradeOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/block/order/create";
    common::detail::json::set_param(req.query, "liquidity", params.liquidity);
    common::detail::json::set_param(req.query, "legs", params.legs);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<NewBlockTradeOrderResponse>
MarketMakerBlockTradeApi::new_block_trade_order(const NewBlockTradeOrderParams& params) const {
    return common::send<NewBlockTradeOrderResponse>(*client_,
                                                    new_block_trade_order_request(params));
}

common::RestRequest MarketMakerBlockTradeApi::query_block_trade_order_request(
    const QueryBlockTradeOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/block/order/orders";
    common::detail::json::set_param(req.query, "blockOrderMatchingKey",
                                    params.block_order_matching_key);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryBlockTradeOrderResponseInner>>
MarketMakerBlockTradeApi::query_block_trade_order(const QueryBlockTradeOrderParams& params) const {
    return common::send<std::vector<QueryBlockTradeOrderResponseInner>>(
        *client_, query_block_trade_order_request(params));
}

} // namespace binance::derivatives_trading_options::rest_api
