//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/position_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

PositionApi::PositionApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
PositionApi::get_position_by_token_request(const GetPositionByTokenParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/position/token";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetPositionByTokenResponse>
PositionApi::get_position_by_token(const GetPositionByTokenParams& params) const {
    return common::send<GetPositionByTokenResponse>(*client_,
                                                    get_position_by_token_request(params));
}

common::RestRequest PositionApi::query_pnl_request(const QueryPnLParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/pnl/query";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    common::detail::json::set_param(req.query, "marketTopicId", params.market_topic_id);
    common::detail::json::set_param(req.query, "activeOnly", params.active_only);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPnLResponse>
PositionApi::query_pnl(const QueryPnLParams& params) const {
    return common::send<QueryPnLResponse>(*client_, query_pnl_request(params));
}

common::RestRequest PositionApi::query_positions_request(const QueryPositionsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/position/list";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "tab", params.tab);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPositionsResponse>
PositionApi::query_positions(const QueryPositionsParams& params) const {
    return common::send<QueryPositionsResponse>(*client_, query_positions_request(params));
}

common::RestRequest
PositionApi::query_positions_by_filter_request(const QueryPositionsByFilterParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/position/filter";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "marketTopicId", params.market_topic_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryPositionsByFilterResponse>
PositionApi::query_positions_by_filter(const QueryPositionsByFilterParams& params) const {
    return common::send<QueryPositionsByFilterResponse>(*client_,
                                                        query_positions_by_filter_request(params));
}

common::RestRequest PositionApi::query_settled_position_history_request(
    const QuerySettledPositionHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/position/settled-history";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "l1Category", params.l1_category);
    common::detail::json::set_param(req.query, "result", params.result);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySettledPositionHistoryResponse>
PositionApi::query_settled_position_history(const QuerySettledPositionHistoryParams& params) const {
    return common::send<QuerySettledPositionHistoryResponse>(
        *client_, query_settled_position_history_request(params));
}

} // namespace binance::w3w_prediction::rest_api
