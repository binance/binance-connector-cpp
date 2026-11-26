//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api/account_api.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_api {

AccountApi::AccountApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params AccountApi::account_information_payload(const AccountInformationParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<AccountInformationResponseResult>
AccountApi::account_information(const AccountInformationParams& params) const {
    return common::send<AccountInformationResponseResult>(*client_, "account.status",
                                                          account_information_payload(params),
                                                          make_options(false, true, false, false));
}

common::Params
AccountApi::account_information_v2_payload(const AccountInformationV2Params& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<AccountInformationV2ResponseResult>
AccountApi::account_information_v2(const AccountInformationV2Params& params) const {
    return common::send<AccountInformationV2ResponseResult>(
        *client_, "v2/account.status", account_information_v2_payload(params),
        make_options(false, true, false, false));
}

common::Params
AccountApi::futures_account_balance_payload(const FuturesAccountBalanceParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<FuturesAccountBalanceResponseResultInner>>
AccountApi::futures_account_balance(const FuturesAccountBalanceParams& params) const {
    return common::send<std::vector<FuturesAccountBalanceResponseResultInner>>(
        *client_, "account.balance", futures_account_balance_payload(params),
        make_options(false, true, false, false));
}

common::Params
AccountApi::futures_account_balance_v2_payload(const FuturesAccountBalanceV2Params& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "recvWindow", params.recv_window);
    return p;
}

common::WebsocketApiResponse<std::vector<FuturesAccountBalanceResponseResultInner>>
AccountApi::futures_account_balance_v2(const FuturesAccountBalanceV2Params& params) const {
    return common::send<std::vector<FuturesAccountBalanceResponseResultInner>>(
        *client_, "v2/account.balance", futures_account_balance_v2_payload(params),
        make_options(false, true, false, false));
}

} // namespace binance::derivatives_trading_usds_futures::websocket_api
