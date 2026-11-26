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
#include <binance/pay/export.hpp>
#include <binance/pay/rest_api/api.hpp>
#include <binance/pay/rest_api/models.hpp>

namespace binance::pay::rest_api {

/// Pay REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_PAY_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Pay REST API).
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

    // Api

    /// Get Pay Trade History
    ///
    /// GET /sapi/v1/pay/transactions.
    ///
    /// Get Pay Trade History
    ///
    /// Weight(UID): 3000
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90 days' data will be returned.
    /// - The max interval between `startTime` and `endTime` is 90 days.
    /// - Support for querying orders within the last 18 months.
    /// - `payerInfo` and `receiverInfo` return different fields in different `orderType` values:
    ///   - C2C sender: `payerInfo=binanceId`; `receiverInfo=name,
    ///   binanceId/accountId/email/countryCode/phoneNumber/mobileCode` (based on user input).
    ///   - C2C receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - CRYPTO_BOX sender: `payerInfo=binanceId`; `receiverInfo=name` (always `"Crypto Box"`).
    ///   - CRYPTO_BOX receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - PAY sender: `payerInfo=binanceId`; `receiverInfo=name`.
    ///   - PAY receiver: `payerInfo=name`; `receiverInfo=binanceId, name`.
    ///   - PAY_REFUND sender: `payerInfo=binanceId, name`; `receiverInfo=name, accountId`.
    ///   - PAY_REFUND receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - PAYOUT sender: `payerInfo=binanceId, name`; `receiverInfo=name, accountId`.
    ///   - PAYOUT receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - CRYPTO_BOX_RF receiver: `payerInfo=name` (always `"Crypto Box"`);
    ///   `receiverInfo=binanceId`.
    ///   - REMITTANCE sender: `payerInfo=binanceId`; `receiverInfo=name, institutionName,
    ///   cardNumber, digitalWalletId`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-pay/api/rest-api/~#get-pay-trade-history
    [[nodiscard]] common::RestApiResponse<GetPayTradeHistoryResponse>
    get_pay_trade_history(const GetPayTradeHistoryParams& params = {}) const {
        return api_.get_pay_trade_history(params);
    }
    /// Asynchronous `get_pay_trade_history()`.
    template <class CompletionToken>
    auto async_get_pay_trade_history(const GetPayTradeHistoryParams& params,
                                     CompletionToken&& token) const {
        return api_.async_get_pay_trade_history(params, std::forward<CompletionToken>(token));
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
    Api api_;
};

} // namespace binance::pay::rest_api
