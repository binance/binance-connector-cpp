//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include <binance/common/config.hpp>
#include <binance/common/rest.hpp>
#include <binance/copy_trading/export.hpp>
#include <binance/copy_trading/rest_api/future_copy_trading_api.hpp>
#include <binance/copy_trading/rest_api/models.hpp>

namespace binance::copy_trading::rest_api {

/// CopyTrading REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_COPY_TRADING_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Copy Trading REST API).
    [[nodiscard]] static RestApi production(common::RestApiConfig config);

    [[nodiscard]] const common::RestApiConfig& configuration() const noexcept;

    /// Calls an endpoint the SDK does not wrap yet. `T` may be `boost::json::value`.
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                 common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), false));
    }

    /// Like `send_request`, but signed (adds `timestamp` and `signature`).
    template <class T>
    [[nodiscard]] common::RestApiResponse<T>
    send_signed_request(std::string endpoint, common::HttpMethod method, common::Params query = {},
                        common::Params body = {}) const {
        return common::send<T>(*client_, make_request(std::move(endpoint), method, std::move(query),
                                                      std::move(body), true));
    }

    template <class T, class CompletionToken>
    auto async_send_request(std::string endpoint, common::HttpMethod method, common::Params query,
                            common::Params body, CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), false),
            std::forward<CompletionToken>(token));
    }

    template <class T, class CompletionToken>
    auto async_send_signed_request(std::string endpoint, common::HttpMethod method,
                                   common::Params query, common::Params body,
                                   CompletionToken&& token) const {
        return common::async_send<T>(
            client_,
            make_request(std::move(endpoint), method, std::move(query), std::move(body), true),
            std::forward<CompletionToken>(token));
    }

    // FutureCopyTradingApi

    /// Get Futures Lead Trader Status (TRADE)
    ///
    /// GET /sapi/v1/copyTrading/futures/userStatus.
    ///
    /// Get Futures Lead Trader Status
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-copy-trading/api/rest-api/future-copy-trading#get-futures-lead-trader-status
    [[nodiscard]] common::RestApiResponse<GetFuturesLeadTraderStatusResponse>
    get_futures_lead_trader_status(const GetFuturesLeadTraderStatusParams& params = {}) const {
        return future_copy_trading_api_.get_futures_lead_trader_status(params);
    }
    /// Asynchronous `get_futures_lead_trader_status()`.
    template <class CompletionToken>
    auto async_get_futures_lead_trader_status(const GetFuturesLeadTraderStatusParams& params,
                                              CompletionToken&& token) const {
        return future_copy_trading_api_.async_get_futures_lead_trader_status(
            params, std::forward<CompletionToken>(token));
    }

    /// Get Futures Lead Trading Symbol Whitelist (USER_DATA)
    ///
    /// GET /sapi/v1/copyTrading/futures/leadSymbol.
    ///
    /// Get Futures Lead Trading Symbol Whitelist
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-copy-trading/api/rest-api/future-copy-trading#get-futures-lead-trading-symbol-whitelist
    [[nodiscard]] common::RestApiResponse<GetFuturesLeadTradingSymbolWhitelistResponse>
    get_futures_lead_trading_symbol_whitelist(
        const GetFuturesLeadTradingSymbolWhitelistParams& params = {}) const {
        return future_copy_trading_api_.get_futures_lead_trading_symbol_whitelist(params);
    }
    /// Asynchronous `get_futures_lead_trading_symbol_whitelist()`.
    template <class CompletionToken>
    auto async_get_futures_lead_trading_symbol_whitelist(
        const GetFuturesLeadTradingSymbolWhitelistParams& params, CompletionToken&& token) const {
        return future_copy_trading_api_.async_get_futures_lead_trading_symbol_whitelist(
            params, std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::RestRequest make_request(std::string endpoint,
                                                          common::HttpMethod method,
                                                          common::Params query, common::Params body,
                                                          bool is_signed) {
        common::RestRequest req;
        req.method = method;
        req.endpoint = std::move(endpoint);
        req.query = std::move(query);
        req.body = std::move(body);
        req.is_signed = is_signed;
        return req;
    }

    std::shared_ptr<common::RestClient> client_;
    FutureCopyTradingApi future_copy_trading_api_;
};

} // namespace binance::copy_trading::rest_api
