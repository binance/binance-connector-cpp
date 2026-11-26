//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/create_renew_listen_key_response.hpp>

namespace binance::stocks::rest_api {

struct CreateRenewListenKeyParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCKS_EXPORT UserDataStreamsApi {
public:
    explicit UserDataStreamsApi(std::shared_ptr<common::RestClient> client);

    /// Create / Renew Listen Key (USER_STREAM)
    ///
    /// POST /sapi/v1/equity/listenKey.
    ///
    /// Create a new stock user-data-stream `listenKey`, or renew an existing one. Calling this
    /// endpoint for the same user with an active `listenKey` extends its validity; if there is no
    /// active key, a new one is issued. Use the returned `listenKey` to subscribe to the stock user
    /// data stream.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/user-data-streams#create-renew-listen-key
    [[nodiscard]] common::RestApiResponse<CreateRenewListenKeyResponse>
    create_renew_listen_key(const CreateRenewListenKeyParams& params = {}) const;

    /// Asynchronous `create_renew_listen_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateRenewListenKeyResponse>)`.
    template <class CompletionToken>
    auto async_create_renew_listen_key(const CreateRenewListenKeyParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<CreateRenewListenKeyResponse>(
            client_, create_renew_listen_key_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_renew_listen_key_request(const CreateRenewListenKeyParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stocks::rest_api
