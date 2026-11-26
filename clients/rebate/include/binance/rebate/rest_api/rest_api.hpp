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
#include <binance/rebate/export.hpp>
#include <binance/rebate/rest_api/api.hpp>
#include <binance/rebate/rest_api/models.hpp>

namespace binance::rebate::rest_api {

/// Rebate REST API client. Cheap to copy: copies share one `common::RestClient`
/// (connection pool and executor).
///
/// Every endpoint has a blocking form (`name(params)`) and an asynchronous form
/// (`async_name(params, token)`) that accepts any Asio completion token.
class BINANCE_REBATE_EXPORT RestApi {
public:
    /// Throws `common::ConfigError` if the configuration is invalid.
    explicit RestApi(common::RestApiConfig configuration);

    /// A client for `config.base_path`, production when it is not set.
    [[nodiscard]] static RestApi from_config(common::RestApiConfig config);
    /// A client for production (Rebate REST API).
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

    /// Get Spot Rebate History Records (USER_DATA)
    ///
    /// GET /sapi/v1/rebate/taxQuery.
    ///
    /// Get Spot Rebate History Records
    ///
    /// Weight(UID): 12000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - If `startTime` and `endTime` are not sent, the recent 7 days' data will be returned.
    /// - The earliest supported `startTime` is June 10, 2020.
    /// - Return up to 200 records per request.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-rebate/api/rest-api/~#get-spot-rebate-history-records
    [[nodiscard]] common::RestApiResponse<GetSpotRebateHistoryRecordsResponse>
    get_spot_rebate_history_records(const GetSpotRebateHistoryRecordsParams& params = {}) const {
        return api_.get_spot_rebate_history_records(params);
    }
    /// Asynchronous `get_spot_rebate_history_records()`.
    template <class CompletionToken>
    auto async_get_spot_rebate_history_records(const GetSpotRebateHistoryRecordsParams& params,
                                               CompletionToken&& token) const {
        return api_.async_get_spot_rebate_history_records(params,
                                                          std::forward<CompletionToken>(token));
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

} // namespace binance::rebate::rest_api
