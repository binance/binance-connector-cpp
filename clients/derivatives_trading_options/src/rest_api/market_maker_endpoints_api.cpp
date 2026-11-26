//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/market_maker_endpoints_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

MarketMakerEndpointsApi::MarketMakerEndpointsApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketMakerEndpointsApi::auto_cancel_all_open_orders_request(
    const AutoCancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/countdownCancelAllHeartBeat";
    common::detail::json::set_param(req.query, "underlyings", params.underlyings);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
MarketMakerEndpointsApi::auto_cancel_all_open_orders(
    const AutoCancelAllOpenOrdersParams& params) const {
    return common::send<AutoCancelAllOpenOrdersResponse>(
        *client_, auto_cancel_all_open_orders_request(params));
}

common::RestRequest MarketMakerEndpointsApi::get_auto_cancel_all_open_orders_request(
    const GetAutoCancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/countdownCancelAll";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetAutoCancelAllOpenOrdersResponse>
MarketMakerEndpointsApi::get_auto_cancel_all_open_orders(
    const GetAutoCancelAllOpenOrdersParams& params) const {
    return common::send<GetAutoCancelAllOpenOrdersResponse>(
        *client_, get_auto_cancel_all_open_orders_request(params));
}

common::RestRequest MarketMakerEndpointsApi::set_auto_cancel_all_open_orders_request(
    const SetAutoCancelAllOpenOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/countdownCancelAll";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "countdownTime", params.countdown_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetAutoCancelAllOpenOrdersResponse>
MarketMakerEndpointsApi::set_auto_cancel_all_open_orders(
    const SetAutoCancelAllOpenOrdersParams& params) const {
    return common::send<SetAutoCancelAllOpenOrdersResponse>(
        *client_, set_auto_cancel_all_open_orders_request(params));
}

common::RestRequest MarketMakerEndpointsApi::get_market_maker_protection_config_request(
    const GetMarketMakerProtectionConfigParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/mmp";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetMarketMakerProtectionConfigResponse>
MarketMakerEndpointsApi::get_market_maker_protection_config(
    const GetMarketMakerProtectionConfigParams& params) const {
    return common::send<GetMarketMakerProtectionConfigResponse>(
        *client_, get_market_maker_protection_config_request(params));
}

common::RestRequest MarketMakerEndpointsApi::reset_market_maker_protection_config_request(
    const ResetMarketMakerProtectionConfigParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/mmpReset";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ResetMarketMakerProtectionConfigResponse>
MarketMakerEndpointsApi::reset_market_maker_protection_config(
    const ResetMarketMakerProtectionConfigParams& params) const {
    return common::send<ResetMarketMakerProtectionConfigResponse>(
        *client_, reset_market_maker_protection_config_request(params));
}

common::RestRequest MarketMakerEndpointsApi::set_market_maker_protection_config_request(
    const SetMarketMakerProtectionConfigParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/eapi/v1/mmpSet";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "windowTimeInMilliseconds",
                                    params.window_time_in_milliseconds);
    common::detail::json::set_param(req.query, "frozenTimeInMilliseconds",
                                    params.frozen_time_in_milliseconds);
    common::detail::json::set_param(req.query, "qtyLimit", params.qty_limit);
    common::detail::json::set_param(req.query, "deltaLimit", params.delta_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SetMarketMakerProtectionConfigResponse>
MarketMakerEndpointsApi::set_market_maker_protection_config(
    const SetMarketMakerProtectionConfigParams& params) const {
    return common::send<SetMarketMakerProtectionConfigResponse>(
        *client_, set_market_maker_protection_config_request(params));
}

} // namespace binance::derivatives_trading_options::rest_api
