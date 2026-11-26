//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/copy_trading/rest_api/future_copy_trading_api.hpp>

namespace binance::copy_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

FutureCopyTradingApi::FutureCopyTradingApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest FutureCopyTradingApi::get_futures_lead_trader_status_request(
    const GetFuturesLeadTraderStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/copyTrading/futures/userStatus";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesLeadTraderStatusResponse>
FutureCopyTradingApi::get_futures_lead_trader_status(
    const GetFuturesLeadTraderStatusParams& params) const {
    return common::send<GetFuturesLeadTraderStatusResponse>(
        *client_, get_futures_lead_trader_status_request(params));
}

common::RestRequest FutureCopyTradingApi::get_futures_lead_trading_symbol_whitelist_request(
    const GetFuturesLeadTradingSymbolWhitelistParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/copyTrading/futures/leadSymbol";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetFuturesLeadTradingSymbolWhitelistResponse>
FutureCopyTradingApi::get_futures_lead_trading_symbol_whitelist(
    const GetFuturesLeadTradingSymbolWhitelistParams& params) const {
    return common::send<GetFuturesLeadTradingSymbolWhitelistResponse>(
        *client_, get_futures_lead_trading_symbol_whitelist_request(params));
}

} // namespace binance::copy_trading::rest_api
