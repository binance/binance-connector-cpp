//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/convert_api.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

ConvertApi::ConvertApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
ConvertApi::accept_the_offered_quote_request(const AcceptTheOfferedQuoteParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/convert/acceptQuote";
    common::detail::json::set_param(req.query, "quoteId", params.quote_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AcceptTheOfferedQuoteResponse>
ConvertApi::accept_the_offered_quote(const AcceptTheOfferedQuoteParams& params) const {
    return common::send<AcceptTheOfferedQuoteResponse>(*client_,
                                                       accept_the_offered_quote_request(params));
}

common::RestRequest
ConvertApi::list_all_convert_pairs_request(const ListAllConvertPairsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/convert/exchangeInfo";
    common::detail::json::set_param(req.query, "fromAsset", params.from_asset);
    common::detail::json::set_param(req.query, "toAsset", params.to_asset);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>
ConvertApi::list_all_convert_pairs(const ListAllConvertPairsParams& params) const {
    return common::send<std::vector<ListAllConvertPairsResponseInner>>(
        *client_, list_all_convert_pairs_request(params));
}

common::RestRequest ConvertApi::order_status_request(const OrderStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/fapi/v1/convert/orderStatus";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "quoteId", params.quote_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<OrderStatusResponse>
ConvertApi::order_status(const OrderStatusParams& params) const {
    return common::send<OrderStatusResponse>(*client_, order_status_request(params));
}

common::RestRequest
ConvertApi::send_quote_request_request(const SendQuoteRequestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/fapi/v1/convert/getQuote";
    common::detail::json::set_param(req.query, "fromAsset", params.from_asset);
    common::detail::json::set_param(req.query, "toAsset", params.to_asset);
    common::detail::json::set_param(req.query, "fromAmount", params.from_amount);
    common::detail::json::set_param(req.query, "toAmount", params.to_amount);
    common::detail::json::set_param(req.query, "validTime", params.valid_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SendQuoteRequestResponse>
ConvertApi::send_quote_request(const SendQuoteRequestParams& params) const {
    return common::send<SendQuoteRequestResponse>(*client_, send_quote_request_request(params));
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
